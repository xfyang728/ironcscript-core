#include "hal/EmbeddedRuntime.h"
#include "platform/k210/K210Hardware.h"
#include "platform/k210/K210Bootloader.h"
#include "platform/stm32/STM32Hardware.h"
#include "platform/stm32/STM32DFUBootloader.h"

namespace cse {

class K210Runtime : public IEmbeddedRuntime {
public:
    explicit K210Runtime(const EmbeddedConfig& config)
        : m_Config(config)
        , m_HAL(std::make_unique<K210Hardware>())
        , m_Bootloader(std::make_unique<K210Bootloader>(static_cast<K210Hardware*>(m_HAL.get())))
        , m_VM(std::make_unique<BytecodeVM>(VMConfig{
            .stackSize = config.stackSize,
            .heapSize = config.heapSize,
            .maxCallDepth = config.maxCallDepth
        }))
    {
    }

    bool initialize() override {
        m_HAL->delay(100);
        m_Bootloader->initialize();
        return true;
    }

    void run() override {
        constexpr uint32_t CSB_ADDR = 0x00080000;
        constexpr size_t CSB_MAX_SIZE = 512 * 1024;

        std::vector<uint8_t> csbData(CSB_MAX_SIZE);
        size_t actualSize = 0;

        if (!m_HAL->readFlash(CSB_ADDR, csbData.data(), CSB_MAX_SIZE)) {
            if (m_LogCallback) {
                m_LogCallback("[K210Runtime] Failed to read CSB from flash\r\n");
            }
            return;
        }

        if (csbData[0] != 'C' || csbData[1] != 'S' || csbData[2] != 'B') {
            if (m_LogCallback) {
                m_LogCallback("[K210Runtime] Invalid CSB magic\r\n");
            }
            return;
        }

        BytecodeModule module;
        if (!module.loadFromFile("memory")) {
            if (m_LogCallback) {
                m_LogCallback("[K210Runtime] Failed to parse CSB module\r\n");
            }
            return;
        }

        m_VM->loadModule(&module);
        m_VM->execute(0);

        if (m_LogCallback) {
            m_LogCallback("[K210Runtime] Execution finished\r\n");
        }
    }

    void shutdown() override {
        m_VM->stop();
    }

    BytecodeVM* getVM() override { return m_VM.get(); }
    IHardwareAbstraction* getHAL() override { return m_HAL.get(); }
    IBootloader* getBootloader() override { return m_Bootloader.get(); }

    void setLogCallback(LogCallback callback) override {
        m_LogCallback = callback;
    }

private:
    EmbeddedConfig m_Config;
    std::unique_ptr<IHardwareAbstraction> m_HAL;
    std::unique_ptr<IBootloader> m_Bootloader;
    std::unique_ptr<BytecodeVM> m_VM;
    LogCallback m_LogCallback;
};

class STM32Runtime : public IEmbeddedRuntime {
public:
    explicit STM32Runtime(const EmbeddedConfig& config)
        : m_Config(config)
        , m_HAL(std::make_unique<STM32Hardware>())
        , m_Bootloader(std::make_unique<STM32DFUBootloader>(static_cast<STM32Hardware*>(m_HAL.get())))
        , m_VM(std::make_unique<BytecodeVM>(VMConfig{
            .stackSize = config.stackSize,
            .heapSize = config.heapSize,
            .maxCallDepth = config.maxCallDepth
        }))
    {
        static_cast<STM32DFUBootloader*>(m_Bootloader.get())->setFlashBase(config.csbStorageAddr);
    }

    bool initialize() override {
        m_HAL->delay(100);
        m_Bootloader->initialize();

        if (m_LogCallback) {
            m_LogCallback("[STM32Runtime] Initialized\r\n");
        }
        return true;
    }

    void run() override {
        const uint32_t CSB_ADDR = m_Config.csbStorageAddr;
        constexpr size_t CSB_MAX_SIZE = 256 * 1024;

        std::vector<uint8_t> csbData(CSB_MAX_SIZE);

        if (!m_HAL->readFlash(CSB_ADDR, csbData.data(), CSB_MAX_SIZE)) {
            if (m_LogCallback) {
                m_LogCallback("[STM32Runtime] Failed to read CSB from flash\r\n");
            }
            return;
        }

        if (csbData[0] != 'C' || csbData[1] != 'S' || csbData[2] != 'B') {
            if (m_LogCallback) {
                m_LogCallback("[STM32Runtime] Invalid CSB magic\r\n");
            }
            return;
        }

        if (m_LogCallback) {
            m_LogCallback("[STM32Runtime] Found valid CSB, executing...\r\n");
        }

        m_VM->execute(0);

        if (m_LogCallback) {
            m_LogCallback("[STM32Runtime] Execution finished\r\n");
        }
    }

    void shutdown() override {
        m_VM->stop();
    }

    BytecodeVM* getVM() override { return m_VM.get(); }
    IHardwareAbstraction* getHAL() override { return m_HAL.get(); }
    IBootloader* getBootloader() override { return m_Bootloader.get(); }

    void setLogCallback(LogCallback callback) override {
        m_LogCallback = callback;
    }

private:
    EmbeddedConfig m_Config;
    std::unique_ptr<IHardwareAbstraction> m_HAL;
    std::unique_ptr<IBootloader> m_Bootloader;
    std::unique_ptr<BytecodeVM> m_VM;
    LogCallback m_LogCallback;
};

std::unique_ptr<IEmbeddedRuntime> EmbeddedRuntimeFactory::create(Platform platform,
                                                                const EmbeddedConfig& config) {
    switch (platform) {
        case Platform::K210:
            return std::make_unique<K210Runtime>(config);
        case Platform::STM32:
            return std::make_unique<STM32Runtime>(config);
        default:
            return nullptr;
    }
}

}