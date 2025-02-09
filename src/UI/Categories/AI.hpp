#pragma once

#include "src/UI/ImGUI/ImCategorySplit.hpp"

#include "src/Config/Config.hpp"

namespace UI{

    class CategoryAI: public ImCategorySplit {
        public:
        CategoryAI(){
            title = "AI";
        }

        void DrawLeft() override;
        void DrawRight() override;

        private:
        SettingsAI& Settings = Config::GetAI();
    };

}