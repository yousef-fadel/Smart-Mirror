#ifndef SMART_MIRROR_H
#define SMART_MIRROR_H

#include <stdio.h>
#include <string.h>
#include "actuators/lcd_i2c.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "actuators/wiper.h"
#include "sensors/light_sensor.h"
#include "sensors/ir_sensor.h"
#include "actuators/led.h"
#include "sensors/ultra_sonic_sensor.h"

void init();

#endif