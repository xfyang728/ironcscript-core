#ifndef CSE_EMBEDDED_RUNTIME_H
#define CSE_EMBEDDED_RUNTIME_H

#include "vm/BytecodeVM.h"
#include "hal/IHardwareAbstraction.h"
#include "hal/IBootloader.h"
#include <memory>
#include <functional>

namespace cse {

constexpr size_t STM32_VM_STACK_SIZE = 512;
constexpr size_t STM32_VM_HEAP_SIZE = 16384;
constexpr size_t STM32_VM_MAX_CALL_DEPTH = 32;

struct EmbeddedConfig {
    size_t stackSize = STM32_VM_STACK_SIZE;
    size_t heapSize = STM32_VM_HEAP_SIZE;
    size_t maxCallDepth = STM32_VM_MAX_CALL_DEPTH;
    uint32_t csbStorageAddr = 0x08020000;
};

class IEmbeddedRuntime {
public:
    virtual ~IEmbeddedRuntime() = default;

    virtual bool initialize() = 0;
    virtual void run() = 0;
    virtual void shutdown() = 0;

    virtual BytecodeVM* getVM() = 0;
    virtual IHardwareAbstraction* getHAL() = 0;
    virtual IBootloader* getBootloader() = 0;

    using LogCallback = std::function<void(const char*)>;
    virtual void setLogCallback(LogCallback callback) = 0;
};

class EmbeddedRuntimeFactory {
public:
    enum class Platform {
        K210,
        STM32,
    };

    static std::unique_ptr<IEmbeddedRuntime> create(Platform platform,
                                                     const EmbeddedConfig& config = EmbeddedConfig{});
};

}

#endif
