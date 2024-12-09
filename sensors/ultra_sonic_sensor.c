#include "ultra_sonic_sensor.h"

static absolute_time_t activation_time;
static bool is_active = false;

void ultra_sonic_init()
{
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);

    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);

    is_active = false; // Initialize active state
}

int read_ultra_sonic()
{
    // If still within the 5-minute activation period, return 1
    if (is_active && absolute_time_diff_us(activation_time, get_absolute_time()) <= 1 * 60 * 1000000)
    {
        return 1;
    }

    gpio_put(TRIG_PIN, 1);
    sleep_ms(10); // Can be micro seconds for more accuracyy
    gpio_put(TRIG_PIN, 0);

    while (gpio_get(ECHO_PIN) == 0)
        ;
    absolute_time_t start_time = get_absolute_time();

    while (gpio_get(ECHO_PIN) == 1)
        ;
    absolute_time_t end_time = get_absolute_time();

    uint32_t duration = absolute_time_diff_us(start_time, end_time);
    float distance = duration * 0.034 / 2;
    printf("distance is %f\n", distance);

    if (distance <= 100 && distance > 1)
    {
        // Start the 5-minute activation period
        activation_time = get_absolute_time();
        is_active = true;
        return 1;
    }

    // If no detection, reset the active state
    is_active = false;
    return 0;
}
