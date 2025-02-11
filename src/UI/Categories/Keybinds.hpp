
#pragma once

#include "src/UI/ImGUI/ImCategory.hpp"
#include "src/Config/Config.hpp"
#include "src/Config/Keybinds.hpp"

namespace UI {

    class CategoryKeybinds : public ImCategory {
        public:
        CategoryKeybinds(){
            title = "Keybinds";
        }
        void Draw() override;

        private:
        const Config& Settings = Config::GetSingleton();
        Input::Keybinds& KeyMgr = Input::Keybinds::GetSingleton();

        int Div = 2;

        std::string SearchRes = "";
        bool HideFiltered = false;
        int RebindIndex = 0;
        std::string VisualKey = "";

    };

}