
#pragma once

#include "src/ImCategory.hpp"
#include "src/Imsplitter.hpp"

namespace GTSUi{

    class CategoryInfo : public ImCategorySplitter {
        public:
        CategoryInfo(){
            title = "Info";
            description = "Info";
        }
        void DrawLeft() override;
        void DrawRight() override;

        bool Load() override;
        bool Save() override;
    };

}