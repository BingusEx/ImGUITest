#pragma once

#include "src/UI/ImGUI/ImCategory.hpp"

namespace UI{

    class CategoryAdvanced: public ImCategory {
        public:
        CategoryAdvanced(){
            title = "Debug";
            description = "Advanced Settings";
        }

        void Draw() override;
    };

}