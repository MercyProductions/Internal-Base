#include "../pch.h"
#include <windows.h>
#include "features/packet.h"
#include "../libs/memory/memory.h"
#include "../libs/detours/detours.h"

using Interceptor::Logger;
using Interceptor::Setup;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReasonForCall, LPVOID lpReserved) 
{
    switch (ulReasonForCall) 
    {
    case DLL_PROCESS_ATTACH:
        DetourRestoreAfterWith();
        Logger::Log("Interceptor", "DLL Loaded.");
        Setup();
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
