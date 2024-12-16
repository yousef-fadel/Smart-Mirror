#include "weather_fetch.h"
#include "jsmn.h"

static char x[10000] ;

err_t http_client_receive_print(__unused void *arg, __unused struct altcp_pcb *conn, struct pbuf *p, err_t err) {
    u16_t offset = 0;
    while (offset < p->tot_len) {
        char c  = (char)pbuf_get_at(p, offset++);
        x[offset - 1] = c;
    }
    return ERR_OK;
}


int fetchWeather()
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
    req.recv_fn = http_client_receive_print;
    int result = http_client_request_sync(cyw43_arch_async_context(), &req);



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