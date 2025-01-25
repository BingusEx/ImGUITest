
#pragma once

#include "src/ImCategory.hpp"
#include "src/Imsplitter.hpp"

namespace GTSUi{

    class CategoryInfo : public ImCategory {
        public:
        CategoryInfo(){
            title = "Info";
            description = "Info";
        }
        void Draw() override;



        ///Unused
        bool Load() override {
            return true;
        }
        bool Save() override {
            return true;
        }
    };

}