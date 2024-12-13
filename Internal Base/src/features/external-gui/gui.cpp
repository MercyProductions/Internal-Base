#include "../../../pch.h"

#include "gui.h"

void EXTERNALGUI::RenderGUI() 
{

    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    {
        //notifications
        if (notiftype == 0)
        {
            ImGui::Begin("Notif0", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove);
            {
                if (notifpressed && 1)
                {
                    shouldmove = true;

                    static float timer = 0.f;
                    timer += 4.f * ImGui::GetIO().DeltaTime;

                    if (timer > 10.f)
                        shouldresize = false;

                    if (timer > 20.f)
                        shouldmove = false;

                    if (timer > 30.f)
                        logoshouldmove = false;

                    if (timer > 40.f)
                        finalresizeshouldmove = false;

                    if (timer > 50.f)
                    {
                        notifpressed = 0;
                        closemove = false;
                    }

                    ImGuiContext& g = *GImGui;
                    anim = ImLerp(anim, shouldmove ? 0.f : 300.f, g.IO.DeltaTime * 6.f);
                    resizeanim = ImLerp(resizeanim, shouldresize ? 0.f : 320.f, g.IO.DeltaTime * 5.f);
                    logomove = ImLerp(logomove, logoshouldmove ? 0.f : 320.f, g.IO.DeltaTime * 5.f);
                    finalresize = ImLerp(finalresize, finalresizeshouldmove ? 0.f : 320.f, g.IO.DeltaTime * 5.f);
                    closeanim = ImLerp(closeanim, closemove ? 0.f : 500.f, g.IO.DeltaTime * 1.f);

                    //sizing + pos
                    ImGui::SetWindowSize(ImVec2(80 + resizeanim + resizeanim - finalresize - finalresize, 60));
                    ImGui::SetWindowPos(ImVec2(900 - resizeanim + finalresize, 900 + closeanim));

                    //helpers def
                    drawlist = ImGui::GetWindowDrawList();
                    pos = ImGui::GetWindowPos() + ImVec2(5, 5);

                    //main draws
                    drawlist->AddRectFilled(pos, ImVec2(pos.x + 70 + resizeanim + resizeanim - finalresize - finalresize, pos.y + 50), ImColor(0, 79, 65, 255), 20.f); //bg
                    drawlist->AddRect(pos, ImVec2(pos.x + 70 + resizeanim + resizeanim - finalresize - finalresize, pos.y + 50), ImColor(0, 229, 189, 255), 20.f, 0, 1.5f); //rect

                    //logo
                    ImGui::PushFont(logo);
                    ImGui::SetCursorPos(ImVec2(15 + logomove - finalresize, 7));
                    ImGui::TextColored(ImColor(255, 255, 255, 255), "A");
                    ImGui::SetCursorPos(ImVec2(15 + logomove - finalresize, 7));
                    ImGui::TextColored(ImColor(0, 229, 189), "B");
                    ImGui::SetCursorPos(ImVec2(15 + logomove - finalresize, 7));
                    ImGui::TextColored(ImColor(0, 229, 189), "C");
                    ImGui::PopFont();

                    //render notifts
                    ImGui::PushFont(notiffont);
                    ImGui::SetCursorPos(ImVec2(78, 13 - anim));
                    ImGui::TextColored(ImColor(255, 255, 255, 255), notiftitle);
                    ImGui::PopFont();

                    ImGui::SetCursorPos(ImVec2(78, 32 - anim));
                    ImGui::TextColored(ImColor(255, 255, 255, 255), notifdesc);

                    ImGui::PushFont(notiffont);
                    ImGui::SetCursorPos(ImVec2(78, 321 - anim - logomove));
                    ImGui::TextColored(ImColor(255, 255, 255, 255), notifsecondtitle);
                    ImGui::PopFont();

                    ImGui::PushFont(notiffont);
                    ImGui::SetCursorPos(ImVec2(80, 341 - logomove - finalresize));
                    ImGui::TextColored(ImColor(255, 255, 255, 255), "Welcome to RageByte");

                    ImGui::SetCursorPos(ImVec2(475, 341 - logomove - finalresize));
                    ImGui::TextColored(ImColor(255, 255, 255, 255), "Dominate the game!");
                    ImGui::PopFont();
                }
            }
            ImGui::End();
        }
        if (notiftype == 1)
        {
            ImGui::Begin("Notif1", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove);
            {
                if (notifpressed && 1)
                {
                    shouldmove = false;

                    static float timer = 0.f;
                    timer += 2.f * ImGui::GetIO().DeltaTime;

                    if (timer > 10.f)
                        shouldmove = true;

                    if (timer > 20.0f)
                    {
                        timer = 0.f;
                        notifpressed = 0;
                    }
                }

                ImGuiContext& g = *GImGui;
                anim = ImLerp(anim, shouldmove ? 0.f : 800.f, g.IO.DeltaTime * 6.f);
                if (anim <= 799.f)
                    shouldresize = true;
                else
                    shouldresize = false;

                resizeanim = ImLerp(resizeanim, shouldresize ? 0.f : 310.f, g.IO.DeltaTime * 5.f);

                //sizing + pos
                ImGui::SetWindowSize(ImVec2(80 + resizeanim, 60));
                ImGui::SetWindowPos(ImVec2(20, -780 + anim));

                //helpers def
                drawlist = ImGui::GetWindowDrawList();
                pos = ImGui::GetWindowPos() + ImVec2(5, 5);

                //main draws
                drawlist->AddRectFilled(pos, ImVec2(pos.x + 70 + resizeanim, pos.y + 50), ImColor(0, 79, 65, 255), 20.f); //bg
                drawlist->AddRect(pos, ImVec2(pos.x + 70 + resizeanim, pos.y + 50), ImColor(0, 229, 189, 255), 20.f, 0, 1.5f); //rect

                //logo
                ImGui::PushFont(logo);
                ImGui::SetCursorPos(ImVec2(15, 7));
                ImGui::TextColored(ImColor(255, 255, 255, 255), "A");
                ImGui::SetCursorPos(ImVec2(15, 7));
                ImGui::TextColored(ImColor(0, 229, 189), "B");
                ImGui::SetCursorPos(ImVec2(15, 7));
                ImGui::TextColored(ImColor(0, 229, 189), "C");
                ImGui::PopFont();

                //render notifts
                ImGui::PushFont(notiffont);
                ImGui::SetCursorPos(ImVec2(78, 13));
                ImGui::TextColored(ImColor(255, 255, 255, 255), notiftitle);
                ImGui::PopFont();

                ImGui::SetCursorPos(ImVec2(78, 32));
                ImGui::TextColored(ImColor(255, 255, 255, 255), notifdesc);
            }
            ImGui::End();
        }

        ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);

        //sizing
        ImGui::SetWindowSize(ImVec2(490, 440));

        //helpers def
        drawlist = ImGui::GetWindowDrawList();
        pos = ImGui::GetWindowPos() + ImVec2(5, 5);

        //main rect
        drawlist->AddRectFilled(pos, ImVec2(pos.x + 480, pos.y + 430), ImColor(29, 40, 54, 150), 6.f, ImDrawFlags_RoundCornersAll);

        //title
        drawlist->AddRectFilled(pos, ImVec2(pos.x + 480, pos.y + 25), ImColor(29, 40, 54, 255), 6.f, ImDrawFlags_RoundCornersTop);
        drawlist->AddText(CenterText(pos, ImVec2(pos.x + 480, pos.y + 25), "RageByte - MWIII"), ImColor(165, 186, 197, 255), "RageByte - MWIII");

        //tabs
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        ImGui::SetCursorPos(ImVec2(5, 35));
        ImGui::BeginGroup();
        {
            if (devconsole)
            {
                if (ImGui::Tabs("Players", ImVec2(80, 20), tabs == 0)) tabs = 0;
                if (ImGui::Tabs("Radar", ImVec2(80, 20), tabs == 1)) tabs = 1;
                if (ImGui::Tabs("Loot", ImVec2(80, 20), tabs == 2)) tabs = 2;
                if (ImGui::Tabs("Aim", ImVec2(80, 20), tabs == 3)) tabs = 3;
                if (ImGui::Tabs("Misc", ImVec2(80, 20), tabs == 4)) tabs = 4;
                if (ImGui::Tabs("Dev", ImVec2(80, 20), tabs == 5)) tabs = 5;
            }
            else
            {
                if (ImGui::Tabs("Players", ImVec2(96, 20), tabs == 0)) tabs = 0;
                if (ImGui::Tabs("Radar", ImVec2(96, 20), tabs == 1)) tabs = 1;
                if (ImGui::Tabs("Loot", ImVec2(96, 20), tabs == 2)) tabs = 2;
                if (ImGui::Tabs("Aim", ImVec2(96, 20), tabs == 3)) tabs = 3;
                if (ImGui::Tabs("Misc", ImVec2(96, 20), tabs == 4)) tabs = 4;
            }
        }
        ImGui::EndGroup();

        //subtabs ( if it's the case )
        if (tabs == 0)
        {
            ImGui::SetCursorPos(ImVec2(5, 55));
            ImGui::BeginGroup();
            {
                if (ImGui::Tabs("Colors", ImVec2(240, 20), subtabs == 0)) subtabs = 0;
                if (ImGui::Tabs("Settings", ImVec2(240, 20), subtabs == 1)) subtabs = 1;
            }
            ImGui::EndGroup();
        }

        ImGui::PopStyleVar(); // this pops the itemspacing push

        //functions
        if (tabs == 0)
        {
            ImGui::SetCursorPos(ImVec2(10, 80));
            ImGui::BeginChild("MainChild", ImVec2(470, 345));
            {
                //demo funcs
                static bool checkbox[8];
                static int sliderint[4];

                //render funcs
                ImGui::SetCursorPos(ImVec2(10, 10));
                ImGui::BeginGroup();
                {
                    ImGui::Checkbox("Only Visible", &checkbox[0]);
                    ImGui::Checkbox("Friends", &checkbox[1]);
                    ImGui::Checkbox("Name", &checkbox[2]);
                    ImGui::Checkbox("Line", &checkbox[3]);
                    ImGui::Checkbox("Health", &checkbox[4]);
                    ImGui::Checkbox("Box 2D", &checkbox[5]);
                    ImGui::Checkbox("Distance", &checkbox[6]);
                    ImGui::Checkbox("Skeleton", &checkbox[7]);
                    ImGui::SliderInt("Size line skeleton", &sliderint[0], 0, 10);
                    ImGui::SliderInt("Skeleton draw distance", &sliderint[1], 0, 100);
                    ImGui::Checkbox("Developer Console", &devconsole);
                }
                ImGui::EndGroup();
            }
            ImGui::EndChild();
        }

        if (tabs == 1)
        {
            ImGui::SetCursorPos(ImVec2(10, 60));
            ImGui::BeginChild("MainChild", ImVec2(470, 365));
            {
                //demo funcs
                static bool checkbox = false;
                static int sliderint = 0;
                static float sliderfloat = 0.f;
                static int combo = 0;
                static const char* multi_items[5] = { "One", "Two", "Three", "Four", "Five" };
                static bool multi_items_count[5];
                static int key = 0;

                //render funcs
                ImGui::SetCursorPos(ImVec2(10, 10));
                ImGui::BeginGroup();
                {
                    ImGui::Checkbox("Checkbox", &checkbox);
                    ImGui::SliderInt("Slider Int", &sliderint, 0, 100);
                    ImGui::SliderFloat("Slider Float", &sliderfloat, 0.f, 100.f, "%.1f");
                    ImGui::Combo("Combo", &combo, "Selectable 1\0\Selectable 2\0\Selectable 3", 3);
                    ImGui::MultiCombo("Multicombo", multi_items_count, multi_items, 5);
                    ImGui::Keybind("Keybind", &key);
                }
                ImGui::EndGroup();
            }
            ImGui::EndChild();
        }

        //achievements
        if (tabs == 2)
        {
            ImGui::SetCursorPos(ImVec2(10, 60));
            ImGui::BeginChild("MainChild", ImVec2(470, 365));
            {
                //render funcs
                ImGui::SetCursorPos(ImVec2(10, 10));
                ImGui::BeginGroup();
                {
                    ImGui::InputText("Notification Title", notiftitle, 64);
                    ImGui::InputText("Notification Description", notifdesc, 64);
                    ImGui::InputText("Notification Second Title", notifsecondtitle, 64);
                    if (ImGui::Button("Showcase notification", ImVec2(200, 25)))
                        notifpressed++;
                    ImGui::Combo("Notificiation Type", &notiftype, "Xbox\0\PS4", 2);
                }
                ImGui::EndGroup();
            }
            ImGui::EndChild();
        }

        if (tabs == 5)
        {
            ImGui::SetCursorPos(ImVec2(10, 60));
            ImGui::BeginChild("MainChild", ImVec2(470, 365));
            {
                //demo funcs
                static bool checkbox[2];
                static int combo = 0;
                static char input0[64] = "";
                static char input1[64] = "";

                //render funcs
                ImGui::SetCursorPos(ImVec2(10, 10));
                ImGui::BeginGroup();
                {
                    if (checkbox[0])
                    {
                        ImGui::InputText("Pointer or Offset", input0, 64, ImGuiInputTextFlags_ReadOnly);
                        ImGui::InputText("Value", input1, 64, ImGuiInputTextFlags_ReadOnly);
                    }
                    else
                    {
                        ImGui::InputText("Pointer or Offset", input0, 64);
                        ImGui::InputText("Value", input1, 64);
                    }
                    ImGui::Checkbox("Read-Only", &checkbox[0]);
                    ImGui::Checkbox("Loop Command", &checkbox[1]);
                    ImGui::Combo("Type", &combo, "Byte\0\r2 Byte\0\r4 Byte\0\rFloat\0\Double\0\String", 6);
                }
                ImGui::EndGroup();
            }
            ImGui::EndChild();
        }

        ImGui::End();

        ImGui::Begin("Radar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        {
            //size + pos
            ImGui::SetWindowSize(ImVec2(260, 260));

            //helpers def
            drawlist = ImGui::GetWindowDrawList();
            pos = ImGui::GetWindowPos();

            //render main rect
            drawlist->AddRectFilled(ImVec2(pos.x + 5, pos.y + 5), ImVec2(pos.x + 255, pos.y + 255), ImColor(25, 25, 25, 150), 8.f);

            //render radar elements
            drawlist->AddLine(ImVec2(pos.x + 130, pos.y + 5), ImVec2(pos.x + 130, pos.y + 255), ImColor(83, 83, 83, 255)); //center
            drawlist->AddLine(ImVec2(pos.x + 8, pos.y + 8), ImVec2(pos.x + 130, pos.y + 130), ImColor(83, 83, 83, 255)); //left
            drawlist->AddLine(ImVec2(pos.x + 253, pos.y + 8), ImVec2(pos.x + 130, pos.y + 130), ImColor(83, 83, 83, 255)); //right

            //border
            drawlist->AddRect(ImVec2(pos.x + 5, pos.y + 5), ImVec2(pos.x + 255, pos.y + 255), ImColor(83, 83, 83, 255), 8.f);

            //main player i assume
            drawlist->AddCircleFilled(ImVec2(pos.x + 130, pos.y + 127), 6.f, ImColor(170, 170, 170, 255));
        }
        ImGui::End();
    }

    // Rendering
    ImGui::Render();
}

