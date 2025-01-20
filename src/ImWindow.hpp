#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_internal.h"
#include <d3d11.h>
#include <tchar.h>
#include <string>
#include <format>
#include <vector>
#include <iostream>
#include <memory>
#include <string>

#include <functional> // For std::function

#include "ImFont.hpp"
#include "ImStyle.hpp"
#include "ImBlur.hpp"
#include "ImUtil.hpp"

class ImWindow {

    public:

    enum WindowAnchor {
        kTopLeft,
        kTopRight,
        kCenter,
        kBottomLeft,
        kBottomRight,
        kTotal
    };

    bool Show = false;
    bool Focus = false;
    bool NeedsInput = true;
    bool Fixed = false;
    bool DoUpdate = true;

    ImVec2 Position = ImVec2(100.f, 100.f);      //Window Position
    //TODO Auto Calculate Based On Contents
    ImVec2 MinSize = ImVec2(400.f, 400.f);      //Minimum Window Size if AllowResize is true
    ImVec2 CornerPadding = ImVec2(30.f, 30.f);  //Padding from the corner of the screen does nothing if AllowMove is true
    float FixedScale = 80.0f;                   //Window scale relative to the viewport
    
    WindowAnchor AnchorPos = WindowAnchor::kCenter;

    std::string Name = "Default";   //Imgui Window Name
    std::string Title = "Default";  //Window Title
    ImGuiWindowFlags flags = ImGuiWindowFlags_None;

    virtual ~ImWindow() noexcept = default;

    virtual void Draw() = 0;

    ImVec2 GetAnchorPos(WindowAnchor a_position, ImVec2 a_padding) {
        auto v = ImGui::GetMainViewport();
        auto s = ImGui::GetWindowSize();

        //Get Total size first then subtract the viewport position to cancel out any offsets
        ImVec2 Origin = v->Size;
        Origin.x -= v->Pos.x;
        Origin.y -= v->Pos.y;

        //Subtract the window size to get the top left corner of the window
        Origin.x -= s.x;
        Origin.y -= s.y;

        switch (a_position) {
            case WindowAnchor::kTopLeft:
                return {a_padding.x, a_padding.y};
            case WindowAnchor::kTopRight:
                return {Origin.x - a_padding.x, a_padding.y};
            case WindowAnchor::kBottomLeft:
                return {a_padding.x, Origin.y - a_padding.y};
            case WindowAnchor::kBottomRight:
                return {Origin.x - a_padding.x, Origin.y - a_padding.y};
            // case WindowAnchor::kTopCenter:
            //     return {Origin.x * 0.5f, a_padding.y};
            // case WindowAnchor::kCenterLeft:
            //     return {a_padding.x, Origin.y * 0.5f};
            // case WindowAnchor::kCenterRight:
            //     return {Origin.x - a_padding.x, Origin.y * 0.5f};
            // case WindowAnchor::kBottomCenter:
            //     return {Origin.x * 0.5f, Origin.y - a_padding.y};
            case WindowAnchor::kCenter: default:
                return {Origin.x * 0.5f, Origin.y * 0.5f};
        }
    }
};

class ImWindowManager {

    private:
    std::vector<std::unique_ptr<ImWindow>> windows;
    ImFontManager& FontMgr = ImFontManager::GetSingleton();
    ImStyleManager& StyleMgr = ImStyleManager::GetSingleton();

    constexpr static std::string WMName = "GTSPluginWM";

    ~ImWindowManager() = default;

    public:

    void Init(){
        //Load Fonts
        FontMgr.Init();
        //Load Styles
        StyleMgr.SetupStyle();
    }


    [[nodiscard]] static inline ImWindowManager& GetSingleton() {
        static ImWindowManager instance;
        return instance;
    }


    void AddWindow(std::unique_ptr<ImWindow> a_window){
        windows.push_back(std::move(a_window));
		//logger::info("UIWindowManager::AddWindow {}", windows.back().get()->GetWindowData()->Name);
    }

    void Draw(){
        if (HasWindows()) {
			for (const auto& window : windows) {
				if (window->Show) {
                    ImGui::Begin((WMName + "##" + window->Name).c_str(), &window->Show, window->flags);
                    ImGui::PushFont(FontMgr.GetFont("text")); //Default font

                    window->flags = (window->Fixed ? (window->flags | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove) : (window->flags & ~ImGuiWindowFlags_NoResize & ~ImGuiWindowFlags_NoMove));
                    


                    //DoBackgroundBlur();

					window->Draw();


                    if(window->Fixed && !ImGui::GetIO().MouseDown[0]){
                        ImGui::SetWindowSize(ImUtil::ScaleToViewport(window->FixedScale));
                        ImGui::SetWindowPos(window->GetAnchorPos(window->AnchorPos, window->CornerPadding));
                    }

                    ImGui::PopFont();
                    ImGui::End();
				}
			}
		}
    }

    [[nodiscard]] inline ImWindow* GetWindowByName(const std::string& a_name) {
        for (const auto& window : windows) {
            if (window->Name == a_name) {
                return window.get();
            }
        }
        return nullptr;
    }

    [[nodiscard]] inline bool HasWindows() {
        return windows.size() > 0;
    }

    void SetWindowDimentions();

    //void SetDimensions(float a_offsetX /*= 0.f*/, float a_offsetY /*= 0.f*/, float a_sizeX /*= -1.f*/, float a_sizeY /*= -1.f*/, WindowAlignment a_alignment /*= WindowAlignment::kTopLeft*/, ImVec2 a_sizeMin /*= ImVec2(0, 0)*/, ImVec2 a_sizeMax /*= ImVec2(0, 0)*/, ImGuiCond_ a_cond /*= ImGuiCond_FirstUseEver*/);

    private:
    ImWindowManager() = default;
    ImWindowManager(const ImWindowManager&) = delete;
    ImWindowManager& operator=(const ImWindowManager&) = delete;



};
