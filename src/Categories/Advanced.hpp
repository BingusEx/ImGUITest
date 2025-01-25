#pragma once

#include "src/ImCategory.hpp"

namespace GTSUi{

    class CategoryAdvanced: public ImCategory {
        public:
        CategoryAdvanced(){
            title = "Debug";
            description = "Advanced Settings";
        }

        void Draw() override;
        bool Load() override;
        bool Save() override;
    };

}