bool EXTERNALGUI::CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC1 sd;
    {
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = NUM_BACK_BUFFERS;
        sd.Width = 0;
        sd.Height = 0;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
        sd.Scaling = DXGI_SCALING_STRETCH;
        sd.Stereo = FALSE;
    }

    // [DEBUG] Enable debug interface
#ifdef DX12_ENABLE_DEBUG_LAYER
    ID3D12Debug* pdx12Debug = nullptr;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pdx12Debug))))
        pdx12Debug->EnableDebugLayer();
#endif

    // Create device
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
    if (D3D12CreateDevice(nullptr, featureLevel, IID_PPV_ARGS(&g_pd3dDevice)) != S_OK)
        return false;

    // [DEBUG] Setup debug interface to break on any warnings/errors
#ifdef DX12_ENABLE_DEBUG_LAYER
    if (pdx12Debug != nullptr)
    {
        ID3D12InfoQueue* pInfoQueue = nullptr;
        g_pd3dDevice->QueryInterface(IID_PPV_ARGS(&pInfoQueue));
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
        pInfoQueue->Release();
        pdx12Debug->Release();
    }
#endif

    {
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        desc.NumDescriptors = NUM_BACK_BUFFERS;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        desc.NodeMask = 1;
        if (g_pd3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pd3dRtvDescHeap)) != S_OK)
            return false;

        SIZE_T rtvDescriptorSize = g_pd3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_pd3dRtvDescHeap->GetCPUDescriptorHandleForHeapStart();
        for (UINT i = 0; i < NUM_BACK_BUFFERS; i++)
        {
            g_mainRenderTargetDescriptor[i] = rtvHandle;
            rtvHandle.ptr += rtvDescriptorSize;
        }
    }

    {
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        desc.NumDescriptors = 1;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        if (g_pd3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pd3dSrvDescHeap)) != S_OK)
            return false;
    }

    {
        D3D12_COMMAND_QUEUE_DESC desc = {};
        desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        desc.NodeMask = 1;
        if (g_pd3dDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&g_pd3dCommandQueue)) != S_OK)
            return false;
    }

    for (UINT i = 0; i < NUM_FRAMES_IN_FLIGHT; i++)
        if (g_pd3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_frameContext[i].CommandAllocator)) != S_OK)
            return false;

    if (g_pd3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_frameContext[0].CommandAllocator, nullptr, IID_PPV_ARGS(&g_pd3dCommandList)) != S_OK ||
        g_pd3dCommandList->Close() != S_OK)
        return false;

    if (g_pd3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_fence)) != S_OK)
        return false;

    g_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (g_fenceEvent == nullptr)
        return false;

    {
        IDXGIFactory4* dxgiFactory = nullptr;
        IDXGISwapChain1* swapChain1 = nullptr;
        if (CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory)) != S_OK)
            return false;
        if (dxgiFactory->CreateSwapChainForHwnd(g_pd3dCommandQueue, hWnd, &sd, nullptr, nullptr, &swapChain1) != S_OK)
            return false;
        if (swapChain1->QueryInterface(IID_PPV_ARGS(&g_pSwapChain)) != S_OK)
            return false;
        swapChain1->Release();
        dxgiFactory->Release();
        g_pSwapChain->SetMaximumFrameLatency(NUM_BACK_BUFFERS);
        g_hSwapChainWaitableObject = g_pSwapChain->GetFrameLatencyWaitableObject();
    }

    CreateRenderTarget();
    return true;
}

