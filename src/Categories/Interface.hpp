
#pragma once

#include "src/ImCategory.hpp"

namespace GTSUi{

    class CategoryInterface : public ImCategory {
        public:
        CategoryInterface(){
            title = "Interface";
            description = "Interface";
        }

        void Draw() override;
        bool Load() override;
        bool Save() override;
    };

}