#include "Gameplay.hpp"
#include "imgui.h"
#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

void CategoryGameplay::DrawLeft(){
   
    //Todo Move to gameplay Perks Section
    if(ImGui::CollapsingHeader("Perk Settings",ImUtil::HeaderFlags)){ 
        ImUtil::SliderF("Size Conversion Mult",&Settings.Balance.fSpellEfficiency,0.1f, 2.0f,"Modify the ammount of attributes stolen by Size Conversion","%.2fx");
        
        ImGui::Spacing();
    }

}

void CategoryGameplay::DrawRight(){
    ImUtil::CheckBox("Enable Voice Override",&Settings.Audio.bEnableVoiceOverride,"Enables overriding the voice pitch of actors");

}