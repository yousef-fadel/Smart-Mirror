#ifndef WIPER_H
#define WIPER_H
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "hardware/timer.h"

#define time 5000

#define SERVO_PIN 11
#define WRAP 20000
#define CLKDIV 16.0f

void wiper_init();
void wiperOn();
void wiperOff();
int64_t timer_interrupt_handler();
void timer_disable();

#endif