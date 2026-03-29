#ifndef CSE_PLATFORM_CONSTANTS_H
#define CSE_PLATFORM_CONSTANTS_H

#include "platform/k210/K210GPIO.h"
#include <cstdint>
#include <cstdio>
#include <functional>

namespace cse {

using RegisterFunc = std::function<void(const char* name, int64_t value)>;

class PlatformConstants {
public:
    static void registerCommon(RegisterFunc& reg) {
        reg("INPUT", 0);
        reg("INPUT_PULL_DOWN", 1);
        reg("INPUT_PULL_UP", 2);
        reg("OUTPUT", 3);
        reg("HIGH", 1);
        reg("LOW", 0);
    }
};

class K210Constants : public PlatformConstants {
public:
    static void registerAll(RegisterFunc& reg) {
        registerCommon(reg);

        for (int i = 0; i < 32; i++) {
            char name[16];
            snprintf(name, sizeof(name), "GPIOHS%d", i);
            reg(name, i);
        }

        for (int i = 0; i < 8; i++) {
            char name[16];
            snprintf(name, sizeof(name), "GPIO%d", i);
            reg(name, 32 + i);
        }

        reg("FUNC_GPIOHS0", K210Pin::FUNC_GPIOHS0);
        reg("FUNC_GPIOHS1", K210Pin::FUNC_GPIOHS1);
        reg("FUNC_GPIOHS2", K210Pin::FUNC_GPIOHS2);
        reg("FUNC_GPIOHS3", K210Pin::FUNC_GPIOHS3);
        reg("FUNC_GPIOHS4", K210Pin::FUNC_GPIOHS4);
        reg("FUNC_GPIOHS5", K210Pin::FUNC_GPIOHS5);
        reg("FUNC_GPIOHS6", K210Pin::FUNC_GPIOHS6);
        reg("FUNC_GPIOHS7", K210Pin::FUNC_GPIOHS7);
        reg("FUNC_GPIOHS8", K210Pin::FUNC_GPIOHS8);
        reg("FUNC_GPIOHS9", K210Pin::FUNC_GPIOHS9);
        reg("FUNC_GPIOHS10", K210Pin::FUNC_GPIOHS10);
        reg("FUNC_GPIOHS11", K210Pin::FUNC_GPIOHS11);
        reg("FUNC_GPIOHS12", K210Pin::FUNC_GPIOHS12);
        reg("FUNC_GPIOHS13", K210Pin::FUNC_GPIOHS13);
        reg("FUNC_GPIOHS14", K210Pin::FUNC_GPIOHS14);
        reg("FUNC_GPIOHS15", K210Pin::FUNC_GPIOHS15);
        reg("FUNC_GPIOHS16", K210Pin::FUNC_GPIOHS16);
        reg("FUNC_GPIOHS17", K210Pin::FUNC_GPIOHS17);
        reg("FUNC_GPIOHS18", K210Pin::FUNC_GPIOHS18);
        reg("FUNC_GPIOHS19", K210Pin::FUNC_GPIOHS19);
        reg("FUNC_GPIOHS20", K210Pin::FUNC_GPIOHS20);
        reg("FUNC_GPIOHS21", K210Pin::FUNC_GPIOHS21);
        reg("FUNC_GPIOHS22", K210Pin::FUNC_GPIOHS22);
        reg("FUNC_GPIOHS23", K210Pin::FUNC_GPIOHS23);
        reg("FUNC_GPIOHS24", K210Pin::FUNC_GPIOHS24);
        reg("FUNC_GPIOHS25", K210Pin::FUNC_GPIOHS25);
        reg("FUNC_GPIOHS26", K210Pin::FUNC_GPIOHS26);
        reg("FUNC_GPIOHS27", K210Pin::FUNC_GPIOHS27);
        reg("FUNC_GPIOHS28", K210Pin::FUNC_GPIOHS28);
        reg("FUNC_GPIOHS29", K210Pin::FUNC_GPIOHS29);
        reg("FUNC_GPIOHS30", K210Pin::FUNC_GPIOHS30);
        reg("FUNC_GPIOHS31", K210Pin::FUNC_GPIOHS31);
        reg("FUNC_GPIO0", K210Pin::FUNC_GPIO0);
        reg("FUNC_GPIO1", K210Pin::FUNC_GPIO1);
        reg("FUNC_GPIO2", K210Pin::FUNC_GPIO2);
        reg("FUNC_GPIO3", K210Pin::FUNC_GPIO3);
        reg("FUNC_GPIO4", K210Pin::FUNC_GPIO4);
        reg("FUNC_GPIO5", K210Pin::FUNC_GPIO5);
        reg("FUNC_GPIO6", K210Pin::FUNC_GPIO6);
        reg("FUNC_GPIO7", K210Pin::FUNC_GPIO7);
    }
};

class STM32Constants : public PlatformConstants {
public:
    static void registerAll(RegisterFunc& reg) {
        registerCommon(reg);

        const char* ports[] = {"PA", "PB", "PC", "PD", "PE", "PF", "PG"};
        for (int p = 0; p < 7; p++) {
            for (int i = 0; i < 16; i++) {
                char name[16];
                snprintf(name, sizeof(name), "P%s%d", &ports[p][1], i);
                reg(name, p * 16 + i);
            }
        }

        reg("PORT_A", 0);
        reg("PORT_B", 1);
        reg("PORT_C", 2);
        reg("PORT_D", 3);
        reg("PORT_E", 4);
        reg("PORT_F", 5);
        reg("PORT_G", 6);
    }
};

}

#endif