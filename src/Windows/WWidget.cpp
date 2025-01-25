#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <string>
#include <format>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <functional> // For std::function

#include "WWidget.hpp"

//Helper libs
#include "src/ImCategory.hpp"
#include "src/ImUtil.hpp"
#include "src/ImFont.hpp"
#include "src/ImStyle.hpp"

//categories
#include "src/Categories/Gameplay.hpp"
#include "src/Categories/Info.hpp"
#include "src/Categories/Interface.hpp"

using namespace GTSUi;

inline void DrawInfo(/*Actor* TargetActor */){

    //Dummy Values
    float _currentScale = 1.42f;
    float _maxScale = 10.85f;
    ImGui::Text("Height");
    std::string res = std::format("{:.2f}/{:.2f}",_currentScale * 1.82f,_maxScale * 1.82f);

    float _aspectOfGTS = 43.0f;
    float _weight = 243.43;

    float _damageResist = 12.0f;
    float _carryWeight = 220.0f;
    float _speed = 113.0f;
    float _jumpHeight = 103.0f;
    float _damage = 141.0f;


    ImGui::BeginGroup();

    ImGui::PushFont(ImFontManager::GetSingleton().GetFont("widgettitle"));

    ImGui::ProgressBar(_currentScale/_maxScale, ImVec2(0.0f,0.0f), res.c_str());
    ImGui::Text("Aspect of GTS: %.2f", _aspectOfGTS);
    ImGui::Text("Weight: %.2f", _weight);
    ImGui::Text("Damage Resist: %.2f", _damageResist);
    ImGui::Text("Carry Weight: %.2f", _carryWeight);
    ImGui::Text("Speed: %.2f", _speed);
    ImGui::Text("Jump Height: %.2f", _jumpHeight);
    ImGui::Text("Damage: %.2f", _damage);

    ImGui::PopFont();

    ImGui::EndGroup();

}


//Do All your Init Stuff here
//Note: Dont do any calls to the imgui api here as the window is not yet created
WWidget::WWidget() {

    Title = "Player Info";
    Name = "WidgetWindow";
    Show = true;
    Fixed = true;
    flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
    AnchorPos = ImWindow::WindowAnchor::kTopRight;
    FixedScale = 10.0f;
}

void WWidget::Draw() {

    if(Fixed){
        ImGui::SetWindowPos(GetAnchorPos(AnchorPos, CornerPadding));
    }

    {  // Title

        ImGui::PushFont(ImFontManager::GetSingleton().GetFont("widgettitle"));
        ImGui::Text(Title.c_str());
        ImGui::PopFont();


    }
    DrawInfo();

    //Auto Scale to fit contents
    //TODO needs padding
    ImGui::SetWindowSize({0.0f,0.0f});

}


