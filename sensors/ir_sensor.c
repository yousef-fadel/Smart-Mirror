#include "ir_sensor.h"
#include "pico/time.h"

static absolute_time_t ir_timer_start = {0}; // Tracks the start of the 10-second period
static bool ir_held_low = false;             // Indicates if the pin is being held low

void ir_sensor_init(int pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
}

int read_ir_sensor(int pin)
{
    // If we are in the 10-second hold period, continue returning 0
    if (ir_held_low && absolute_time_diff_us(ir_timer_start, get_absolute_time()) <= 10 * 1000000)
    {
        return 0;
    }

    int sensor_value = gpio_get(pin);

    if (sensor_value == 0)
    {
        ir_timer_start = get_absolute_time();
        ir_held_low = true;
        return 0;
    }

    ir_held_low = false;
    return sensor_value;
}
