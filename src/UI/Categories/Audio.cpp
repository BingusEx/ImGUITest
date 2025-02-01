#include "Audio.hpp"
#include "imgui.h"
#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

void CategoryAudio::DrawLeft(){
    if(ImGui::CollapsingHeader("Sounds",ImUtil::HeaderFlags)){ 
        ImUtil::CheckBox("Footstep Sounds",&Settings.Audio.bFootstepSounds,"Enable / disable footstep sounds when large");
        ImUtil::CheckBox("Moans On Slow Growth",&Settings.Audio.bSlowGrowMoans,"Enable moan sounds when using the slow growth spell");
        //ImUtil::CheckBox("Use Old Sounds",&Settings.Audio.bUseOldSounds,"Use Old Sounds");
       
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Voice",ImUtil::HeaderFlags)){
        ImUtil::CheckBox("Enable Voice Override",&Settings.Audio.bEnableVoiceOverride,"Enables overriding the voice pitch of actors");
        ImUtil::SliderF("Voice Pitch Max",&Settings.Audio.fMaxVoiceFrequency, 1.0f, 1.6f, "Change the maximum voice pitch, Higher values will lower the pitch when the actor is large","%.2fx",!Settings.Audio.bEnableVoiceOverride);
        
        

        ImGui::Spacing();
    }

}

void CategoryAudio::DrawRight(){

    if(ImGui::CollapsingHeader("Volume Settings",ImUtil::HeaderFlags)){ 
        ImUtil::SliderF("Voices",&Settings.Audio.fVolumeVoice, 0.0f, 1.0f, "TODO: Describe me","%.2fx");
        ImUtil::SliderF("Effects",&Settings.Audio.fVolumeEffects, 0.0f, 1.0f, "TODO: Describe me","%.2fx");
        ImUtil::SliderF("Footsteps",&Settings.Audio.fVolumeFootstep, 0.0f, 1.0f, "TODO: Describe me","%.2fx");
        ImUtil::SliderF("Footstep Effects",&Settings.Audio.fVolumeFootstepEffects, 0.0f, 1.0f, "TODO: Describe me","%.2fx");
        ImUtil::SliderF("Impacts",&Settings.Audio.fVolumeImpacts, 0.0f, 1.0f, "TODO: Describe me","%.2fx");
        ImGui::Spacing();
    }
}