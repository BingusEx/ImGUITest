// Dear ImGui: standalone example application for DirectX 11
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include "ui.h"
#include <string>
#include <format>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include "imgui_internal.h"

// Data
static ID3D11Device*            g_pd3dDevice = NULL;
static ID3D11DeviceContext*     g_pd3dDeviceContext = NULL;
static IDXGISwapChain*          g_pSwapChain = NULL;
static ID3D11RenderTargetView*  g_mainRenderTargetView = NULL;

ImFont* _FontTitle = nullptr;
ImFont* _FontText = nullptr;
ImFont* _FontSidebar = nullptr;

//Predefined colors {R, G, B, A} (0.0 to 1.0f)
constexpr ImVec4 _ColorRed = {1.0f, 0.15f, 0.15f, 1.0f};
std::once_flag _CategoryInitFlag;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Singleton
class ImCategory {
    protected:
    std::string title;
    std::string description;

    public:
    virtual ~ImCategory() = default;
    ImCategory() : title("Category"), description("Default description") {}
    
    virtual void Draw() {
        ImGui::Text("No Content");
    };

    const std::string& GetTitle() {
        return title;
    }

    const std::string& GetDescription() {
        return description;
    }

};

[[nodiscard]] static inline bool ImGuiValidState() noexcept {
    ImGuiContext* ctx = ImGui::GetCurrentContext();
    return ctx && ctx->WithinFrameScope;
}

class ImCategoryManager {
    private:
    // List of categories
    std::vector<std::shared_ptr<ImCategory>> categories;
    
    public:
    ~ImCategoryManager() = default;

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

        if(!ImGuiValidState()) return -1.0f;

        float longest = 0.0f;

        for(auto& category : categories){
            auto len = ImGui::CalcTextSize(category.get()->GetTitle().c_str());
            longest = std::max(len.x + len.y,longest);
        }

        return longest;
    }

    private:
    ImCategoryManager() = default;
    ImCategoryManager(const ImCategoryManager&) = delete;
    ImCategoryManager& operator=(const ImCategoryManager&) = delete;
};

class CategoryGeneral : public ImCategory {
    public:
    CategoryGeneral(){
        title = "General";
        description = "General Settings";
    }

    void Draw() override {
        ImGui::Text("[PH] Content for the General page goes here");
    }
};

class CategoryInfo : public ImCategory {
    public:
    CategoryInfo(){
        title = "Info";
        description = "Show actor information";
    }

    void Draw() override {
        ImGui::Text("[PH] Content for the Info page goes here");
    }
};

class CategoryGameplay : public ImCategory {
    public:
    CategoryGameplay(){
        title = "Gameplay";
        description = "Gameplay Settings";
    }

    // void Draw() override {
    //     ImGui::Text("[PH] Content for the Gameplay page goes here");
    // }
};



void Setup(){
    auto& CatMgr = ImCategoryManager::GetSingleton();
    CatMgr.AddCategory(std::make_shared<CategoryGeneral>());
    CatMgr.AddCategory(std::make_shared<CategoryInfo>());
    CatMgr.AddCategory(std::make_shared<CategoryGameplay>());
}

inline void DrawTitle(){
    {

    }


}

inline void DrawInfo(/*Actor* TargetActor */){

    //Dummy Values
    float _currentScale = 1.42f;
    float _maxScale = 10.85f;
    std::string res = std::format("{}/{}({}/{})",_currentScale,_maxScale,_currentScale * 1.82f,_maxScale * 1.82f);

    // float _aspectOfGTS = 43.0f;
    // float _weight = 243.43;

    // float _damageResist = 12.0f;
    // float _carryWeight = 220.0f;
    // float _speed = 113.0f;
    // float _jumpHeight = 103.0f;
    // float _damage = 141.0f;

    ImGui::BeginGroup();

    ImGui::ProgressBar(_currentScale/_maxScale);


    ImGui::EndGroup();

}



void ShowSplitWindowWithChildWindows() {
    bool open = true;
    constexpr ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar;
    ImGui::Begin("Main Window", &open, flags);

    auto& CatMgr = ImCategoryManager::GetSingleton();
    auto& categories = CatMgr.GetCategories();
    static size_t selectedCategory = 0;


    {   // Title

        ImGui::PushFont(_FontTitle);  // Push larger font
        ImGui::BeginChild("TitleBar", ImVec2(0,ImGui::GetTextLineHeight() + 20), true);
        //ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(200, ImGui::GetStyle().FramePadding.y));
        ImGui::Text("Size Matters Configuration");
        ImGui::PopFont();            // Restore the previous font
        //ImGui::PopStyleVar();
        ImGui::EndChild();
    }

    {  // Sidebar

        //Initialize the sidebar width
        static float sidebarWidth = 100.0f;
        std::call_once(_CategoryInitFlag, [](){
            auto length = ImCategoryManager::GetSingleton().GetLongestCategory();
            if(length > 0.0f){
                sidebarWidth = length;
            }
        });
        
        //TODO Lenght Should be Slightly smaller to allow for a small box at the bottom containing mod version and stuff.
        ImGui::BeginChild("Sidebar", ImVec2(sidebarWidth, 0), true);
        ImGui::PushFont(_FontSidebar);
        
        // Display the categories in the sidebar
        for (size_t i = 0; i < categories.size(); i++) {
            ImCategory* category = categories[i].get();
            if (ImGui::Selectable(category->GetTitle().c_str(), selectedCategory == i)) {
                selectedCategory = i;
            }
        }

        ImGui::PopFont();
        ImGui::EndChild();

    }

    // { // Sidebar Info



    // }

    ImGui::SameLine(); // Position the content area to the right of the sidebar

    { // Content Area

        ImGui::BeginChild("Content", ImVec2(0, 0), true); // Remaining width

        // Validate selectedCategory to ensure it's within bounds
        if (selectedCategory >= 0 && selectedCategory < categories.size()) {
            ImCategory* selected = categories[selectedCategory].get();
            selected->Draw(); // Call the Draw method of the selected category
        } 
        else {
            ImGui::TextColored(_ColorRed,"Invalid category or no categories exist!");
        }

        ImGui::EndChild();
    }

    ImGui::End();
}


// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"ImGui Example", NULL };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui DirectX11 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    // Setup Dear ImGui style


    SetupImGuiStyle();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    io.Fonts->AddFontDefault();
    _FontTitle = io.Fonts->AddFontFromFileTTF("Futura Condensed.ttf", 56.0f); // Larger font size
    _FontSidebar = io.Fonts->AddFontFromFileTTF("Futura Condensed.ttf", 30.0f); // Larger font size
    _FontText = io.Fonts->AddFontFromFileTTF("arial.ttf", 22.0f); //

    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    Setup();
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }


        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::PushFont(_FontText);
        ShowSplitWindowWithChildWindows();
        ImGui::PopFont();

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_WARP, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
        case WM_SIZE:
            if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
            {
                CleanupRenderTarget();
                g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
                CreateRenderTarget();
            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        case WM_DPICHANGED:
            if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
            {
                //const int dpi = HIWORD(wParam);
                //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
                const RECT* suggested_rect = (RECT*)lParam;
                ::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
            }
            break;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
