#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

namespace UI {

    class ImFontManager {
        private:

        //Consts
        const std::string _ext = ".ttf";
        const std::string _basePath = "GTSPlugin\\Fonts\\";

        const std::string _SkyrimGUI_Light = _basePath +"Futura Condensed Light" + _ext;
        const std::string _SkyrimGUI_Medium = _basePath + "Futura Condensed Medium" + _ext;
        const std::string _SkyrimGUI_Console = _basePath + "Arial" + _ext;

        //Structs
        typedef struct FontData {
            std::string name;
            std::string path;
            float size;
            ImFontConfig* conf = new ImFontConfig();
            ImFont* font;
            FontData(const std::string& name, const std::string& path, float size) : name(name), path(path), size(size) {
                //This is probably overkill...
                conf->OversampleH = 8;
                conf->OversampleV = 8;
            }
        } FontData;

        enum AQueueType {
            kRasterizerScale
        };

        //Lists
        std::stack<std::pair<AQueueType, float>> ActionQueue;
        std::unordered_map<std::string, FontData*> Fonts;

        //Funcs
        void ChangeRasterizerScaleImpl(float a_scale);
        void RebuildFontAtlas();

        public:
        ~ImFontManager() = default;

        [[nodiscard]] static inline ImFontManager& GetSingleton() {
            static ImFontManager instance;
            return instance;
        }

        inline void PushAction(AQueueType a_type, float a_value){
            ActionQueue.push(std::make_pair(a_type, a_value));
        }

        inline void ChangeRasterizerScale(float a_scale) {
            PushAction(AQueueType::kRasterizerScale,a_scale);
        }

        void Init();
        void AddFont(FontData* a_font);
        [[nodiscard]] ImFont* GetFont(const std::string& fontName);
        void ProcessActions();

    };
}