void EXTERNALGUI::CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->SetFullscreenState(false, nullptr); g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_hSwapChainWaitableObject != nullptr) { CloseHandle(g_hSwapChainWaitableObject); }
    for (UINT i = 0; i < NUM_FRAMES_IN_FLIGHT; i++)
        if (g_frameContext[i].CommandAllocator) { g_frameContext[i].CommandAllocator->Release(); g_frameContext[i].CommandAllocator = nullptr; }
    if (g_pd3dCommandQueue) { g_pd3dCommandQueue->Release(); g_pd3dCommandQueue = nullptr; }
    if (g_pd3dCommandList) { g_pd3dCommandList->Release(); g_pd3dCommandList = nullptr; }
    if (g_pd3dRtvDescHeap) { g_pd3dRtvDescHeap->Release(); g_pd3dRtvDescHeap = nullptr; }
    if (g_pd3dSrvDescHeap) { g_pd3dSrvDescHeap->Release(); g_pd3dSrvDescHeap = nullptr; }
    if (g_fence) { g_fence->Release(); g_fence = nullptr; }
    if (g_fenceEvent) { CloseHandle(g_fenceEvent); g_fenceEvent = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }

#ifdef DX12_ENABLE_DEBUG_LAYER
    IDXGIDebug1* pDebug = nullptr;
    if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&pDebug))))
    {
        pDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_SUMMARY);
        pDebug->Release();
    }
