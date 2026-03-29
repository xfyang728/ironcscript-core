#include "STM32Timer.h"
#include <cstring>

#ifdef STM32_HAL_TIMER_H
#include "stm32f4xx_hal.h"
#endif

namespace cse {

STM32Timer::STM32Timer(uint32_t timer_id)
    : m_TimerID(timer_id), m_Running(false),
      m_Mode(TimerMode::PERIODIC), m_Period(0),
      m_Frequency(1000000), m_Callback(nullptr) {
}

STM32Timer::~STM32Timer() {
    stop();
}

bool STM32Timer::start(uint32_t period_us, bool periodic) {
    if (m_TimerID >= STM32_TIMER_COUNT) {
        return false;
    }

    m_Period = period_us;
    m_Mode = periodic ? TimerMode::PERIODIC : TimerMode::ONESHOT;

#ifdef STM32_HAL_TIMER_H
    TIM_HandleTypeDef htim = {};
    htim.Instance = reinterpret_cast<TIM_TypeDef*>(0x40000000 + m_TimerID * 0x400);
    htim.Init.Prescaler = 84 - 1;
    htim.Init.CounterMode = periodic ? TIM_COUNTERMODE_UP : TIM_COUNTERMODE_DOWN;
    htim.Init.Period = period_us;
    htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&htim);
    HAL_TIM_Base_Start(&htim);
#endif

    m_Running = true;
    return true;
}

void STM32Timer::stop() {
    if (m_TimerID >= STM32_TIMER_COUNT) {
        return;
    }

#ifdef STM32_HAL_TIMER_H
    TIM_HandleTypeDef htim = {};
    htim.Instance = reinterpret_cast<TIM_TypeDef*>(0x40000000 + m_TimerID * 0x400);
    HAL_TIM_Base_Stop(&htim);
#endif

    m_Running = false;
}

bool STM32Timer::isRunning() {
    return m_Running;
}

uint64_t STM32Timer::getTicks() {
    if (m_TimerID >= STM32_TIMER_COUNT) {
        return 0;
    }

#ifdef STM32_HAL_TIMER_H
    TIM_HandleTypeDef htim = {};
    htim.Instance = reinterpret_cast<TIM_TypeDef*>(0x40000000 + m_TimerID * 0x400);
    return __HAL_TIM_GET_COUNTER(&htim);
#else
    return 0;
#endif
}

bool STM32Timer::configurePWM(uint32_t frequency_hz, uint8_t duty_cycle) {
    if (m_TimerID >= STM32_TIMER_COUNT) {
        return false;
    }

    m_Frequency = frequency_hz;
    m_Mode = TimerMode::PWM;

#ifdef STM32_HAL_TIMER_H
    TIM_OC_InitTypeDef sConfig = {};
    sConfig.OCMode = TIM_OCMODE_PWM1;
    sConfig.Pulse = (duty_cycle * 1000) / 100;
    sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfig.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim, &sConfig, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1);
#endif

    return true;
}

bool STM32Timer::setDutyCycle(uint8_t duty_cycle) {
    if (!m_Running || m_Mode != TimerMode::PWM) {
        return false;
    }

    if (m_TimerID >= STM32_TIMER_COUNT) {
        return false;
    }

#ifdef STM32_HAL_TIMER_H
    TIM_HandleTypeDef htim = {};
    htim.Instance = reinterpret_cast<TIM_TypeDef*>(0x40000000 + m_TimerID * 0x400);
    __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_1, (duty_cycle * 1000) / 100);
#endif

    return true;
}

bool STM32Timer::setFrequency(uint32_t frequency_hz) {
    if (m_Mode != TimerMode::PWM) {
        return false;
    }

    uint8_t current_duty = 50;
    return configurePWM(frequency_hz, current_duty);
}

bool STM32Timer::enableCapture(bool rising, bool falling) {
    if (m_TimerID >= STM32_TIMER_COUNT) {
        return false;
    }

    m_Mode = TimerMode::CAPTURE;
    m_Running = true;

#ifdef STM32_HAL_TIMER_H
    TIM_IC_InitTypeDef sConfig = {};
    sConfig.ICPolarity = rising ? TIM_ICPOLARITY_RISING : TIM_ICPOLARITY_FALLING;
    sConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sConfig.ICPrescaler = TIM_ICPSC_DIV1;
    sConfig.ICFilter = 0;
    HAL_TIM_IC_ConfigChannel(&htim, &sConfig, TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(&htim, TIM_CHANNEL_1);
#endif

    return true;
}

uint32_t STM32Timer::getCaptureValue() {
    if (m_TimerID >= STM32_TIMER_COUNT) {
        return 0;
    }

#ifdef STM32_HAL_TIMER_H
    TIM_HandleTypeDef htim = {};
    htim.Instance = reinterpret_cast<TIM_TypeDef*>(0x40000000 + m_TimerID * 0x400);
    return __HAL_TIM_GET_CAPTURE(&htim, TIM_CHANNEL_1);
#else
    return 0;
#endif
}

void STM32Timer::setCallback(TimerCallback callback) {
    m_Callback = callback;
}

}