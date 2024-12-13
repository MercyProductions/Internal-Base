#ifndef PACKET_H
#define PACKET_H

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>
#include <thread>
#include <atomic>

namespace Interceptor {

    class Logger {
    public:
        static void SetTextColor(WORD color);
        static void ResetTextColor();
        static void Log(const std::string& context, const std::string& message);
        static void Error(const std::string& context, const std::string& message);
    };

    class WinsockInterceptor {
    public:
        static void Initialize();
        static void MonitorTraffic();
        static int WSAAPI HookedSend(SOCKET s, const char* buf, int len, int flags);
        static int WSAAPI HookedRecv(SOCKET s, char* buf, int len, int flags);

    private:
        static bool IsSpecificPacket(const std::string& packet);
        static std::string ModifyPacket(const std::string& packet);
    };

    class DriverInterceptor {
    public:
        static void Initialize();
        static void MonitorTraffic();
        static BOOL WINAPI HookedDeviceIoControl(
            HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize,
            LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);
    };

    void AllocateConsole();
    void Setup();

} // namespace Interceptor

#endif // PACKET_H
