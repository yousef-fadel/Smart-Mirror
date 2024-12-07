
#ifndef IR_SENSOR
#define IR_SENSOR

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

#define ACTIVATE_MIRROR_IR_SENSOR 19
#define ACTIVATE_WIPER_IR_SENSOR 20
void ir_sensor_init(int pin);
int read_ir_sensor(int pin);

#endif