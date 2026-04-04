#include "stm32f10x.h"
#include "hardware/OLED.h"
#include "hardware/Serial.h"

extern void SystemInit(void);

void Delay_ms(uint32_t ms)
{
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 7200; j++);
    }
}

int main(void) {
    SystemInit();

    OLED_Init();
    OLED_ShowString(1, 1, "IronCScript");

    Serial_Init();
    OLED_ShowString(2, 1, "Serial OK");
    Serial_SendString("Serial OK\r\n");

    int counter = 0;
    while (1) {
        counter++;
        OLED_ShowNum(3, 1, counter, 6);
        Serial_SendString("Counter: ");
        Serial_SendNumber(counter, 6);
        Serial_SendString("\r\n");
        Delay_ms(1000);
    }

    return 0;
}