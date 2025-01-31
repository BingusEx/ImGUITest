#include "AI.hpp"
#include "imgui.h"

#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

void CategoryAI::DrawLeft(){
    if(ImGui::CollapsingHeader("Action AI Settings",ImUtil::HeaderFlags)){
        ImGui::PushID("AI##Settings");
        ImUtil::CheckBox("Enable AI",&Settings.AI.bEnableActionAI, "Enable / Disable the action AI");

        {
            ImGui::BeginDisabled(!Settings.AI.bEnableActionAI);
            
            ImUtil::SliderF("Try To Start A New Action",&Settings.AI.fMasterTimer, 2.0f, 15.0f, "Set the time interval NPCs should attempt to start a new GTS action","Every %.1f Seconds");
            ImGui::Spacing();
            ImUtil::CheckBox("Target Player", &Settings.AI.bAllowPlayer, "Allow the AI to target the player");
            ImUtil::CheckBox("Target Other Followers", &Settings.AI.bAllowFollowers, "Allow the AI to target other followers");
            ImUtil::CheckBox("Enable AI Only During Combat",&Settings.AI.bCombatOnly, "Only allow the action AI to be active during combat");
            
            ImGui::EndDisabled();
        }


        ImGui::PopID();
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Misc Settings",ImUtil::HeaderFlags)){
        ImGui::PushID("AI##Settings");
        ImUtil::CheckBox("Actors Panic", &Settings.AI.bPanic, "Toggle wether other NPCs should panic when near a GTS");
        ImGui::PopID();
        ImGui::Spacing();
    }

}

