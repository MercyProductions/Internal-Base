#include "../../pch.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>

class Memory 
{
public:
    template<typename T>
    static T Read(uintptr_t address) 
    {
        T value;
        if (!ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(address), &value, sizeof(T), nullptr)) 
        {
            std::cerr << "[Memory] Failed to read memory at address: " << std::hex << address << std::endl;
            return T{};
        }
        return value;
    }

    template<typename T>
    static bool Write(uintptr_t address, T value) 
    {
        if (!WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(address), &value, sizeof(T), nullptr)) 
        {
            std::cerr << "[Memory] Failed to write memory at address: " << std::hex << address << std::endl;
            return false;
        }
        return true;
    }

    static int32_t ReadInt32(uintptr_t address) 
    {
        return Read<int32_t>(address);
    }

    static bool WriteInt32(uintptr_t address, int32_t value) 
    {
        return Write<int32_t>(address, value);
    }

    static int64_t ReadInt64(uintptr_t address) 
    {
        return Read<int64_t>(address);
    }

    static bool WriteInt64(uintptr_t address, int64_t value) 
    {
        return Write<int64_t>(address, value);
    }

    static float ReadFloat(uintptr_t address) 
    {
        return Read<float>(address);
    }

    static bool WriteFloat(uintptr_t address, float value) 
    {
        return Write<float>(address, value);
    }

    static double ReadDouble(uintptr_t address) 
    {
        return Read<double>(address);
    }

    static bool WriteDouble(uintptr_t address, double value) 
    {
        return Write<double>(address, value);
    }

    static std::string ReadString(uintptr_t address, size_t length) 
    {
        char* buffer = new char[length + 1]();
        if (!ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(address), buffer, length, nullptr)) 
        {
            std::cerr << "[Memory] Failed to read string at address: " << std::hex << address << std::endl;
            delete[] buffer;
            return "";
        }
        std::string result(buffer);
        delete[] buffer;
        return result;
    }

    static bool WriteString(uintptr_t address, const std::string& value) 
    {
        return WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(address), value.c_str(), value.size() + 1, nullptr);
    }

    static bool ReadBytes(uintptr_t address, void* buffer, size_t size) 
    {
        return ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(address), buffer, size, nullptr) != 0;
    }

    static bool WriteBytes(uintptr_t address, const void* buffer, size_t size) 
    {
        return WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(address), buffer, size, nullptr) != 0;
    }

    static uintptr_t ScanSignature(uintptr_t baseAddress, size_t size, const std::vector<BYTE>& signature, const std::string& mask) 
    {
        BYTE* buffer = new BYTE[size];
        if (!ReadBytes(baseAddress, buffer, size)) 
        {
            std::cerr << "[Memory] Failed to read memory for signature scanning." << std::endl;
            delete[] buffer;
            return 0;
        }

        for (size_t i = 0; i < size - signature.size(); ++i) 
        {
            bool found = true;
            for (size_t j = 0; j < signature.size(); ++j) 
            {
                if (mask[j] != '?' && signature[j] != buffer[i + j]) 
                {
                    found = false;
                    break;
                }
            }
            if (found) 
            {
                delete[] buffer;
                return baseAddress + i;
            }
        }

        delete[] buffer;
        return 0;
    }

    static uintptr_t CreateCodeCave(uintptr_t baseAddress, size_t size) 
    {
        void* allocatedMemory = VirtualAlloc(reinterpret_cast<LPVOID>(baseAddress), size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (!allocatedMemory) 
        {
            std::cerr << "[Memory] Failed to create code cave." << std::endl;
            return 0;
        }
        return reinterpret_cast<uintptr_t>(allocatedMemory);
    }

    static uintptr_t GetBaseAddress() 
    {
        return reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
    }

    static uintptr_t GetModuleAddress(const std::string& moduleName) 
    {
        HMODULE hModule = GetModuleHandleA(moduleName.c_str());
        if (!hModule) 
        {
            std::cerr << "[Memory] Failed to get module handle for: " << moduleName << std::endl;
            return 0;
        }
        return reinterpret_cast<uintptr_t>(hModule);
    }
};
