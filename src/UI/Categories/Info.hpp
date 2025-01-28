
#pragma once

#include "src/UI/ImGUI/ImCategory.hpp"

namespace UI{

    class CategoryInfo : public ImCategory {
        public:
        CategoryInfo(){
            title = "Info";
            description = "Info";
        }
        void Draw() override;

    };

}