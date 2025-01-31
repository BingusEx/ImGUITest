#include "Interface.hpp"

#include "src/UI/ImGUI/ImUtil.hpp"
#include "src/UI/ImGUI/ImWindowManager.hpp"
#include "src/UI/ImGui/ImUtil.hpp"

#include "magic_enum/magic_enum.hpp"

using namespace UI;

void CategoryInterface::DrawLeft(){


    // --------------------------- UI Settings
    if(ImGui::CollapsingHeader("Misc Settings",ImUtil::HeaderFlags)){
        ImGui::PushID("UISettings##Other");
        
        ImUtil::ComboEx<DisplayUnit>("Measurement Units",Settings.UI.sDisplayUnits,"Select which form of measurement units to use");

        ImGui::Spacing();
        ImGui::PopID();
    }

    // --------------------------- UI Settings
    if(ImGui::CollapsingHeader("UI Settings",ImUtil::HeaderFlags)){
        ImGui::PushID("UISettings##Main");
        
        ImUtil::SliderF("UI Scale", &Settings.UI.fScale, 0.8f, 1.5, "Change the scale of every element and font","%.1fx");
        if (ImGui::IsItemDeactivatedAfterEdit()) {
            StyleMgr.LoadStyle();
            FontMgr.RebuildFonts();
        }

        ImGui::ColorEdit3("Accent Color", Settings.UI.f3AccentColor.data(), ImGuiColorEditFlags_DisplayHSV);
        if (ImGui::IsItemDeactivatedAfterEdit() || (ImGui::IsItemActive() && ImGui::GetIO().MouseDown[0])) {
            StyleMgr.LoadStyle();
        }
        if (ImGui::IsItemHovered()){
            ImGui::SetTooltip("Change the accent color of the UI");
        }

        ImGui::Spacing();
        ImGui::PopID();
    }

    //Main Window Settings
    if(ImGui::CollapsingHeader("Config Window", ImUtil::HeaderFlags)){ 
        ImGui::PushID("UISettings##Config");
        
        ImUtil::CheckBox("Lock Config Window Position", &Settings.UI.wSettings.bLock, "Prevents this window from being movable/resizable. You can can change the position and size below.");
        ImGui::BeginDisabled(!Settings.UI.wSettings.bLock);
        {   
            ImUtil::SliderF("Window Size", &Settings.UI.wSettings.fWindowSize, 60.0f, 100.0f, "Change the size of this window","%.0f%%");
            ImUtil::ComboEx<ImWindow::WindowAnchor>("Anchor", Settings.UI.wSettings.sAnchor,"Select where the window should be aligned/anchored at");
            ImGui::BeginDisabled(Settings.UI.wSettings.sAnchor == "kCenter");
            {
                ImUtil::SliderF("Offset (Left/Right)", &Settings.UI.wSettings.f2Offset[0], 0.0f, 700.0f, "Offset the window to the left or right depending on which anchor position you choose","%.1f%");
                ImUtil::SliderF("Offset (Up/Down)", &Settings.UI.wSettings.f2Offset[1], 0.0f, 700.0f, "Offset the window up or down depending on which anchor position you choose","%.1f%");
            }
            ImGui::EndDisabled();
        }

        ImGui::EndDisabled();
        ImGui::Spacing();
        ImGui::PopID();
    }

    

}

void CategoryInterface::DrawRight(){

    //Stats Window Settings
    if(ImGui::CollapsingHeader("Status Widget",ImUtil::HeaderFlags)){ 
        ImGui::PushID("UISettings##Stats");

        ImUtil::CheckBox("Show status widget", &Settings.UI.wStatus.bVisible, "Show/hide the status widget");

        ImUtil::SliderF("Widget Alpha", &Settings.UI.wStatus.fAlpha, 0.1f, 1.0f, "Increase/Decrease the alpha (visibility) of the stats window",("%.1fx"));
        
        ImGui::Spacing();
        
        ImUtil::CheckBox("Lock Stats Window Position", &Settings.UI.wStatus.bLock, "Prevents the stats window from being movable/resizable");
        ImGui::BeginDisabled(!Settings.UI.wStatus.bLock);
        {   
            ImUtil::ComboEx<ImWindow::WindowAnchor>("Anchor", Settings.UI.wStatus.sAnchor, "Select where the window should be aligned/anchored at");
            ImGui::BeginDisabled(Settings.UI.wStatus.sAnchor == "kCenter");
            {
                ImUtil::SliderF("Offset (Left/Right)", &Settings.UI.wStatus.f2Offset[0], 0.0f, 700.0f, "Offset the window to the left or right depending on which anchor position you choose","%.1f%");
                ImUtil::SliderF("Offset (Up/Down)", &Settings.UI.wStatus.f2Offset[1], 0.0f, 700.0f, "Offset the window up or down depending on which anchor position you choose","%.1f%");
            }
            ImGui::EndDisabled();
        }

        //ImUtil::Bitfield("Bits",&Settings.UI.wStatus.iDisplayItems);
        ImGui::EndDisabled();
        ImGui::Spacing();
        ImGui::PopID();
    }

}

