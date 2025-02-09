#pragma once

#include "src/UI/ImGUI/ImCategorySplit.hpp"
#include "src/Config/Config.hpp"

namespace UI{

    class CategoryCamera: public ImCategorySplit {
        public:
        CategoryCamera(){
            title = "Camera";
        }

        void DrawLeft() override;
        void DrawRight() override;

        private:
        SettingsCamera& Settings = Config::GetCamera();
    };

}