#include "AI.hpp"
#include "imgui.h"

#include "src/UI/ImGui/ImUtil.hpp"

using namespace UI;

void CategoryAI::DrawLeft(){
    if(ImGui::CollapsingHeader("AI Interactions",ImUtil::HeaderFlags)){

        ImUtil::CheckBox("Target Player", &Settings.AI.bAllowPlayer, "Allow the AI to target the player");
        ImUtil::CheckBox("Target Other Followers", &Settings.AI.bAllowFollowers, "Allow the AI to target other followers");
        ImUtil::CheckBox("Enable AI Only During Combat",&Settings.AI.bCombatOnly, "Only allow the action AI to be active during combat");
        ImUtil::CheckBox("Enable Actor Panic",&Settings.AI.bPanic, "Enable NPCs panicking when near a large player/follower");

        ImGui::Spacing();
    }
}

void CategoryAI::DrawRight(){
    if(ImGui::CollapsingHeader("AI Actions",ImUtil::HeaderFlags)){

        // ImUtil::CheckBox("Vore", &Settings.AI.bAllowVore);
        // ImUtil::CheckBox("Stomps", &Settings.AI.bAllowStomp);
        // ImUtil::CheckBox("Kicks/Swipes", &Settings.AI.bAllowKick);
        // ImUtil::CheckBox("Hugs", &Settings.AI.bAllowHugs);
        // ImUtil::CheckBox("Butt Crush Simple", &Settings.AI.bAllowButtCrush);
        ImUtil::CheckBox("Butt Crush Targeted", &Settings.AI.bAllowFollowers);
        ImUtil::CheckBox("Thigh Sandwich", &Settings.AI.bAllowFollowers);
        ImUtil::CheckBox("Thigh Crush", &Settings.AI.bAllowFollowers);

        ImGui::Spacing();
    }
}