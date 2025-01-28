#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "magic_enum/magic_enum.hpp"

#include "WindowConfig.hpp"

//categories
#include "src/UI/Categories/Gameplay.hpp"
#include "src/UI/Categories/Info.hpp"
#include "src/UI/Categories/Interface.hpp"
#include "src/UI/Categories/Audio.hpp"
#include "src/UI/Categories/AI.hpp"
#include "src/UI/Categories/Advanced.hpp"
#include "src/UI/Categories/Audio.hpp"
#include "src/UI/Categories/Camera.hpp"


#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

//Do All your Init Stuff here
//Note: Dont do any calls to the imgui api here as the window is not yet created
WindowConfig::WindowConfig() {

    Title = "Configuration";
    Name = "ConfigWindow";
    Show = true;
    flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;

    //Add Categories
    CatMgr.AddCategory(std::make_shared<CategoryInfo>());
    CatMgr.AddCategory(std::make_shared<CategoryGameplay>());
    CatMgr.AddCategory(std::make_shared<CategoryAudio>());
    CatMgr.AddCategory(std::make_shared<CategoryAI>());
    CatMgr.AddCategory(std::make_shared<CategoryCamera>());
    CatMgr.AddCategory(std::make_shared<CategoryInterface>());
    CatMgr.AddCategory(std::make_shared<CategoryAdvanced>());
}



void WindowConfig::Draw() {

    this->flags = (Settings.UI.wStatus.bLock ? (this->flags | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove) : (this->flags & ~ImGuiWindowFlags_NoResize & ~ImGuiWindowFlags_NoMove));

    //Handle Fixed Position and Size
    if(Settings.UI.wStatus.bLock){
        ImGui::SetWindowSize(ImUtil::ScaleToViewport(Settings.UI.wSettings.fWindowScale));

        //Mousedown Check Prevents the window from moving around and messing with the slider while dragging
        if(!std::any_of(ImGui::GetIO().MouseDown, ImGui::GetIO().MouseDown + IM_ARRAYSIZE(ImGui::GetIO().MouseDown), [](bool v) { return v; })){
            //X,Y
            const ImVec2 Offset {Settings.UI.wStatus.f2Offset[0], Settings.UI.wStatus.f2Offset[1]};
            ImGui::SetWindowPos(GetAnchorPos(AnchorPos, Offset));
        }
    }
    

    {  // Draw Title

        ImGui::PushFont(FontMgr.GetFont("title"));
        ImGui::Text(Title.c_str());
        ImGui::PopFont();

    }

    ImUtil::SeperatorH();
    auto& categories = CatMgr.GetCategories();

    const float footer_height = ImGui::GetFrameHeightWithSpacing() + (ImGui::GetStyle().ItemSpacing.y * 3 + 30.0f) + ((StyleMgr.GetScale() * 8) - 8);  // text + separator

    {  // Draw Sidebar

        ImGui::BeginChild((Name + "##Sidebar").c_str(), ImVec2(CatMgr.GetLongestCategory(), -footer_height), true);
        ImGui::PushFont(FontMgr.GetFont("sidebar"));

        
        // Display the categories in the sidebar
        for (uint8_t i = 0; i < categories.size(); i++) {
            ImCategory* category = categories[i].get();
            if(!category->IsVisible()) continue;
            if (ImGui::Selectable(category->GetTitle().c_str(), CatMgr.activeIndex == i)) {
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip(category->GetDescription().c_str());
                }
                CatMgr.activeIndex = i;
            }

        }

        ImGui::PopFont();
        ImGui::EndChild();

    }

    ImUtil::SeperatorV();

    { // Content Area, Where categories are drawn

        ImGui::BeginChild((Name + "##Content").c_str(), ImVec2(0, -footer_height), true); // Remaining width

        // Validate selectedCategory to ensure it's within bounds
        if (CatMgr.activeIndex >= 0 && CatMgr.activeIndex < categories.size()) {
            ImCategory* selected = categories[CatMgr.activeIndex].get();
            selected->Draw(); // Call the Draw method of the selected category
        } 
        else {
            ImGui::TextColored(ImUtil::ColorError,"Invalid category or no categories exist!");
        }

        ImGui::EndChild();
    }

    ImUtil::SeperatorH();

    {   //Footer - Mod Info
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(ImGui::GetStyle().WindowPadding.x, 0.0f));
        ImGui::BeginChild((Name + "##Info").c_str(),ImVec2((ImGui::GetWindowWidth() * 0.3f) ,0.f), true);
        ImGui::PopStyleVar(); // Restore style after setting up the child window
        ImGui::PushFont(FontMgr.GetFont("subscript"));

        //TODO Grab the version string from the project
        ImGui::TextColored(ImUtil::ColorSubscript,"GTSPlugin v2.0.0");
        ImGui::TextColored(ImUtil::ColorSubscript,"Build Date: %s %s", __DATE__, __TIME__);
        ImGui::TextColored(ImUtil::ColorSubscript,"Git SHA1: %s", (git::AnyUncommittedChanges() ? "Custom" : git::CommitSHA1().c_str()));

        ImGui::PopFont();
        ImGui::EndChild();


    }

    ImGui::SameLine();
   
    {   // Footer - Buttons and Messages

        ImGui::BeginChild((Name + "##Footer").c_str(),ImVec2(0,0), true);

        ImGui::PushFont(FontMgr.GetFont("footer"));

        // Align buttons to the right
        float button_width = (18.f * StyleMgr.GetScale() * 3) + ImGui::GetStyle().FramePadding.x * 2.0f;
        float spacing = ImGui::GetStyle().ItemSpacing.x;
        float total_width = button_width * 3 + spacing;

        ImGui::SetCursorPosX(ImGui::GetWindowWidth() - total_width);

        if(ImUtil::Button("Load", "(Re)Load the values stored in Settings.toml")){

            if(!Settings.LoadSettings()){
                //TODO Use Gts' task class to make a 10 second single fire task that displays an error message in the footer
                //logger::error("Failed to settings category: {}");
            }
        }

        ImGui::SameLine();
        
        if(ImUtil::Button("Save", "Save changes to Settings.toml")){
            if(!Settings.SaveSettings()){
                //TODO Use Gts' task class to make a 10 second single fire task that displays an error message in the footer
                //logger::error("Failed to save settings: {}");
            }
        }

        ImUtil::SeperatorV();
        
        if(ImUtil::Button("Reset", "Load the default values, this does not save them to the config file")){
            Settings.ResetToDefaults();
            //logger::info("Settings reset");
                //TODO Use Gts' task class to make a 10 second single fire task that displays an error message in the footer
        };

        ImGui::PopFont();
        ImGui::EndChild();
    }

}

void WindowConfig::ShowFooterMessage(){
    
}


