#include "ImUtil.hpp"

namespace ImUtil {

    //------------------------------------
    //  Modified/Extended Imgui Controls
    //------------------------------------

    const bool Button(const char* a_label, const char* a_Tooltip, const bool a_disabled, const float a_padding){
        
        const float paddingX = ImGui::GetStyle().FramePadding.x;
        const float paddingY = ImGui::GetStyle().FramePadding.y;
        const ImVec2 textSize = ImGui::CalcTextSize(a_label);
        const ImVec2 buttonSize = ImVec2(textSize.x + a_padding * (paddingX * 2), textSize.y + a_padding * (paddingY * 2));

        ImGui::BeginDisabled(a_disabled);
        const bool res = ImGui::Button(a_label, buttonSize);
        if (ImGui::IsItemHovered() && a_Tooltip && GImGui->HoveredIdTimer > TooltipDelay){
            ImGui::SetTooltip(a_Tooltip);
        }
        ImGui::EndDisabled();
        return res;
    }

    const bool CheckBox(const char* a_label, bool* a_state, const char* a_Tooltip, const bool a_disabled){
        ImGui::BeginDisabled(a_disabled);
        const bool res = ImGui::Checkbox(a_label, a_state);
        
        if (ImGui::IsItemHovered() && a_Tooltip && GImGui->HoveredIdTimer > TooltipDelay){
            ImGui::SetTooltip(a_Tooltip);
        
        }
        ImGui::EndDisabled();
        return res;
    }

    const bool SliderF(const char* a_label, float* a_value, float a_min, float a_max, const char* a_Tooltip, const char* fmt, const bool a_disabled, const bool a_alwaysclamp){
        ImGui::BeginDisabled(a_disabled);

        if(a_alwaysclamp){
            if (*a_value > a_max)
                *a_value = a_max;
            if (*a_value < a_min)
                *a_value = a_min;
        }

        const bool res = ImGui::SliderFloat(a_label, a_value, a_min, a_max, fmt, ImGuiSliderFlags_AlwaysClamp);

        if (ImGui::IsItemHovered() && a_Tooltip && GImGui->HoveredIdTimer > TooltipDelay){
            ImGui::SetTooltip(a_Tooltip);
        }
        ImGui::EndDisabled();
        return res;
    }

    const bool SliderF3(const char* a_label, float* a_value, float a_min, float a_max, const char* a_Tooltip, const char* fmt, const bool a_disabled){
        ImGui::BeginDisabled(a_disabled);
        const bool res = ImGui::SliderFloat3(a_label, a_value, a_min, a_max, fmt, ImGuiSliderFlags_AlwaysClamp);

        if (ImGui::IsItemHovered() && a_Tooltip && GImGui->HoveredIdTimer > TooltipDelay){
            ImGui::SetTooltip(a_Tooltip);
        }
        ImGui::EndDisabled();
        return res;
    }

    const bool SliderF2(const char* a_label, float* a_value, float a_min, float a_max, const char* a_Tooltip, const char* fmt, const bool a_disabled){
        ImGui::BeginDisabled(a_disabled);
        const bool res = ImGui::SliderFloat2(a_label, a_value, a_min, a_max, fmt, ImGuiSliderFlags_AlwaysClamp);

        if (ImGui::IsItemHovered() && a_Tooltip && GImGui->HoveredIdTimer > TooltipDelay){
            ImGui::SetTooltip(a_Tooltip);
        }
        ImGui::EndDisabled();
        return res;
    }



    // Helper to display a little (?) mark which shows a tooltip when hovered.
    void HelpMarker(const char* a_desc) {

        ImGui::Text("[?]");
        if (ImGui::BeginItemTooltip()){

            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(a_desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

    const bool ConditionalHeader(const std::string a_label, const std::string a_ConditionText, const bool a_condition, const bool a_defaultopen){
        ImGui::BeginDisabled(!a_condition);
        auto flags = ImGuiTreeNodeFlags_None | (a_condition && a_defaultopen ? ImGuiTreeNodeFlags_DefaultOpen : 0);
        
        //TODO Optimize this POS;
        const std::string _FullText = (a_label + (a_condition ? "##" : (" [" + a_ConditionText + "]")));
        
        bool Res = ImGui::CollapsingHeader(_FullText.c_str(),flags);

        ImGui::EndDisabled();

        return Res;
    }



    //------------------------------------
    //  Misc
    //------------------------------------

    // Helper function to pretty-print enum names
    const std::string HumanizeEnum(std::string_view name) {
        if (name.empty()) {
            return {};
        }

        std::string result;

        // Remove leading 'k'
        if (name[0] == 'k') {
            name.remove_prefix(1);
        }

        bool first_char = true;
        for (char c : name) {
            if (c == '_') {
                // Replace underscores with spaces, avoiding consecutive spaces
                if (result.empty() || result.back() != ' ') {
                    result += ' ';
                }
                first_char = false;
                continue;
            }

            // Add space before uppercase letters if needed
            if (!first_char && std::isupper(static_cast<unsigned char>(c))) {
                if (result.empty() || result.back() != ' ') {
                    result += ' ';
                }
            }

            result += c;
            first_char = false;
        }

        // Trim leading and trailing spaces
        size_t start = result.find_first_not_of(' ');
        if (start == std::string::npos) {
            return "";
        }

        size_t end = result.find_last_not_of(' ');
        result = result.substr(start, end - start + 1);

        // Collapse consecutive spaces into a single space
        std::string final_result;
        bool prev_space = false;
        for (char c : result) {
            if (c == ' ') {
                if (!prev_space) {
                    final_result += ' ';
                    prev_space = true;
                }
            } else {
                final_result += c;
                prev_space = false;
            }
        }

        return final_result;
    }

    void CenteredProgress(float fraction, const ImVec2& size_arg, const char* overlay) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;

        // Calculate progress bar dimensions
        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), g.FontSize + style.FramePadding.y * 2.0f);
        ImVec2 possize = {pos.x + size.x, pos.y + size.y};
        ImRect bb(pos, possize);
        
        // Register the item and handle clipping
        ImGui::ItemSize(size, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, 0))
            return;

        // Render background
        ImU32 bg_color = ImGui::GetColorU32(ImGuiCol_FrameBg);
        ImU32 fill_color = ImGui::GetColorU32(ImGuiCol_PlotHistogram);
        float frame_rounding = style.FrameRounding;
        window->DrawList->AddRectFilled(bb.Min, bb.Max, bg_color, frame_rounding);

        // Render filled portion
        if (fraction > 0.0f) {
            float fill_width = ImMax(size.x * fraction, 2.0f);
            ImRect fill_bb(bb.Min, ImVec2(bb.Min.x + fill_width, bb.Max.y));
            window->DrawList->AddRectFilled(fill_bb.Min, fill_bb.Max, fill_color, frame_rounding);
        }

        // Render centered text
        if (overlay != nullptr) {
            ImVec2 overlay_size = ImGui::CalcTextSize(overlay);
            ImVec2 text_pos = ImVec2(
                bb.Min.x + (size.x - overlay_size.x) * 0.5f,
                bb.Min.y + (size.y - overlay_size.y) * 0.5f
            );
            
            // Draw text with contrasting shadow
            window->DrawList->AddText(
                ImVec2(text_pos.x + 1, text_pos.y + 1), 
                IM_COL32(0,0,0,128 * ImGui::GetStyle().Alpha), 
                overlay
            );
            window->DrawList->AddText(text_pos, ImGui::GetColorU32(ImGuiCol_Text), overlay);
        }
    }
    
}