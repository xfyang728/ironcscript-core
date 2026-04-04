#include "stm32f10x.h"
#include "hardware/OLED.h"
#include "hardware/Serial.h"

extern void SystemInit(void);

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
    }

    return 0;
}