#include "../../pch.h"

#include "gui.h"

void GUI::InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	//ImGui_ImplDX11_Init(pDevice, pContext);
}

void GUI::LoadFonts()
{
	ImGui::GetIO().Fonts->AddFontDefault();
	ImFontConfig font_cfg;
	font_cfg.GlyphExtraSpacing.x = 1.2;
}

void GUI::RenderUI()
{

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	// menu


	ImGui::EndFrame();
	ImGui::Render();
	//ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}

