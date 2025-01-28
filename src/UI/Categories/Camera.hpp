#pragma once

#include "src/UI/ImGUI/ImCategory.hpp"

namespace UI{

    class CategoryCamera: public ImCategory {
        public:
        CategoryCamera(){
            title = "Camera";
            description = "Change how the camera behaves";
        }

        void Draw() override;
    };

}