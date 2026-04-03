/**
 * @file HardwareFactory.h
 * @brief 硬件抽象层工厂类
 * @note 统一管理GPIO、UART、Timer、Stdio等硬件接口的创建和生命周期
 */
#ifndef CSE_HAL_HARDWARE_FACTORY_H
#define CSE_HAL_HARDWARE_FACTORY_H

#include "IStandardGPIO.h"
#include "IStandardUART.h"
#include "IStandardTimer.h"
#include "IStandardStdio.h"
#include <memory>
#include <string>

namespace cse {

enum class HardwarePlatform {
    AUTO,
    K210,
    STM32,
    MOCK,
};

class HardwareFactory {
public:
    static HardwareFactory& instance();

    void initialize(HardwarePlatform platform = HardwarePlatform::AUTO);

    IStandardGPIO* getGPIO() { return m_GPIO.get(); }
    IStandardUART* getUART(uint32_t id = 0);
    IStandardTimer* getTimer(uint32_t id = 0);
    IStandardStdio* getStdio() { return m_Stdio.get(); }

    HardwarePlatform getCurrentPlatform() const { return m_Platform; }
    const char* getPlatformName() const;

    void shutdown();

private:
    HardwareFactory();
    ~HardwareFactory();

    HardwareFactory(const HardwareFactory&) = delete;
    HardwareFactory& operator=(const HardwareFactory&) = delete;

    void createK210Hardware();
    void createSTM32Hardware();
    void createMockHardware();

    HardwarePlatform m_Platform = HardwarePlatform::AUTO;
    std::unique_ptr<IStandardGPIO> m_GPIO;
    std::unique_ptr<IStandardUART> m_UARTs[3];
    std::unique_ptr<IStandardTimer> m_Timers[4];
    std::unique_ptr<IStandardStdio> m_Stdio;
};

}

#endif
