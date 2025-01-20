#include "Interface.hpp"
#include "src/ImCategory.hpp"
#include "src/ImUtil.hpp"
#include "src/ImFont.hpp"
#include "src/ImStyle.hpp"
#include "src/ImWindow.hpp"
#include <windows.h>

using namespace GTSUi;



void CategoryInterface::DrawLeft(){

    ImWindowManager& WinMgr = ImWindowManager::GetSingleton();

    {   //Global UI Settings
        auto& StyleMgr = ImStyleManager::GetSingleton();
        static float _gScale = StyleMgr.GetScale();
        ImGui::SeparatorText("Global UI Settings");

        ImUtil::SliderF("Font Scale", &_gScale, 0.5f, 2.0, "Change the scale of every element and font");

        if (ImGui::IsItemDeactivatedAfterEdit()) {
            StyleMgr.SetScale(_gScale);
        }

    }

    {   ///Options For Configuring the Config Window Size/Pos

        ImGui::SeparatorText("Configuration Window");

        if(auto configwindow = WinMgr.GetWindowByName("ConfigWindow")){

            ImUtil::CheckBox("Lock Window", &configwindow->Fixed, "Lock the position and size of this window. You can can change the position and size below.");
            
            ImGui::BeginDisabled(!configwindow->Fixed);
            {
                ImUtil::SliderF("Window Scale", &configwindow->FixedScale, 50.0f, 95.0f, "Change the size of this window");
                ImGui::Combo("Anchor", (int*)&configwindow->AnchorPos, "Top Left\0Top Right\0Center\0Bottom Left\0Bottom Right\0");
                ImGui::BeginDisabled(configwindow->AnchorPos == ImWindow::WindowAnchor::kCenter);
                {
                    ImUtil::SliderF("Offset (Left/Right)", &configwindow->CornerPadding.x, 0.0f, 50.0f, "Offset the window to the left or right depending on which anchor position you choose");
                    ImUtil::SliderF("Offset (Up/Down)", &configwindow->CornerPadding.y, 0.0f, 50.0f, "Offset the window up or down depending on which anchor position you choose");
                }
                ImGui::EndDisabled();
            }
            ImGui::EndDisabled();
        }
        else{
            ImGui::TextColored(ImUtil::ColorError,"Can't find the reference to the config window!");
        }
    }   

    if(ImUtil::Button("Close Program", "Close the program", false, 1.0f)){
        //Call Win32 API to close the program
        PostQuitMessage(0);
    }
}







void CategoryInterface::DrawRight(){

    {   //Info About the Config Window
        ImGui::SeparatorText("Runtime Info");
        ImGui::BulletText("Viewport Size: (%.2f,%.2f)", ImGui::GetMainViewport()->Size.x, ImGui::GetMainViewport()->Size.y);
        ImGui::BulletText("Viewport Pos: (%.2f,%.2f)", ImGui::GetMainViewport()->Pos.x, ImGui::GetMainViewport()->Pos.y);
        ImGui::BulletText("Config Window Size: (%.2f,%.2f)", ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
        ImGui::BulletText("Config Window Pos: (%.2f,%.2f)", ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);

    }

}


bool CategoryInterface::Load(){
    return true;
}

bool CategoryInterface::Save(){
    return true;
}