#include <stdio.h>
#include "lcd_i2c.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "wiper.h"
#include "light_sensor.h"
#include "ir_sensor.h"

int main()
{
    stdio_init_all();
    // light_sensor_init();
    // init_ir_sensor();
    wiper_init();
    printf("hello");
    // servo_init(0);
    while (1)
    {
        // printf("light: %d \n", read_ir_sensor());
        wiperOn();
        // wiperReset();
        // sleep_ms(1000);
        // printf("hello");
        // wiperTest();
        // sleep_ms(1000);
        // printf("hello");
        // servo_set_angle(0, 0);
        // sleep_ms(500);
        // servo_set_angle(0, 0);
        // sleep_ms(500);
        // wiperOn();

        // servoControl(0);

        // sleep_ms(5000);
    }
}
