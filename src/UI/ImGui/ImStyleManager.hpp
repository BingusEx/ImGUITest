#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "src/Config.hpp"

namespace UI {

    //Inspired by Community shaders
    class ImStyleManager {

        private:
        Config& Settings = Config::GetSingleton();
        ImGuiStyle defaultStyle;

        void InitializeDefaultStyle() {
            defaultStyle = ImGuiStyle();
            auto& style = defaultStyle;

            //Rounding
            style.WindowRounding = 1.5f;
            style.TabRounding = 1.5f;
            style.GrabRounding = 0.5f;
            style.FrameRounding = 1.5f;
            style.ScrollbarRounding = 1.5f;

            //Anti-Aliasing
            style.AntiAliasedFill = true;
            style.AntiAliasedLines = true;

            //Borders
            style.WindowBorderSize = 0.0f;
            style.ChildBorderSize = 0.0f;
            style.FrameBorderSize = 0.1f;
            style.ScrollbarSize = 8.0f;

            //Spacing
            style.ItemSpacing.y = 5;

            //Padding
            style.FramePadding = { 4.0f, 4.0f };
            style.CellPadding = { 2.f, 2.f };
        }

        void ApplyAccentColor(ImGuiStyle& style) {
            auto& colors = style.Colors;
            const auto& accent = Settings.UI.f3AccentColor;
            const ImVec4 accentColor = {accent[0], accent[1], accent[2], 0.0f};


            



            // Set accent-based colors
            colors[ImGuiCol_CheckMark] = CalculateContrastColor(accentColor);
            colors[ImGuiCol_PlotHistogram] = accentColor;
            colors[ImGuiCol_SliderGrab] = AdjustAlpha(accentColor, 0.25f);
            colors[ImGuiCol_SliderGrabActive] = AdjustAlpha(accentColor, 0.53f);
            colors[ImGuiCol_Header] = AdjustAlpha(accentColor, 0.15f);
            colors[ImGuiCol_HeaderHovered] = AdjustAlpha(accentColor, 0.1f);
        }






        //Settings.UI.f4AccentColor std::array<float, 4>

