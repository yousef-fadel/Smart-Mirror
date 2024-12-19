#include "Smart_Mirror.h"
struct weather_fetch* api_call_result;
int mirrorActivation;

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
    if(mirrorActivation)
    {
        int lightIntensity = read_light_sensor();
        set_led(lightIntensity);
    }
    return true;
}

bool check_time_api_callback(struct repeating_timer * call_timer_api)
{
    if(mirrorActivation)
        api_call_result = fetchWeatherAndTime();
    return true;
}

void wiper_isr(uint gpio, uint32_t events)
{
    if(mirrorActivation)
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
    lcd_set_cursor(0,0);
    lcd_string(result);
}
void writeTime(char* timeNow)
{
    char result[16] = "";  
    strcat(result, timeNow);
    lcd_set_cursor(1,0);
    lcd_string(result);
}

int main()
{
    stdio_init_all();
    init();

    lcd_string("Fetching weather");
    api_call_result = fetchWeatherAndTime();
    sleep_ms(6000);

    // interrupt for wiper
    gpio_set_irq_enabled_with_callback(ACTIVATE_WIPER_IR_SENSOR, GPIO_IRQ_LEVEL_LOW, true, &wiper_isr);
    irq_set_priority(IO_IRQ_BANK0, 255); 
    irq_set_enabled(IO_IRQ_BANK0, true); 

    // check light every 2 seconds to change LED strip brightness
    struct repeating_timer check_light_sensor;
    add_repeating_timer_ms(2000, light_adjust_callback, NULL, &check_light_sensor);

    // check if time has been updated while mirror is on every 30 seconds
    // struct repeating_timer check_time;
    // add_repeating_timer_ms(10000, check_time_api_callback, NULL, &check_time);
    

    lcd_clear();
    mirrorActivation = read_ultra_sonic();
    while (1)
    {
        mirrorActivation = read_ultra_sonic();
        while (mirrorActivation)
        {
            sleep_ms(500);
            lcd_clear();
            writeWeather(api_call_result -> weather);
            writeTime(api_call_result -> timeNow);
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
