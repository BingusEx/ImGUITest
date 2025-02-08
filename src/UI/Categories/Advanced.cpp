#include "Advanced.hpp"
#include "imgui.h"

#include "src/UI/ImGui/ImWindowManager.hpp"
#include "src/UI/ImGui/ImUtil.hpp"
#include "spdlog/spdlog.h" 

using namespace UI;

void CategoryAdvanced::DrawLeft(){


    ImUtil_Unique {
        
        const char* T0 = "Enable the profiler to diagnose performance issues.";
        const char* T1 = "Call AllocConsole() during mod startup to display stdout and stderr messages.";
        const char* T2 = "Enable the debug overlay.";
        const char* T3 = "Set the log severity level. The higher it is the more info is dumped into GTSPlugin.log";

        const char* T4 = "Set the flush severity level. The higher it is the more info is dumped into GTSPlugin.log when a crash happens\n"
                         "Sidenote: I've never actually seen this do anything... No extra info is flushed out. I guess we always immediatly empty the log buffer...";

        if(ImGui::CollapsingHeader("Logging / Debugging",ImUtil::HeaderFlags)){
            ImUtil::CheckBox("Enable Profiling",&Settings.bProfile, T0);
            ImUtil::CheckBox("Allocate Console",&Settings.bAllocConsole, T1);
            ImUtil::CheckBox("Show Debug Overlay",&Settings.bShowOverlay,T2);
            
            if(ImUtil::ComboEx<spdlog::level::level_enum>("Log Level", Settings.sLogLevel,T3,false,true)){
                 //TODO Call spdlog function to immediately Change the values
            }

            if(ImUtil::ComboEx<spdlog::level::level_enum>("Flush Level", Settings.sFlushLevel,T4,false,true)){
                 //TODO Call spdlog function to immediately Change the values
            }
            ImGui::Spacing();
        }

    }

    ImUtil_Unique {
        
        const char* T0 = "Apply computationally expensive damage calculations to all actors.";

        if(ImGui::CollapsingHeader("Mod Features",ImUtil::HeaderFlags)){ 
            ImUtil::CheckBox("Apply Size Effects to all Actors",&Settings.bAllActorSizeEffects, T0);
            ImGui::Spacing();
        }
    }

    ImUtil_Unique {
        
        const char* T0 = "Immediately return from DamageAV Calls for the player.";
        const char* T1 = "Bypass action cooldowns.";

        if(ImGui::CollapsingHeader("Cheats",ImUtil::HeaderFlags)){ 
            ImUtil::CheckBox("ActorValue Damage",&Settings.bDamageAV, T0);
            ImUtil::CheckBox("Action Cooldowns",&Settings.bCooldowns, T1);
            ImGui::Spacing();
        }
    }
}

void CategoryAdvanced::DrawRight(){

    ImUtil_Unique 
    {   
        //ImGui Debug
        if(ImGui::CollapsingHeader("ImGui Debug",ImUtil::HeaderFlags)){
            ImGui::BulletText("Viewport Size: (%.2f,%.2f)", ImGui::GetMainViewport()->Size.x, ImGui::GetMainViewport()->Size.y);
            ImGui::BulletText("Viewport Position: (%.2f,%.2f)", ImGui::GetMainViewport()->Pos.x, ImGui::GetMainViewport()->Pos.y);
            ImGui::BulletText("Config Window Size: (%.2f,%.2f)", ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
            ImGui::BulletText("Config Window Position: (%.2f,%.2f)", ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
            ImGui::Spacing();
        
            {   
                const char* T0 = "Show ImGui's Metrics Window";
                const char* T1 = "Show ImGui's Stack Window";

                ImUtil::CheckBox("Show Metrics", &ImWindowManager::GetSingleton().ShowMetrics,T0);
                ImUtil::CheckBox("Show Stack", &ImWindowManager::GetSingleton().ShowStack,T1);
            }
        }

    }

    if(ImUtil::Button("Quit", "Close the program\nTODO: Remove this later", false, 1.0f)){
        PostQuitMessage(0);
    }


}