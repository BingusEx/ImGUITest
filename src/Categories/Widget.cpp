#include "Widget.hpp"

using namespace GTSUi;

void CategoryWidget::Draw(){
    ImGui::Text("CategoryWidget");
}

bool CategoryWidget::Load(){
    return true;
}

bool CategoryWidget::Save(){
    return true;
}

inline void DrawInfo(/*Actor* TargetActor */){

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
