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
        kTopCenter,
        kTopRight,
        kCenterLeft,
        kCenter,
        kCenterRight,
        kBottomLeft,
        kBottomCenter,
        kBottomRight,
        kTotal
    };

    bool Show = false;
    bool Focus = false;
    bool NeedsInput = true;
    bool AllowMove = true;
    bool AllowResize = true;

    ImVec2 Size = ImVec2(100.f, 100.f);         //Window Size
    ImVec2 Position = ImVec2(100.f, 100.f);     //Window Position
    ImVec2 MinSize = ImVec2(100.f, 100.f);      //Minimum Window Size if AllowResize is true
    ImVec2 CornerPadding = ImVec2(30.f, 30.f);  //Padding from the corner of the screen does nothin if AllowMove is true
    float FixedPadding = 0.0f;                  //Padding from the corner of the screen does nothin if AllowMove is true
    
    WindowAnchor AnchorPos = WindowAnchor::kCenter;

    std::string Name = "Default";
    std::string Title = "Default";
    ImGuiWindowFlags flags = ImGuiWindowFlags_None;

    virtual ~ImWindow() noexcept = default;

    virtual void Draw() = 0;

    static ImVec2 GetAnchorPos(WindowAnchor a_position, ImVec2 a_padding) {
        ImVec2 viewportSize = ImGui::GetMainViewport()->Size;
        switch (a_position) {
            case WindowAnchor::kTopLeft:
                return {a_padding.x, a_padding.y};
            case WindowAnchor::kTopRight:
                return {viewportSize.x - a_padding.x, a_padding.y};
            case WindowAnchor::kBottomLeft:
                return {a_padding.x, viewportSize.y - a_padding.y};
            case WindowAnchor::kBottomRight:
                return {viewportSize.x - a_padding.x, viewportSize.y - a_padding.y};
            case WindowAnchor::kTopCenter:
                return {viewportSize.x * 0.5f, a_padding.y};
            case WindowAnchor::kCenterLeft:
                return {a_padding.x, viewportSize.y * 0.5f};
            case WindowAnchor::kCenterRight:
                return {viewportSize.x - a_padding.x, viewportSize.y * 0.5f};
            case WindowAnchor::kBottomCenter:
                return {viewportSize.x * 0.5f, viewportSize.y - a_padding.y};
            case WindowAnchor::kCenter: default:
                return {viewportSize.x * 0.5f, viewportSize.y * 0.5f};
        }
    }
};


class ImWindowManager {

    private:
    std::vector<std::unique_ptr<ImWindow>> windows;
    ImFontManager& FontMgr = ImFontManager::GetSingleton();
    ImStyleManager& StyleMgr = ImStyleManager::GetSingleton();

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
                    ImGui::Begin(window->Name.c_str(), &window->Show, window->flags);
                    ImGui::PushFont(FontMgr.GetFont("text")); //Default font

                    window->flags = (!window->AllowResize ? (window->flags | ImGuiWindowFlags_NoResize) : (window->flags & ~ImGuiWindowFlags_NoResize));
                    window->flags = (!window->AllowMove ? (window->flags | ImGuiWindowFlags_NoMove) : (window->flags & ~ImGuiWindowFlags_NoMove));
                    
                    if(!window->AllowResize){
                        //ImGui::SetNextWindowSizeConstraints(window->MinSize, ImVec2(FLT_MAX, FLT_MAX));
                        window->Size = ImUtil::ScaleToViewport(0.1f);

                        ImGui::SetWindowSize(window->Size);
                        ImGui::SetWindowPos(window->GetAnchorPos((ImWindow::WindowAnchor)window->AnchorPos, ImVec2(50.f, 50.f)));
                    }

                    //DoBackgroundBlur();

					window->Draw();

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
