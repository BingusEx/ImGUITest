
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

//Helper libs
#include "ImCategory.hpp"
#include "ImUtil.hpp"
#include "ImFont.hpp"
#include "ImStyle.hpp"

//categories
#include "Categories/Gameplay.hpp"
#include "Categories/Info.hpp"
#include "Categories/General.hpp"

#include "MainWindow.hpp"

//namespace {
//Singleton
auto& CatMgr = ImCategoryManager::GetSingleton();
auto& FontMgr = ImFontManager::GetSingleton();
auto& StyleMgr = ImStyleManager::GetSingleton();

std::once_flag _CategoryInitFlag;

using namespace GTSUi;

void Setup(ImGuiIO& io){
    StyleMgr.SetupStyle();
    FontMgr.Init(io);
    CatMgr.AddCategory(std::make_shared<CategoryGeneral>());
    CatMgr.AddCategory(std::make_shared<CategoryInfo>());
    CatMgr.AddCategory(std::make_shared<CategoryGameplay>());
}

inline void Footer(){

    {   //Footer

        ImGui::BeginChild("Info",ImVec2(150,0),true);
        FontMgr.Subscript();
        ImGui::TextColored(ImUtil::ColorSubscript,"GTSPlugin v2.0.0");
        ImGui::TextColored(ImUtil::ColorSubscript,"Build 22/01/25");
        FontMgr.Pop();
        ImGui::EndChild();

    }

    ImGui::SameLine();
   
    {   // Footer Buttons [Right Aligned]

        ImGui::BeginChild("Footer",ImVec2(0,0),true);
        FontMgr.Footer();
        ImUtil::ButtonSimple("Load");

        ImGui::SameLine();
        
        ImUtil::ButtonSimple("Save");

        FontMgr.Pop();
        //ImGui::PopStyleVar();
        ImGui::EndChild();
    }

}

void ShowSplitWindowWithChildWindows() {

    FontMgr.Text();

    bool open = true;
    constexpr ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar;
    ImGui::Begin("Main Window", &open, flags);
    float footer_height = ImGui::GetFrameHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y * 3 + 26.0f;  // text + separator

    auto& categories = CatMgr.GetCategories();
    static size_t selectedCategory = 0;


    {   // Title

        FontMgr.Title();
        ImGui::Text("Size Matters Configuration");
        FontMgr.Pop();

    }

    ImUtil::SeperatorH();

    {  // Sidebar

        //Initialize the sidebar width
        static float sidebarWidth = 100.0f;
        //Cant call it once if we plan to allow ui scaling :(
       // std::call_once(_CategoryInitFlag, [](){
            auto length = ImCategoryManager::GetSingleton().GetLongestCategory();
            if(length > 0.0f){
                sidebarWidth = length;
            }
       // });
        
        ImGui::BeginChild("Sidebar", ImVec2(sidebarWidth, -footer_height), true);
        FontMgr.Sidebar();
        
        // Display the categories in the sidebar
        for (size_t i = 0; i < categories.size(); i++) {
            ImCategory* category = categories[i].get();
            if (ImGui::Selectable(category->GetTitle().c_str(), selectedCategory == i)) {
                selectedCategory = i;
            }
        }

        FontMgr.Pop();
        ImGui::EndChild();

    }

    ImUtil::SeperatorV();

    { // Content Area

        ImGui::BeginChild("Content", ImVec2(0, -footer_height), true); // Remaining width

        // Validate selectedCategory to ensure it's within bounds
        if (selectedCategory >= 0 && selectedCategory < categories.size()) {
            ImCategory* selected = categories[selectedCategory].get();
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

    FontMgr.Pop();
    ImGui::End();
}
