#include "STM32GPIO.h"
#include <cstring>

namespace cse {

STM32GPIO::STM32GPIO(uint32_t portBase)
    : m_PortBase(portBase), m_PortValue(0), m_PortMask(0), m_InterruptMask(0) {
    memset(m_Callbacks, 0, sizeof(m_Callbacks));
    memset(m_Modes, 0, sizeof(m_Modes));

    for (uint32_t i = 0; i < STM32_GPIO_PIN_COUNT; i++) {
        m_Modes[i] = GPIOMode::INPUT;
    }
}

STM32GPIO::~STM32GPIO() {
}

bool STM32GPIO::setMode(uint32_t pin, GPIOMode mode) {
    if (pin >= STM32_GPIO_PIN_COUNT) {
        return false;
    }

    m_Modes[pin] = mode;

#ifdef STM32_HAL_GPIO_H
    GPIO_TypeDef* port = reinterpret_cast<GPIO_TypeDef*>(m_PortBase);
    uint32_t pin_bit = (1UL << pin);

    uint32_t mode_mode = 0;
    switch (mode) {
        case GPIOMode::INPUT:
            mode_mode = GPIO_MODE_INPUT;
            break;
        case GPIOMode::INPUT_PULL_UP:
            mode_mode = GPIO_MODE_INPUT;
            break;
        case GPIOMode::INPUT_PULL_DOWN:
            mode_mode = GPIO_MODE_INPUT;
            break;
        case GPIOMode::OUTPUT:
            mode_mode = GPIO_MODE_OUTPUT_PP;
            break;
        case GPIOMode::OUTPUT_OD:
            mode_mode = GPIO_MODE_OUTPUT_OD;
            break;
        default:
            return false;
    }

    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = pin_bit;
    GPIO_InitStruct.Mode = mode_mode;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
#endif

    return true;
}

bool STM32GPIO::write(uint32_t pin, bool value) {
    if (pin >= STM32_GPIO_PIN_COUNT) {
        return false;
    }

    if (m_Modes[pin] != GPIOMode::OUTPUT && m_Modes[pin] != GPIOMode::OUTPUT_OD) {
        return false;
    }

    if (value) {
        m_PortValue |= (1 << pin);
    } else {
        m_PortValue &= ~(1 << pin);
    }

#ifdef STM32_HAL_GPIO_H
    GPIO_TypeDef* port = reinterpret_cast<GPIO_TypeDef*>(m_PortBase);
    HAL_GPIO_WritePin(port, (1UL << pin), value ? GPIO_PIN_SET : GPIO_PIN_RESET);
#else
    (void)pin;
    (void)value;
#endif

    return true;
}

bool STM32GPIO::read(uint32_t pin) {
    if (pin >= STM32_GPIO_PIN_COUNT) {
        return false;
    }

#ifdef STM32_HAL_GPIO_H
    GPIO_TypeDef* port = reinterpret_cast<GPIO_TypeDef*>(m_PortBase);
    return HAL_GPIO_ReadPin(port, (1UL << pin)) == GPIO_PIN_SET;
#else
    return false;
#endif
}

uint32_t STM32GPIO::readPort() {
    uint32_t value = 0;

#ifdef STM32_HAL_GPIO_H
    GPIO_TypeDef* port = reinterpret_cast<GPIO_TypeDef*>(m_PortBase);
    value = HAL_GPIO_ReadPin(port, 0xFFFF);
#endif

    return value;
}

void STM32GPIO::writePort(uint32_t value) {
    for (uint32_t i = 0; i < STM32_GPIO_PIN_COUNT; i++) {
        if ((m_PortMask & (1 << i)) == 0) {
            write(i, (value & (1 << i)) != 0);
        }
    }
}

void STM32GPIO::setPortMask(uint32_t mask) {
    m_PortMask = mask;
}

void STM32GPIO::clearPortMask(uint32_t mask) {
    m_PortMask &= ~mask;
}

bool STM32GPIO::enableInterrupt(uint32_t pin, GPIOMode mode,
                              GPIOInterruptCallback callback) {
    if (pin >= STM32_GPIO_PIN_COUNT) {
        return false;
    }

    m_Callbacks[pin] = callback;
    m_InterruptMask |= (1 << pin);

#ifdef STM32_HAL_GPIO_H
    GPIO_TypeDef* port = reinterpret_cast<GPIO_TypeDef*>(m_PortBase);
    uint32_t pin_bit = (1UL << pin);

    uint32_t mode_mode = GPIO_MODE_IT_RISING;
    switch (mode) {
        case GPIOMode::INPUT:
        case GPIOMode::INPUT_PULL_UP:
        case GPIOMode::INPUT_PULL_DOWN:
            mode_mode = GPIO_MODE_IT_RISING_FALLING;
            break;
        default:
            break;
    }

    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = pin_bit;
    GPIO_InitStruct.Mode = mode_mode;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(port, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(EXTI0_IRQn + pin, 6, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn + pin);
#endif

    return true;
}

bool STM32GPIO::disableInterrupt(uint32_t pin) {
    if (pin >= STM32_GPIO_PIN_COUNT) {
        return false;
    }

    m_InterruptMask &= ~(1 << pin);
    m_Callbacks[pin] = nullptr;

#ifdef STM32_HAL_GPIO_H
    HAL_NVIC_DisableIRQ(EXTI0_IRQn + pin);
#endif

    return true;
}

void STM32GPIO::pollInterrupts() {
#ifdef STM32_HAL_GPIO_H
    for (uint32_t pin = 0; pin < STM32_GPIO_PIN_COUNT; pin++) {
        if ((m_InterruptMask & (1 << pin)) && m_Callbacks[pin]) {
            GPIO_TypeDef* port = reinterpret_cast<GPIO_TypeDef*>(m_PortBase);
            if (__HAL_GPIO_EXTI_GET_FLAG(1UL << pin)) {
                __HAL_GPIO_EXTI_CLEAR_FLAG(1UL << pin);
                m_Callbacks[pin](pin);
            }
        }
    }
#endif
}

}