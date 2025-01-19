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


    //Add Categories
    CatMgr.AddCategory(std::make_shared<CategoryGeneral>());
    CatMgr.AddCategory(std::make_shared<CategoryGameplay>());
    CatMgr.AddCategory(std::make_shared<CategoryInterface>());
    CatMgr.AddCategory(std::make_shared<CategoryWidget>());
    CatMgr.AddCategory(std::make_shared<CategoryInfo>());

}
float padding = 0.1f;
int pos = 0;
//

inline void Footer(){

    {   //Footer

        ImGui::BeginChild("Info",ImVec2(150,0),true);

        ImGui::PushFont(FontMgr.GetFont("subscript"));
        ImGui::TextColored(ImUtil::ColorSubscript,"GTSPlugin v2.0.0");
        ImGui::TextColored(ImUtil::ColorSubscript,"Build 22/01/25");
        ImGui::PopFont();

        ImGui::EndChild();

    }

    ImGui::SameLine();
   
    {   // Footer Buttons [Right Aligned]

        ImGui::BeginChild("Footer",ImVec2(0,0),true);
        ImGui::PushFont(FontMgr.GetFont("footer"));
        ImUtil::ButtonSimple("Load");

        ImGui::SameLine();
        
        ImUtil::ButtonSimple("Save");

        ImGui::PopFont();
        //ImGui::PopStyleVar();
        ImGui::EndChild();
    }

}

void WConfig::Draw() {

    {  // Title

        ImGui::PushFont(FontMgr.GetFont("title"));
        ImGui::Text(Title.c_str());
        ImGui::PopFont();

    }

    ImUtil::SeperatorH();
    auto& categories = CatMgr.GetCategories();
    float footer_height = ImGui::GetFrameHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y * 3 + 26.0f;  // text + separator

    {  // Sidebar

        ImGui::BeginChild("Sidebar", ImVec2(CatMgr.GetLongestCategory(), -footer_height), true);
        ImGui::PushFont(FontMgr.GetFont("sidebar"));

        
        // Display the categories in the sidebar
        for (uint8_t i = 0; i < categories.size(); i++) {
            ImCategory* category = categories[i].get();
            if (ImGui::Selectable(category->GetTitle().c_str(), CatMgr.activeIndex == i)) {
                CatMgr.activeIndex = i;
            }
        }

        ImGui::PopFont();
        ImGui::EndChild();

    }

    ImUtil::SeperatorV();

    { // Content Area

        ImGui::BeginChild("Content", ImVec2(0, -footer_height), true); // Remaining width

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

    Footer();

}


