#include "ultra_sonic_sensor.h"
void ultra_sonic_init()
{
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);

    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
}

int read_ultra_sonic()
{
    gpio_put(TRIG_PIN, 1);
    sleep_ms(10);
    gpio_put(TRIG_PIN, 0);

    while (gpio_get(ECHO_PIN) == 0)
        ;
    absolute_time_t start_time = get_absolute_time();

    while (gpio_get(ECHO_PIN) == 1)
        ;
    absolute_time_t end_time = get_absolute_time();

    uint32_t duration = absolute_time_diff_us(start_time, end_time);
    float distance = duration * 0.034 / 2;
    if (distance > 50)
        return 0;
    return 1;
}