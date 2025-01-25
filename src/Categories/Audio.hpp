#pragma once

#include "src/ImCategory.hpp"

namespace GTSUi{

    class CategoryAudio: public ImCategory {
        public:
        CategoryAudio(){
            title = "Audio";
            description = "Change the mod's audio settings";
        }

        void Draw() override;
        bool Load() override;
        bool Save() override;
    };

}