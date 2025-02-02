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
        
        ImUtil::ComboEx<DisplayUnit>("Measurement Units",Settings.sDisplayUnits,"Select which form of measurement units to use");

        ImGui::Spacing();
        ImGui::PopID();
    }

    // --------------------------- UI Settings
    if(ImGui::CollapsingHeader("UI Settings",ImUtil::HeaderFlags)){
        ImGui::PushID("UISettings##Main");
        
        ImUtil::SliderF("UI Scale", &Settings.fScale, 0.8f, 1.5, "Change the scale of every element and font","%.1fx");
        if (ImGui::IsItemDeactivatedAfterEdit()) {
            StyleMgr.LoadStyle();
            FontMgr.RebuildFonts();
        }

        ImUtil::SliderF("Item Width", &Settings.fItemWidth, 0.4f, 0.7f, "Change the width of the imGui controls","%.2fx");
        // if (ImGui::IsItemDeactivatedAfterEdit()) {
        //     StyleMgr.LoadStyle();
        //     FontMgr.RebuildFonts();
        // }

        ImGui::ColorEdit3("Accent Color", Settings.f3AccentColor.data(), ImGuiColorEditFlags_DisplayHSV);
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
        
        ImUtil::CheckBox("Lock Config Window Position", &Settings.wSettings.bLock, "Prevents this window from being movable/resizable. You can can change the position and size below.");
        ImGui::BeginDisabled(!Settings.wSettings.bLock);
        {   
            ImUtil::SliderF("Window Size", &Settings.wSettings.fWindowSize, 60.0f, 100.0f, "Change the size of this window","%.0f%%");
            ImUtil::ComboEx<ImWindow::WindowAnchor>("Anchor", Settings.wSettings.sAnchor,"Select where the window should be aligned/anchored at");
            ImGui::BeginDisabled(Settings.wSettings.sAnchor == "kCenter");
            {
                ImUtil::SliderF("Offset (Left/Right)", &Settings.wSettings.f2Offset[0], 0.0f, 700.0f, "Offset the window to the left or right depending on which anchor position you choose","%.1f%");
                ImUtil::SliderF("Offset (Up/Down)", &Settings.wSettings.f2Offset[1], 0.0f, 700.0f, "Offset the window up or down depending on which anchor position you choose","%.1f%");
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

        ImUtil::CheckBox("Show Stats Widget", &Settings.wStatus.bVisible, "Show/hide the status widget");

        ImUtil::SliderF("Widget Alpha", &Settings.wStatus.fAlpha, 0.1f, 1.0f, "Increase/Decrease the alpha (visibility) of the stats window",("%.1fx"));
        
        ImGui::Spacing();
        
        ImUtil::CheckBox("Lock Widget Position", &Settings.wStatus.bLock, "Prevents the stats window from being movable/resizable");
        ImGui::BeginDisabled(!Settings.wStatus.bLock);
        {   
            ImUtil::ComboEx<ImWindow::WindowAnchor>("Anchor", Settings.wStatus.sAnchor, "Select where the window should be aligned/anchored at");
            ImGui::BeginDisabled(Settings.wStatus.sAnchor == "kCenter");
            {
                ImUtil::SliderF("Offset (Left/Right)", &Settings.wStatus.f2Offset[0], 0.0f, 700.0f, "Offset the window to the left or right depending on which anchor position you choose","%.1f%");
                ImUtil::SliderF("Offset (Up/Down)", &Settings.wStatus.f2Offset[1], 0.0f, 700.0f, "Offset the window up or down depending on which anchor position you choose","%.1f%");
            }
            ImGui::EndDisabled();
        }

        //ImUtil::Bitfield("Bits",&Settings.wStatus.iDisplayItems);
        ImGui::EndDisabled();
        ImGui::Spacing();
        ImGui::PopID();
    }

}

