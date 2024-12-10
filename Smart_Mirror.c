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

// char res[2000] = "light : ";
// char numStr[20];
// sprintf(numStr, "%d", lightIntensity); // Convert integer to string

// strcat(res, numStr);
int main()
{
    stdio_init_all();
    init();

    lcd_set_cursor(0, 0);
    while (1)
    {
        int mirrorActivation = read_ultra_sonic();
        if (mirrorActivation)
        {
            printf("Mirror is active\n");

            lcd_clear();
            lcd_string("Weather is 25C");
            while (mirrorActivation)
            {
                sleep_ms(500);
                int lightIntensity = read_light_sensor();
                printf("i am activated, light is %d\n", lightIntensity);
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
                    lcd_string("Weather is 25C");
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
