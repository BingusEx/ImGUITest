#include "Camera.hpp"
#include "imgui.h"
#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

inline void DrawCameraOffsets(const char* a_strID, const char* a_title, const char* a_toolip,  std::array<float,3>* a_offsets){
    ImGui::Spacing();

    ImGui::PushID(a_strID);
    ImGui::Text(a_title);
    ImGui::BeginGroup();

    ImUtil::SliderF("Left - Right", &a_offsets->at(0) ,-100.f, 100.f,nullptr,"%.1f");
    ImUtil::SliderF("Up - Down", &a_offsets->at(2),-200.f, 200.f,nullptr,"%.1f");
    ImUtil::SliderF("Forward - Back", &a_offsets->at(1) ,-200.f, 200.f,nullptr,"%.1f");

    ImGui::EndGroup();

    //Applies to the whole group
    if (ImGui::IsItemHovered()){
        ImGui::SetTooltip(a_toolip);
    }

    ImGui::PopID();

}


void DrawCameraSettings(CameraOffsets* a_set, const char* a_strID, const char* a_title){
    ImGui::PushID(a_strID);
    if(ImGui::CollapsingHeader(a_title,ImGuiTreeNodeFlags_Bullet)){ 
        ImUtil::ComboEx<CameraTrackingUsr>("Center On Bone", a_set->sCenterOnBone,"Select which skeleton bone the camera should track");

        DrawCameraOffsets(
            "##Standing",
            "Offsets | Standing",
            "Adjust Camera offsets when standing",
            &a_set->f3NormalStand
        );

        DrawCameraOffsets(
            "##Standing##Combat",
            "Offsets | Standing Combat",
            "Adjust Camera offsets when standing and in combat",
            &a_set->f3CombatStand
        );

        DrawCameraOffsets(
            "##Sneak",
            "Offsets | Sneak",
            "Adjust Camera offsets when sneaking/crawling/proning",
            &a_set->f3NormalSneak
        );

        DrawCameraOffsets(
            "##Sneak##Combat",
            "Offsets | Sneak Combat",
            "Adjust Camera offsets when sneaking/crawling/proning and in combat",
            &a_set->f3CombatSneak
        );
        ImGui::Spacing();
        ImGui::Spacing();
    }
    
    ImGui::PopID();
}


void CategoryCamera::DrawLeft(){

    if(ImGui::CollapsingHeader("Camera Shake",ImUtil::HeaderFlags)){ 
        ImUtil::SliderF("Player Total Shake Power",&Settings.Camera.fCameraShakePlayer, 0.1f, 3.0f ,"Change the intensity of camera shakes when doing actions as the player","%.1fx");
        ImUtil::SliderF("NPC Total Shake Power",&Settings.Camera.fCameraShakeOther, 0.1f, 3.0f ,"Change the intensity of camera shakes for NPCs","%.1fx");
        ImGui::Spacing();
    }

    
    if(ImGui::CollapsingHeader("Crawl Height",ImUtil::HeaderFlags)){ 
        ImUtil::SliderF("1st P. Crawl Height",&Settings.Camera.fFPCrawlHeightMult, 0.01f, 1.0f ,"Change the height multiplier of the camera when crawling in first person","%.1fx");
        ImUtil::SliderF("3rd P. Crawl Height",&Settings.Camera.fTPCrawlHeightMult, 0.01f, 1.0f ,"Change the height multiplier of the camera when crawling in third person","%.1fx");
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Camera Colision",ImUtil::HeaderFlags)){ 

        ImUtil::CheckBox("Collide With Actors",&Settings.Camera.bCamCollideActor);
        ImGui::SameLine();
        ImUtil::CheckBox("Collide With Trees",&Settings.Camera.bCamCollideTree);
        ImUtil::CheckBox("Collide With Debris",&Settings.Camera.bCamCollideDebris);
        ImGui::SameLine();
        ImUtil::CheckBox("Collide With Terrain",&Settings.Camera.bCamCollideTerrain);
        ImUtil::CheckBox("Collide With Statics",&Settings.Camera.bCamCollideStatics);

        ImUtil::SliderF("Apply at Scale",&Settings.Camera.fModifyCamCollideAt, 1.0f, 50.0f ,"Change the scale at which the above collision options should start applying","%.1fx");
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Skyrim Camera Settings",ImUtil::HeaderFlags)){ 
        //TODO Fix MinMax for the sliders
        ImUtil::SliderF("Minimum Distance",&Settings.Camera.fCameraDistMin, -10.0f, 100.0f ,"Change the minimum zoom distance","%.0f Unit(s)");
        ImUtil::SliderF("Maximum Distance",&Settings.Camera.fCameraDistMax, 200.0f, 700.0f ,"Change the maximum zoom distance","%.0f Unit(s)");
        ImUtil::SliderF("Zoom Speed",&Settings.Camera.fCameraZoom, 5.0f, 40.0f ,"Change the minimum zoom distance","%.0f Unit(s)");
        ImUtil::SliderF("Zoom Step",&Settings.Camera.fCameraStep, 0.0f, 0.3f ,"Change the minimum zoom distance","%.04f Unit(s)");
        ImGui::Spacing();
    }

}   

void CategoryCamera::DrawRight(){
    if(ImGui::CollapsingHeader("Automatic Camera",ImUtil::HeaderFlags)){ 
        ImUtil::CheckBox("Enable Automatic Camera",&Settings.Camera.bAutomaticCamera,"Enables the automatic camera");
        ImUtil::ComboEx<CameraModeTP>("TP Camera Mode", Settings.Camera.sAutoCameraModeTP,"Change the 3rd person camera mode");
        ImUtil::ComboEx<CameraModeFP>("FP Camera Mode", Settings.Camera.sAutoCameraModeFP,"Change the 1st person camera mode");
        ImGui::Spacing();
    }
   
    DrawCameraSettings(&Settings.Camera.tCONormal, "CameraSettings##Normal", "Normal Camera");
    DrawCameraSettings(&Settings.Camera.tCOAlt, "CameraSettings##Alt", "Alt Camera");
    
    if(ImGui::CollapsingHeader("Foot Camera",ImGuiTreeNodeFlags_Bullet)){ 
        ImUtil::SliderF("Forward - Back", &Settings.Camera.fFootCameraFBOffset ,-100.f, 100.f,nullptr,"%.0f");
        ImGui::Spacing();
    }

}