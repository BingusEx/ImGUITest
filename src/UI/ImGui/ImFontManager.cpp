#include "ImFontManager.hpp"

using namespace UI;

void ImFontManager::Init(){
    //Default
    ImGui::GetIO().Fonts->AddFontDefault();

    //Initalzie font data, add any new font defines here.
    AddFont( new FontData("sidebar",_SkyrimGUI_Light, 28.0f));
    AddFont( new FontData("title",_SkyrimGUI_Medium, 56.0f));
    AddFont( new FontData("footer",_SkyrimGUI_Medium, 20.0f));
    AddFont( new FontData("text",_SkyrimGUI_Console, 18.0f));
    AddFont( new FontData("subscript",_SkyrimGUI_Console, 12.0f));
    AddFont( new FontData("widgetbody",_SkyrimGUI_Light, 18.0f));
    AddFont( new FontData("widgettitle",_SkyrimGUI_Light, 22.0f));

    for(auto& [key, value] : Fonts){
        if(value->font == nullptr){
            //logger::critical("Could not load font: {}", key);
            //SKSE Report and fail
        }
    }
}

void ImFontManager::AddFont(FontData* a_font){
    ImGuiIO& io = ImGui::GetIO();
    ImFontAtlas* fontAtlas = io.Fonts;

    if(a_font) {
        Fonts[a_font->name] = a_font;
        a_font->font = fontAtlas->AddFontFromFileTTF(a_font->path.c_str(), a_font->size, a_font->conf);
    }
}

// Utility function to get a font with fallback
ImFont* ImFontManager::GetFont(const std::string& fontName) {
    auto it = Fonts.find(fontName);
    if (it != Fonts.end()) {
        return it->second->font;  // Font found
    }
    return ImGui::GetIO().Fonts->Fonts[0];    // Fallback to default font
}

void ImFontManager::ProcessActions(){
    if(!ActionQueue.empty()){

        auto [type, value] = ActionQueue.top();
        
        switch (type) {

            case kRasterizerScale:{
                ChangeRasterizerScaleImpl(value);
                break;
            }

            default:{
                //logger::warn("ImFontmanager: Unimplemented Action!")
                break;
            }

        }

        ActionQueue.pop();
    }
}


void ImFontManager::ChangeRasterizerScaleImpl(float a_scale) {
    for(auto [key, value] : Fonts){
        if(value->font != nullptr){
            value->conf->RasterizerDensity = a_scale;
        }
    }
    RebuildFontAtlas();
}

void ImFontManager::RebuildFontAtlas(){
    ImGui::GetIO().Fonts->Build();

    //Causes a complete reinit of the imgui context
    //Idealy we'd only want to invalidate the font related stuff
    //That requires a modification to ImGuiDX11, which we can't do... :(
    //As long as you dont spam this it's fine.
    //Even if you did it doesn't cause a memleak. It just lags for ~100ms on each call
    ImGui_ImplDX11_InvalidateDeviceObjects();
}
