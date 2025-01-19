
#pragma once

#include "src/ImCategory.hpp"

namespace GTSUi{

    class CategoryInfo : public ImCategory {
        public:
        CategoryInfo(){
            title = "Info";
            description = "Info";
        }

        void Draw() override;
        bool Load() override;
        bool Save() override;
    };

}