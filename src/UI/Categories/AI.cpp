#include "AI.hpp"
#include "imgui.h"

#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

void CategoryAI::DrawLeft(){
    if(ImGui::CollapsingHeader("Action AI Settings",ImUtil::HeaderFlags)){
        ImGui::PushID("AI##Settings");
        ImUtil::CheckBox("Enable AI",&Settings.bEnableActionAI, "Enable / Disable the action AI");

        {
            ImGui::BeginDisabled(!Settings.bEnableActionAI);
            
            ImUtil::SliderF("Try To Start A New Action",&Settings.fMasterTimer, 2.0f, 15.0f, "Set the time interval NPCs should attempt to start a new GTS action","Every %.1f Seconds");
            ImGui::Spacing();
            ImUtil::CheckBox("Target Player", &Settings.bAllowPlayer, "Allow the AI to target the player");
            ImUtil::CheckBox("Target Other Followers", &Settings.bAllowFollowers, "Allow the AI to target other followers");
            ImUtil::CheckBox("Enable AI Only During Combat",&Settings.bCombatOnly, "Only allow the action AI to be active during combat");
            
            ImGui::EndDisabled();
        }


        ImGui::PopID();
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Misc Settings",ImUtil::HeaderFlags)){
        ImGui::PushID("AI##Settings");
        ImUtil::CheckBox("Actors Panic", &Settings.bPanic, "Toggle wether other NPCs should panic when near a GTS");
        ImGui::PopID();
        ImGui::Spacing();
    }

}