void CategoryAI::DrawRight(){

    ImGui::BeginDisabled(!Settings.AI.bEnableActionAI);

    if(ImGui::CollapsingHeader("Vore",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##Vore");
        ImUtil::CheckBox("Enable Vore", &Settings.AI.tVore.bEnableAction);
        ImUtil::SliderF("Vore Probability", &Settings.AI.tVore.fProbability, 1.0f, 100.0f, "Set the chance for vore to happen","%.0f%%",!Settings.AI.tVore.bEnableAction);
        ImGui::PopID();
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Stomps",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##Stomps");
        ImUtil::CheckBox("Enable Stomps", &Settings.AI.tStomp.bEnableAction);
        ImUtil::SliderF("Stomp Probability", &Settings.AI.tStomp.fProbability, 1.0f, 100.0f, "Set the chance for stomps to happen","%.0f%%",!Settings.AI.tStomp.bEnableAction);
        ImGui::PopID();
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Kicks / Swipes",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##KickSwipe");
        ImUtil::CheckBox("Enable Kicks / Swipes", &Settings.AI.tKickSwipe.bEnableAction);
        ImUtil::SliderF("Kick / Swipe Probability", &Settings.AI.tKickSwipe.fProbability, 1.0f, 100.0f, "Set the chance for Kicks and swipes to happen","%.0f%%",!Settings.AI.tKickSwipe.bEnableAction);
        ImGui::PopID();
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Thigh Sandwich",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##ThighSandwich");
        ImUtil::CheckBox("Enable Thigh Sandwich", &Settings.AI.tThighSandwich.bEnableAction);

        {
            ImGui::BeginDisabled(!Settings.AI.tThighSandwich.bEnableAction);
            ImUtil::SliderF("Thigh Sandwich Probability", &Settings.AI.tThighSandwich.fProbability, 1.0f, 100.0f, "Set the chance for a thigh sandwich action to be started","%.0f%%");
                        
            ImGui::Spacing();

            ImUtil::SliderF("Action Interval",&Settings.AI.tThighSandwich.fInterval, 1.0f, 5.0f, "Set the interval at which an attempt is made to attack. If an attack happens depends on the probabilities set below", "Every %.1f Second(s)");
            ImUtil::SliderF("Heavy Attack Chance",&Settings.AI.tThighSandwich.fProbabilityHeavy, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Light Attack Chance",&Settings.AI.tThighSandwich.fProbabilityLight, 0.0f, 100.0f, nullptr, "%.0f%%");
            
            ImGui::EndDisabled();
        }


        ImGui::PopID();
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Thigh Crush",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##ThighCrush");
        ImUtil::CheckBox("Enable Thigh Crush", &Settings.AI.tThighCrush.bEnableAction);
        
        {
            ImGui::BeginDisabled(!Settings.AI.tThighCrush.bEnableAction);
            ImUtil::SliderF("Thigh Crush Probability", &Settings.AI.tThighCrush.fProbability, 1.0f, 100.0f, "Set the chance for a thigh crush action to be started","%.0f%%");
            
            ImGui::Spacing();

            ImUtil::SliderF("Action Interval",&Settings.AI.tThighCrush.fInterval, 1.0f, 10.0f, "Set the interval at which an attempt is made to attack. If an attack happens depends on the probabilities set below", "Every %.1f Second(s)");
            ImUtil::SliderF("Attack Chance",&Settings.AI.tThighCrush.fProbabilityHeavy, 0.0f, 100.0f, nullptr, "%.0f%%");
            
            ImGui::EndDisabled();
        }


        ImGui::PopID();
        ImGui::Spacing();
    }


    if(ImGui::CollapsingHeader("Hugs",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##Hugs");
        ImUtil::CheckBox("Enable Hugs", &Settings.AI.tHugs.bEnableAction);

        {
            ImGui::BeginDisabled(!Settings.AI.tHugs.bEnableAction);
            ImUtil::SliderF("Start Hugs Probability", &Settings.AI.tHugs.fProbability, 1.0f, 100.0f, "Set the chance for a thigh crush action to be started","%.0f%%");
            
            ImGui::Spacing();

            ImUtil::CheckBox("Allow Killing Followers", &Settings.AI.tHugs.bKillFollowers);
            ImUtil::CheckBox("Allow Killing Friendlies", &Settings.AI.tHugs.bKillFriendlies);
            ImUtil::CheckBox("Stop After Health Is Full", &Settings.AI.tHugs.bStopAtFullHP, "Should the follower continue hugging someone after hug healing them to full HP");

            ImGui::Spacing();

            ImUtil::SliderF("Action Interval",&Settings.AI.tHugs.fInterval, 1.0f, 10.0f, "Set the interval at which an attempt is made to do any of the below hug actions. If a hug action happens depends on the probabilities set below", "Every %.1f Second(s)");
            ImUtil::SliderF("Chance To Heal",&Settings.AI.tHugs.fHealProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Chance To Kill",&Settings.AI.tHugs.fKillProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Chance To Shrink",&Settings.AI.tHugs.fShrinkProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            
            ImGui::EndDisabled();
        }


        ImGui::PopID();
        ImGui::Spacing();
    }


    if(ImGui::CollapsingHeader("Butt Crush",ImGuiTreeNodeFlags_Bullet)){
        ImGui::PushID("AI##Butt");
        ImUtil::CheckBox("Enable Butt Crush", &Settings.AI.tButtCrush.bEnableAction);

        {
            ImGui::BeginDisabled(!Settings.AI.tButtCrush.bEnableAction);
            ImUtil::SliderF("Start Butt Crush Probability", &Settings.AI.tButtCrush.fProbability, 1.0f, 100.0f, "Set the chance for a thigh crush action to be started","%.0f%%");
            
            ImGui::Spacing();

            ImUtil::SliderF("Action Interval",&Settings.AI.tButtCrush.fInterval, 1.0f, 10.0f, "Set the interval at which an attempt is made to do any of the below actions. If an action happens depends on the probabilities set below", "Every %.1f Second(s)");
            ImUtil::SliderF("Chance To Grow",&Settings.AI.tButtCrush.fGrowProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Simple Crush Chance",&Settings.AI.tButtCrush.fFastProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Targeted Crush Chance",&Settings.AI.tButtCrush.fTargetedProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            
            ImGui::Spacing();

            {
                const float Max = 51.0f;
                float* Scale = &Settings.AI.tButtCrush.fGrowUntilScale;
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
        ImUtil::CheckBox("Enable Grabs", &Settings.AI.tGrab.bEnableAction);

        {
            ImGui::BeginDisabled(!Settings.AI.tGrab.bEnableAction);
            ImUtil::SliderF("Start Grabs Probability", &Settings.AI.tGrab.fProbability, 1.0f, 100.0f, "Set the chance for a thigh crush action to be started","%.0f%%");
            
            ImGui::Spacing();

            ImUtil::SliderF("Action Interval",&Settings.AI.tGrab.fInterval, 1.0f, 10.0f, "Set the interval at which an attempt is made to do any of the below grab actions. If a grab action happens depends on the probabilities set below", "Every %.1f Second(s)");
            ImUtil::SliderF("Chance To Throw",&Settings.AI.tGrab.fThrowProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Chance To Vore",&Settings.AI.tGrab.fVoreProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Chance To Crush",&Settings.AI.tGrab.fCrushProb, 0.0f, 100.0f, nullptr, "%.0f%%");
        
            ImGui::Spacing();

            ImUtil::SliderF("Place in Cleavage Chance",&Settings.AI.tGrab.fCleavageProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Cleavage Absorb Chance",&Settings.AI.tGrab.fCleavageAbsorbProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Cleavage Crush Chance",&Settings.AI.tGrab.fCleavageAttackProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            ImUtil::SliderF("Cleavage Suffocate Chance",&Settings.AI.tGrab.fCleavageSuffocateProb, 0.0f, 100.0f, nullptr, "%.0f%%");

            ImGui::EndDisabled();
        }


        ImGui::PopID();
        ImGui::Spacing();
    }
    ImGui::EndDisabled();


}