#include "Smart_Mirror.h"
struct weather_fetch* api_call_result;


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
    if(read_ultra_sonic())
    {
        int lightIntensity = read_light_sensor();
        set_led(lightIntensity);
    }
}

bool check_time_api_callback(struct repeating_timer * call_timer_api)
{
    api_call_result = fetchWeatherAndTime();
}

void wiper_isr(uint gpio, uint32_t events)
{
    if(read_ultra_sonic())
    {
        lcd_clear();
        lcd_string("Wiper is on");
        wiperOn();
        wiperOff();
        lcd_clear();
    }
}

void writeWeather(float weather)
{
    char result[16] = "Weather is ";  
    int weatherInt = (int)weather;
    sprintf(result + strlen(result), "%dC", weatherInt);
    lcd_set_cursor(1,0);
    lcd_string(result);
}
void writeTime(char* timeNow)
{
    char result[16] = "";  
    strcat(result, timeNow);
    lcd_set_cursor(0,0);
    lcd_string(result);
}

int main()
{
    stdio_init_all();
    init();

    lcd_string("Fetching weather");
    api_call_result = fetchWeatherAndTime();
    sleep_ms(5000);

    // interrupt for wiper
    gpio_set_irq_enabled_with_callback(ACTIVATE_WIPER_IR_SENSOR, GPIO_IRQ_LEVEL_LOW, true, &wiper_isr);
    irq_set_priority(IO_IRQ_BANK0, 200); 
    irq_set_enabled(IO_IRQ_BANK0, true); 

    // check light every 3 seconds to change LED strip brightness
    struct repeating_timer check_light_sensor;
    add_repeating_timer_ms(2000, light_adjust_callback, NULL, &check_light_sensor);

    // check if time has been updated while mirror is on every 15 seconds
    struct repeating_timer check_time;
    add_repeating_timer_ms(30000, check_time_api_callback, NULL, &check_time);
    

    lcd_clear();
    while (1)
    {
        int mirrorActivation = read_ultra_sonic();
        while (mirrorActivation)
        {
            sleep_ms(500);
            writeTime(api_call_result -> timeNow);
            writeWeather(api_call_result -> weather);
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
