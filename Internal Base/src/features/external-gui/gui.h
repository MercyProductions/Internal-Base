#pragma once

#include "../../../libs/imgui/imgui.h"
#include "../../../libs/imgui/imgui_impl_win32.h"
#include "../../../libs/imgui/imgui_impl_dx12.h"
#include "../../../libs/imgui/imgui_internal.h"
#include "../../../libs/imgui/fonts.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <vector>
#include <string>
#include <tchar.h>

#define IMGUI_DEFINE_MATH_OPERATORS

#ifdef _DEBUG
    #define DX12_ENABLE_DEBUG_LAYER
#endif

#ifdef DX12_ENABLE_DEBUG_LAYER
    #include <dxgidebug.h>
    #pragma comment(lib, "dxguid.lib")
#endif

struct FrameContext
{
    ID3D12CommandAllocator* CommandAllocator;
    UINT64 FenceValue;
};


inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) {
    return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) {
    return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline ImVec2 operator/(const ImVec2& vec, float scalar) {
    return ImVec2(vec.x / scalar, vec.y / scalar);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class EXTERNALGUI {
public:
    static EXTERNALGUI& GetInstance() {
        static EXTERNALGUI instance;
        return instance;
    }

    bool Setup();
    void RenderGUI();

private:

    // Data
    static inline int const NUM_FRAMES_IN_FLIGHT = 3;
    FrameContext g_frameContext[NUM_FRAMES_IN_FLIGHT] = {};
    UINT g_frameIndex = 0;

    static inline int const NUM_BACK_BUFFERS = 3;
    ID3D12Device* g_pd3dDevice = nullptr;
    ID3D12DescriptorHeap* g_pd3dRtvDescHeap = nullptr;
    ID3D12DescriptorHeap* g_pd3dSrvDescHeap = nullptr;
    ID3D12CommandQueue* g_pd3dCommandQueue = nullptr;
    ID3D12GraphicsCommandList* g_pd3dCommandList = nullptr;
    ID3D12Fence* g_fence = nullptr;
    HANDLE g_fenceEvent = nullptr;
    UINT64 g_fenceLastSignaledValue = 0;
    IDXGISwapChain3* g_pSwapChain = nullptr;
    HANDLE g_hSwapChainWaitableObject = nullptr;
    ID3D12Resource* g_mainRenderTargetResource[NUM_BACK_BUFFERS] = {};
    D3D12_CPU_DESCRIPTOR_HANDLE  g_mainRenderTargetDescriptor[NUM_BACK_BUFFERS] = {};

    //Helpers
    ImDrawList* drawlist;
    ImVec2 pos;
    ImFont* notiffont;
    ImFont* logo;
    ImFont* logo_bigger;
    int tabs = 0;
    int subtabs = 0;
    int notifs = 0;
    int notiftype = 0;
    static inline int notify_select = 0;
    const char* notify_items[2]{ "Circle", "Line" };

    char notiftitle[64] = "Hello Mercy";
    char notifdesc[64] = "This is a super cool description";
    char notifsecondtitle[64] = "I completely ran out of ideas apologies";
    int notifpressed = 0;
    float anim = 0;
    float resizeanim = 0;
    float logomove = 0;
    float finalresize = 0;
    float closeanim = 0;
    bool shouldmove = true;
    bool shouldresize = true;
    bool logoshouldmove = true;
    bool finalresizeshouldmove = true;
    bool closemove = true;

    bool devconsole = false;

    bool CreateDeviceD3D(HWND hWnd);
    void CleanupDeviceD3D();
    void CreateRenderTarget();
    void CleanupRenderTarget();
    void WaitForLastSubmittedFrame();
    FrameContext* WaitForNextFrameResources();
    LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    ImVec2 CenterText(ImVec2 min, ImVec2 max, const char* text) {
        return min + (max - min) / 2.0f - ImGui::CalcTextSize(text) / 2.0f;
    }

    EXTERNALGUI() = default;
    ~EXTERNALGUI() = default;

    EXTERNALGUI(const EXTERNALGUI&) = delete;
    EXTERNALGUI& operator=(const EXTERNALGUI&) = delete;
};