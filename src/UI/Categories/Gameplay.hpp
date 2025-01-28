#pragma once

#include "src/UI/ImGUI/ImCategory.hpp"

namespace UI{

    class CategoryGameplay: public ImCategory {
        public:
        CategoryGameplay(){
            title = "Gameplay";
            description = "Gameplay Settings";
        }

        void Draw() override;
    };

}