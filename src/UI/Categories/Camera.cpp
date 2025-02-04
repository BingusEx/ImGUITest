#include "Camera.hpp"
#include "imgui.h"
#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

inline void DrawCameraOffsets(const char* a_title, const char* a_toolip,  std::array<float,3>* a_offsets){
    ImGui::Spacing();

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
}


void DrawCameraSettings(CameraOffsets* a_set, const char* a_title){
    if(ImGui::CollapsingHeader(a_title,ImGuiTreeNodeFlags_Bullet)){ 
        ImUtil::ComboEx<CameraTrackingUsr>("Center On Bone", a_set->sCenterOnBone,"Select which skeleton bone the camera should track");

        ImUtil_Unique {
            DrawCameraOffsets(
                "Offsets | Standing",
                "Adjust Camera offsets when standing",
                &a_set->f3NormalStand
            );
        }

        ImUtil_Unique {
            DrawCameraOffsets(
                "Offsets | Standing Combat",
                "Adjust Camera offsets when standing and in combat",
                &a_set->f3CombatStand
            );
        }

        ImUtil_Unique {
            DrawCameraOffsets(
                "Offsets | Sneak",
                "Adjust Camera offsets when sneaking/crawling/proning",
                &a_set->f3NormalSneak
            );
        }

        ImUtil_Unique {
            DrawCameraOffsets(
                "Offsets | Sneak Combat",
                "Adjust Camera offsets when sneaking/crawling/proning and in combat",
                &a_set->f3CombatSneak
            );
        }
        ImGui::Spacing();
        ImGui::Spacing();
    }
    
}


void CategoryCamera::DrawLeft(){

    if(ImGui::CollapsingHeader("Camera Shake",ImUtil::HeaderFlags)){ 
        ImUtil::SliderF("Player Total Shake Power",&Settings.fCameraShakePlayer, 0.1f, 3.0f ,"Change the intensity of camera shakes when doing actions as the player","%.1fx");
        ImUtil::SliderF("NPC Total Shake Power",&Settings.fCameraShakeOther, 0.1f, 3.0f ,"Change the intensity of camera shakes for NPCs","%.1fx");
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Crawl Height",ImUtil::HeaderFlags)){ 
        ImUtil::SliderF("1st P. Crawl Height",&Settings.fFPCrawlHeightMult, 0.01f, 1.0f ,"Change the height multiplier of the camera when crawling in first person","%.1fx");
        ImUtil::SliderF("3rd P. Crawl Height",&Settings.fTPCrawlHeightMult, 0.01f, 1.0f ,"Change the height multiplier of the camera when crawling in third person","%.1fx");
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Camera Colision",ImUtil::HeaderFlags)){ 

        ImUtil::CheckBox("Collide With Actors",&Settings.bCamCollideActor);
        ImGui::SameLine();
        ImUtil::CheckBox("Collide With Trees",&Settings.bCamCollideTree);
        ImUtil::CheckBox("Collide With Debris",&Settings.bCamCollideDebris);
        ImGui::SameLine();
        ImUtil::CheckBox("Collide With Terrain",&Settings.bCamCollideTerrain);
        ImUtil::CheckBox("Collide With Statics",&Settings.bCamCollideStatics);

        ImUtil::SliderF("Apply at Scale",&Settings.fModifyCamCollideAt, 1.0f, 50.0f ,"Change the scale at which the above colission options should start to be applied at","%.1fx");
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Skyrim Camera Settings",ImUtil::HeaderFlags)){ 
        //TODO Fix MinMax for the sliders
        ImUtil::SliderF("Minimum Distance",&Settings.fCameraDistMin, -10.0f, 100.0f ,"Change the minimum zoom distance","%.0f");
        ImUtil::SliderF("Maximum Distance",&Settings.fCameraDistMax, 200.0f, 700.0f ,"Change the maximum zoom distance","%.0f");
        ImUtil::SliderF("Zoom Speed",&Settings.fCameraZoom, 5.0f, 40.0f ,"Change the zoom speed","%.0f");
        ImUtil::SliderF("Zoom Step",&Settings.fCameraStep, 0.0f, 0.3f ,"Change zoom step","%.3f");
        ImGui::Spacing();
    }

}   

void CategoryCamera::DrawRight(){
    if(ImGui::CollapsingHeader("Automatic Camera",ImUtil::HeaderFlags)){ 
        ImUtil::CheckBox("Enable Automatic Camera",&Settings.bAutomaticCamera,"Enables the automatic camera");
        ImUtil::ComboEx<CameraModeTP>("TP Camera Mode", Settings.sAutoCameraModeTP,"Change the 3rd person camera mode",!Settings.bAutomaticCamera);
        ImUtil::ComboEx<CameraModeFP>("FP Camera Mode", Settings.sAutoCameraModeFP,"Change the 1st person camera mode",!Settings.bAutomaticCamera);
        ImGui::Spacing();
    }
    ImGui::BeginDisabled(!Settings.bAutomaticCamera);
    
    ImUtil_Unique {
        DrawCameraSettings(&Settings.OffsetsNormal, "Normal Camera");
    }

    ImUtil_Unique {
        DrawCameraSettings(&Settings.OffsetsAlt, "Alt Camera");
    }
    
    if(ImGui::CollapsingHeader("Foot Camera",ImGuiTreeNodeFlags_Bullet)){ 
        ImUtil::SliderF("Forward - Back", &Settings.fFootCameraFBOffset ,-200.f, 200.f,nullptr,"%.1f");
        ImGui::Spacing();
    }
    ImGui::EndDisabled();

}