
#pragma once

#include "src/UI/ImGUI/ImCategorySplit.hpp"
#include "src/UI/ImGui/ImStyleManager.hpp"
#include "src/UI/ImGui/ImFontManager.hpp"

#include "src/Config.hpp"

namespace UI {

    class CategoryInterface : public ImCategorySplit {
        public:
        CategoryInterface(){
            title = "Interface";
            description = "Interface";
        }

        void DrawLeft() override;
        void DrawRight() override;
        
        private:
        ImStyleManager& StyleMgr = ImStyleManager::GetSingleton();
        ImFontManager& FontMgr = ImFontManager::GetSingleton();
        Config& Settings = Config::GetSingleton();

        void ConfigureWindow(const std::string& a_WindowName, const std::string& a_Friendlyname);

    };

}