        ImGuiStyle GTSStyle = [this]() {
            defaultStyle = ImGuiStyle();

            auto& style = m_defaultStyle;
            auto& colors = style.Colors;

            //Rounding
            style.WindowRounding = 1.5f;
            style.TabRounding = 1.5f;
            style.GrabRounding = 0.5f;
            style.FrameRounding = 1.5f;
            style.ScrollbarRounding = 1.5f;

            //Anti-Aliasing
            style.AntiAliasedFill = true;
            style.AntiAliasedLines = true;

            //Borders
            style.WindowBorderSize = 0.0f;
            style.ChildBorderSize = 0.0f;
            style.FrameBorderSize = 0.1f;
            style.ScrollbarSize = 8.0f;

            //Spacing
            style.ItemSpacing.y = 5;

            //Padding
            style.FramePadding = { 4.0f, 4.0f };
            style.CellPadding = { 2.f, 2.f };

            //Colors
            ImVec4 resizeGripHovered = {1.0f,1.0f,1.0f,0.1f};
            ImVec4 textDisabled = {0.0,0.0,0.0,1.0};
            ImVec4 header{ 1.0f, 1.0f, 1.0f, 0.15f };
            ImVec4 headerHovered = { 1.0f, 1.0f, 1.0f, 0.1f };
            ImVec4 tabHovered{ 0.2f, 0.2f, 0.2f, 1.0f };
            ImVec4 sliderGrab{ 1.0f, 1.0f, 1.0f, 0.245f };
            ImVec4 sliderGrabActive{ 1.0f, 1.0f, 1.0f, 0.531f };
            ImVec4 scrollbarGrab{ 0.31f, 0.31f, 0.31f, 1.0f };
            ImVec4 scrollbarGrabHovered{ 0.41f, 0.41f, 0.41f, 1.0f };
            ImVec4 scrollbarGrabActive{ 0.51f, 0.51f, 0.51f, 1.0f };

            colors[ImGuiCol_WindowBg] = { 0.0f, 0.0f, 0.0f, 0.7f };
            colors[ImGuiCol_ChildBg] = ImVec4();
            colors[ImGuiCol_ScrollbarBg] = ImVec4();
            colors[ImGuiCol_TableHeaderBg] = ImVec4();
            colors[ImGuiCol_TableRowBg] = ImVec4();
            colors[ImGuiCol_TableRowBgAlt] = ImVec4();

            colors[ImGuiCol_Border] = { 0.50f, 0.50f, 0.50f, 0.7f };//Fix
            colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
            colors[ImGuiCol_ResizeGrip] = colors[ImGuiCol_Border];
            colors[ImGuiCol_ResizeGripHovered] = resizeGripHovered;
            colors[ImGuiCol_ResizeGripActive] = colors[ImGuiCol_ResizeGripHovered];

            colors[ImGuiCol_Text] = {1.0,1.0,1.0,1.0};
            colors[ImGuiCol_TextDisabled] = textDisabled;

            colors[ImGuiCol_FrameBg] = {0.0,0.0,0.0,1.0};//Fix

            colors[ImGuiCol_FrameBgHovered] = colors[ImGuiCol_FrameBg];
            colors[ImGuiCol_FrameBgActive] = colors[ImGuiCol_FrameBg];

            //TODO Make some of these configurable
            //TODO Uppon doing this add a way to calc the inverse text color
            //To make light / dark accent colors readable.
            colors[ImGuiCol_PlotHistogram] = {0.0f,0.6f,0.6f,1.0f};

            colors[ImGuiCol_SliderGrab] = sliderGrab;
            colors[ImGuiCol_SliderGrabActive] = sliderGrabActive;

            colors[ImGuiCol_Header] = header;
            colors[ImGuiCol_HeaderActive] = colors[ImGuiCol_Header];
            colors[ImGuiCol_HeaderHovered] = headerHovered;

            colors[ImGuiCol_Button] = {0.0f,0.0f,0.0f,0.4f};
            colors[ImGuiCol_ButtonHovered] = headerHovered;
            colors[ImGuiCol_ButtonActive] = ImVec4();

            colors[ImGuiCol_ScrollbarGrab] = scrollbarGrab;
            colors[ImGuiCol_ScrollbarGrabHovered] = scrollbarGrabHovered;
            colors[ImGuiCol_ScrollbarGrabActive] = scrollbarGrabActive;

            colors[ImGuiCol_TitleBg] = colors[ImGuiCol_TitleBg];
            colors[ImGuiCol_TitleBgActive] = colors[ImGuiCol_TitleBg];
            colors[ImGuiCol_TitleBgCollapsed] = colors[ImGuiCol_TitleBg];

            colors[ImGuiCol_Tab] = ImVec4();
            colors[ImGuiCol_TabHovered] = tabHovered;
            colors[ImGuiCol_TabActive] = colors[ImGuiCol_TabHovered];
            colors[ImGuiCol_TabUnfocused] = colors[ImGuiCol_Tab];
            colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_TabHovered];

            colors[ImGuiCol_CheckMark] = {1.0,1.0,1.0,1.0};

            colors[ImGuiCol_NavHighlight] = ImVec4();

            return std::move(style);
        }();

        void SetupStyleImpl();

        public:
        ~ImStyleManager() = default;
        [[nodiscard]] static inline ImStyleManager& GetSingleton() {
            static ImStyleManager instance;
            return instance;
        }

        [[nodiscard]] inline float GetScale(){
            return Settings.UI.fFontScale;
        }

        inline void SetScale(float a_scale){
            Settings.UI.fFontScale = a_scale;
            SetupStyleImpl();
        }

        inline void LoadStyle(){
            SetupStyleImpl();
        }

    };
}