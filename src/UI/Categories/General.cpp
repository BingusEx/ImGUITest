#include "General.hpp"
#include "imgui.h"
#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

void CategoryGeneral::DrawLeft(){
    
    //-------------------------------- Compatibility
    if(ImGui::CollapsingHeader("Compatibility",ImUtil::HeaderFlags)){ 
        ImGui::PushID("UIGameplay##Compat");

        //ImUtil::CheckBox("Devourment Compatibility",&Settings.Gameplay.bDevourmentCompat,"Enable/Disable compatibility for the Devourment mod. If enabled vore actions will use it to handle voring NPCs");
        //ImUtil::CheckBox("Alt Conversation Cam. Compatibility",&Settings.Gameplay.bConversationCamCompat,"Enable/Disable compatibility for the Alternate conversation camera mod. If enabled, disables this mods' camera manipulation during dialogue");
       
        ImGui::Spacing();
        ImGui::PopID();
    }

    if(ImGui::CollapsingHeader("Visuals",ImUtil::HeaderFlags)){ 
        ImUtil::CheckBox("Less Gore",&Settings.Advanced.bProfile);
        ImUtil::CheckBox("Allocate Console",&Settings.Advanced.bAllocConsole,"Open/Close a Console Window Showing Debug Information. Needs Restart To Apply");
        ImUtil::CheckBox("Show Debug Overlay",&Settings.Advanced.bShowOverlay);
        
    
        ImGui::Spacing();
    }


































}

void CategoryGeneral::DrawRight(){}