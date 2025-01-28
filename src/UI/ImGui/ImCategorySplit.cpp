#include "ImCategorySplit.hpp"
#include "ImUtil.hpp"

using namespace UI;

void ImCategorySplit::Draw() {

    {   //Left
        const std::string SpltNam = title + "##SLeft";
        ImGui::BeginChild(SpltNam.c_str(), ImVec2(ImGui::GetContentRegionAvail().x / splitRatio, 0), flags);
        DrawLeft();
        ImGui::EndChild();
    }

    ImUtil::SeperatorV();
    
    {   //Right
        const std::string SpltNam = title + "##SRight";
        ImGui::BeginChild(SpltNam.c_str(), ImVec2(0, 0), flags);
        DrawRight();
        ImGui::EndChild();
    }

}