#pragma once

#include "src/UI/ImGUI/ImCategorySplit.hpp"
#include "src/Config.hpp"

namespace UI{

    class CategoryCamera: public ImCategorySplit {
        public:
        CategoryCamera(){
            title = "Camera";
            description = "Change how the camera behaves";
        }

        void DrawLeft() override;
        void DrawRight() override;

        private:
        Config& Settings = Config::GetSingleton();
    };

}