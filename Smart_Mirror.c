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

void gpio_wiper_isr(uint gpio, uint32_t events)
{
    lcd_clear();
    lcd_string("Wiper is on");
    wiperOn();
    lcd_clear();
    lcd_string("Weather is 25C");
}
int main()
{
    stdio_init_all();
    init();

    gpio_set_irq_enabled_with_callback(read_ir_sensor(ACTIVATE_MIRROR_IR_SENSOR), GPIO_IRQ_LEVEL_LOW, true, &gpio_wiper_isr);
    irq_set_priority(IO_IRQ_BANK0, 0);

    lcd_set_cursor(0, 0);
    while (1)
    {
        int mirrorActivation = read_ultra_sonic(ACTIVATE_MIRROR_IR_SENSOR);
        if (mirrorActivation)
        {
            irq_set_enabled(IO_IRQ_BANK0, 1);
            lcd_clear();
            lcd_string("Weather is 25C");
            while (1)
            {
                sleep_ms(500);
                int lightIntensity = read_light_sensor();
                printf("i am activated, light is %d\n", lightIntensity);
                set_led(lightIntensity);
            }
        }
        else
        {
            irq_set_enabled(IO_IRQ_BANK0, 0);
            set_led(0);
            lcd_clear();
            wiperOff();
            printf("i am not activated \n");
        }
        sleep_ms(500);
    }
}
