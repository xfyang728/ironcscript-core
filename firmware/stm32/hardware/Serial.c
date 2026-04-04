#include "stm32f10x.h"

void Serial_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;

    GPIOA->CRH = (GPIOA->CRH & ~0x0FF0) | 0x04B0;

    USART1->BRR = 0x271;
    USART1->CR1 = USART_CR1_TE | USART_CR1_UE;
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

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        Serial_SendByte(Number / (100000 / (1 << i)) % 10 + '0');
    }
}