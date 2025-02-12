
#pragma once

#include "src/UI/ImGUI/ImCategory.hpp"
#include "src/Config/Config.hpp"
#include "src/Config/Keybinds.hpp"
#include "src/UI/ImGui/ImWindowManager.hpp"

namespace UI {

    class CategoryKeybinds : public ImCategory {
        public:
        CategoryKeybinds(){
            title = "Keybinds";
            for(auto& e : Input::DefaultEvents){
                HeaderStateMap.emplace(e.Event,false);
            }
        }
        void Draw() override;


        private:
        const Config& Settings = Config::GetSingleton();
        Input::Keybinds& KeyMgr = Input::Keybinds::GetSingleton();

        //UI

        void DrawOptions();
        void DrawContent();


        int Div = 2;
        std::string SearchRes = "";
        bool HideFiltered = false;
        volatile uint8_t ColExpState = 0;

        std::unordered_map<std::string, bool> HeaderStateMap = {};
        //InputEvent Rebinding
        std::string VisualKeyString = "";
        std::vector<std::string> TempKeys = {};
        int RebindIndex = 0;
        int CurEventIndex = 1000;
        float Width = 0.0f;
        bool DrawInputEvent(InputEvent& Event, std::string a_name);
        const int HeaderFlags =  ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AutoResizeX ;

    };

}