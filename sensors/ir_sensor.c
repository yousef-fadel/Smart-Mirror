#include "ir_sensor.h"
#include "pico/time.h"

void ir_sensor_init(int pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
}

int read_ir_sensor(int pin)
{
    int sensor_value = gpio_get(pin);
    return sensor_value;
}
