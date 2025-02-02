#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "magic_enum/magic_enum.hpp"
#include "WindowStatus.hpp"

//categories
#include "src/UI/ImGui/ImUtil.hpp"
using namespace UI;

inline void DrawInfo(/*Actor* TargetActor */){

    // ImGui::PushFont(ImFontManager::GetSingleton().GetFont("widgettitle"));
    // ImGui::Text("Arial");
    // ImGui::PopFont();

    ImGui::PushFont(ImFontManager::GetSingleton().GetFont("widgetbody"));

    //Dummy Values
    float _currentScale = 1.42f;
    float _maxScale = 10.85f;
    std::string res = std::format("{:.2f}m",_currentScale * 1.82f);

    float _aspectOfGTS = 43.0f;
    float _weight = 243.43f;

    float _damageResist = 12.0f;
    float _carryWeight = 220.0f;
    float _speed = 113.0f;
    float _jumpHeight = 103.0f;
    float _damage = 141.0f;


    ImGui::BeginGroup();
    ImGui::ProgressBar(_currentScale/_maxScale, ImVec2(200.0f,0.0f), res.c_str());
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
WindowStatus::WindowStatus() {

    Title = "Player Info";
    Name = "WidgetWindow";
    this->flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoNavInputs;
    AnchorPos = ImWindow::WindowAnchor::kTopRight;
}

void WindowStatus::Draw() {


    flags = (Settings.UI.wStatus.bLock ? (flags | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove) : (flags & ~ImGuiWindowFlags_NoResize & ~ImGuiWindowFlags_NoMove));

    //Handle Fixed Position and Size
    if(Settings.UI.wStatus.bLock){
        //X,Y
        const ImVec2 Offset {Settings.UI.wStatus.f2Offset[0], Settings.UI.wStatus.f2Offset[1]};
        ImGui::SetWindowPos(GetAnchorPos(Config::StringToEnum<ImWindow::WindowAnchor>(Settings.UI.wStatus.sAnchor), Offset));
        
    }
    

    {  // Title


        
    }
    DrawInfo();

    //Auto Scale to fit contents
    //TODO needs padding
    ImGui::SetWindowSize({0.0f,0.0f});

}


