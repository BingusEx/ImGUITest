#pragma once

#include "src/ImCategory.hpp"

namespace GTSUi{

    class CategoryCamera: public ImCategory {
        public:
        CategoryCamera(){
            title = "Camera";
            description = "Change how the camera behaves";
        }

        void Draw() override;
        bool Load() override;
        bool Save() override;
    };

}