#include "Balance.hpp"
#include "imgui.h"
#include "src/UI/ImGui/ImUtil.hpp"
#include "fmt/format.h"

using namespace UI;

void CategoryBalance::DrawLeft(){

    if(ImGui::CollapsingHeader("Balance Mode",ImUtil::HeaderFlags)){ 
        ImUtil::CheckBox("Enable Balance Mode",&Settings.Balance.bBalanceMode, "TODO: Explain What Balance mode does");

        ImGui::BeginDisabled(!Settings.Balance.bBalanceMode);

        ImUtil::SliderF("Size Gain Penalty",&Settings.Balance.fBMSizeGainPenaltyMult, 1.0f, 10.0f,"Penalty multiplier to all size gain if balance mode is enabled","%.2fx");
        ImUtil::SliderF("Shrink Rate",&Settings.Balance.fBMShrinkRate, 1.0f, 10.0f,"TODO: Description","%.2fx");
        ImUtil::SliderF("Shrink Rate Combat",&Settings.Balance.fBMShrinkRateCombat, 0.01f, 1.0f,"TODO: Description","%.2fx");
        ImUtil::SliderF("Shrink On Hit",&Settings.Balance.fBMShrinkOnHitMult, 0.01f, 2.0f,"TODO: Description","%.2fx");
        
        ImGui::EndDisabled();
        
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Misc Settings",ImUtil::HeaderFlags)){ 
        
        ImUtil::CheckBox("Player Size Damage Immunity",&Settings.Balance.bPlayerFriendlyImmunity,"Should the player recieve size related damage");
        ImUtil::CheckBox("Followers Size Damage Immunity",&Settings.Balance.bFollowerFriendlyImmunity,"Should followers recieve size related damage");
        ImUtil::CheckBox("Allow Friendly Stagger",&Settings.Balance.bAllowFriendlyStagger,"Should the player and followers stagger / ragdoll due to others' size");
        ImUtil::CheckBox("Allow Stagger",&Settings.Balance.bAllowOthersStagger, "Should other NPCs stagger / ragdoll due to others' size");
        
        ImGui::Spacing();
    }

}

void CategoryBalance::DrawRight(){

    if(ImGui::CollapsingHeader("Size Options",ImUtil::HeaderFlags)){ 

        if(ImUtil::ComboEx<SizeMode>("Size Gain Mode",Settings.Balance.sSizeMode,"TODO:Describe Me")){
            //TODO These should be enum compares....
            if(Settings.Balance.sSizeMode == "kNormal") Settings.Balance.fSpellEfficiency = 0.55f;
            if(Settings.Balance.sSizeMode == "kMassBased") Settings.Balance.fSpellEfficiency = 0.33f;
        }

        ImUtil::SliderF("Efficiency Mult",&Settings.Balance.fSpellEfficiency,0.1f, 1.0f,"Adjust the global multiplier for all size gains / losses","%.2fx");
        
        ImGui::Spacing();
    }

    const bool temp = true;

    if(ImUtil::ConditionalHeader("Size Limits", "Requires \"Colossal Growth\" Perk", temp)){ 
        
        //Assumed Max From Audio > 128x Is Mega. Seems Like good compromise for the slider resolution
        const float Max = 129.0f; 
        const float Min = 0.0;

        {   //Player Size
            float* Scale = &Settings.Balance.fMaxPlayerSize;
            const bool ShouldBeInf = *Scale > Max - 1.0f;
            const bool ShouldBeAuto = *Scale < Min + 1.0f;

            std::string _Frmt = "";

            if(ShouldBeInf) {
                _Frmt = "Infinite";
                *Scale = 10000.0f;
            }
            else if(ShouldBeAuto){
                //TODO Implement this shit....
                const float SkillBasedLimit = 9.13f;
                //Getting Size needs to be completely redone, Its done in papyrus currently AAAAAAAAAAAARRRRRRHG!!!!!
                _Frmt = fmt::format("Skill Based [{}x]", SkillBasedLimit);
                *Scale = 0.0f;
            }
            else{
                _Frmt = "%.1fx";
            }

            std::string ToolTip = fmt::format("Change the maximum player size\nHigher than {:.0f}x scale disables the limit entirely\nBelow 1.0x the limit is based on your skill level and perks", Max - 1.0f);

            ImUtil::SliderF("Max Player Size", Scale, Min, Max, ToolTip.c_str(),_Frmt.c_str());
            
        }

        {   //Max Follower Size
            
            float* Scale = &Settings.Balance.fMaxFollowerSize;
            const bool ShouldBeInf = *Scale > Max - 1.0f;
            const bool ShouldBeAuto = *Scale < Min + 1.0f;

            std::string _Frmt = "";
            if(ShouldBeInf) {
                _Frmt = "Infinite";
                *Scale = 10000.0f;
            }
            else if(ShouldBeAuto){
                //TODO Implement this shit.... Whatever you end up doing here needs to be done for followers too
                const float PlayersLimit = 9.13f;
                //Getting Size needs to be completely redone, Its done in papyrus currently AAAAAAAAAAAARRRRRRHG!!!!!
                _Frmt = fmt::format("Based on Player [{}x]", PlayersLimit);
                *Scale = 0.0f;
            }
            else{
                _Frmt = "%.1fx";
            }

            std::string ToolTip = fmt::format("Change the maximum follower size\nHigher than {:.0f}x scale disables the limit entirely\nBelow 1.0x will base the limit on whatever the player's limit currently is", Max - 1.0f);
            ImUtil::SliderF("Max Follower Size", Scale, Min, Max, ToolTip.c_str(),_Frmt.c_str());
        }
        
        {   //Other NPC Max Size
            
            float* Scale = &Settings.Balance.fMaxOtherSize;
            const bool ShouldBeInf = *Scale > Max - 1.0f;
            const bool ShouldBeAuto = *Scale < Min + 1.0f;

            std::string _Frmt = "";
            if(ShouldBeInf) {
                _Frmt = "Infinite";
                *Scale = 10000.0f;
            }
            else if(ShouldBeAuto){
                //TODO Implement this shit.... Whatever you end up doing here needs to be done for other npc's too.
                const float NPCsLimit = 9.13f;
                //Getting Size needs to be completely redone, Its done in papyrus currently AAAAAAAAAAAARRRRRRHG!!!!!
                _Frmt = fmt::format("Based on Player [{}x]", NPCsLimit);
                *Scale = 0.0f;
            }
            else{
                _Frmt = "%.1fx";
            }

            std::string ToolTip = fmt::format("Change the maximum size for non follower NPCs\nHigher than {:.0f}x scale disables the limit entirely\nBelow 1.0x will base the limit on whatever the player's limit currently is", Max - 1.0f);
            ImUtil::SliderF("Max NPC Size", Scale, Min, Max, ToolTip.c_str(),_Frmt.c_str());
        }
        
        ImGui::Spacing();
    }

    if(ImGui::CollapsingHeader("Multipiers",ImUtil::HeaderFlags)){ 

        ImUtil::SliderF("Size Damage Mult",&Settings.Balance.fSizeDamageMult,0.1f, 2.0f,"Changes the ammount of damage size related actions do","%.2fx");
        ImUtil::SliderF("Damage Mult",&Settings.Balance.fStatBonusDamageMult,0.1f, 2.0f,"Changes the ammount of damage increase gained for normal attacks","%.2fx");
        ImUtil::SliderF("Experience Mult",&Settings.Balance.fExpMult,0.1f, 5.0f,"Adjust the speed at which you gain","%.2fx");
        
        ImGui::Spacing();
    }

}