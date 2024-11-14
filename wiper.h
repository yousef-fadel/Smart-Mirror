
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#define time 5000

#define WIPER_PIN 2

#define SERVO_PIN 3
#define WRAP 10000
#define CLKDIV 16.0f

void wiper_init();
void wiperOn();
void wiperOff();
