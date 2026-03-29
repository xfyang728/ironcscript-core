#ifndef CSE_K210_GPIO_H
#define CSE_K210_GPIO_H

#include "hal/IStandardGPIO.h"
#include <cstdint>

namespace cse
{

    namespace K210Pin
    {
        constexpr uint32_t GPIOHS0 = 0;
        constexpr uint32_t GPIOHS1 = 1;
        constexpr uint32_t GPIOHS2 = 2;
        constexpr uint32_t GPIOHS3 = 3;
        constexpr uint32_t GPIOHS4 = 4;
        constexpr uint32_t GPIOHS5 = 5;
        constexpr uint32_t GPIOHS6 = 6;
        constexpr uint32_t GPIOHS7 = 7;
        constexpr uint32_t GPIOHS8 = 8;
        constexpr uint32_t GPIOHS9 = 9;
        constexpr uint32_t GPIOHS10 = 10;
        constexpr uint32_t GPIOHS11 = 11;
        constexpr uint32_t GPIOHS12 = 12;
        constexpr uint32_t GPIOHS13 = 13;
        constexpr uint32_t GPIOHS14 = 14;
        constexpr uint32_t GPIOHS15 = 15;
        constexpr uint32_t GPIOHS16 = 16;
        constexpr uint32_t GPIOHS17 = 17;
        constexpr uint32_t GPIOHS18 = 18;
        constexpr uint32_t GPIOHS19 = 19;
        constexpr uint32_t GPIOHS20 = 20;
        constexpr uint32_t GPIOHS21 = 21;
        constexpr uint32_t GPIOHS22 = 22;
        constexpr uint32_t GPIOHS23 = 23;
        constexpr uint32_t GPIOHS24 = 24;
        constexpr uint32_t GPIOHS25 = 25;
        constexpr uint32_t GPIOHS26 = 26;
        constexpr uint32_t GPIOHS27 = 27;
        constexpr uint32_t GPIOHS28 = 28;
        constexpr uint32_t GPIOHS29 = 29;
        constexpr uint32_t GPIOHS30 = 30;
        constexpr uint32_t GPIOHS31 = 31;

        constexpr uint32_t GPIO0 = 32;
        constexpr uint32_t GPIO1 = 33;
        constexpr uint32_t GPIO2 = 34;
        constexpr uint32_t GPIO3 = 35;
        constexpr uint32_t GPIO4 = 36;
        constexpr uint32_t GPIO5 = 37;
        constexpr uint32_t GPIO6 = 38;
        constexpr uint32_t GPIO7 = 39;

        constexpr uint32_t FUNC_GPIOHS0 = 24;
        constexpr uint32_t FUNC_GPIOHS1 = 25;
        constexpr uint32_t FUNC_GPIOHS2 = 26;
        constexpr uint32_t FUNC_GPIOHS3 = 27;
        constexpr uint32_t FUNC_GPIOHS4 = 28;
        constexpr uint32_t FUNC_GPIOHS5 = 29;
        constexpr uint32_t FUNC_GPIOHS6 = 30;
        constexpr uint32_t FUNC_GPIOHS7 = 31;
        constexpr uint32_t FUNC_GPIOHS8 = 32;
        constexpr uint32_t FUNC_GPIOHS9 = 33;
        constexpr uint32_t FUNC_GPIOHS10 = 34;
        constexpr uint32_t FUNC_GPIOHS11 = 35;
        constexpr uint32_t FUNC_GPIOHS12 = 36;
        constexpr uint32_t FUNC_GPIOHS13 = 37;
        constexpr uint32_t FUNC_GPIOHS14 = 38;
        constexpr uint32_t FUNC_GPIOHS15 = 39;
        constexpr uint32_t FUNC_GPIOHS16 = 40;
        constexpr uint32_t FUNC_GPIOHS17 = 41;
        constexpr uint32_t FUNC_GPIOHS18 = 42;
        constexpr uint32_t FUNC_GPIOHS19 = 43;
        constexpr uint32_t FUNC_GPIOHS20 = 44;
        constexpr uint32_t FUNC_GPIOHS21 = 45;
        constexpr uint32_t FUNC_GPIOHS22 = 46;
        constexpr uint32_t FUNC_GPIOHS23 = 47;
        constexpr uint32_t FUNC_GPIOHS24 = 48;
        constexpr uint32_t FUNC_GPIOHS25 = 49;
        constexpr uint32_t FUNC_GPIOHS26 = 50;
        constexpr uint32_t FUNC_GPIOHS27 = 51;
        constexpr uint32_t FUNC_GPIOHS28 = 52;
        constexpr uint32_t FUNC_GPIOHS29 = 53;
        constexpr uint32_t FUNC_GPIOHS30 = 54;
        constexpr uint32_t FUNC_GPIOHS31 = 55;
        constexpr uint32_t FUNC_GPIO0 = 56;
        constexpr uint32_t FUNC_GPIO1 = 57;
        constexpr uint32_t FUNC_GPIO2 = 58;
        constexpr uint32_t FUNC_GPIO3 = 59;
        constexpr uint32_t FUNC_GPIO4 = 60;
        constexpr uint32_t FUNC_GPIO5 = 61;
        constexpr uint32_t FUNC_GPIO6 = 62;
        constexpr uint32_t FUNC_GPIO7 = 63;
    }

    constexpr uint32_t K210_GPIOHS_COUNT = 32;
    constexpr uint32_t K210_GPIO_COUNT = 8;
    constexpr uint32_t K210_TOTAL_PIN_COUNT = 40;

    class K210GPIO : public IStandardGPIO
    {
    public:
        K210GPIO();
        ~K210GPIO() override;

        bool setMode(uint32_t pin, GPIOMode mode) override;
        bool write(uint32_t pin, bool value) override;
        bool read(uint32_t pin) override;

        uint32_t readPort() override;
        void writePort(uint32_t value) override;
        void setPortMask(uint32_t mask) override;
        void clearPortMask(uint32_t mask) override;

        bool enableInterrupt(uint32_t pin, GPIOMode mode,
                             GPIOInterruptCallback callback) override;
        bool disableInterrupt(uint32_t pin) override;
        void pollInterrupts() override;

        const char *getPlatformName() const override { return "K210"; }

        void setFPIOAFunction(uint32_t pin, uint32_t function);

        void setPWM(uint32_t pin, int value);

    private:
        bool isGPIOHS(uint32_t pin) const { return pin < K210_GPIOHS_COUNT; }
        bool isGPIO(uint32_t pin) const { return pin >= K210_GPIOHS_COUNT && pin < K210_TOTAL_PIN_COUNT; }
        uint32_t toGPIOIndex(uint32_t pin) const { return pin - K210_GPIOHS_COUNT; }

        uint32_t m_PortValue;
        uint32_t m_PortMask;
        uint32_t m_InterruptMask;
        GPIOInterruptCallback m_Callbacks[K210_GPIOHS_COUNT];
        GPIOMode m_Modes[K210_GPIOHS_COUNT];
    };

}

#endif
