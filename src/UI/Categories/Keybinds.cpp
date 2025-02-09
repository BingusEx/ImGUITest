#include "Keybinds.hpp"
#include "imgui.h"

#include "src/UI/imGui/ImUtil.hpp"
#include "imgui_stdlib.h"

using namespace UI;
using namespace Input;



void CategoryKeybinds::Draw(){

    int Counter = 1200;

    static std::string SearchRes = "";
    static bool HideFiltered = false;
    static bool AutoOpenFiltered = false;

    ImGui::InputText("Search Filter",&SearchRes);
    ImGui::Checkbox("Hide Filtered",&HideFiltered);
    ImGui::Checkbox("Open Filtered",&AutoOpenFiltered);

    for (auto& Event : KeyMgr.InputEvents){

        std::string NewName = ImUtil::HumanizeString(Event.Event);
        bool Filtered = !ImUtil::ContainsString(NewName, SearchRes);
        
        if(Filtered && HideFiltered){
            continue;
        }
        
        //ImGui::BeginChild(Counter++, {0.f,0.f},true);

        NewName = Filtered ? NewName + " [Filtered]" : NewName;
        
        ImGui::BeginDisabled(Filtered);
        
        ImGui::SetNextItemOpen(!Filtered);
 
        if(ImGui::CollapsingHeader(NewName.c_str(), ImGuiTreeNodeFlags_Bullet)){
            ImUtil::CheckBox("Disabled", &Event.Disabled);
            ImGui::BeginDisabled(Event.Disabled);
            ImUtil::CheckBox("Exclusive", &Event.Exclusive);
            ImUtil::ComboEx<Triggers>("Trigger",Event.Trigger);
            ImUtil::ComboEx<BlockInputTypes>("Block Input",Event.Trigger);
            ImGui::EndDisabled();
            ImGui::Spacing();
        }
        ImGui::EndDisabled();
        







        //ImGui::EndChild();


    }
    
}

