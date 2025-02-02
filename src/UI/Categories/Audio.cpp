#include "Audio.hpp"
#include "imgui.h"
#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

void CategoryAudio::DrawLeft(){
    if(ImGui::CollapsingHeader("Sounds",ImUtil::HeaderFlags)){ 
        ImUtil::CheckBox("Footstep Sounds",&Settings.bFootstepSounds,"Enable / disable footstep sounds when large");
        ImUtil::CheckBox("Moans On Slow Growth",&Settings.bSlowGrowMoans,"Enable moan sounds when using the slow growth spell");
        //ImUtil::CheckBox("Use Old Sounds",&Settings.bUseOldSounds,"Use Old Sounds");
       
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Voice",ImUtil::HeaderFlags)){
        ImUtil::CheckBox("Enable Voice Override",&Settings.bEnableVoiceOverride,"Enables overriding the voice pitch of actors");
        ImUtil::SliderF("Voice Pitch Max",&Settings.fMaxVoiceFrequency, 1.0f, 1.6f, "Change the maximum voice pitch, Higher values will lower the pitch when the actor is large","%.2fx",!Settings.bEnableVoiceOverride);
        
        

        ImGui::Spacing();
    }

}

void CategoryAudio::DrawRight(){

    if(ImGui::CollapsingHeader("Volume Settings",ImUtil::HeaderFlags)){ 
        ImUtil::SliderF("Voices",&Settings.fVolumeVoice, 0.0f, 1.0f, "TODO: Describe me","%.2fx");
        ImUtil::SliderF("Effects",&Settings.fVolumeEffects, 0.0f, 1.0f, "TODO: Describe me","%.2fx");
        ImUtil::SliderF("Footsteps",&Settings.fVolumeFootstep, 0.0f, 1.0f, "TODO: Describe me","%.2fx");
        ImUtil::SliderF("Footstep Effects",&Settings.fVolumeFootstepEffects, 0.0f, 1.0f, "TODO: Describe me","%.2fx");
        ImUtil::SliderF("Impacts",&Settings.fVolumeImpacts, 0.0f, 1.0f, "TODO: Describe me","%.2fx");
        ImGui::Spacing();
    }
}