void CategoryAI::DrawRight(){

    ImGui::BeginDisabled(!Settings.bEnableActionAI);

    if(ImGui::CollapsingHeader("Vore",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##Vore");
        ImUtil::CheckBox("Enable Vore", &Settings.tVore.bEnableAction);
        ImUtil::SliderF("Vore Probability", &Settings.tVore.fProbability, 1.0f, 100.0f, "Set the chance for vore to happen","%.0f%%",!Settings.tVore.bEnableAction);
        ImGui::PopID();
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Stomps",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##Stomps");
        ImUtil::CheckBox("Enable Stomps", &Settings.tStomp.bEnableAction);
        ImUtil::SliderF("Stomp Probability", &Settings.tStomp.fProbability, 1.0f, 100.0f, "Set the chance for stomps to happen","%.0f%%",!Settings.tStomp.bEnableAction);
        ImGui::PopID();
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Kicks / Swipes",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##KickSwipe");
        ImUtil::CheckBox("Enable Kicks / Swipes", &Settings.tKickSwipe.bEnableAction);
        ImUtil::SliderF("Kick / Swipe Probability", &Settings.tKickSwipe.fProbability, 1.0f, 100.0f, "Set the chance for Kicks and swipes to happen","%.0f%%",!Settings.tKickSwipe.bEnableAction);
        ImGui::PopID();
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Thigh Sandwich",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##ThighSandwich");
        ImUtil::CheckBox("Enable Thigh Sandwich", &Settings.tThighSandwich.bEnableAction);

        {
            ImGui::BeginDisabled(!Settings.tThighSandwich.bEnableAction);
            ImUtil::SliderF("Thigh Sandwich Probability", &Settings.tThighSandwich.fProbability, 1.0f, 100.0f, "Set the chance for a thigh sandwich action to be started","%.0f%%");
                        
            ImGui::Spacing();

            ImUtil::SliderF("Action Interval",&Settings.tThighSandwich.fInterval, 1.0f, 5.0f, "Set the interval at which an attempt is made to attack. If an attack happens depends on the probabilities set below", "Every %.1f Second(s)");
            ImUtil::SliderF("Heavy Attack Chance",&Settings.tThighSandwich.fProbabilityHeavy, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Light Attack Chance",&Settings.tThighSandwich.fProbabilityLight, 0.0f, 100.0f, nullptr, "%.0f%%");
            
            ImGui::EndDisabled();
        }


        ImGui::PopID();
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Thigh Crush",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##ThighCrush");
        ImUtil::CheckBox("Enable Thigh Crush", &Settings.tThighCrush.bEnableAction);
        
        {
            ImGui::BeginDisabled(!Settings.tThighCrush.bEnableAction);
            ImUtil::SliderF("Thigh Crush Probability", &Settings.tThighCrush.fProbability, 1.0f, 100.0f, "Set the chance for a thigh crush action to be started","%.0f%%");
            
            ImGui::Spacing();

            ImUtil::SliderF("Action Interval",&Settings.tThighCrush.fInterval, 1.0f, 10.0f, "Set the interval at which an attempt is made to attack. If an attack happens depends on the probabilities set below", "Every %.1f Second(s)");
            ImUtil::SliderF("Attack Chance",&Settings.tThighCrush.fProbabilityHeavy, 0.0f, 100.0f, nullptr, "%.0f%%");
            
            ImGui::EndDisabled();
        }


        ImGui::PopID();
        ImGui::Spacing();
    }


    if(ImGui::CollapsingHeader("Hugs",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##Hugs");
        ImUtil::CheckBox("Enable Hugs", &Settings.tHugs.bEnableAction);

        {
            ImGui::BeginDisabled(!Settings.tHugs.bEnableAction);
            ImUtil::SliderF("Start Hugs Probability", &Settings.tHugs.fProbability, 1.0f, 100.0f, "Set the chance for a thigh crush action to be started","%.0f%%");
            
            ImGui::Spacing();

            ImUtil::CheckBox("Allow Killing Followers", &Settings.tHugs.bKillFollowers);
            ImUtil::CheckBox("Allow Killing Friendlies", &Settings.tHugs.bKillFriendlies);
            ImUtil::CheckBox("Stop After Health Is Full", &Settings.tHugs.bStopAtFullHP, "Should the follower continue hugging someone after hug healing them to full HP");

            ImGui::Spacing();

            ImUtil::SliderF("Action Interval",&Settings.tHugs.fInterval, 1.0f, 10.0f, "Set the interval at which an attempt is made to do any of the below hug actions. If a hug action happens depends on the probabilities set below", "Every %.1f Second(s)");
            ImUtil::SliderF("Chance To Heal",&Settings.tHugs.fHealProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Chance To Kill",&Settings.tHugs.fKillProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Chance To Shrink",&Settings.tHugs.fShrinkProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            
            ImGui::EndDisabled();
        }


        ImGui::PopID();
        ImGui::Spacing();
    }


    if(ImGui::CollapsingHeader("Butt Crush",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##Butt");
        ImUtil::CheckBox("Enable Butt Crush", &Settings.tButtCrush.bEnableAction);

        {
            ImGui::BeginDisabled(!Settings.tButtCrush.bEnableAction);
            ImUtil::SliderF("Start Butt Crush Probability", &Settings.tButtCrush.fProbability, 1.0f, 100.0f, "Set the chance for a thigh crush action to be started","%.0f%%");
            
            ImGui::Spacing();

            ImUtil::SliderF("Action Interval",&Settings.tButtCrush.fInterval, 1.0f, 10.0f, "Set the interval at which an attempt is made to do any of the below actions. If an action happens depends on the probabilities set below", "Every %.1f Second(s)");
            ImUtil::SliderF("Chance To Grow",&Settings.tButtCrush.fGrowProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Simple Crush Chance",&Settings.tButtCrush.fFastProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Targeted Crush Chance",&Settings.tButtCrush.fTargetedProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            
            ImGui::Spacing();

            {
                const float Max = 51.0f;
                float* Scale = &Settings.tButtCrush.fGrowUntilScale;
                const bool ShouldBeInf = *Scale > Max - 1.0f;

                if(ShouldBeInf) 
                    *Scale = 10000.0f;

                ImUtil::SliderF("Grow Scale Cap", Scale, 2.0f, Max, "Cap the scale which AI should grow up to. Note this doesn't guarantee the AI will grow to this scale, it just prevents them from growing any larger", ShouldBeInf ? "Infinite" : "%.1fx");
            }
            
            ImGui::EndDisabled();
        }


        ImGui::PopID();
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Grabs",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##Grabs");
        ImUtil::CheckBox("Enable Grabs", &Settings.tGrab.bEnableAction);

        {
            ImGui::BeginDisabled(!Settings.tGrab.bEnableAction);
            ImUtil::SliderF("Start Grabs Probability", &Settings.tGrab.fProbability, 1.0f, 100.0f, "Set the chance for a thigh crush action to be started","%.0f%%");
            
            ImGui::Spacing();

            ImUtil::SliderF("Action Interval",&Settings.tGrab.fInterval, 1.0f, 10.0f, "Set the interval at which an attempt is made to do any of the below grab actions. If a grab action happens depends on the probabilities set below", "Every %.1f Second(s)");
            ImUtil::SliderF("Chance To Throw",&Settings.tGrab.fThrowProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Chance To Vore",&Settings.tGrab.fVoreProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Chance To Crush",&Settings.tGrab.fCrushProb, 0.0f, 100.0f, nullptr, "%.0f%%");
        
            ImGui::Spacing();

            ImUtil::SliderF("Place in Cleavage Chance",&Settings.tGrab.fCleavageProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Cleavage Absorb Chance",&Settings.tGrab.fCleavageAbsorbProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Cleavage Crush Chance",&Settings.tGrab.fCleavageAttackProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Cleavage Suffocate Chance",&Settings.tGrab.fCleavageSuffocateProb, 0.0f, 100.0f, nullptr, "%.0f%%");

            ImGui::EndDisabled();
        }


        ImGui::PopID();
        ImGui::Spacing();
    }
    ImGui::EndDisabled();


}