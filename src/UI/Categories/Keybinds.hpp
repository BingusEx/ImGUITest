
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

        void HandleKeys(std::string bindingStr, int CurrentIndex);

        private:
        const Config& Settings = Config::GetSingleton();
        Input::Keybinds& KeyMgr = Input::Keybinds::GetSingleton();

        int Div = 2;

        std::string SearchRes = "";
        bool HideFiltered = false;
        std::string VisualKeyString = "";
        std::vector<std::string> TempKeys = {};
        int RebindIndex = 0;
    };

}