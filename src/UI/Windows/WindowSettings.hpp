#pragma once

#include "src/UI/ImGUI/ImWindow.hpp"
#include "src/UI/ImGUI/ImCategoryContainer.hpp"
#include "src/UI/ImGUI/ImFontManager.hpp"
#include "src/UI/ImGUI/ImStyleManager.hpp"

#include "src/Config/Config.hpp"
#include "src/Config/Keybinds.hpp"

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
        void AsyncLoad();
        void AsyncSave();

        std::atomic<bool> SaveLoadBusy = false;

        std::string ErrorString = "";
        ImCategoryManager& CatMgr = ImCategoryManager::GetSingleton();
        ImFontManager& FontMgr = ImFontManager::GetSingleton();
        ImStyleManager& StyleMgr = ImStyleManager::GetSingleton();

        Config& Settings = Config::GetSingleton();
        Input::Keybinds& KeyMgr = Input::Keybinds::GetSingleton();
        const SettingsHidden& sHidden = Config::GetHidden();
        const WindowConfSettings& sUI= Config::GetUI().SettingsWindow;
    };
}