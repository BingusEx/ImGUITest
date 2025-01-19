
#pragma once

#include "src/ImCategory.hpp"

namespace GTSUi{

    class CategoryWidget: public ImCategory {
        public:
        CategoryWidget(){
            title = "Widget";
            description = "Widget";
        }

        void Draw() override;
        bool Load() override;
        bool Save() override;
    };

}