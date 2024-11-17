#include <stdio.h>
#include "lcd_i2c.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "wiper.h"
#include "light_sensor.h"

int main()
{
    stdio_init_all();
    while (1)
    {
        int something = read_light_sensor();
        printf("res: %d \n", something);
        sleep_ms(1000);
    }
}
