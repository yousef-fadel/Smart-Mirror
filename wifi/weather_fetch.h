
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "pico/cyw43_arch.h"
#include "pico/async_context.h"
#include "lwip/altcp_tls.h"
#include "example_http_client_util.h"

struct weather_fetch
{
    char *timeNow;
    float weather;
};


#define HOST "api.weatherstack.com"
#define URL_REQUEST ""

struct weather_fetch* fetchWeatherAndTime();
