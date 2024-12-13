#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>

#include "../../libs/imgui/imgui.h"
#include "../../libs/imgui/imgui_impl_win32.h"
#include "../../libs/imgui/imgui_impl_dx12.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

class GUI {
public:
	static GUI& GetInstance() {
		static GUI instance;
		return instance;
	}

	Present oPresent = NULL;

private:

	HWND window = NULL;
	WNDPROC oWndProc = NULL;
	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* mainRenderTargetView = nullptr;
	bool HkPresentInitialized = false;

	HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void LoadFonts();

	void InitImGui();
	void RenderUI();

	GUI() = default;
	~GUI() = default;

	GUI(const GUI&) = delete;
	GUI& operator=(const GUI&) = delete;
};