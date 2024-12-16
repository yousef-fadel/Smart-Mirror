
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "pico/cyw43_arch.h"
#include "pico/async_context.h"
#include "lwip/altcp_tls.h"
#include "example_http_client_util.h"

#define HOST "api.weatherstack.com"
#define URL_REQUEST "/current?access_key=def8265aad3bd5e9c3088bb121c9f0c5&query=Cairo"

int fetchWeather();
