#include "light_sensor.h"

void light_sensor_init()
{
    adc_init();
    adc_gpio_init(LIGHT_SENSOR_PIN);
}

int read_light_sensor()
{
    adc_select_input(0);
    return adc_read();
}