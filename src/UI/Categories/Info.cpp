#include "Info.hpp"
#include "imgui.h"

#include "src/UI/imGui/ImUtil.hpp"

using namespace UI;

inline void DrawInfo(/* Actor* TargetActor */){
    

    //Animations Installed <--- Make a fancy colored checkmark out of it

    //---- Base Values
    //Current Size (Scale / Height)
    //Max Size (Scale / Height)
    //Aspect Of Giantess%
    //CurrentWeight

    //---- Stat Bonuses
    //DamageResist%
    //BonucCarryWeight
    //BonusSpeed%
    //BonusJumpHeight%
    //BonusDamage%


    //Dummy Values
    float _currentScale = 1.42f;
    float _maxScale = 10.85f;
    //std::string res = std::format("{}/{}({}/{})",_currentScale,_maxScale,_currentScale * 1.82f,_maxScale * 1.82f);

    // float _aspectOfGTS = 43.0f;
    // float _weight = 243.43;

    // float _damageResist = 12.0f;
    // float _carryWeight = 220.0f;
    // float _speed = 113.0f;
    // float _jumpHeight = 103.0f;
    // float _damage = 141.0f;

    ImGui::BeginGroup();

    ImGui::ProgressBar(_currentScale/_maxScale);

    ImGui::EndGroup();

}

void CategoryInfo::Draw(){
    ImUtil::CheckBox("IKnowWhatImDoing",&Settings.IKnowWhatImDoing, "@Sermit, This option enables hidden/debug settings\nThe idea is to keep these hidden so idiots dont kill their game. The settings loader completely ignores these settings if it cant find a hidden config option\nThis Config option must be added manually to the toml like this.\n\n[Hidden]\nIKnowWhatImDoing = true");
}


