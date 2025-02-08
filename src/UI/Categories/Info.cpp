#include "Info.hpp"
#include "imgui.h"

#include "src/UI/imGui/ImUtil.hpp"
#include "src/UI/Windows/GTSInfo.hpp"
#include "src/UI/ImGui/ImFontManager.hpp"

using namespace UI;

void CategoryInfo::Draw(){

    //Get Curr Follower Count;
    const int TempFollowerCount = 1;
    const float DivWidth = (ImGui::GetContentRegionAvail().x / (TempFollowerCount + 1)) - (ImGui::GetStyle().CellPadding.x + ImGui::GetStyle().FramePadding.x + ImGui::GetStyle().WindowPadding.x);

    ImGui::BeginChild("PlayerInfo",{DivWidth,0},true,true);
    {

        ImGui::PushFont(ImFontManager::GetFont("widgettitle"));

        //Player Singleton -> Get Name;
        ImGui::Text("PLAYERNAME");

        ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal, 1.0f);

        ImGui::PopFont();


        ImGui::PushFont(ImFontManager::GetFont("widgetbody"));
        DrawGTSInfo((GTSInfoFeatures)UINT32_MAX);
        ImGui::PopFont();

    }
    ImGui::EndChild();

    //This should be a foreach loop for every follower

    for (int i = TempFollowerCount; i > 0; i--){
        ImUtil::SeperatorV();
        ImGui::BeginChild(i + 1,{DivWidth,0});
        ImGui::PushFont(ImFontManager::GetFont("widgettitle"));
        ImGui::Text("FOLOWER %d", i);
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal, 1.0f);
        ImGui::PopFont();
        ImGui::PushFont(ImFontManager::GetFont("widgetbody"));
        DrawGTSInfo((GTSInfoFeatures)UINT32_MAX);
        ImGui::PopFont();
        ImGui::EndChild();

    }

}