#endif
}

void EXTERNALGUI::CreateRenderTarget()
{
    for (UINT i = 0; i < NUM_BACK_BUFFERS; i++)
    {
        ID3D12Resource* pBackBuffer = nullptr;
        g_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
        g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, g_mainRenderTargetDescriptor[i]);
        g_mainRenderTargetResource[i] = pBackBuffer;
    }
}

void EXTERNALGUI::CleanupRenderTarget()
{
    WaitForLastSubmittedFrame();

    for (UINT i = 0; i < NUM_BACK_BUFFERS; i++)
        if (g_mainRenderTargetResource[i]) { g_mainRenderTargetResource[i]->Release(); g_mainRenderTargetResource[i] = nullptr; }
}

void EXTERNALGUI::WaitForLastSubmittedFrame()
{
    FrameContext* frameCtx = &g_frameContext[g_frameIndex % NUM_FRAMES_IN_FLIGHT];

    UINT64 fenceValue = frameCtx->FenceValue;
    if (fenceValue == 0)
        return; // No fence was signaled

    frameCtx->FenceValue = 0;
    if (g_fence->GetCompletedValue() >= fenceValue)
        return;

    g_fence->SetEventOnCompletion(fenceValue, g_fenceEvent);
    WaitForSingleObject(g_fenceEvent, INFINITE);
}

