#include <stdio.h>
#include <string.h>
#include "lcd_i2c.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "wiper.h"
#include "light_sensor.h"
#include "ir_sensor.h"
#include "led.h"
#include "ultra_sonic_sensor.h"

void init()
{
    led_init();
    wiper_init();
    light_sensor_init();
    ir_sensor_init(ACTIVATE_MIRROR_IR_SENSOR);
    ir_sensor_init(ACTIVATE_WIPER_IR_SENSOR);
    lcd_init();
    ultra_sonic_init();
}

// char res[2000] = "light : ";
// char numStr[20];
// sprintf(numStr, "%d", lightIntensity); // Convert integer to string

// strcat(res, numStr);
int main()
{
    stdio_init_all();
    init();

    lcd_set_cursor(0, 0);
    while (1)
    {
        int mirrorActivation = read_ultra_sonic(ACTIVATE_MIRROR_IR_SENSOR);
        if (mirrorActivation)
        {
            int lightIntensity = read_light_sensor();
            lcd_clear();
            lcd_string("hello");
            printf("i am activated, light is %d\n", lightIntensity);
            set_led(lightIntensity);
            // if (!read_ir_sensor(ACTIVATE_WIPER_IR_SENSOR))
            // {
            //     wiperOn();
            // }
        }
        else
        {
            set_led(0);
            lcd_clear();
            lcd_string("mesh sha8al");
            printf("i am not activated 3ashan 5awal\n");
        }
        sleep_ms(500);
    }
}
