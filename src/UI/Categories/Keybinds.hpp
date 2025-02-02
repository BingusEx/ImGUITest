
#pragma once

#include "src/UI/ImGUI/ImCategory.hpp"
#include "src/Config.hpp"

namespace UI{

    class CategoryKeybinds : public ImCategory {
        public:
        CategoryKeybinds(){
            title = "Keybinds";
        }
        void Draw() override;

        private:
        const Config& Settings = Config::GetSingleton();
    };

}