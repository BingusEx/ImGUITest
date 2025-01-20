
#pragma once

#include "src/ImCategory.hpp"
#include "src/Imsplitter.hpp"

namespace GTSUi{

    class CategoryInterface : public ImCategorySplitter {
        public:
        CategoryInterface(){
            title = "Interface";
            description = "Interface";
        }

        void DrawLeft() override;
        void DrawRight() override;
        
        bool Load() override;
        bool Save() override;
    };

}