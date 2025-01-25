#pragma once

#include "src/ImCategory.hpp"

namespace GTSUi{

    class CategoryAI: public ImCategory {
        public:
        CategoryAI(){
            title = "AI";
            description = "Configure the behavior of NPCs/Followers";
        }

        void Draw() override;
        bool Load() override;
        bool Save() override;
    };

}