.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.global g_pfnVectors
.global Reset_Handler

.word 0x20005000
.word Reset_Handler
.word NMI_Handler
.word HardFault_Handler
.word MemManage_Handler
.word BusFault_Handler
.word UsageFault_Handler
.word 0
.word 0
.word 0
.word 0
.word SVC_Handler
.word DebugMon_Handler
.word 0
.word PendSV_Handler
.word SysTick_Handler

.word WWDG_IRQHandler
.word PVD_IRQHandler
.word TAMPER_IRQHandler
.word RTC_IRQHandler
.word FLASH_IRQHandler
.word RCC_IRQHandler
.word EXTI0_IRQHandler
.word EXTI1_IRQHandler
.word EXTI2_IRQHandler
.word EXTI3_IRQHandler
.word EXTI4_IRQHandler
.word DMA1_Channel1_IRQHandler
.word DMA1_Channel2_IRQHandler
.word DMA1_Channel3_IRQHandler
.word DMA1_Channel4_IRQHandler
.word DMA1_Channel5_IRQHandler
.word DMA1_Channel6_IRQHandler
.word DMA1_Channel7_IRQHandler
.word ADC1_2_IRQHandler
.word USB_HP_CAN1_TX_IRQHandler
.word USB_LP_CAN1_RX0_IRQHandler
.word CAN1_RX1_IRQHandler
.word CAN1_SCE_IRQHandler
.word EXTI9_5_IRQHandler
.word TIM1_BRK_IRQHandler
.word TIM1_UP_IRQHandler
.word TIM1_TRG_COM_IRQHandler
.word TIM1_CC_IRQHandler
.word TIM2_IRQHandler
.word TIM3_IRQHandler
.word TIM4_IRQHandler
.word I2C1_EV_IRQHandler
.word I2C1_ER_IRQHandler
.word I2C2_EV_IRQHandler
.word I2C2_ER_IRQHandler
.word SPI1_IRQHandler
.word SPI2_IRQHandler
.word USART1_IRQHandler
.word USART2_IRQHandler
.word USART3_IRQHandler
.word EXTI15_10_IRQHandler
.word RTCAlarm_IRQHandler
.word USBWakeUp_IRQHandler

.type Reset_Handler, %function
Reset_Handler:
    bl main
    b Reset_Handler

.type NMI_Handler, %function
NMI_Handler:
    b NMI_Handler

.type HardFault_Handler, %function
HardFault_Handler:
    b HardFault_Handler

.type MemManage_Handler, %function
MemManage_Handler:
    b MemManage_Handler

.type BusFault_Handler, %function
BusFault_Handler:
    b BusFault_Handler

.type UsageFault_Handler, %function
UsageFault_Handler:
    b UsageFault_Handler

.type SVC_Handler, %function
SVC_Handler:
    b SVC_Handler

.type DebugMon_Handler, %function
DebugMon_Handler:
    b DebugMon_Handler

.type PendSV_Handler, %function
PendSV_Handler:
    b PendSV_Handler

.type SysTick_Handler, %function
SysTick_Handler:
    b SysTick_Handler

.type WWDG_IRQHandler, %function
WWDG_IRQHandler:
    b WWDG_IRQHandler

.type PVD_IRQHandler, %function
PVD_IRQHandler:
    b PVD_IRQHandler

.type TAMPER_IRQHandler, %function
TAMPER_IRQHandler:
    b TAMPER_IRQHandler

.type RTC_IRQHandler, %function
RTC_IRQHandler:
    b RTC_IRQHandler

.type FLASH_IRQHandler, %function
FLASH_IRQHandler:
    b FLASH_IRQHandler

.type RCC_IRQHandler, %function
RCC_IRQHandler:
    b RCC_IRQHandler

.type EXTI0_IRQHandler, %function
EXTI0_IRQHandler:
    b EXTI0_IRQHandler

.type EXTI1_IRQHandler, %function
EXTI1_IRQHandler:
    b EXTI1_IRQHandler

.type EXTI2_IRQHandler, %function
EXTI2_IRQHandler:
    b EXTI2_IRQHandler

.type EXTI3_IRQHandler, %function
EXTI3_IRQHandler:
    b EXTI3_IRQHandler

.type EXTI4_IRQHandler, %function
EXTI4_IRQHandler:
    b EXTI4_IRQHandler

