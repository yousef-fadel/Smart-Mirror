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

void light_detection_isr(uint gpio, uint32_t events)
{
    int lightIntensity = read_light_sensor();
    set_led(lightIntensity);
}

void wiper_isr(uint gpio, uint32_t events)
{
    printf("hi");
    lcd_clear();
    lcd_string("Wiper is on");
    wiperOn();
    printf("goodbye");
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

    lcd_set_cursor(0, 0);
    while (1)
    {
        int mirrorActivation = read_ultra_sonic();
        if (mirrorActivation)
        {
            printf("Mirror is active\n");

            lcd_clear();
            lcd_string(result);
            while (mirrorActivation)
            {
                sleep_ms(500);
                wiperOff();
                lcd_clear();
                lcd_string(result);
                mirrorActivation = read_ultra_sonic();
            }
        }
        else
        {
            set_led(0);
            lcd_clear();
            wiperOff();
        }
        sleep_ms(500);
    }
}
