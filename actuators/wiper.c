#include "wiper.h"

alarm_id_t alarm_id;
int i = 0;

// Initialize the wiper pin as output
void wiper_init()
{
    gpio_init(SERVO_PIN);
    gpio_set_dir(SERVO_PIN, GPIO_OUT);
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_set_wrap(slice_num, WRAP);
    pwm_set_clkdiv(slice_num, CLKDIV); // A larger divider slows down the PWM frequency, while a smaller divider speeds it up.

    pwm_set_enabled(slice_num, true);
}

void wiperOn()
{
    pwm_set_gpio_level(SERVO_PIN, 6000);
    sleep_ms(500);
    pwm_set_gpio_level(SERVO_PIN, 13750);
    sleep_ms(500);
}

void wiperOff()
{
    pwm_set_gpio_level(SERVO_PIN, 6000);
}
