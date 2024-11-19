#include "ir_sensor.h"

void init_ir_sensor()
{

    gpio_init(IR_SENSOR_PIN);
    gpio_set_dir(IR_SENSOR_PIN, GPIO_IN);
}

bool read_ir_sensor()
{
    return gpio_get(IR_SENSOR_PIN);
}