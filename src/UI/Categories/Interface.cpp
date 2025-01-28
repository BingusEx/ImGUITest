#include "Interface.hpp"

#include "src/UI/ImGUI/ImUtil.hpp"
#include "src/UI/ImGUI/ImWindowManager.hpp"
#include "src/UI/ImGui/ImUtil.hpp"

#include "magic_enum/magic_enum.hpp"

using namespace UI;

//Template function for configuring windows
void CategoryInterface::ConfigureWindow(const std::string& a_WindowName, const std::string& a_Friendlyname){

    // ///Options For Configuring the Window Size/Pos

    // const char* _cFriendly = a_Friendlyname.c_str();
    // ImGui::SeparatorText(_cFriendly);
    
    // //Push ID to prevent conflicts
    // ImGui::PushID(a_WindowName.c_str());
    // if(auto window = ImWindowManager::GetSingleton().GetWindowByName(a_WindowName)){

    //     ImUtil::CheckBox("Lock Window", &Settings.UI.wSettings.bLock, "Lock the position and size of this window. You can can change the position and size below.");
        
    //     ImGui::BeginDisabled(!window->Fixed);
    //     {
    //         ImUtil::SliderF("Window Scale", &window->FixedScale, 50.0f, 95.0f, "Change the size of this window");
    //         ImGui::Combo("Anchor", (int*)&window->AnchorPos, "Top Left\0Top Right\0Center\0Bottom Left\0Bottom Right\0");
    //         ImGui::BeginDisabled(window->AnchorPos == ImWindow::WindowAnchor::kCenter);
    //         {
    //             ImUtil::SliderF("Offset (Left/Right)", &window->CornerPadding.x, 0.0f, 50.0f, "Offset the window to the left or right depending on which anchor position you choose");
    //             ImUtil::SliderF("Offset (Up/Down)", &window->CornerPadding.y, 0.0f, 50.0f, "Offset the window up or down depending on which anchor position you choose");
    //         }
    //         ImGui::EndDisabled();
    //     }
    //     ImGui::EndDisabled();
    // }
    // else{
    //     ImGui::TextColored(ImUtil::ColorError,"Can't find window with name: %s", a_WindowName.c_str());
    // }
    // ImGui::PopID();
}

void CategoryInterface::DrawLeft(){

    {   //Global UI Settings
        
        static float _gScale = StyleMgr.GetScale();
        ImGui::SeparatorText("Global UI Settings");

        ImUtil::SliderF("Font Scale", &_gScale, 0.8f, 2.0, "Change the scale of every element and font");
        if (ImGui::IsItemDeactivatedAfterEdit()) {
            StyleMgr.SetScale(_gScale);
            FontMgr.ChangeRasterizerScale(_gScale);
        }

        ImGui::ColorEdit3("Accent Color", Settings.UI.f3AccentColor.data(), true);
        if (ImGui::IsItemDeactivatedAfterEdit()) {
            StyleMgr.LoadStyle();
        }
    }

    {   //Main Window Settings

       ImUtil::CheckBox("Lock Window", &Settings.UI.wSettings.bLock, "Lock the position and size of this window. You can can change the position and size below.");
        
        ImGui::BeginDisabled(!Settings.UI.wSettings.bLock);
        {   
            auto anchorEnumOpt = magic_enum::enum_cast<ImWindow::WindowAnchor>(Settings.UI.wSettings.sAnchor);
            ImWindow::WindowAnchor anchorEnum = anchorEnumOpt.value_or(ImWindow::WindowAnchor::kTopLeft);
            int anchorIndex = static_cast<int>(anchorEnum);

            ImUtil::SliderF("Window Scale", &Settings.UI.wSettings.fWindowScale, 50.0f, 95.0f, "Change the size of this window");

            ImUtil::ImGuiEnumCombo<ImWindow::WindowAnchor>("Anchor", Settings.UI.wSettings.sAnchor);
            //ImGui::Combo("Anchor", &anchorIndex, "Top Left\0Top Right\0Center\0Bottom Left\0Bottom Right\0");




            // ImGui::BeginDisabled(window->AnchorPos == ImWindow::WindowAnchor::kCenter);
            // {
            //     ImUtil::SliderF("Offset (Left/Right)", &window->CornerPadding.x, 0.0f, 50.0f, "Offset the window to the left or right depending on which anchor position you choose");
            //     ImUtil::SliderF("Offset (Up/Down)", &window->CornerPadding.y, 0.0f, 50.0f, "Offset the window up or down depending on which anchor position you choose");
            // }
           // ImGui::EndDisabled();
        }
        ImGui::EndDisabled();

    }



    ConfigureWindow("ConfigWindow", "Configuration Window Settings");
    ConfigureWindow("WidgetWindow", "Widget Window Settings");

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

