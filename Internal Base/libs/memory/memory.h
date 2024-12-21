#ifndef MEMORY_H
#define MEMORY_H

#include <windows.h>
#include <string>
#include <vector>

class Memory {
public:
    template<typename T>
    static T Read(uintptr_t address);

    template<typename T>
    static bool Write(uintptr_t address, T value);

    static int32_t ReadInt32(uintptr_t address);
    static bool WriteInt32(uintptr_t address, int32_t value);
    static int64_t ReadInt64(uintptr_t address);
    static bool WriteInt64(uintptr_t address, int64_t value);
    static float ReadFloat(uintptr_t address);
    static bool WriteFloat(uintptr_t address, float value);
    static double ReadDouble(uintptr_t address);
    static bool WriteDouble(uintptr_t address, double value);
    static std::string ReadString(uintptr_t address, size_t length);
    static bool WriteString(uintptr_t address, const std::string& value);
    static bool ReadBytes(uintptr_t address, void* buffer, size_t size);
    static bool WriteBytes(uintptr_t address, const void* buffer, size_t size);
    static uintptr_t ScanSignature(uintptr_t baseAddress, size_t size, const std::vector<BYTE>& signature, const std::string& mask);
    static uintptr_t CreateCodeCave(uintptr_t baseAddress, size_t size);
    static uintptr_t GetBaseAddress();
    static uintptr_t GetModuleAddress(const std::string& moduleName);
};

#endif // MEMORY_H
