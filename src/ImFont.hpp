#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <utility>
#include <algorithm>
#include <span>
#include <string>


class ImFontManager {
    private:

    template <typename... T>
        bool IsAnyNull(T... args) {
        return ((args == nullptr) || ...);
    }

    ImFont* _FontTitle;
    ImFont* _FontText ;
    ImFont* _FontSidebar;
    ImFont* _FontSubscript;
    ImFont* _FontFooter;

    const std::string _ext = ".ttf";
    const std::string _basePath = "GTSPlugin\\Fonts\\";

    const std::string _SkyrimGUI_Light = _basePath +"Futura Condensed Light" + _ext;
    const std::string _SkyrimGUI_Medium = _basePath + "Futura Condensed Medium" + _ext;
    const std::string _SkyrimGUI_Console = _basePath + "Arial" + _ext;

    public:
    ~ImFontManager() = default;

    [[nodiscard]] static inline ImFontManager& GetSingleton(){
        static ImFontManager instance;
        return instance;
    }

    void Init(ImGuiIO& io){        
        //Default
        io.Fonts->AddFontDefault();

        _FontSidebar =      io.Fonts->AddFontFromFileTTF(_SkyrimGUI_Light.c_str(), 28.0f);

        _FontTitle =        io.Fonts->AddFontFromFileTTF(_SkyrimGUI_Medium.c_str(), 56.0f);
        _FontFooter =       io.Fonts->AddFontFromFileTTF(_SkyrimGUI_Medium.c_str(), 20.0f);

        _FontText =         io.Fonts->AddFontFromFileTTF(_SkyrimGUI_Console.c_str(), 18.0f);
        _FontSubscript =    io.Fonts->AddFontFromFileTTF(_SkyrimGUI_Console.c_str(), 12.0f);
        
        if(IsAnyNull(_FontSidebar,_FontTitle,_FontFooter,_FontText,_FontSubscript)){
            //logger::critical("Could load load some fonts");
            //SKSE Report and fail
            assert(false);
        }

    }

    inline void Title(){
        if(_FontTitle) [[likely]]
        ImGui::PushFont(_FontTitle);
    }

    inline void Footer(){
        if(_FontFooter) [[likely]]
        ImGui::PushFont(_FontFooter);
    }

    inline void Text(){
        if(_FontText) [[likely]]
        ImGui::PushFont(_FontText);
    }

    inline void Subscript(){
        if(_FontSubscript) [[likely]]
        ImGui::PushFont(_FontSubscript);
    }

    inline void Sidebar(){
        if(_FontSidebar) [[likely]]
        ImGui::PushFont(_FontSidebar);
    }

    //Pointless, but its here for completness' sake
    inline void Pop(){
        ImGui::PopFont();
    }

};