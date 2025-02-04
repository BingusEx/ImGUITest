#pragma once

#include "src/UI/ImGUI/ImWindow.hpp"
#include "src/UI/ImGUI/ImFontManager.hpp"
#include "src/UI/ImGUI/ImStyleManager.hpp"

#include "src/Config.hpp"

namespace UI {

    class WindowStatus : public ImWindow {

        public:
        
        WindowStatus();

        void Draw() override;

        private:
        Config& Settings = Config::GetSingleton();
        const SettingsHidden& sHidden = Config::GetHidden();
        const WindowConfStatus& sUI= Config::GetUI().StatusWindow;

        inline bool ShouldShow() override {
            return sUI.bVisible;
        }

        inline float GetAlpha() override {
            return sUI.fAlpha;
        }
    };
}