FrameContext* EXTERNALGUI::WaitForNextFrameResources()
{
    UINT nextFrameIndex = g_frameIndex + 1;
    g_frameIndex = nextFrameIndex;

    HANDLE waitableObjects[] = { g_hSwapChainWaitableObject, nullptr };
    DWORD numWaitableObjects = 1;

    FrameContext* frameCtx = &g_frameContext[nextFrameIndex % NUM_FRAMES_IN_FLIGHT];
    UINT64 fenceValue = frameCtx->FenceValue;
    if (fenceValue != 0) // means no fence was signaled
    {
        frameCtx->FenceValue = 0;
        g_fence->SetEventOnCompletion(fenceValue, g_fenceEvent);
        waitableObjects[1] = g_fenceEvent;
        numWaitableObjects = 2;
    }

    WaitForMultipleObjects(numWaitableObjects, waitableObjects, TRUE, INFINITE);

    return frameCtx;
}

LRESULT __stdcall EXTERNALGUI::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    switch (uMsg)
    {
        case WM_SIZE:
            if (g_pd3dDevice != nullptr && wParam != SIZE_MINIMIZED)
            {
                WaitForLastSubmittedFrame();
                CleanupRenderTarget();
                HRESULT result = g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT);
                assert(SUCCEEDED(result) && "Failed to resize swapchain.");
                CreateRenderTarget();
            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU)
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
    }

    return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

