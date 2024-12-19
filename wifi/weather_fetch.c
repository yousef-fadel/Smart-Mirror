#include "weather_fetch.h"
static char weatherFetch [700];
static char timeFetch [700];

// Global buffer to store incoming data
err_t write_to_weather_buffer(__unused void *arg, __unused struct altcp_pcb *conn, struct pbuf *p, err_t err) {
    u16_t offset = 0;
    while (offset < p->tot_len) {
        char c  = (char)pbuf_get_at(p, offset);
        weatherFetch[offset] = c;
        timeFetch[offset] = c;
        offset++;
    }
    return ERR_OK;
}

// Function to parse the temperature from the JSON response
float parse_temperature(const char *json_string)
{
    float temperature = 0.0;
    sscanf(strstr(json_string, "\"temperature\":") + 14, "%f", &temperature);
    return temperature;
}

char* parse_time(const char* json_string)
{
    const char *key = "\"localtime\":\"";  
    static char localtime[20];  

    char *start_pos = strstr(json_string, key);
    start_pos += strlen(key);
    sscanf(start_pos, "%19[^\"]", localtime);  

    return localtime;
}
struct weather_fetch* fetchWeatherAndTime()
{
    if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return NULL;
    }
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms("Kamalsk", "barca123", CYW43_AUTH_WPA2_AES_PSK, 20000)) {
        printf("failed to connect\n");
        return NULL; 
    }

    // this code works; the other code is commented in case we need async
    EXAMPLE_HTTP_REQUEST_T req = {0};
    req.hostname = HOST;
    req.url = URL_REQUEST;
    req.recv_fn = write_to_weather_buffer; // Incremental parsing callback

    // Perform the HTTP request (synchronously)
    int result = http_client_request_sync(cyw43_arch_async_context(), &req);


    if (result != 0) {
        panic("test failed");
        return NULL;
    }

    // Clean up Wi-Fi resources
    cyw43_arch_deinit(); 
    static struct weather_fetch weatherResult;
    weatherResult.weather = parse_temperature(weatherFetch);
    weatherResult.timeNow = parse_time(timeFetch);
    return &weatherResult;
}