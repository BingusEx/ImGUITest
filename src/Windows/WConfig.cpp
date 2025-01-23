#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <string>
#include <format>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <functional> // For std::function
#include <unordered_map>
#include <algorithm>
#include "magic_enum/magic_enum.hpp"

#include "WConfig.hpp"

//Helper libs
#include "src/ImCategory.hpp"
#include "src/ImUtil.hpp"
#include "src/ImFont.hpp"
#include "src/ImStyle.hpp"

//categories
#include "src/Categories/Gameplay.hpp"
#include "src/Categories/Info.hpp"
#include "src/Categories/General.hpp"
#include "src/Categories/Widget.hpp"
#include "src/Categories/Interface.hpp"

#include "git.h"

auto& CatMgr = ImCategoryManager::GetSingleton();
auto& FontMgr = ImFontManager::GetSingleton();
auto& StyleMgr = ImStyleManager::GetSingleton();

using namespace GTSUi;

//Do All your Init Stuff here
//Note: Dont do any calls to the imgui api here as the window is not yet created
WConfig::WConfig() {

    Title = "Configuration";
    Name = "ConfigWindow";
    Show = true;
    flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
    //flags = true;

    //Add Categories
    CatMgr.AddCategory(std::make_shared<CategoryGeneral>());
    CatMgr.AddCategory(std::make_shared<CategoryGameplay>());
    CatMgr.AddCategory(std::make_shared<CategoryInterface>());
    CatMgr.AddCategory(std::make_shared<CategoryWidget>());
    CatMgr.AddCategory(std::make_shared<CategoryInfo>());

}

void WConfig::Draw() {

    //Handle Fixed Position and Size
    if(Fixed){
        ImGui::SetWindowSize(ImUtil::ScaleToViewport(FixedScale));

        //Mousedown Check Prevents the window from moving around and messing with the slider while dragging
        if(!std::any_of(ImGui::GetIO().MouseDown, ImGui::GetIO().MouseDown + IM_ARRAYSIZE(ImGui::GetIO().MouseDown), [](bool v) { return v; })){
            ImGui::SetWindowPos(GetAnchorPos(AnchorPos, CornerPadding));
        }
    }
    

    {  // Title

        ImGui::PushFont(FontMgr.GetFont("title"));
        ImGui::Text(Title.c_str());
        ImGui::PopFont();

    }

    ImUtil::SeperatorH();
    auto& categories = CatMgr.GetCategories();
    const float footer_height = ImGui::GetFrameHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y * 3 + 30.0f;  // text + separator

    {  // Sidebar

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

    { // Content Area

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

    ImGui::Spacing();

    ImUtil::SeperatorH();

    {   //Footer
        ImGui::BeginChild((Name + "##Info").c_str(),ImVec2((ImGui::GetWindowWidth() * 0.3) * StyleMgr.GetScale() ,0), true);

        ImGui::PushFont(FontMgr.GetFont("subscript"));

        ImGui::TextColored(ImUtil::ColorSubscript,"GTSPlugin v2.0.0");
        ImGui::TextColored(ImUtil::ColorSubscript,"Build Date: %s %s", __DATE__, __TIME__);
        ImGui::TextColored(ImUtil::ColorSubscript,"Git SHA1: %s", git::AnyUncommittedChanges() ? "Custom" : git::CommitSHA1().c_str());

        ImGui::PopFont();
        ImGui::EndChild();

    }

    ImGui::SameLine();
   
    {   // Footer Buttons [Right Aligned]

        ImGui::BeginChild((Name + "##Footer").c_str(),ImVec2(0,0),true);

        ImGui::PushFont(FontMgr.GetFont("footer"));

        // Align buttons to the right
        //TODO Fix this AAAAAAAAAAA
        float button_width = ImGui::CalcTextSize("AAAAA").x + ImGui::GetStyle().FramePadding.x * 2.0f;
        float spacing = ImGui::GetStyle().ItemSpacing.x;
        float total_width = button_width * 3 + spacing;

        ImGui::SetCursorPosX(ImGui::GetWindowWidth() - total_width);

        if(ImUtil::Button("Load", "(Re)Load the values stored in GtsPlugin.toml")){
            for(auto& category : categories){
                if(!category->Load()){
                    //logger::error("Failed to load category: {}", category->GetTitle());
                }
            }
        }

        ImGui::SameLine();
        
        if(ImUtil::Button("Save", "Save changes to GtsPlugin.toml")){
            for(auto& category : categories){
                if(!category->Save()){
                    //logger::error("Failed to save category: {}", category->GetTitle());
                }
            }
        }

        ImGui::SameLine();

        ImUtil::SeperatorV();
        
        ImUtil::Button("Reset", "Load the default values, this does not save them to the config file");

        ImGui::SameLine();

        ImGui::PopFont();
        ImGui::EndChild();
    }

}


