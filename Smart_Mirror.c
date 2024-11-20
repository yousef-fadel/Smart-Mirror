#include <stdio.h>
#include "lcd_i2c.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "wiper.h"
#include "light_sensor.h"
#include "ir_sensor.h"
#include "led.h"

void init()
{
    // led_init();
    // wiper_init();
    // light_sensor_init();
    // ir_sensor_init();
    lcd_init();
}

int main()
{
    stdio_init_all();
    init();
    lcd_set_cursor(0, 0);
    lcd_string("hello");

    while (1)
    {
        int lightValue = read_light_sensor();
        printf("light value: %d \n", lightValue / 16);

        sleep_ms(200);
        set_led(lightValue / 16);
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
