#pragma once

#include "src/UI/ImGUI/ImCategorySplit.hpp"
#include "src/Config/Config.hpp"

namespace UI{

    class CategoryBalance: public ImCategorySplit {
        public:
        CategoryBalance(){
            title = "Balance";
        }

        void DrawLeft() override;
        void DrawRight() override;

        private:
        SettingsBalance& Settings = Config::GetBalance();
    };

}