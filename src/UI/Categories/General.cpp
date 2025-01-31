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



































}

void CategoryGeneral::DrawRight(){}