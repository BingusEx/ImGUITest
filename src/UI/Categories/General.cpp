#include "General.hpp"
#include "imgui.h"
#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

void CategoryGeneral::DrawLeft(){
    
    //-------------------------------- Compatibility

    if(ImGui::CollapsingHeader("Protect Actors",ImUtil::HeaderFlags)){ 

        ImUtil::CheckBox("Protect Essential NPCs",&Settings.bProtectEssentials,"Protect essential NPCs from GTS actions");
        ImUtil::CheckBox("Protect Followers",&Settings.bProtectFollowers,"Protect essential NPCs from GTS actions");
        
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Compatibility",ImUtil::HeaderFlags)){ 

        ImUtil::CheckBox("Devourment Compatibility",&Settings.bDevourmentCompat,"Enable/Disable compatibility for the Devourment mod. If enabled vore actions will use it to handle voring NPCs");
        ImUtil::CheckBox("Alt Conversation Cam. Compatibility",&Settings.bConversationCamCompat,"Enable/Disable compatibility for the Alternate conversation camera mod. If enabled, disables this mods' camera manipulation during dialogue");
       
        ImGui::Spacing();

    }

    if(ImGui::CollapsingHeader("Visuals",ImUtil::HeaderFlags)){ 

        ImUtil::CheckBox("Less Gore",&Settings.bLessGore);
        ImUtil::CheckBox("Heart Effects",&Settings.bShowHearts,"Open/Close a Console Window Showing Debug Information. Needs Restart To Apply");
        ImUtil::CheckBox("Show Action Icons",&Settings.bShowIcons);
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("High-Heels",ImUtil::HeaderFlags)){
        ImUtil::CheckBox("Enable Height Adjustment",&Settings.bEnableHighHeels);
        ImUtil::CheckBox("Disable When Using Furniture",&Settings.bHighheelsFurniture,"Open/Close a Console Window Showing Debug Information. Needs Restart To Apply");
        ImGui::Spacing();
    }

}

void CategoryGeneral::DrawRight(){

    if(ImGui::CollapsingHeader("Miscelaneous",ImUtil::HeaderFlags)){ 
        ImUtil::CheckBox("Dynamic Size",&Settings.bDynamicSize);
        ImUtil::CheckBox("Dynamic Animation Speed",&Settings.bDynamicAnimspeed,"Open/Close a Console Window Showing Debug Information. Needs Restart To Apply");
        ImUtil::CheckBox("Enable FOV Edits",&Settings.bEnableFOVEdits);
        ImUtil::CheckBox("Enable Layered Sneak",&Settings.bLayeredSneak);
        ImGui::Spacing();
    }


    if(ImGui::CollapsingHeader("Experimental",ImUtil::HeaderFlags)){
        ImUtil::CheckBox("Allow Male Actors",&Settings.bEnableMales);
        ImGui::Spacing();
    }


}