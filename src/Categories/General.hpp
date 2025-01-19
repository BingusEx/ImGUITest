#pragma once

#include "src\ImCategory.hpp"

namespace GTSUi{

    class CategoryGeneral : public ImCategory {
        public:
        CategoryGeneral(){
            title = "General";
            description = "General Settings";
        }

        void Draw() override;
        bool Load() override;
        bool Save() override;
    };

}