#ifndef __LIGHT_SENSOR_H
#define __LIGHT_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

void LightSensor_Init(void);
uint8_t LightSensor_Get(void);

#ifdef __cplusplus
}
#endif

#endif