bool EXTERNALGUI::Setup()
{

    /*WNDCLASSEXW wc = {
        sizeof(wc), 
        CS_CLASSDC, 
        WndProc, 
        0L, 
        0L,
        GetModuleHandle(nullptr), 
        nullptr, nullptr, nullptr, nullptr, 
        L"ImGui Example", 
        nullptr 
    };

    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui DirectX12 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1920, 1080, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return false;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX12_Init(g_pd3dDevice, NUM_FRAMES_IN_FLIGHT,
        DXGI_FORMAT_R8G8B8A8_UNORM, g_pd3dSrvDescHeap,
        g_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
        g_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart());

    // Load Fonts
    io.Fonts->AddFontFromMemoryTTF(&mainfonthxd, sizeof mainfonthxd, 14, NULL, io.Fonts->GetGlyphRangesCyrillic());
    notiffont = io.Fonts->AddFontFromMemoryTTF(&boldfonthxd, sizeof boldfonthxd, 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
    logo = io.Fonts->AddFontFromMemoryTTF(&logohxd, sizeof logohxd, 48, NULL, io.Fonts->GetGlyphRangesCyrillic());
    logo_bigger = io.Fonts->AddFontFromMemoryTTF(&logohxd, sizeof logohxd, 80, NULL, io.Fonts->GetGlyphRangesCyrillic());

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        RenderGUI();

        FrameContext* frameCtx = WaitForNextFrameResources();
        UINT backBufferIdx = g_pSwapChain->GetCurrentBackBufferIndex();
        frameCtx->CommandAllocator->Reset();

        D3D12_RESOURCE_BARRIER barrier = {};
        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        barrier.Transition.pResource = g_mainRenderTargetResource[backBufferIdx];
        barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
        g_pd3dCommandList->Reset(frameCtx->CommandAllocator, nullptr);
        g_pd3dCommandList->ResourceBarrier(1, &barrier);

        // Render Dear ImGui graphics
        const float clear_color_with_alpha[4] = { 0.f, 0.f, 0.f, 0.f };
        g_pd3dCommandList->ClearRenderTargetView(g_mainRenderTargetDescriptor[backBufferIdx], clear_color_with_alpha, 0, nullptr);
        g_pd3dCommandList->OMSetRenderTargets(1, &g_mainRenderTargetDescriptor[backBufferIdx], FALSE, nullptr);
        g_pd3dCommandList->SetDescriptorHeaps(1, &g_pd3dSrvDescHeap);
        ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), g_pd3dCommandList);
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
        g_pd3dCommandList->ResourceBarrier(1, &barrier);
        g_pd3dCommandList->Close();

        g_pd3dCommandQueue->ExecuteCommandLists(1, (ID3D12CommandList* const*)&g_pd3dCommandList);

        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync

        UINT64 fenceValue = g_fenceLastSignaledValue + 1;
        g_pd3dCommandQueue->Signal(g_fence, fenceValue);
        g_fenceLastSignaledValue = fenceValue;
        frameCtx->FenceValue = fenceValue;
    }

    WaitForLastSubmittedFrame();

    // Cleanup
    ImGui_ImplDX12_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
    */
    return true;
}
