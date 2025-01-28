#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_internal.h"

#include "magic_enum/magic_enum.hpp"

namespace ImUtil {

    //-------------------
    //  Constants
    //-------------------

    //Predefined colors {R, G, B, A} (0.0 to 1.0f)
    constexpr ImVec4 ColorError = {1.0f, 0.15f, 0.15f, 1.0f};
    constexpr ImVec4 ColorSubscript = {.8f, 0.8f, 0.8f, .7f};

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

    inline bool Button(const char* a_label, const char* a_Tooltip = nullptr, const bool a_disabled = false, const float a_padding = 1.0f){
    
        const float paddingX = ImGui::GetStyle().FramePadding.x;
        const float paddingY = ImGui::GetStyle().FramePadding.y;
        const ImVec2 textSize = ImGui::CalcTextSize(a_label);
        const ImVec2 buttonSize = ImVec2(textSize.x + a_padding * (paddingX * 2), textSize.y + a_padding * (paddingY * 2));

        ImGui::BeginDisabled(a_disabled);
        const bool res = ImGui::Button(a_label, buttonSize);
        if (ImGui::IsItemHovered() && a_Tooltip){
            ImGui::SetTooltip(a_Tooltip);
        }
        ImGui::EndDisabled();
        return res;
    }


// Extended helper function for ImGui::Combo with automatic enum name list generation
template <typename T>
bool ImGuiEnumCombo(const char* label, std::string& currentValue) {
    // Retrieve all enum names as a string view array
    constexpr auto enumNames = magic_enum::enum_names<T>();

    // Dynamically construct the combo items string
    std::ostringstream itemsStream;
    for (size_t i = 0; i < enumNames.size(); ++i) {
        itemsStream << enumNames[i];
        if (i < enumNames.size() - 1) {
            itemsStream << '\0'; // Separate items with null characters
        }
    }
    std::string items = itemsStream.str();

    // Convert the current string to an enum value
    auto enumOpt = magic_enum::enum_cast<T>(currentValue);
    T enumValue = enumOpt.value_or(static_cast<T>(0)); // Default to the first enum value
    int index = static_cast<int>(enumValue);

    // Show the combo box
    bool changed = ImGui::Combo(label, &index, items.c_str());

    // If the user changes the selection
    if (changed) {
        // Convert the selected index back to an enum
        T newEnumValue = static_cast<T>(index);

        // Update the current value with the enum's string name
        currentValue = std::string(magic_enum::enum_name(newEnumValue));
    }

    return changed;
}

   inline bool CheckBox(const char* a_label, bool* a_state, const char* a_Tooltip = nullptr, const bool a_disabled = false){
        ImGui::BeginDisabled(a_disabled);
        const bool res = ImGui::Checkbox(a_label,a_state);
        if (ImGui::IsItemHovered() && a_Tooltip){
            ImGui::SetTooltip(a_Tooltip);
        }
        ImGui::EndDisabled();
        return res;
    }

   inline bool SliderF(const char* a_label, float* a_value, float a_min, float a_max, const char* a_Tooltip = nullptr, const bool a_disabled = false){
        ImGui::BeginDisabled(a_disabled);
        const bool res = ImGui::SliderFloat(a_label, a_value, a_min, a_max, "%.2f", ImGuiSliderFlags_NoInput);

        if (ImGui::IsItemHovered() && a_Tooltip){
            ImGui::SetTooltip(a_Tooltip);
        }
        ImGui::EndDisabled();
        return res;
    }

   inline bool SliderF2(const char* a_label, float* a_value, float a_min, float a_max, const char* a_Tooltip = nullptr, const bool a_disabled = false){
        ImGui::BeginDisabled(a_disabled);
        const bool res = ImGui::SliderFloat2(a_label, a_value, a_min, a_max, "%.2f", ImGuiSliderFlags_NoInput);

        if (ImGui::IsItemHovered() && a_Tooltip){
            ImGui::SetTooltip(a_Tooltip);
        }
        ImGui::EndDisabled();
        return res;
    }

    // static inline bool SliderFS(const char* a_label, float* a_value, float a_min, float a_max, float a_step, const char* a_Tooltip = nullptr, const bool a_disabled = false){
        
    //     const int _NumSteps = (a_max - a_min) / a_step;
    //     int _Stepped = *a_value / a_step;

    //     std::ostream ss = std::format("{:.2f}", *a_value);
        
    //     if (ImGui::SliderInt(a_label, &_Stepped, (int)a_min, (int)a_max, , ImGuiSliderFlags_NoInput)) {
    //         height = heightSliderValue * heightSliderStep;
    //     }

    //     a_value = heightSliderValue;
    // }


    [[nodiscard]] inline ImVec2 ScaleToViewport(float a_Percentage) {
        ImVec2 viewportSize = ImGui::GetMainViewport()->Size;
        //std::clamp(a_Percentage, 10.0f, 100.0f);
        return { viewportSize.x * (a_Percentage / 100.f), viewportSize.y * (a_Percentage / 100.f) };
    }

}

