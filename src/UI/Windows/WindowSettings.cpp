#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "magic_enum/magic_enum.hpp"

#include "WindowSettings.hpp"

//categories
#include "src/UI/Categories/Gameplay.hpp"
#include "src/UI/Categories/Info.hpp"
#include "src/UI/Categories/Interface.hpp"
#include "src/UI/Categories/Audio.hpp"
#include "src/UI/Categories/AI.hpp"
#include "src/UI/Categories/Advanced.hpp"
#include "src/UI/Categories/Audio.hpp"
#include "src/UI/Categories/Camera.hpp"
#include "src/UI/Categories/Keybinds.hpp"
#include "src/UI/Categories/General.hpp"
#include "src/UI/Categories/Balance.hpp"

#include "src/UI/ImGui/ImUtil.hpp"

volatile double rendertime;
volatile double renderloop;
volatile double maxtime;
using namespace UI;


//Not the most elegant solution but it does work...
void WindowSettings::AsyncLoad(){

    if(!Settings.LoadSettings()){
        ErrorString = "Could Not Load Settings! Check GTSPlugin.log for more info";
    }
    else{
        ErrorString = "";
    }

    StyleMgr.LoadStyle();
    FontMgr.RebuildFonts();
    SaveLoadBusy.store(false);
}

void WindowSettings::AsyncSave(){
    if(!Settings.SaveSettings()){
        ErrorString = "Could Not Save Settings! Check GTSPlugin.log for more info";
    }
    else{
        ErrorString = "";
    }

    SaveLoadBusy.store(false);
}


//Do All your Init Stuff here
//Note: Dont do any calls to the imgui api here as the window is not yet created
WindowSettings::WindowSettings() {

    Title = "Configuration";
    Name = "Settings";
    Show = true;
    flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoNavInputs;

    //Add Categories
    CatMgr.AddCategory(std::make_shared<CategoryInfo>());
    CatMgr.AddCategory(std::make_shared<CategoryGeneral>());
    CatMgr.AddCategory(std::make_shared<CategoryGameplay>());
    CatMgr.AddCategory(std::make_shared<CategoryBalance>());
    CatMgr.AddCategory(std::make_shared<CategoryAudio>());
    CatMgr.AddCategory(std::make_shared<CategoryAI>());
    CatMgr.AddCategory(std::make_shared<CategoryCamera>());
    CatMgr.AddCategory(std::make_shared<CategoryInterface>());
    CatMgr.AddCategory(std::make_shared<CategoryKeybinds>());
    CatMgr.AddCategory(std::make_shared<CategoryAdvanced>());
}

