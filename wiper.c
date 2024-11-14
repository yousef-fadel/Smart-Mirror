#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "wiper.h"

alarm_id_t alarm_id;

// Initialize the wiper pin as output
void wiper_init()
{
    gpio_init(WIPER_PIN);
    gpio_set_dir(WIPER_PIN, GPIO_OUT);

    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);

    pwm_set_wrap(slice_num, WRAP);     // In this case, the PWM counter will reset after counting up to 10,000,
    pwm_set_clkdiv(slice_num, CLKDIV); // A larger divider slows down the PWM frequency, while a smaller divider speeds it up.

    pwm_set_enabled(slice_num, true);
}

void wiperOn()
{
    gpio_put(WIPER_PIN, 1);
    alarm_id = add_alarm_in_ms(time, &timer_interrupt_handler, NULL, false);
}

void wiperOff()
{
    gpio_put(WIPER_PIN, 0);
}

void servoControl(int angle)
{
    // Ensure the angle is between 0 and 90
    if (angle < 0)
        angle = 0;
    if (angle > 90)
        angle = 90;

    // Map the angle (0-90) to PWM level (0-10000)
    int pwm_level = (angle * 10000) / 90; // Scale the angle to the PWM range

    // Set the PWM level for the servo
    pwm_set_gpio_level(SERVO_PIN, pwm_level);
}

void timer_interrupt_handler()
{
    wiperOff();
    timer_disable();
}

void timer_disable()
{
    cancel_alarm(alarm_id);
}
