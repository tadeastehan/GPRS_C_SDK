#ifndef __BME280_H_
#define __BME280_H_

#include <stdint.h>

void bme280_init(void);
void bme280_startConvertion(void);
uint8_t bme280_status(void);
int32_t bme280_readTemperature(void);
int32_t bme280_readHumidity(void);
int32_t bme280_readPressure(void);
float bme280_readAltitude(float seaLevel);

#endif
