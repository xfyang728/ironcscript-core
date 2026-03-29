#include "HardwareFactory.h"
#include "IStandardGPIO.h"
#include "IStandardUART.h"
#include "IStandardTimer.h"
#include "platform/k210/K210GPIO.h"
#include "platform/k210/K210Timer.h"
#include "platform/k210/K210UART.h"
#include "platform/mock/MockGPIO.h"
#include "platform/mock/MockTimer.h"
#include "platform/mock/MockUART.h"
#include <cstdio>
#include <cstring>

#if defined(__K210__) || defined(CSE_K210)
#include "platform/k210/K210Hardware.h"
#endif

#if defined(CSE_STM32) || defined(STM32F4) || defined(STM32H7)
#include "platform/stm32/STM32GPIO.h"
#include "platform/stm32/STM32Timer.h"
#include "platform/stm32/STM32UART.h"
#endif

namespace cse {

HardwareFactory::HardwareFactory()
    : m_Platform(HardwarePlatform::AUTO) {
}

HardwareFactory::~HardwareFactory() {
    shutdown();
}

HardwareFactory& HardwareFactory::instance() {
    static HardwareFactory factory;
    return factory;
}

void HardwareFactory::initialize(HardwarePlatform platform) {
    if (platform == HardwarePlatform::AUTO) {
#if defined(__K210__) || defined(CSE_K210)
        platform = HardwarePlatform::K210;
#elif defined(CSE_EMBEDDED)
        platform = HardwarePlatform::STM32;
#else
        platform = HardwarePlatform::MOCK;
#endif
    }

    m_Platform = platform;

    switch (m_Platform) {
        case HardwarePlatform::K210:
            createK210Hardware();
            break;
        case HardwarePlatform::STM32:
            createSTM32Hardware();
            break;
        case HardwarePlatform::MOCK:
        default:
            createMockHardware();
            break;
    }

    printf("[HardwareFactory] Initialized for platform: %s\r\n", getPlatformName());
}

IStandardUART* HardwareFactory::getUART(uint32_t id) {
    if (id >= 3) return nullptr;
    return m_UARTs[id].get();
}

const char* HardwareFactory::getPlatformName() const {
    switch (m_Platform) {
        case HardwarePlatform::K210: return "K210";
        case HardwarePlatform::STM32: return "STM32";
        case HardwarePlatform::MOCK: return "Mock";
        default: return "Unknown";
    }
}

void HardwareFactory::shutdown() {
    m_GPIO.reset();

    for (int i = 0; i < 3; i++) {
        m_UARTs[i].reset();
    }

    for (int i = 0; i < 4; i++) {
        m_Timers[i].reset();
    }

    printf("[HardwareFactory] Shutdown complete\r\n");
}

void HardwareFactory::createK210Hardware() {
#if defined(__K210__) || defined(CSE_K210)
    m_GPIO = std::make_unique<K210GPIO>();
    for (int i = 0; i < 3; i++) {
        m_UARTs[i] = std::make_unique<K210UART>(i);
    }
    for (int i = 0; i < 4; i++) {
        m_Timers[i] = std::make_unique<K210Timer>(i);
    }
    printf("[HardwareFactory] K210 hardware created\r\n");
#else
    printf("[HardwareFactory] K210 platform not available on this host\r\n");
    createMockHardware();
#endif
}

void HardwareFactory::createSTM32Hardware() {
#if defined(CSE_STM32) || defined(STM32F4) || defined(STM32H7)
    m_GPIO = std::make_unique<STM32GPIO>();
    for (int i = 0; i < 3; i++) {
        m_UARTs[i] = std::make_unique<STM32UART>(i);
    }
    for (int i = 0; i < 4; i++) {
        m_Timers[i] = std::make_unique<STM32Timer>(i);
    }
    printf("[HardwareFactory] STM32 hardware created\r\n");
#else
    printf("[HardwareFactory] STM32 platform not available on this host\r\n");
    createMockHardware();
#endif
}

void HardwareFactory::createMockHardware() {
    m_GPIO = std::make_unique<MockGPIO>();
    for (int i = 0; i < 3; i++) {
        m_UARTs[i] = std::make_unique<MockUART>(i);
    }
    for (int i = 0; i < 4; i++) {
        m_Timers[i] = std::make_unique<MockTimer>(i);
    }
    printf("[HardwareFactory] Mock hardware created\r\n");
}

}