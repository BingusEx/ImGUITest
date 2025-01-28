#pragma once

#include "src/UI/ImGUI/ImCategory.hpp"

namespace UI{

    class CategoryAudio: public ImCategory {
        public:
        CategoryAudio(){
            title = "Audio";
            description = "Change the mod's audio settings";
        }

        void Draw() override;
    };

}