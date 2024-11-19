#ifndef LED_H
#define LED_H

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define LED_PIN 0

void led_init();
void set_led(int lightIntensity);
#endif