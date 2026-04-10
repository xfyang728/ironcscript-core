#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif

void LED_Init(void);
void LED_On(void);
void LED_Off(void);

#ifdef __cplusplus
}
#endif

#endif