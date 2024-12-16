#include "weather_fetch.h"

static char x [10000];

// Global buffer to store incoming data
err_t http_client_receive_print(__unused void *arg, __unused struct altcp_pcb *conn, struct pbuf *p, err_t err) {
    u16_t offset = 0;
    while (offset < p->tot_len) {
        char c  = (char)pbuf_get_at(p, offset++);
        x[offset - 1] = c;
    }
    return ERR_OK;
}

// Function to parse the temperature from the JSON response
double parse_temperature(const char *json_string)
{
    float temperature = 0.0;
    char localtime[100];

    // Extract the temperature using sscanf
    sscanf(strstr(json_string, "\"temperature\":") + 14, "%f", &temperature);
    printf("%d\n", temperature);

    // Extract the localtime using sscanf
    sscanf(strstr(json_string, "\"localtime\":\"") + 13, "%99[^\"]", localtime);

    // Print extracted values
    return temperature;
}

// Weather fetch function with dynamic request
double fetchWeather()
{
    if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return 1;
    }
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms("Kamalsk", "barca123", CYW43_AUTH_WPA2_AES_PSK, 20000)) {
        printf("failed to connect\n");
        return 1;
    }

    // this code works; the other code is commented in case we need async
    EXAMPLE_HTTP_REQUEST_T req = {0};
    req.hostname = HOST;
    req.url = URL_REQUEST;
    req.recv_fn = http_client_receive_print; // Incremental parsing callback

    // Perform the HTTP request (synchronously)
    int result = http_client_request_sync(cyw43_arch_async_context(), &req);


    if (result != 0) {
        panic("test failed");
    }

    // Clean up Wi-Fi resources
    cyw43_arch_deinit(); 
    printf("%s\n", x);
    return parse_temperature(x);

}
