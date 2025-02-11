#include "Keybinds.hpp"
#include "imgui.h"

#include "src/UI/imGui/ImUtil.hpp"
#include "imgui_stdlib.h"

using namespace UI;
using namespace Input;



void CategoryKeybinds::Draw(){

    const char* T0 = "";
    const char* T1 = "";
    const char* T2 = "";
    const char* T3 = "";
    const char* T4 = "";
    const char* T5 = "";
    const char* T6 = "";
    const char* T7 = "";
    const char* T8 = "";
    const char* T9 = "";

    int Counter = 1000;
   
    float Width = ImGui::GetContentRegionAvail().x - (((ImGui::GetStyle().CellPadding.x + ImGui::GetStyle().FramePadding.x) * Div) + ImGui::GetStyle().WindowPadding.x * 2);

    ImGui::PushItemWidth(Width / 6.0f);

    ImGui::InputText("Search Filter",&SearchRes);
    ImGui::SameLine();
    ImGui::Checkbox("Hide Filtered",&HideFiltered);
    ImGui::SameLine();
    ImGui::InputInt("Columns",&Div,1,1);

    if(Div < 1)
        Div = 1;
    if(Div > 3)
        Div = 3;

    ImGui::PopItemWidth();
    ImGui::Spacing();
    ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
    ImGui::Spacing();




    for (auto& Event : KeyMgr.InputEvents){

        std::string NewName = ImUtil::HumanizeString(Event.Event);
        bool Filtered = !ImUtil::ContainsString(NewName, SearchRes);
        
        if(Filtered && HideFiltered){
            continue;
        }
        
  

        NewName = Filtered ? NewName + " [Filtered]" : NewName;


        ImGui::BeginChild(Counter++,{Width/Div, Filtered ? 35.0f : 300.f},true,true);
        ImGui::BeginDisabled(Filtered);
        
        ImGui::SetNextItemOpen(!Filtered);

        ImGui::PushStyleColor(ImGuiCol_Header, (Filtered ? ImVec4(0.0f,0.0f,0.0f,0.1f) : ImGui::GetStyle().Colors[ImGuiCol_Header]));
 
        if(ImGui::CollapsingHeader(NewName.c_str(), ImGuiTreeNodeFlags_Bullet)){
            ImUtil::CheckBox("Disabled", &Event.Disabled);

            if(!Event.Disabled){
                ImUtil::CheckBox("Exclusive", &Event.Exclusive);
                ImUtil::ComboEx<Triggers>("Trigger Type",Event.Trigger);
                ImUtil::ComboEx<BlockInputTypes>("Block Input",Event.BlockInput);
                ImGui::InputFloat("Trigger After",&Event.Duration,0.1f,0.01f,"%.2f Seconds");

                VisualKey = "";
                const int NumOfKeys = static_cast<int>(Event.Keys.size());

                for (int i = 0; i < NumOfKeys; i++){
                    VisualKey +=  Event.Keys[i];

                    if(i != NumOfKeys - 1){
                        VisualKey += " + ";
                    }
                    
                   // ImGui::

                }
     

                //ImGui::Button("Keys", &VisualKey);


            }

            ImGui::Spacing();
        }
        ImGui::EndDisabled();
        ImGui::PopStyleColor();

        ImGui::EndChild();

        //Offset counter by -1 if Div is uneven
        if((Counter - (Div % 3 == 0)) % Div) {
            ImGui::SameLine();
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
            ImGui::SameLine();
        }
        







        //ImGui::EndChild();


    }
    
}

