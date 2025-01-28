#include "ImWindowManager.hpp"

using namespace UI;

//TODO Move Init to UIManager
void ImWindowManager::Init(){
    FontMgr.Init();
    StyleMgr.LoadStyle();
}

void ImWindowManager::AddWindow(std::unique_ptr<ImWindow> a_window){

    assert(a_window != nullptr);

    if(HasWindows()){
        for(const auto& window : windows){
            if(window->Name == a_window->Name){
                //logger::warn("UIWindowManager::AddWindow: Window with name {} already exists, Not Adding New Window", a_window->Name);
                return;
            }
        }
    }

    windows.push_back(std::move(a_window));
    //logger::info("UIWindowManager::AddWindow {}", windows.back().get()->GetWindowData()->Name);
}

void ImWindowManager::Draw(){
    if (HasWindows()) {
        for (const auto& window : windows) {
            if (window->Show) {
                
                //Begin Window
                ImGui::Begin((wmName + "##" + window->Name).c_str(), &window->Show, window->flags);
                ImGui::PushFont(FontMgr.GetFont("text")); //Default font

                window->Draw();

                ImGui::PopFont();
                ImGui::End();
            }
        }
    }
}

//Gets a ptr to the window which fully matches the "Name" var.
//Name var gets set in the ctor of the child window, otherwise its "Default"
//If 2 Or more default windows exist only the earliest one will be returned
ImWindow* ImWindowManager::GetWindowByName(const std::string& a_name) {
    for (const auto& window : windows) {
        if (window->Name == a_name) {
            return window.get();
        }
    }
    return nullptr;
}
