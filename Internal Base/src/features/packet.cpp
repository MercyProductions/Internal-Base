#include "../../pch.h"
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include "../../libs/detours/detours.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <atomic>
#include "gui.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "detours.lib")

namespace Interceptor
{

    std::atomic<bool> Debug = true;

    class Logger
    {
    public:
        static void SetTextColor(WORD color)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, color);
        }

        static void ResetTextColor()
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }

        static void Log(const std::string& context, const std::string& message)
        {
            SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN);
            SYSTEMTIME time;
            GetLocalTime(&time);
            std::cout << "[" << std::setfill('0') << std::setw(2) << time.wHour << ":"
                << std::setw(2) << time.wMinute << ":" << std::setw(2) << time.wSecond
                << "] " << context << ": " << message << std::endl;
            ResetTextColor();
        }

        static void Error(const std::string& context, const std::string& message)
        {
            SetTextColor(FOREGROUND_RED);
            Log(context, "ERROR: " + message);
            ResetTextColor();
        }
    };

    class Analyzer
    {
    public:
        static double CalculateEntropy(const char* data, size_t size)
        {
            int freq[256] = { 0 };
            for (size_t i = 0; i < size; ++i)
            {
                freq[(unsigned char)data[i]]++;
            }

            double entropy = 0.0;
            for (int i = 0; i < 256; ++i)
            {
                if (freq[i] > 0)
                {
                    double p = (double)freq[i] / size;
                    entropy -= p * log2(p);
                }
            }
            return entropy;
        }

        static bool IsEncrypted(const char* data, size_t size)
        {
            double entropy = CalculateEntropy(data, size);
            Logger::Log("Analyzer", "Entropy: " + std::to_string(entropy));
            return entropy > 7.5;
        }
    };

    class WinsockInterceptor
    {
    private:
        typedef int (WSAAPI* send_t)(SOCKET, const char*, int, int);
        typedef int (WSAAPI* recv_t)(SOCKET, char*, int, int);

    public:
        static send_t OriginalSend;
        static recv_t OriginalRecv;

        static void Initialize()
        {
            Logger::Log("WinsockInterceptor", "Initializing hooks...");
            HMODULE ws2_32 = GetModuleHandleA("Ws2_32.dll");
            if (!ws2_32)
            {
                Logger::Error("WinsockInterceptor", "Failed to get Ws2_32.dll handle.");
                return;
            }

            OriginalSend = (send_t)GetProcAddress(ws2_32, "send");
            OriginalRecv = (recv_t)GetProcAddress(ws2_32, "recv");

            if (!OriginalSend || !OriginalRecv)
            {
                Logger::Error("WinsockInterceptor", "Failed to get send/recv function addresses.");
                return;
            }

            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(&(PVOID&)OriginalSend, HookedSend);
            DetourAttach(&(PVOID&)OriginalRecv, HookedRecv);
            if (DetourTransactionCommit() != NO_ERROR)
            {
                Logger::Error("WinsockInterceptor", "Failed to commit hooks.");
            }
            else
            {
                Logger::Log("WinsockInterceptor", "Hooks installed successfully.");
            }
        }

        static int WSAAPI HookedSend(SOCKET s, const char* buf, int len, int flags)
        {
            Logger::Log("WinsockInterceptor", "Intercepting outgoing data...");

            std::string data(buf, len);

            if (IsSpecificPacket(data))
            {
                Logger::Log("WinsockInterceptor", "Specific outgoing packet detected: Contains 'health'!");

                std::string modifiedData = ModifyPacket(data);
                Logger::Log("WinsockInterceptor", "Modified Outgoing Data: " + modifiedData);

                return OriginalSend(s, modifiedData.c_str(), (int)modifiedData.size(), flags);
            }

            return OriginalSend(s, buf, len, flags);
        }

        static int WSAAPI HookedRecv(SOCKET s, char* buf, int len, int flags)
        {
            int ret = OriginalRecv(s, buf, len, flags);
            if (ret > 0)
            {
                Logger::Log("WinsockInterceptor", "Intercepting incoming data...");

                std::string data(buf, ret);

                if (IsSpecificPacket(data))
                {
                    Logger::Log("WinsockInterceptor", "Specific incoming packet detected: Contains 'health'!");

                    std::string modifiedData = ModifyPacket(data);
                    Logger::Log("WinsockInterceptor", "Modified Incoming Data: " + modifiedData);

                    memcpy(buf, modifiedData.c_str(), modifiedData.size());
                    ret = (int)modifiedData.size();
                }
            }
            return ret;
        }

        static bool IsSpecificPacket(const std::string& packet)
        {
            return packet.find("health") != std::string::npos;
        }

        static std::string ModifyPacket(const std::string& packet)
        {
            std::string modifiedPacket = packet;
            size_t pos = modifiedPacket.find("health");
            if (pos != std::string::npos)
            {
                modifiedPacket.replace(pos, 6, "full_health");
            }
            return modifiedPacket;
        }

        static void MonitorTraffic()
        {
            while (Debug)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    };

    WinsockInterceptor::send_t WinsockInterceptor::OriginalSend = nullptr;
    WinsockInterceptor::recv_t WinsockInterceptor::OriginalRecv = nullptr;

    class DriverInterceptor
    {
    private:
        typedef BOOL(WINAPI* DeviceIoControl_t)(HANDLE, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);

    public:
        static DeviceIoControl_t OriginalDeviceIoControl;

        static void Initialize()
        {
            Logger::Log("DriverInterceptor", "Initializing hooks...");
            HMODULE kernel32 = GetModuleHandleA("Kernel32.dll");
            if (!kernel32)
            {
                Logger::Error("DriverInterceptor", "Failed to get Kernel32.dll handle.");
                return;
            }

            OriginalDeviceIoControl = (DeviceIoControl_t)GetProcAddress(kernel32, "DeviceIoControl");
            if (!OriginalDeviceIoControl)
            {
                Logger::Error("DriverInterceptor", "Failed to get DeviceIoControl function address.");
                return;
            }

            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(&(PVOID&)OriginalDeviceIoControl, HookedDeviceIoControl);
            if (DetourTransactionCommit() != NO_ERROR)
            {
                Logger::Error("DriverInterceptor", "Failed to commit DeviceIoControl hook.");
            }
            else
            {
                Logger::Log("DriverInterceptor", "Hooks installed successfully.");
            }
        }

        static BOOL WINAPI HookedDeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped)
        {
            Logger::Log("DriverInterceptor", "Intercepting communication with driver...");
            Logger::Log("DriverInterceptor", "IOCTL Code: " + std::to_string(dwIoControlCode));
            if (lpInBuffer && nInBufferSize > 0) {
                std::string inputData((char*)lpInBuffer, nInBufferSize);
                Logger::Log("DriverInterceptor", "Input Data: " + inputData);
            }
            if (lpOutBuffer && nOutBufferSize > 0) {
                std::string outputData((char*)lpOutBuffer, nOutBufferSize);
                Logger::Log("DriverInterceptor", "Output Data: " + outputData);
            }
            return OriginalDeviceIoControl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
        }

        static void MonitorTraffic() {
            while (Debug) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    };

    DriverInterceptor::DeviceIoControl_t DriverInterceptor::OriginalDeviceIoControl = nullptr;

    void AllocateConsole() {
        AllocConsole();
        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        freopen_s(&fp, "CONIN$", "r", stdin);
        Logger::Log("Setup", "Console allocated.");
    }

    void Setup() {
        if (!Debug) {
            Logger::Log("Setup", "Debug mode is disabled. Skipping setup.");
            return;
        }

        AllocateConsole();

        Logger::Log("Setup", "Debug mode is enabled. Setting up interceptors...");

        //GUI::GetInstance().Setup();

        WinsockInterceptor::Initialize();
        DriverInterceptor::Initialize();

        std::thread(WinsockInterceptor::MonitorTraffic).detach();
        std::thread(DriverInterceptor::MonitorTraffic).detach();
    }

}