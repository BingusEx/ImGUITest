#include "Advanced.hpp"
#include "imgui.h"

#include "src/UI/ImGui/ImUtil.hpp"
#include "spdlog/spdlog.h"

using namespace UI;

void CategoryAdvanced::DrawLeft(){
    if(ImGui::CollapsingHeader("Logging / Debugging",ImUtil::HeaderFlags)){ 
        ImUtil::CheckBox("Enable Profiling",&Settings.Advanced.bProfile);
        ImUtil::CheckBox("Allocate Console",&Settings.Advanced.bAllocConsole,"Open/Close a Console Window Showing Debug Information. Needs Restart To Apply");
        ImUtil::CheckBox("Show Debug Overlay",&Settings.Advanced.bShowOverlay);
        
        ImUtil::ComboEx<spdlog::level::level_enum>("Log Level", Settings.Advanced.sLogLevel,nullptr,false,true);
        ImUtil::ComboEx<spdlog::level::level_enum>("Flush Level", Settings.Advanced.sFlushLevel,nullptr,false,true);
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Mod Features",ImUtil::HeaderFlags)){ 
        ImUtil::CheckBox("ActorValue Damage",&Settings.Advanced.bDamageAV);
        ImUtil::CheckBox("Action Cooldowns",&Settings.Advanced.bCooldowns);
        ImUtil::CheckBox("Apply Size Effects to all Actors",&Settings.Advanced.bAllActorSizeEffects);
        ImGui::Spacing();
    }
}

void CategoryAdvanced::DrawRight(){

    {   //Info About the Config Window
        ImGui::SeparatorText("ImGUI Info");
        ImGui::BulletText("Viewport Size: (%.2f,%.2f)", ImGui::GetMainViewport()->Size.x, ImGui::GetMainViewport()->Size.y);
        ImGui::BulletText("Viewport Pos: (%.2f,%.2f)", ImGui::GetMainViewport()->Pos.x, ImGui::GetMainViewport()->Pos.y);
        ImGui::BulletText("Config Window Size: (%.2f,%.2f)", ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
        ImGui::BulletText("Config Window Pos: (%.2f,%.2f)", ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);

    }

    if(ImUtil::Button("Close Program", "Close the program", false, 1.0f)){
        //Call Win32 API to close this program
        PostQuitMessage(0);
    }
}