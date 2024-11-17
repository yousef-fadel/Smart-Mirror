#include <stdio.h>
#include "lcd_i2c.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "wiper.h"

int main()
{
    stdio_init_all();
    while (1)
    {

        printf("hi");
        sleep_ms(3000);
    }
}
