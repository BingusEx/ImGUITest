#pragma once

#include "src/UI/ImGUI/ImCategory.hpp"
#include "imgui.h"

namespace UI {

    //Interface for a splitter window
    class ImCategorySplit : public ImCategory {
        private:
        const ImGuiChildFlags flags = ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY;
        const float splitRatio = 2.17f;

        void Draw() override;

        public:
        virtual ~ImCategorySplit() override = default;
        virtual void DrawLeft() = 0;
        virtual void DrawRight() = 0;
    };
}