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

    constexpr uint32_t HeaderFlags = ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_DefaultOpen;

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
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical, 2.f);
        ImGui::SameLine();
    }

    [[nodiscard]] inline ImVec2 ScaleToViewport(float a_Percentage) {
        ImVec2 viewportSize = ImGui::GetMainViewport()->Size;
        //std::clamp(a_Percentage, 10.0f, 100.0f);
        return { viewportSize.x * (a_Percentage / 100.f), viewportSize.y * (a_Percentage / 100.f) };
    }

    const std::string HumanizeEnum(std::string_view name);

    const bool Button(const char* a_label, const char* a_Tooltip = nullptr, const bool a_disabled = false, const float a_padding = 1.0f);
    const bool CheckBox(const char* a_label, bool* a_state, const char* a_Tooltip = nullptr, const bool a_disabled = false);
    const bool SliderF(const char* a_label, float* a_value, float a_min, float a_max, const char* a_Tooltip = nullptr, const char* fmt = "%.2f", const bool a_disabled = false);
    const bool SliderF2(const char* a_label, float* a_value, float a_min, float a_max, const char* a_Tooltip = nullptr, const char* fmt = "%.2f", const bool a_disabled = false);
    const bool SliderF3(const char* a_label, float* a_value, float a_min, float a_max, const char* a_Tooltip = nullptr, const char* fmt = "%.2f", const bool a_disabled = false);
    
    void Bitfield(const char* a_label, uint32_t* a_bitfield);

    void HelpMarker(const char* a_desc);

    const bool ConditionalHeader(const std::string a_label, const std::string a_ConditionText, const bool a_condition);

    template <typename T>
    bool ComboEx(const char* label, std::string& currentValue, const char* a_Tooltip = nullptr, bool a_disabled = false, bool a_hasTotal = false) {
        // Retrieve enum metadata
        constexpr auto enumNames = magic_enum::enum_names<T>();
        constexpr auto enumValues = magic_enum::enum_values<T>();

        // Build the items string with pretty-printed names
        std::ostringstream itemsStream;
        const int offset = a_hasTotal ? 2 : 1;
        for (size_t i = 0; i <= enumNames.size() - offset; i++) {
            itemsStream << HumanizeEnum(enumNames[i]) << '\0';
        }
        std::string items = itemsStream.str();

        // Find current enum index
        auto currentEnum = magic_enum::enum_cast<T>(currentValue);
        int currentIndex = 0;
        
        if (currentEnum.has_value()) {
            // Find the index of the current enum value
            const auto it = std::find(enumValues.begin(), enumValues.end(), currentEnum.value());
            if (it != enumValues.end()) {
                currentIndex = static_cast<int>(std::distance(enumValues.begin(), it));
            }
        } 
        else {
            // Reset to first value if invalid
            currentValue = std::string(enumNames[0]);
        }

        ImGui::BeginDisabled(a_disabled);
        bool res = ImGui::Combo(label, &currentIndex, items.c_str());
        if (ImGui::IsItemHovered() && a_Tooltip){
            ImGui::SetTooltip(a_Tooltip);
        }
        ImGui::EndDisabled();

        if(res){
            T selectedEnum = enumValues[currentIndex];
            currentValue = std::string(magic_enum::enum_name(selectedEnum));
        }

        return res;
    }

}