void WindowSettings::Draw() {

    auto& Categories = CatMgr.GetCategories();
    const float Footer = ImGui::GetFrameHeightWithSpacing() + (ImGui::GetStyle().ItemSpacing.y * 4);  // text + separator
    
    //Calc Button Width
    std::array<const char*,3> Lables = { "Load", "Save", "Reset" };
    const ImGuiStyle& Style = ImGui::GetStyle();

    float TotalWidth = Style.ItemSpacing.x; // Add Seperator offset
    for (auto& Str : Lables){
        TotalWidth += (ImGui::CalcTextSize(Str).x + 2.0f * Style.FramePadding.x) + Style.ItemSpacing.x;
    }

    const float ButtonStartX = ImGui::GetWindowWidth() - TotalWidth - Style.WindowPadding.x;
    
    //While mathematically correct 2.0 Just doesn't look right...
    const float TextCenter = ButtonStartX / 2.0f - ImGui::CalcTextSize(ErrorString.c_str()).x / 2.5f;

    //Update Window Flags
    flags = (sUI.bLock ? (flags | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove) : (flags & ~ImGuiWindowFlags_NoResize & ~ImGuiWindowFlags_NoMove));

    //Handle Fixed Position and Size
    if(sUI.bLock){
        ImGui::SetWindowSize(ImUtil::ScaleToViewport(sUI.fWindowSize));

        //Mousedown Check Prevents the window from moving around and messing with the slider while dragging
        if(!ImGui::GetIO().MouseDown[0]){
            //X,Y
            const ImVec2 Offset {sUI.f2Offset[0], sUI.f2Offset[1]};
            ImGui::SetWindowPos(GetAnchorPos(Config::StringToEnum<ImWindow::WindowAnchor>(sUI.sAnchor), Offset));
        }
    }
    
    {  // Draw Title

        ImGui::PushFont(FontMgr.GetFont("title"));
        ImGui::Text(Title.c_str());
        ImGui::PopFont();
    }

    {  // Debug Draw Window Manager total time

        ImGui::PushFont(FontMgr.GetFont("subscript"));
        ImGui::Text("Window Manager: %.3f ms",rendertime);
        ImGui::SameLine();
        ImGui::Text("%.3fms",maxtime);
        ImGui::Text("Render Loop: %.3f ms",renderloop);
        ImGui::PopFont();
    }

    ImUtil::SeperatorH();

    {  // Draw Sidebar

        ImGui::BeginChild("Sidebar", ImVec2(CatMgr.GetLongestCategory(), -Footer), true);
        ImGui::PushFont(FontMgr.GetFont("sidebar"));

        // Display the categories in the sidebar
        for (uint8_t i = 0; i < Categories.size(); i++) {
            ImCategory* category = Categories[i].get();

            //If nullptr / invisible / or dbg category, Do not draw.

            if(!category) continue;
            if(!sHidden.IKnowWhatImDoing && category->GetTitle() == "Advanced") continue;
            if(!category->IsVisible()) continue;

            if (ImGui::Selectable(category->GetTitle().c_str(), CatMgr.activeIndex == i)) {
                CatMgr.activeIndex = i;
            }

        }

        ImGui::PopFont();
        ImGui::EndChild();
    }

    ImUtil::SeperatorV();

    { // Content Area, Where the category contents are drawn

        ImGui::BeginChild("Content", ImVec2(0, -Footer), true); // Remaining width

        // Validate selectedCategory to ensure it's within bounds
        if (CatMgr.activeIndex >= 0 && CatMgr.activeIndex < Categories.size()) {
            ImCategory* selected = Categories[CatMgr.activeIndex].get();
            selected->Draw(); // Call the Draw method of the selected category
        } 
        else {
            ImGui::TextColored(ImUtil::ColorError,"Invalid category or no categories exist!");
        }

        ImGui::EndChild();
    }

    ImUtil::SeperatorH();
    
    {   //Footer - Mod Info

        ImGui::PushFont(FontMgr.GetFont("subscript"));
        //TODO Grab the version string from the project
        ImGui::TextColored(ImUtil::ColorSubscript,"GTSPlugin v2.0.0\nBuild Date: %s %s\nGit SHA1: %s", __DATE__, __TIME__,(git::AnyUncommittedChanges() ? "Custom" : git::CommitSHA1().c_str()));
        ImGui::PopFont();
    }

    ImGui::SameLine(TextCenter);

    {   
        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - (Footer / 2.0f) - Style.FramePadding.y);
        ImGui::PushFont(FontMgr.GetFont("errortext"));
        ImGui::PushStyleColor(ImGuiCol_Text,ImUtil::ColorError);
        ImGui::Text(ErrorString.c_str());
        ImGui::PopStyleColor();
        ImGui::PopFont();
    }

    ImGui::SameLine(ButtonStartX);
    
    {   //-------------  Buttons
        
        volatile bool buttonstate = SaveLoadBusy.load();

        //Load
        if(ImUtil::Button(Lables[0], "Reload and apply the values currenly stored in Settings.toml", buttonstate, 1.3f)){
            SaveLoadBusy.store(true);
            std::thread(&WindowSettings::AsyncLoad, this).detach();
        }

        ImGui::SameLine();

        //Save
        if(ImUtil::Button(Lables[1], "Save changes to Settings.toml", buttonstate, 1.3f)){
            SaveLoadBusy.store(true);
            std::thread(&WindowSettings::AsyncSave, this).detach();
        }

        ImUtil::SeperatorV();
        
        //Reset
        if(ImUtil::Button(Lables[2], "Load the default values.\nThis does not delete any previous saved changes unless you explicitly overwrite them by saving.", buttonstate, 1.3f)){
            Settings.ResetToDefaults();
            StyleMgr.LoadStyle();
            FontMgr.RebuildFonts();
        }
    }
}
