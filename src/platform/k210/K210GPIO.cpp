#include "K210GPIO.h"
#include "K210HAL.h"
#include <cstring>

extern "C" {
#include "fpioa.h"
#include "gpio.h"
#include "gpiohs.h"
#include "plic.h"
}

namespace cse {

static volatile uint32_t g_GPIOHS_InterruptCount = 0;

static int gpiohs_isr(void* ctx) {
    (void)ctx;
    g_GPIOHS_InterruptCount++;
    return 0;
}

K210GPIO::K210GPIO()
    : m_PortValue(0), m_PortMask(0), m_InterruptMask(0) {
    memset(m_Callbacks, 0, sizeof(m_Callbacks));
    memset(m_Modes, 0, sizeof(m_Modes));

    for (uint32_t i = 0; i < K210_GPIOHS_COUNT; i++) {
        m_Modes[i] = GPIOMode::INPUT;
    }
}

K210GPIO::~K210GPIO() {
}

bool K210GPIO::setMode(uint32_t pin, GPIOMode mode) {
    if (pin >= K210_TOTAL_PIN_COUNT) {
        return false;
    }

    gpio_drive_mode_t drive_mode;
    if (mode == GPIOMode::INPUT) {
        drive_mode = GPIO_DM_INPUT;
    } else if (mode == GPIOMode::INPUT_PULL_UP) {
        drive_mode = GPIO_DM_INPUT_PULL_UP;
    } else if (mode == GPIOMode::INPUT_PULL_DOWN) {
        drive_mode = GPIO_DM_INPUT_PULL_DOWN;
    } else if (mode == GPIOMode::OUTPUT || mode == GPIOMode::OUTPUT_OD) {
        drive_mode = GPIO_DM_OUTPUT;
    } else {
        return false;
    }

    if (isGPIOHS(pin)) {
        m_Modes[pin] = mode;
        gpiohs_set_drive_mode(pin, drive_mode);
    } else if (isGPIO(pin)) {
        gpio_set_drive_mode(toGPIOIndex(pin), drive_mode);
    }

    return true;
}

bool K210GPIO::write(uint32_t pin, bool value) {
    if (pin >= K210_TOTAL_PIN_COUNT) {
        return false;
    }

    gpio_pin_value_t gpio_value = value ? GPIO_PV_HIGH : GPIO_PV_LOW;

    if (isGPIOHS(pin)) {
        if (m_Modes[pin] != GPIOMode::OUTPUT && m_Modes[pin] != GPIOMode::OUTPUT_OD) {
            return false;
        }
        if (value) {
            m_PortValue |= (1 << pin);
        } else {
            m_PortValue &= ~(1 << pin);
        }
        gpiohs_set_pin(pin, gpio_value);
    } else if (isGPIO(pin)) {
        gpio_set_pin(toGPIOIndex(pin), gpio_value);
    }

    return true;
}

bool K210GPIO::read(uint32_t pin) {
    if (pin >= K210_TOTAL_PIN_COUNT) {
        return false;
    }

    gpio_pin_value_t value;

    if (isGPIOHS(pin)) {
        value = gpiohs_get_pin(pin);
    } else if (isGPIO(pin)) {
        value = gpio_get_pin(toGPIOIndex(pin));
    } else {
        return false;
    }

    return value == GPIO_PV_HIGH;
}

uint32_t K210GPIO::readPort() {
    uint32_t value = 0;

    if (m_PortMask == 0) {
        for (uint32_t i = 0; i < K210_GPIOHS_COUNT; i++) {
            if (read(i)) {
                value |= (1 << i);
            }
        }
    } else {
        for (uint32_t i = 0; i < K210_GPIOHS_COUNT; i++) {
            if ((m_PortMask & (1 << i)) == 0) {
                if (read(i)) {
                    value |= (1 << i);
                }
            }
        }
    }

    return value;
}

void K210GPIO::writePort(uint32_t value) {
    for (uint32_t i = 0; i < K210_GPIOHS_COUNT; i++) {
        if ((m_PortMask & (1 << i)) == 0) {
            write(i, (value & (1 << i)) != 0);
        }
    }
}

void K210GPIO::setPortMask(uint32_t mask) {
    m_PortMask = mask;
}

void K210GPIO::clearPortMask(uint32_t mask) {
    m_PortMask &= ~mask;
}

bool K210GPIO::enableInterrupt(uint32_t pin, GPIOMode mode,
                             GPIOInterruptCallback callback) {
    if (!isGPIOHS(pin)) {
        return false;
    }

    gpiohs_set_drive_mode(pin, GPIO_DM_INPUT);

    plic_irq_t irq_num = static_cast<plic_irq_t>(IRQN_GPIOHS0_INTERRUPT + pin);

    if (callback) {
        m_Callbacks[pin] = callback;
        m_InterruptMask |= (1 << pin);

        plic_irq_register(irq_num, gpiohs_isr, this);
        plic_set_priority(irq_num, 1);
        plic_irq_enable(irq_num);
    }

    (void)mode;
    return true;
}

bool K210GPIO::disableInterrupt(uint32_t pin) {
    if (!isGPIOHS(pin)) {
        return false;
    }

    plic_irq_t irq_num = static_cast<plic_irq_t>(IRQN_GPIOHS0_INTERRUPT + pin);

    plic_irq_disable(irq_num);
    plic_irq_unregister(irq_num);

    m_InterruptMask &= ~(1 << pin);
    m_Callbacks[pin] = nullptr;

    return true;
}

void K210GPIO::pollInterrupts() {
}

void K210GPIO::setFPIOAFunction(uint32_t pin, uint32_t function) {
    fpioa_set_function(pin, static_cast<fpioa_function_t>(function));
}

void K210GPIO::setPWM(uint32_t pin, int value) {
    if (pin >= K210_TOTAL_PIN_COUNT) {
        return;
    }
    
    if (value < 0) value = 0;
    if (value > 255) value = 255;
    
    if (value == 0) {
        write(pin, false);
    } else if (value == 255) {
        write(pin, true);
    } else {
        bool pwmValue = (value > 127);
        write(pin, pwmValue);
    }
}

}
