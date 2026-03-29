#pragma once

#include "PlatformAbstraction.h"

namespace cse {

class RiscV64Platform : public PlatformAbstraction {
public:
    void callStandardLibraryFunction(const std::string& funcName, const std::vector<void*>& args) override;
    std::string getPlatformName() const override;
    void* getStandardLibraryFunctionAddress(const std::string& funcName) override;
    void registerFFIFunction(const std::string& name, void* address) override;
    void* getFFIFunctionAddress(const std::string& funcName) override;
    bool isFFIFunction(const std::string& funcName) const override;

    void* allocateExecutableMemory(size_t size) override;
    void freeExecutableMemory(void* memory, size_t size) override;
    bool setMemoryProtection(void* memory, size_t size, bool executable) override;

private:
    std::unordered_map<std::string, void*> m_ffiFunctions;
};

} // namespace cse