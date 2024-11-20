#ifndef ULTRA_SONIC_H
#define ULTRA_SONIC_H

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "pico/time.h"

#define ECHO_PIN 17
#define TRIG_PIN 16

int read_ultra_sonic();
void ultra_sonic_init();
#endif