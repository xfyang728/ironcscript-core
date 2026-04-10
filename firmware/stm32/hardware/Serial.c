#include "stm32f10x.h"
#include "Serial.h"

static uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
    uint32_t result = 1;
    while (y--) {
        result *= x;
    }
    return result;
}

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

void Serial_SendString(const char *String)
{
    uint8_t i = 0;
    while (String[i] != '\0') {
        Serial_SendByte(String[i]);
        i++;
    }
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    if (Length >= 16) {
        uint8_t hexDigits[8];
        for (int i = 7; i >= 0; i--) {
            uint8_t digit = Number & 0xF;
            hexDigits[i] = digit < 10 ? digit + '0' : digit - 10 + 'A';
            Number >>= 4;
        }
        for (int i = 0; i < 8; i++) {
            Serial_SendByte(hexDigits[i]);
        }
    } else {
        uint8_t i;
        for (i = 0; i < Length; i++) {
            uint8_t digit = Number / Serial_Pow(10, Length - i - 1) % 10;
            Serial_SendByte(digit + '0');
        }
    }
}

void int2str(int32_t value, char *buffer)
{
    char temp[16];
    uint8_t isNeg = 0;
    uint8_t idx = 0;

    if (value < 0) {
        isNeg = 1;
        value = -value;
    }

    if (value == 0) {
        temp[idx++] = '0';
    } else {
        while (value > 0) {
            temp[idx++] = '0' + (value % 10);
            value /= 10;
        }
    }

    uint8_t i = 0;
    if (isNeg) {
        buffer[i++] = '-';
    }

    for (int j = idx - 1; j >= 0; j--) {
        buffer[i++] = temp[j];
    }
    buffer[i] = '\0';
}