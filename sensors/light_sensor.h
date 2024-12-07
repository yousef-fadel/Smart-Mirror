#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define LIGHT_SENSOR_PIN 26
void light_sensor_init();
int read_light_sensor();
#endif