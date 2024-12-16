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

int main()
{
    stdio_init_all();
    init();
    double temperature = fetchWeather();
    char result[100] = "Weather is ";  // Initial string
    sprintf(result + strlen(result), "%.2f", temperature);
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
                int lightIntensity = read_light_sensor();
                set_led(lightIntensity);
                if (!read_ir_sensor(ACTIVATE_WIPER_IR_SENSOR))
                {
                    lcd_clear();
                    lcd_string("Wiper is on");
                    wiperOn();
                }
                else
                {
                    wiperOff();
                    lcd_clear();
                    lcd_string(result);
                }
                mirrorActivation = read_ultra_sonic();
            }
        }
        else
        {
            set_led(0);
            lcd_clear();
            wiperOff();
            printf("i am not activated \n");
        }
        sleep_ms(500);
    }
}
