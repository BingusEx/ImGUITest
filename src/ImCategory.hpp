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

#include "ImUtil.hpp"

class ImCategory {
    protected:
    std::string title = "Default";
    std::string description = "Default";
    bool visible = true;

    public:
    virtual ~ImCategory() = default;

    virtual void Draw() = 0;
    virtual bool Save() = 0;
    virtual bool Load() = 0;

    [[nodiscard]] const inline std::string& GetTitle() {
        return title;
    }

    [[nodiscard]] const inline std::string& GetDescription() {
        return description;
    }

    [[nodiscard]] const inline bool IsVisible() {
        return visible;
    }

};

class ImCategoryManager {
    private:
    // List of categories
    std::vector<std::shared_ptr<ImCategory>> categories;

    public:
    ~ImCategoryManager() = default;
    
    //Would we need to keep track of more than 255 categories??
    uint8_t activeIndex;

    // Singleton accessor
    [[nodiscard]] static inline ImCategoryManager& GetSingleton() noexcept {
        static ImCategoryManager instance;
        return instance;
    }

    // Access the list of categories
    [[nodiscard]] inline std::vector<std::shared_ptr<ImCategory>>& GetCategories() {
        return categories;
    }

    // Add a new category
    inline void AddCategory(std::shared_ptr<ImCategory> category) {
        categories.push_back(std::move(category));
    }

    [[nodiscard]] float GetLongestCategory(){

        if(!ImUtil::ValidState()) return -1.0f;

        float longest = 0.0f;
        const float scale = ImGui::GetIO().FontGlobalScale;
        const float paddingX = (ImGui::GetStyle().FramePadding.x + 64.f) * scale;

        for(auto& category : categories){
            if(!category.get()->IsVisible()) continue;
            auto len = ImGui::CalcTextSize(category.get()->GetTitle().c_str());
            longest = std::max(len.x + paddingX ,longest);
        }

        return longest;
    }

    private:
    ImCategoryManager() = default;
    ImCategoryManager(const ImCategoryManager&) = delete;
    ImCategoryManager& operator=(const ImCategoryManager&) = delete;
};