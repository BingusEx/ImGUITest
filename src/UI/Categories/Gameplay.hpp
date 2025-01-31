#pragma once

#include "src/UI/ImGUI/ImCategorySplit.hpp"
#include "src/Config.hpp"

namespace UI{

    class CategoryGameplay: public ImCategorySplit {
        public:
        CategoryGameplay(){
            title = "Gameplay";
            description = "Gameplay Settings";
        }

        void DrawLeft() override;
        void DrawRight() override;

        private:
        Config& Settings = Config::GetSingleton();
    };

}