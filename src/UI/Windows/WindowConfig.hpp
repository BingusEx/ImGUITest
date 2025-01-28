#pragma once

#include "src/UI/ImGUI/ImWindow.hpp"
#include "src/UI/ImGUI/ImCategoryManager.hpp"
#include "src/UI/ImGUI/ImFontManager.hpp"
#include "src/UI/ImGUI/ImStyleManager.hpp"

#include "src/Config.hpp"

namespace UI {

    class WindowConfig : public ImWindow {

        public:
        
        WindowConfig();

        void Draw() override;


        private:
        void ShowFooterMessage();

        std::string ErrorString = "";
        ImCategoryManager& CatMgr = ImCategoryManager::GetSingleton();
        ImFontManager& FontMgr = ImFontManager::GetSingleton();
        ImStyleManager& StyleMgr = ImStyleManager::GetSingleton();
        Config& Settings = Config::GetSingleton();
    };
}