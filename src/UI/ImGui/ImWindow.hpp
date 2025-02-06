#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_internal.h"

#include "src/Config.hpp"

namespace UI {

    class ImWindow {

        private:

        public:

        enum WindowAnchor {
            kTopLeft,
            kTopRight,
            kCenter,
            kBottomLeft,
            kBottomRight,
        };

        enum WindowMessage {
            kUpdateStyle,
        };

        //Internal Flags
        bool Show = false;
        bool ConsumeInput = false;
        bool DrawBG = true;
        
        float FixedScaleMax = 95.0f;                //Max scale for the window
        float FixedScaleMin = 40.0f;                //Min scale for the window
        
        WindowAnchor AnchorPos = WindowAnchor::kCenter;

        std::string Name = "Default";   //Imgui Window Name (Must be unique)
        std::string Title = "Default";  //Window Title
        ImGuiWindowFlags flags = ImGuiWindowFlags_None | ImGuiWindowFlags_NavFlattened;

        virtual ~ImWindow() noexcept = default;

        virtual void Draw() = 0;
        virtual inline bool ShouldShow() = 0;
        virtual inline float GetAlpha() = 0;

        ImVec2 GetAnchorPos(WindowAnchor a_position, ImVec2 a_padding);
    };
}