#pragma once

#include "src/UI/ImGUI/ImWindow.hpp"
#include "src/UI/ImGUI/ImCategoryContainer.hpp"
#include "src/UI/ImGUI/ImFontManager.hpp"
#include "src/UI/ImGUI/ImStyleManager.hpp"

#include "src/Config.hpp"

namespace UI {

    class WindowSettings : public ImWindow {

        public:
        
        WindowSettings();

        void Draw() override;

        inline bool ShouldShow() override {
            return true;
        }

        inline float GetAlpha() override {
            return 1.0f;
        }


        private:
        void ShowFooterMessage();

        std::string ErrorString = "";
        ImCategoryManager& CatMgr = ImCategoryManager::GetSingleton();
        ImFontManager& FontMgr = ImFontManager::GetSingleton();
        ImStyleManager& StyleMgr = ImStyleManager::GetSingleton();

        Config& Settings = Config::GetSingleton();
        const SettingsHidden& sHidden = Config::GetHidden();
        const WindowConfSettings& sUI= Config::GetUI().wSettings;
    };
}