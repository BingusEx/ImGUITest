#pragma once

#include "src/UI/ImGUI/ImCategorySplit.hpp"
#include "src/Config.hpp"

namespace UI{

    class CategoryAdvanced: public ImCategorySplit {
        public:
        CategoryAdvanced(){
            title = "Advanced";
        }

        void DrawLeft() override;
        void DrawRight() override;

        private:
        SettingsAdvanced& Settings = Config::GetSingleton().GetAdvanced();
    };

}