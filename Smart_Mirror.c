#include <stdio.h>
#include <string.h>
#include "lcd_i2c.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "wiper.h"
#include "sensors/light_sensor.h"
#include "sensors/ir_sensor.h"
#include "led.h"
#include "sensors/ultra_sonic_sensor.h"

volatile bool mirror_timer_finished = false;
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

int64_t mirror_on_timer()
{
    int mirrorActivation = read_ultra_sonic(ACTIVATE_MIRROR_IR_SENSOR);
    if (mirrorActivation)
        return -1; // mesh error, this makes so the timer reactivates for the same amount of time we originally input
    mirror_timer_finished = true;
    return 0; // disables timer
}
int main()
{
    stdio_init_all();
    init();

    gpio_set_irq_enabled_with_callback(read_ir_sensor(ACTIVATE_MIRROR_IR_SENSOR), GPIO_IRQ_LEVEL_LOW, true, &gpio_wiper_isr);
    // need to have the priority lower than the timer
    // irq_set_priority(IO_IRQ_BANK0, 0);

    lcd_set_cursor(0, 0);
    while (1)
    {
        int mirrorActivation = 1;
        if (mirrorActivation)
        {
            add_alarm_in_ms(10000, mirror_on_timer, NULL, true);
            irq_set_enabled(IO_IRQ_BANK0, 1);
            lcd_clear();
            lcd_string("Weather is 25C");
            while (!mirror_timer_finished)
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
