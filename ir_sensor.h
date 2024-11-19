
#ifndef IR_SENSOR
#define IR_SENSOR

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

#define IR_SENSOR_PIN 0
void init_ir_sensor();
bool read_ir_sensor();

#endif