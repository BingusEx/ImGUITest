
#pragma once

#include "src/UI/ImGUI/ImCategorySplit.hpp"
#include "src/UI/ImGui/ImStyleManager.hpp"
#include "src/UI/ImGui/ImFontManager.hpp"

#include "src/Config/Config.hpp"

namespace UI {

    class CategoryInterface : public ImCategorySplit {
        public:
        CategoryInterface(){
            title = "Interface";
        }

        void DrawLeft() override;
        void DrawRight() override;
        
        private:
        ImStyleManager& StyleMgr = ImStyleManager::GetSingleton();
        ImFontManager& FontMgr = ImFontManager::GetSingleton();
        SettingsUI& Settings = Config::GetUI();
    };

}