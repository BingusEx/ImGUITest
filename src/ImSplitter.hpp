#pragma once

#include "src\ImWindow.hpp"

//Interface for a splitter window
class ImCategorySplitter : public ImCategory {
    private:
    const ImGuiChildFlags flags = ImGuiChildFlags_AlwaysAutoResize;
    const float splitRatio = 2.2f;

    public:
    virtual ~ImCategorySplitter() = default;

    virtual void DrawLeft() = 0;
    virtual void DrawRight() = 0;

    
    void Draw() override {
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
};
