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


    //TODO: All these consts need to be loaded from the toml
    const std::string _ext = ".ttf";
    const std::string _basePath = "GTSPlugin\\Fonts\\";

    const std::string _SkyrimGUI_Light = _basePath +"Futura Condensed Light" + _ext;
    const std::string _SkyrimGUI_Medium = _basePath + "Futura Condensed Medium" + _ext;
    const std::string _SkyrimGUI_Console = _basePath + "Arial" + _ext;

    typedef struct FontData {
        std::string name;
        std::string path;
        float size;
        FontData(const std::string& name, const std::string& path, float size) : name(name), path(path), size(size) {}
    } FontData;

    //std::unordered_map<FontData*, ImFont*> Fonts;
    std::unordered_map<std::string, ImFont*> Fonts;

    public:
    ~ImFontManager() = default;


    [[nodiscard]] static inline ImFontManager& GetSingleton(){
        static ImFontManager instance;
        return instance;
    }

    //TODO: Load Paths from config
    void Init(){
        
        ImGuiIO& io = ImGui::GetIO();
        ImFontAtlas* fontAtlas = io.Fonts;

        io.Fonts->AddFontDefault();

        //Initalzie default font data
        // auto a = new FontData("sidebar",_SkyrimGUI_Light, 28.0f);
        // auto a = new FontData("title",_SkyrimGUI_Medium, 56.0f);
        // auto a = new FontData("footer",_SkyrimGUI_Medium, 20.0f);
        // auto a = new FontData("text",_SkyrimGUI_Console, 18.0f);
        // auto a = new FontData("subscript",_SkyrimGUI_Console, 12.0f);


        Fonts["sidebar"] =      fontAtlas->AddFontFromFileTTF(_SkyrimGUI_Light.c_str(), 28.0f);
        Fonts["title"] =        fontAtlas->AddFontFromFileTTF(_SkyrimGUI_Medium.c_str(), 56.0f);
        Fonts["footer"] =       fontAtlas->AddFontFromFileTTF(_SkyrimGUI_Medium.c_str(), 28.0f);
        Fonts["text"] =         fontAtlas->AddFontFromFileTTF(_SkyrimGUI_Console.c_str(), 18.0f);
        Fonts["subscript"] =    fontAtlas->AddFontFromFileTTF(_SkyrimGUI_Console.c_str(), 12.0f);

        Fonts["widgetbody"] =    fontAtlas->AddFontFromFileTTF(_SkyrimGUI_Light.c_str(), 18.0f);
        Fonts["widgettitle"] =   fontAtlas->AddFontFromFileTTF(_SkyrimGUI_Light.c_str(), 22.0f);


        for(auto& [key, value] : Fonts){
            if(value == nullptr){
                //logger::critical("Could not load font: {}", key);
                //SKSE Report and fail
            }
        }
    }

    // Utility function to get a font with fallback
    ImFont* GetFont(const std::string& fontName) {
        auto it = Fonts.find(fontName);
        if (it != Fonts.end()) {
            return it->second;  // Font found
        }
        return ImGui::GetIO().Fonts->Fonts[0];    // Fallback to default font
    }

};