#include "stm32f10x.h"

void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART1->BRR = 0x271;
    USART1->CR1 = USART_CR1_TE | USART_CR1_UE;
    USART1->CR2 = 0;
    USART1->CR3 = 0;
}

void Serial_SendByte(uint8_t Byte)
{
    USART1->DR = Byte;
    volatile uint32_t timeout = 0;
    while ((USART1->SR & USART_SR_TXE) == 0) {
        timeout++;
        if (timeout > 0xFFFF) break;
    }
}

void Serial_SendString(char *String)
{
    uint8_t i = 0;
    while (String[i] != '\0') {
        Serial_SendByte(String[i]);
        i++;
    }
}

static uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
    uint32_t result = 1;
    while (y--) {
        result *= x;
    }
    return result;
}

void Serial_SendNumber(uint32_t number, uint8_t length)
{
    uint8_t i;
    for (i = 0; i < length; i++) {
        uint8_t digit = number / Serial_Pow(10, length - i - 1) % 10;
        Serial_SendByte(digit + '0');
    }
}