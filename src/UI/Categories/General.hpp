#pragma once

#include "src/UI/ImGUI/ImCategorySplit.hpp"
#include "src/Config/Config.hpp"

namespace UI{

    class CategoryGeneral: public ImCategorySplit {
        public:
        CategoryGeneral(){
            title = "General";
        }

        void DrawLeft() override;
        void DrawRight() override;

        private:
        SettingsGeneral& Settings = Config::GetGeneral();
    };

}