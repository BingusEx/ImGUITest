#pragma once

#include "src/UI/ImGUI/ImCategorySplit.hpp"
#include "src/Config/Config.hpp"

namespace UI{

    class CategoryGameplay: public ImCategorySplit {
        public:
        CategoryGameplay(){
            title = "Gameplay";
        }

        void DrawLeft() override;
        void DrawRight() override;

        private:
        SettingsGameplay& Settings = Config::GetGameplay();
        void GameModeOptions(const char* a_title, GameplayActorSettings* a_Settings);
    };

}