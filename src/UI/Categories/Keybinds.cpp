#include "Keybinds.hpp"
#include "imgui.h"

#include "src/UI/imGui/ImUtil.hpp"
#include "imgui_stdlib.h"
#include "src/UI/ImGui/ImInput.hpp"

using namespace UI;
using namespace Input;

static std::vector<std::string> currentBinding;      // Temporary storage for keys pressed during rebind mode
static std::vector<std::string> actionBinding;       // The “action” binding (the currently assigned key sequence)


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

    int CurEventIndex = 1000;
    const float Width = ImGui::GetContentRegionAvail().x - (((ImGui::GetStyle().CellPadding.x + ImGui::GetStyle().FramePadding.x) * Div) + ImGui::GetStyle().WindowPadding.x * 2);

    {   // Top Bar Controls
        ImGui::PushItemWidth(Width / 6.0f);

        ImGui::InputText("Search Filter", &SearchRes);
        if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > ImUtil::TooltipDelay){
            ImGui::SetTooltip(T0);
        }

        ImGui::SameLine();
        ImUtil::CheckBox("Hide Filtered", &HideFiltered, T1);
        
        ImGui::SameLine();
        ImGui::InputInt("Columns",&Div,1,1);
        if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > ImUtil::TooltipDelay){
            ImGui::SetTooltip(T2);
        }
        std::clamp(Div,1,3);

        ImGui::PopItemWidth();
    }

    ImUtil::SeperatorH();

    //KeyRender Loop

    for (auto& Event : KeyMgr.InputEvents){

        //Run The event name through the enum humanizer.
        std::string Pretty_Event = ImUtil::HumanizeString(Event.Event);

        //Is This current result filtered? -> Does Pretty_Event Contain SearcRes?
        //If it doesn't it means its not what the user searched for.
        bool Filtered = !ImUtil::ContainsString(Pretty_Event, SearchRes);
        
        if(Filtered && HideFiltered){
            continue;
        }
        
        Pretty_Event = Filtered ? Pretty_Event + " [Filtered]" : Pretty_Event;

        //Hack, Imgui will autoscale the child to fullscreen if values 0,0 are set.
        //If the child is off-screen the child is scaled to its contents.
        //There's no way to tell imgui to do that for on-screen elements currently.
        //So just hardcode it...
        ImGui::BeginChild(CurEventIndex++,{Width/Div, Filtered ? 35.0f : 300.f},true,true);

        { // --  CollapsingHeader Control Begin
            
            ImGui::BeginDisabled(Filtered || (RebindIndex != CurEventIndex && RebindIndex != 0));
            
            //Auto Collapse/expand based on if the control is filtered.
            ImGui::SetNextItemOpen(!Filtered);
            
            //Gray out Filtered Headers.
            ImGui::PushStyleColor(ImGuiCol_Header, (Filtered ? ImVec4(0.0f,0.0f,0.0f,0.1f) : ImGui::GetStyle().Colors[ImGuiCol_Header]));
    
            if(ImGui::CollapsingHeader(Pretty_Event.c_str(), ImGuiTreeNodeFlags_Bullet)){

                ImUtil::CheckBox("Disabled", &Event.Disabled,T3);
                
                //If Disabled: Don't draw at all.
                if(!Event.Disabled){

                    { //-- Basic (Easy to implement) Controls
                        ImUtil::CheckBox("Exclusive", &Event.Exclusive, T4);
                        ImUtil::ComboEx<Triggers>("Trigger Type",Event.Trigger, T5);
                        ImUtil::ComboEx<BlockInputTypes>("Block Input",Event.BlockInput, T6);
                        ImGui::InputFloat("Trigger After",&Event.Duration,0.1f,0.01f,"%.2f Seconds");
                        if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > ImUtil::TooltipDelay){
                            ImGui::SetTooltip(T7);
                        }
                    }

                    const bool IsRebinding = RebindIndex == CurEventIndex;
                    static bool prevKeysDown[1024] = { false };

                    {   // Keybind Hell...

                        

                        VisualKeyString = "";

                        const std::vector<std::string>& VisualKeyList = IsRebinding ? TempKeys : Event.Keys;

                        const int NumOfKeys = static_cast<int>(VisualKeyList.size());

                        for (int i = 0; i < NumOfKeys; i++){
                            VisualKeyString +=  VisualKeyList[i];

                            if(i != NumOfKeys - 1){
                                VisualKeyString += " + ";
                            }
                        }

                    }

                    const std::string ButtonText = IsRebinding ? (VisualKeyString.size() > 0 ? "Save" : "Enter New Binds") : "Rebind Action";
                    std::string InputText = VisualKeyString.size() == 0 ? "Press New Keys / ESC To Cancel" : VisualKeyString;
                    const float Pad = 4.0f;
                    //Disable Control Without Graying it out... This api will break in the future...
                    //As of v1.91.8 works as we want it to.
                    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                    ImGui::PushItemWidth(ImGui::CalcItemWidth() - (ImGui::CalcTextSize(ButtonText.c_str()).x + ImGui::GetStyle().CellPadding.x * 2.0f + Pad));
                    ImGui::InputText("##KeyRebind", &InputText, ImGuiInputTextFlags_ReadOnly);
                    if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > ImUtil::TooltipDelay){
                        ImGui::SetTooltip(T8);
                    }
                    ImGui::PopItemFlag();
                    ImGui::PopItemWidth();

                    ImGui::SameLine(0.f, Pad);

                    ImGui::BeginDisabled(TempKeys.size() == 0 && IsRebinding);
                    if(ImUtil::Button(ButtonText.c_str(),T9)){
                        RebindIndex = CurEventIndex;

                        if(IsRebinding && TempKeys.size() > 0){
                            //Save
                            Event.Keys = TempKeys;
                            TempKeys.clear();
                            RebindIndex = 0;
                        }
                    }
                    ImGui::EndDisabled();

                    //If Escape Stop Rebind
                    if(ImGui::IsKeyDown(ImGuiKey_Escape)){
                        RebindIndex = 0;
                        TempKeys.clear();
                    }

                    else if (IsRebinding && !ImGui::IsItemHovered()){

                        for (int key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key++)
                        {
                            // Detect a new key press (key is down now but wasn’t in previous frame)
                            if (ImGui::IsKeyPressed(static_cast<ImGuiKey>(key))){

                                // Convert the key to a string representation.
                                std::string keyName = GetDIKStringFromImGuiKey(static_cast<ImGuiKey>(key));
                                if(keyName == "INVALID") continue;
                                // Only append if it's not already in TempKeys.
                                if (std::find(TempKeys.begin(), TempKeys.end(), keyName) == TempKeys.end() && TempKeys.size() < 5){
                                    TempKeys.push_back(keyName);
                                }

                                // Sort TempKeys in descending order based on string length.
                                std::sort(TempKeys.begin(), TempKeys.end(), [](const std::string &a, const std::string &b) {
                                    return a.size() > b.size();
                                });
                                
                            }
                        }
                    }
                }
            }
            ImGui::EndDisabled();
            ImGui::PopStyleColor();

        }

        ImGui::EndChild();

        //Offset counter by -1 if Div is uneven
        if((CurEventIndex - (Div % 3 == 0)) % Div) {
            ImUtil::SeperatorV();
        }
    }
}