#include "led.h"

void led_init()
{
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    pwm_set_wrap(slice_num, 255);
    pwm_set_clkdiv(slice_num, 4.0f);
    pwm_set_enabled(slice_num, true);
}

void set_led(int lightIntensity)
{
    pwm_set_gpio_level(LED_PIN, lightIntensity);
}