#include "Smart_Mirror.h"

void init()
{
    led_init();
    wiper_init();
    light_sensor_init();
    ir_sensor_init(ACTIVATE_WIPER_IR_SENSOR);
    lcd_init();
    ultra_sonic_init();
}

bool light_adjust_callback(struct repeating_timer *check_light_timer)
{
    int lightIntensity = read_light_sensor();
    set_led(lightIntensity);
}

bool check_time_api_callback(struct repeating_timer * call_timer_api)
{

}

void wiper_isr(uint gpio, uint32_t events)
{
    lcd_clear();
    lcd_string("Wiper is on");
    wiperOn();
}

int main()
{
    stdio_init_all();
    init();

    double temperature = fetchWeather();
    char result[100] = "Weather is ";  
    sprintf(result + strlen(result), "%.2f", temperature);

    gpio_set_irq_enabled_with_callback(ACTIVATE_WIPER_IR_SENSOR, GPIO_IRQ_LEVEL_LOW, true, &wiper_isr);
    irq_set_priority(IO_IRQ_BANK0, 255); 
    irq_set_enabled(IO_IRQ_BANK0, true); 

    struct repeating_timer check_light_sensor;
    add_repeating_timer_ms(3000, light_adjust_callback, NULL, &check_light_sensor);

    int lightIntensity = read_light_sensor();
    set_led(lightIntensity);

    lcd_set_cursor(0, 0);
    while (1)
    {
        int mirrorActivation = read_ultra_sonic();
        while (mirrorActivation)
        {
            lcd_clear();
            lcd_string(result);
            sleep_ms(500);
            wiperOff();
            mirrorActivation = read_ultra_sonic();
        }
        if(!mirrorActivation)
        {
            set_led(0);
            lcd_clear();
            wiperOff();
        }
        sleep_ms(500);
    }
}