.type DMA1_Channel1_IRQHandler, %function
DMA1_Channel1_IRQHandler:
    b DMA1_Channel1_IRQHandler

.type DMA1_Channel2_IRQHandler, %function
DMA1_Channel2_IRQHandler:
    b DMA1_Channel2_IRQHandler

.type DMA1_Channel3_IRQHandler, %function
DMA1_Channel3_IRQHandler:
    b DMA1_Channel3_IRQHandler

.type DMA1_Channel4_IRQHandler, %function
DMA1_Channel4_IRQHandler:
    b DMA1_Channel4_IRQHandler

.type DMA1_Channel5_IRQHandler, %function
DMA1_Channel5_IRQHandler:
    b DMA1_Channel5_IRQHandler

.type DMA1_Channel6_IRQHandler, %function
DMA1_Channel6_IRQHandler:
    b DMA1_Channel6_IRQHandler

.type DMA1_Channel7_IRQHandler, %function
DMA1_Channel7_IRQHandler:
    b DMA1_Channel7_IRQHandler

.type ADC1_2_IRQHandler, %function
ADC1_2_IRQHandler:
    b ADC1_2_IRQHandler

.type USB_HP_CAN1_TX_IRQHandler, %function
USB_HP_CAN1_TX_IRQHandler:
    b USB_HP_CAN1_TX_IRQHandler

.type USB_LP_CAN1_RX0_IRQHandler, %function
USB_LP_CAN1_RX0_IRQHandler:
    b USB_LP_CAN1_RX0_IRQHandler

.type CAN1_RX1_IRQHandler, %function
CAN1_RX1_IRQHandler:
    b CAN1_RX1_IRQHandler

.type CAN1_SCE_IRQHandler, %function
CAN1_SCE_IRQHandler:
    b CAN1_SCE_IRQHandler

.type EXTI9_5_IRQHandler, %function
EXTI9_5_IRQHandler:
    b EXTI9_5_IRQHandler

.type TIM1_BRK_IRQHandler, %function
TIM1_BRK_IRQHandler:
    b TIM1_BRK_IRQHandler

.type TIM1_UP_IRQHandler, %function
TIM1_UP_IRQHandler:
    b TIM1_UP_IRQHandler

.type TIM1_TRG_COM_IRQHandler, %function
TIM1_TRG_COM_IRQHandler:
    b TIM1_TRG_COM_IRQHandler

.type TIM1_CC_IRQHandler, %function
TIM1_CC_IRQHandler:
    b TIM1_CC_IRQHandler

.type TIM2_IRQHandler, %function
TIM2_IRQHandler:
    b TIM2_IRQHandler

.type TIM3_IRQHandler, %function
TIM3_IRQHandler:
    b TIM3_IRQHandler

.type TIM4_IRQHandler, %function
TIM4_IRQHandler:
    b TIM4_IRQHandler

.type I2C1_EV_IRQHandler, %function
I2C1_EV_IRQHandler:
    b I2C1_EV_IRQHandler

.type I2C1_ER_IRQHandler, %function
I2C1_ER_IRQHandler:
    b I2C1_ER_IRQHandler

.type I2C2_EV_IRQHandler, %function
I2C2_EV_IRQHandler:
    b I2C2_EV_IRQHandler

.type I2C2_ER_IRQHandler, %function
I2C2_ER_IRQHandler:
    b I2C2_ER_IRQHandler

.type SPI1_IRQHandler, %function
SPI1_IRQHandler:
    b SPI1_IRQHandler

.type SPI2_IRQHandler, %function
SPI2_IRQHandler:
    b SPI2_IRQHandler

.type USART1_IRQHandler, %function
USART1_IRQHandler:
    b USART1_IRQHandler

.type USART2_IRQHandler, %function
USART2_IRQHandler:
    b USART2_IRQHandler

.type USART3_IRQHandler, %function
USART3_IRQHandler:
    b USART3_IRQHandler

.type EXTI15_10_IRQHandler, %function
EXTI15_10_IRQHandler:
    b EXTI15_10_IRQHandler

.type RTCAlarm_IRQHandler, %function
RTCAlarm_IRQHandler:
    b RTCAlarm_IRQHandler

.type USBWakeUp_IRQHandler, %function
USBWakeUp_IRQHandler:
    b USBWakeUp_IRQHandler

.size Reset_Handler, .-Reset_Handler