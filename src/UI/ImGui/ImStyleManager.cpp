#include "ImStyleManager.hpp"

using namespace UI;

void ImStyleManager::SetupStyleImpl(){
    auto& style = ImGui::GetStyle();

    auto customStyle = GTSStyle;
    customStyle.ScaleAllSizes(exp2(Settings.UI.fFontScale));
    customStyle.MouseCursorScale = 1.0f;

    style = customStyle;

    ImGui::GetIO().FontGlobalScale = Settings.UI.fFontScale;
}
