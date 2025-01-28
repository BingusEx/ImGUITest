#pragma once

#include "src/UI/ImGUI/ImCategory.hpp"

namespace UI{

    class CategoryAI: public ImCategory {
        public:
        CategoryAI(){
            title = "AI";
            description = "Configure the behavior of NPCs/Followers";
        }

        void Draw() override;
    };

}