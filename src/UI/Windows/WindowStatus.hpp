#pragma once

#include "src/UI/ImGUI/ImWindow.hpp"
#include "src/UI/ImGUI/ImCategoryManager.hpp"
#include "src/UI/ImGUI/ImFontManager.hpp"
#include "src/UI/ImGUI/ImStyleManager.hpp"

#include "src/Config.hpp"

namespace UI {

    class WindowStatus : public ImWindow {

        public:
        
        WindowStatus();

        void Draw() override;

        private:
        ImCategoryManager& CatMgr = ImCategoryManager::GetSingleton();
        ImFontManager& FontMgr = ImFontManager::GetSingleton();
        ImStyleManager& StyleMgr = ImStyleManager::GetSingleton();
        Config& Settings = Config::GetSingleton();

        inline bool ShouldShow() override {
            return Settings.UI.wStatus.bVisible;
        }

        inline float GetAlpha() override {
            return Settings.UI.wStatus.fAlpha;
        }
    };
}