#include "weather_fetch.h"

int fetchWeather()
{
    if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return 1;
    }
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms("", "", CYW43_AUTH_WPA2_AES_PSK, 20000)) {
        printf("failed to connect\n");
        return 1;
    }

    // this code works; the other code is commented in case we need async
    EXAMPLE_HTTP_REQUEST_T req1 = {0};
    req1.hostname = HOST;
    req1.url = URL_REQUEST;
    req1.recv_fn = http_client_receive_print_fn;
    int result = http_client_request_sync(cyw43_arch_async_context(), &req1);

    // test async
    // EXAMPLE_HTTP_REQUEST_T req2 = req1;
    // result += http_client_request_async(cyw43_arch_async_context(), &req1);
    // result += http_client_request_async(cyw43_arch_async_context(), &req2);
    // while(!req1.complete && !req2.complete) {
    //     async_context_poll(cyw43_arch_async_context());
    //     async_context_wait_for_work_ms(cyw43_arch_async_context(), 1000);
    // }

    // req1.tls_config = altcp_tls_create_config_client(NULL, 0); // https
    // result += http_client_request_sync(cyw43_arch_async_context(), &req1);
    // result += http_client_request_sync(cyw43_arch_async_context(), &req1); // repeat
    // altcp_tls_free_config(req1.tls_config);

    if (result != 0) {
        panic("test failed");
    }
    cyw43_arch_deinit();
    printf("Test passed\n");
    sleep_ms(100);
    return 0;
}