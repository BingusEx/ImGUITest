#pragma once

#include "src/UI/ImGUI/ImCategorySplit.hpp"
#include "src/Config.hpp"

namespace UI{

    class CategoryAudio: public ImCategorySplit {
        public:
        CategoryAudio(){
            title = "Audio";
        }

        void DrawLeft() override;
        void DrawRight() override;

        private:
        SettingsAudio& Settings = Config::GetAudio();
    };
}