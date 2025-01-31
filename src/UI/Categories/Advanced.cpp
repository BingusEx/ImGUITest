#include "Advanced.hpp"
#include "imgui.h"

#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

void CategoryAdvanced::Draw(){
    {   //Info About the Config Window
        ImGui::SeparatorText("Runtime Info");
        ImGui::BulletText("Viewport Size: (%.2f,%.2f)", ImGui::GetMainViewport()->Size.x, ImGui::GetMainViewport()->Size.y);
        ImGui::BulletText("Viewport Pos: (%.2f,%.2f)", ImGui::GetMainViewport()->Pos.x, ImGui::GetMainViewport()->Pos.y);
        ImGui::BulletText("Config Window Size: (%.2f,%.2f)", ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
        ImGui::BulletText("Config Window Pos: (%.2f,%.2f)", ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);

    }

    if(ImUtil::Button("Close Program", "Close the program", false, 1.0f)){
        //Call Win32 API to close the program
        PostQuitMessage(0);
    }
}