#include "AI.hpp"
#include "imgui.h"

#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

void CategoryAI::DrawLeft(){

    if(ImGui::CollapsingHeader("Action AI Settings",ImUtil::HeaderFlags)){
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

        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Misc Settings",ImUtil::HeaderFlags)){
        ImUtil::CheckBox("Actors Panic", &Settings.bPanic, "Toggle wether other NPCs should panic when near a GTS");
        ImGui::Spacing();
    }

}

void CategoryAI::DrawRight(){

    ImGui::BeginDisabled(!Settings.bEnableActionAI);

    ImUtil_Unique {

        if(ImGui::CollapsingHeader("Vore",ImGuiTreeNodeFlags_Bullet)){
            ImUtil::CheckBox("Enable Vore", &Settings.Vore.bEnableAction);
            ImUtil::SliderF("Vore Probability", &Settings.Vore.fProbability, 1.0f, 100.0f, "Set the chance for vore to happen","%.0f%%",!Settings.Vore.bEnableAction);
            ImGui::Spacing();
        }
    }

    ImUtil_Unique {

        if(ImGui::CollapsingHeader("Stomps",ImGuiTreeNodeFlags_Bullet)){
            ImUtil::CheckBox("Enable Stomps", &Settings.Stomp.bEnableAction);
            ImUtil::SliderF("Stomp Probability", &Settings.Stomp.fProbability, 1.0f, 100.0f, "Set the chance for stomps to happen","%.0f%%",!Settings.Stomp.bEnableAction);
            ImGui::Spacing();
        }
    }

    ImUtil_Unique {

        if(ImGui::CollapsingHeader("Kicks / Swipes",ImGuiTreeNodeFlags_Bullet)){
            ImUtil::CheckBox("Enable Kicks / Swipes", &Settings.KickSwipe.bEnableAction);
            ImUtil::SliderF("Kick / Swipe Probability", &Settings.KickSwipe.fProbability, 1.0f, 100.0f, "Set the chance for Kicks and swipes to happen","%.0f%%",!Settings.KickSwipe.bEnableAction);
            ImGui::Spacing();
        }
    }

    ImUtil_Unique {

        if(ImGui::CollapsingHeader("Thigh Sandwich",ImGuiTreeNodeFlags_Bullet)){
            ImUtil::CheckBox("Enable Thigh Sandwich", &Settings.ThighSandwich.bEnableAction);

            {
                ImGui::BeginDisabled(!Settings.ThighSandwich.bEnableAction);
                ImUtil::SliderF("Thigh Sandwich Probability", &Settings.ThighSandwich.fProbability, 1.0f, 100.0f, "Set the chance for a thigh sandwich action to be started","%.0f%%");
                            
                ImGui::Spacing();

                ImUtil::SliderF("Action Interval",&Settings.ThighSandwich.fInterval, 1.0f, 5.0f, "Set the interval at which an attempt is made to attack. If an attack happens depends on the probabilities set below", "Every %.1f Second(s)");
                ImUtil::SliderF("Heavy Attack Chance",&Settings.ThighSandwich.fProbabilityHeavy, 0.0f, 100.0f, nullptr, "%.0f%%");
                ImUtil::SliderF("Light Attack Chance",&Settings.ThighSandwich.fProbabilityLight, 0.0f, 100.0f, nullptr, "%.0f%%");
                
                ImGui::EndDisabled();
            }
            ImGui::Spacing();
        }
    }

    ImUtil_Unique {

        if(ImGui::CollapsingHeader("Thigh Crush",ImGuiTreeNodeFlags_Bullet)){

            ImUtil::CheckBox("Enable Thigh Crush", &Settings.ThighCrush.bEnableAction);
            
            {
                ImGui::BeginDisabled(!Settings.ThighCrush.bEnableAction);
                ImUtil::SliderF("Thigh Crush Probability", &Settings.ThighCrush.fProbability, 1.0f, 100.0f, "Set the chance for a thigh crush action to be started","%.0f%%");
                
                ImGui::Spacing();

                ImUtil::SliderF("Action Interval",&Settings.ThighCrush.fInterval, 1.0f, 10.0f, "Set the interval at which an attempt is made to attack. If an attack happens depends on the probabilities set below", "Every %.1f Second(s)");
                ImUtil::SliderF("Attack Chance",&Settings.ThighCrush.fProbabilityHeavy, 0.0f, 100.0f, nullptr, "%.0f%%");
                
                ImGui::EndDisabled();
            }

            ImGui::Spacing();
        }
    }

    ImUtil_Unique {

        if(ImGui::CollapsingHeader("Hugs",ImGuiTreeNodeFlags_Bullet)){

            ImUtil::CheckBox("Enable Hugs", &Settings.Hugs.bEnableAction);

            {
                ImGui::BeginDisabled(!Settings.Hugs.bEnableAction);
                ImUtil::SliderF("Start Hugs Probability", &Settings.Hugs.fProbability, 1.0f, 100.0f, "Set the chance for a thigh crush action to be started","%.0f%%");
                
                ImGui::Spacing();

                ImUtil::CheckBox("Allow Killing Followers", &Settings.Hugs.bKillFollowers);
                ImUtil::CheckBox("Allow Killing Friendlies", &Settings.Hugs.bKillFriendlies);
                ImUtil::CheckBox("Stop After Health Is Full", &Settings.Hugs.bStopAtFullHP, "Should the follower continue hugging someone after hug healing them to full HP");

                ImGui::Spacing();

                ImUtil::SliderF("Action Interval",&Settings.Hugs.fInterval, 1.0f, 10.0f, "Set the interval at which an attempt is made to do any of the below hug actions. If a hug action happens depends on the probabilities set below", "Every %.1f Second(s)");
                ImUtil::SliderF("Chance To Heal",&Settings.Hugs.fHealProb, 0.0f, 100.0f, nullptr, "%.0f%%");
                ImUtil::SliderF("Chance To Kill",&Settings.Hugs.fKillProb, 0.0f, 100.0f, nullptr, "%.0f%%");
                ImUtil::SliderF("Chance To Shrink",&Settings.Hugs.fShrinkProb, 0.0f, 100.0f, nullptr, "%.0f%%");
                
                ImGui::EndDisabled();
            }
            ImGui::Spacing();
        }
    }

    ImUtil_Unique {

        if(ImGui::CollapsingHeader("Butt Crush",ImGuiTreeNodeFlags_Bullet)){

            ImUtil::CheckBox("Enable Butt Crush", &Settings.ButtCrush.bEnableAction);

            {
                ImGui::BeginDisabled(!Settings.ButtCrush.bEnableAction);
                ImUtil::SliderF("Start Butt Crush Probability", &Settings.ButtCrush.fProbability, 1.0f, 100.0f, "Set the chance for a thigh crush action to be started","%.0f%%");
                
                ImGui::Spacing();

                ImUtil::SliderF("Action Interval",&Settings.ButtCrush.fInterval, 1.0f, 10.0f, "Set the interval at which an attempt is made to do any of the below actions. If an action happens depends on the probabilities set below", "Every %.1f Second(s)");
                ImUtil::SliderF("Chance To Grow",&Settings.ButtCrush.fGrowProb, 0.0f, 100.0f, nullptr, "%.0f%%");
                ImUtil::SliderF("Simple Crush Chance",&Settings.ButtCrush.fFastProb, 0.0f, 100.0f, nullptr, "%.0f%%");
                ImUtil::SliderF("Targeted Crush Chance",&Settings.ButtCrush.fTargetedProb, 0.0f, 100.0f, nullptr, "%.0f%%");
                
                ImGui::Spacing();

                {
                    const float Max = 51.0f;
                    float* Scale = &Settings.ButtCrush.fGrowUntilScale;
                    const bool ShouldBeInf = *Scale > Max - 1.0f;

                    if(ShouldBeInf) 
                        *Scale = 10000.0f;

                    ImUtil::SliderF("Grow Scale Cap", Scale, 2.0f, Max, "Cap the scale which AI should grow up to. Note this doesn't guarantee the AI will grow to this scale, it just prevents them from growing any larger", ShouldBeInf ? "Infinite" : "%.1fx");
                }
                
                ImGui::EndDisabled();
            }

            ImGui::Spacing();
        }
    }

    ImUtil_Unique {

        if(ImGui::CollapsingHeader("Grabs",ImGuiTreeNodeFlags_Bullet)){

            ImUtil::CheckBox("Enable Grabs", &Settings.Grab.bEnableAction);

            {
                ImGui::BeginDisabled(!Settings.Grab.bEnableAction);
                ImUtil::SliderF("Start Grabs Probability", &Settings.Grab.fProbability, 1.0f, 100.0f, "Set the chance for a thigh crush action to be started","%.0f%%");
                
                ImGui::Spacing();

                ImUtil::SliderF("Action Interval",&Settings.Grab.fInterval, 1.0f, 10.0f, "Set the interval at which an attempt is made to do any of the below grab actions. If a grab action happens depends on the probabilities set below", "Every %.1f Second(s)");
                ImUtil::SliderF("Chance To Throw",&Settings.Grab.fThrowProb, 0.0f, 100.0f, nullptr, "%.0f%%");
                ImUtil::SliderF("Chance To Vore",&Settings.Grab.fVoreProb, 0.0f, 100.0f, nullptr, "%.0f%%");
                ImUtil::SliderF("Chance To Crush",&Settings.Grab.fCrushProb, 0.0f, 100.0f, nullptr, "%.0f%%");
            
                ImGui::Spacing();

                ImUtil::SliderF("Place in Cleavage Chance",&Settings.Grab.fCleavageProb, 0.0f, 100.0f, nullptr, "%.0f%%");
                ImUtil::SliderF("Cleavage Absorb Chance",&Settings.Grab.fCleavageAbsorbProb, 0.0f, 100.0f, nullptr, "%.0f%%");
                ImUtil::SliderF("Cleavage Crush Chance",&Settings.Grab.fCleavageAttackProb, 0.0f, 100.0f, nullptr, "%.0f%%");
                ImUtil::SliderF("Cleavage Suffocate Chance",&Settings.Grab.fCleavageSuffocateProb, 0.0f, 100.0f, nullptr, "%.0f%%");

                ImGui::EndDisabled();
            }

            ImGui::Spacing();
        }
        ImGui::EndDisabled();
    }

}