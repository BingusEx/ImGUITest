#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_internal.h"
#include <d3d11.h>
#include <tchar.h>
#include <string>
#include <format>
#include <vector>
#include <iostream>
#include <memory>
#include <string>

#include <functional> // For std::function

using namespace std;

namespace ImUtil {

    //-------------------
    //  Constants
    //-------------------

    //Predefined colors {R, G, B, A} (0.0 to 1.0f)
    constexpr ImVec4 ColorError = {1.0f, 0.15f, 0.15f, 1.0f};
    constexpr ImVec4 ColorSubscript = {.5f, 0.5f, 0.5f, .5f};

    //-------------------
    //  Utility
    //-------------------

    [[nodiscard]] static inline bool ValidState() noexcept {
        ImGuiContext* ctx = ImGui::GetCurrentContext();
        return ctx && ctx->WithinFrameScope;
    }

    inline void SeperatorH(){
        ImGui::Spacing();
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal, 2.0f);
        ImGui::Spacing();
    }

    inline void SeperatorV(){
        ImGui::SameLine();
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical, 2.0f);
        ImGui::SameLine();
    }

    //---------------------
    //  Button
    //---------------------

    static inline void ButtonSimple(const char* a_label, const std::function<void()>& a_callback = nullptr, const float a_padding = 1.0f){
    
        const float paddingX = ImGui::GetStyle().FramePadding.x;
        const float paddingY = ImGui::GetStyle().FramePadding.y;
        const ImVec2 textSize = ImGui::CalcTextSize(a_label);
        const ImVec2 buttonSize = ImVec2(textSize.x + a_padding * (paddingX * 2), textSize.y + a_padding * (paddingY * 2));

        if(ImGui::Button(a_label, buttonSize) && a_callback) {
            a_callback();
        }

    }

    static inline void ButtonColor(const char* a_label, const ImVec4 a_color, const std::function<void()>& a_callback = nullptr, const float a_padding = 1.0f){
    
        const float paddingX = ImGui::GetStyle().FramePadding.x;
        const float paddingY = ImGui::GetStyle().FramePadding.y;
        const ImVec2 textSize = ImGui::CalcTextSize(a_label);
        const ImVec2 buttonSize = ImVec2(textSize.x + a_padding * (paddingX * 2), textSize.y + a_padding * (paddingY * 2));

        if(ImGui::ColorButton(a_label, a_color, ImGuiColorEditFlags_Float, buttonSize) && a_callback) {
            a_callback();
        }

    }

}