#include "ImCategorySplit.hpp"
#include "ImUtil.hpp"
#include "src/Config.hpp"

using namespace UI;

void ImCategorySplit::Draw() {

    constexpr float wMult = 0.55f;
    const auto WMult = Config::GetSingleton().UI.fItemWidth;
    {   //Left
        const std::string SpltNam = title + "##SLeft";
        ImGui::BeginChild(SpltNam.c_str(), ImVec2(ImGui::GetContentRegionAvail().x / splitRatio, 0), ImGuiChildFlags_AlwaysUseWindowPadding);
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * WMult);
        DrawLeft();
        ImGui::PopItemWidth();
        ImGui::EndChild();
    }

    ImGui::SameLine(0.0,8.0f);
    ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical, 1.f);
    ImGui::SameLine(0.0,8.0f);

    {   //Right
        const std::string SpltNam = title + "##SRight";
        ImGui::BeginChild(SpltNam.c_str(), ImVec2(0, 0), ImGuiChildFlags_AlwaysUseWindowPadding);
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * WMult);
        DrawRight();
        ImGui::PopItemWidth();
        ImGui::EndChild();
    }

    //ImGui::PopItemWidth();

}