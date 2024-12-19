#include "framework.h"
#include <windows.h>
#include "features/packet.h"
#include "../libs/memory/memory.h"
#include "../libs/detours/detours.h"
#include "../libs/kiero/kiero.h"
#include "features/gui.h"

using Interceptor::Logger;
using Interceptor::Setup;

DWORD WINAPI Init(LPVOID lpReserved)
{
    bool init_hook = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            Setup();
            kiero::bind(8, (void**)&GUI::GetInstance().oPresent, GUI::hkPresentWrapper);
            init_hook = true;
        }
    } while (!init_hook);
    return TRUE;

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReasonForCall, LPVOID lpReserved) 
{
    switch (ulReasonForCall) 
    {
    case DLL_PROCESS_ATTACH:
        DetourRestoreAfterWith();
        Logger::Log("Interceptor", "DLL Loaded.");
        CreateThread(nullptr, 0, Init, hModule, 0, nullptr);

        break;
    case DLL_PROCESS_DETACH:
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourTransactionCommit();
        Logger::Log("Interceptor", "DLL Unloaded.");
        break;
    }
    return TRUE;
}
