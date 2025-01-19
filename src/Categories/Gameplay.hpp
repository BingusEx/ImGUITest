#pragma once

#include "src/ImCategory.hpp"

namespace GTSUi{

    class CategoryGameplay: public ImCategory {
        public:
        CategoryGameplay(){
            title = "Gameplay";
            description = "Gameplay Settings";
        }

        void Draw() override;
        bool Load() override;
        bool Save() override;
    };

}