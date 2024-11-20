#include "ir_sensor.h"

void ir_sensor_init(int pin)
{

    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
}

int read_ir_sensor(int pin)
{
    return gpio_get(pin);
}