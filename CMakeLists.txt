# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Smart_Mirror C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

pico_add_library(example_lwip_http_util NOFLAG)
target_sources(example_lwip_http_util INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/wifi/example_http_client_util.c
        )
pico_mirrored_target_link_libraries(example_lwip_http_util INTERFACE
        pico_lwip_http
        pico_lwip_mbedtls
        pico_mbedtls
        )
target_include_directories(example_lwip_http_util INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
        )

# Add executable. Default name is the project name, version 0.1
add_executable(Smart_Mirror 
    Smart_Mirror.h 
    Smart_Mirror.c 
    actuators/lcd_i2c.h 
    actuators/lcd_i2c.c 
    actuators/wiper.h 
    actuators/wiper.c 
    actuators/led.h 
    actuators/led.c 
    sensors/light_sensor.h 
    sensors/light_sensor.c 
    sensors/ir_sensor.h 
    sensors/ir_sensor.c 
    sensors/ultra_sonic_sensor.h
    sensors/ultra_sonic_sensor.c 
    wifi/weather_fetch.h
    wifi/weather_fetch.c
)

pico_set_program_name(Smart_Mirror "Smart_Mirror")
pico_set_program_version(Smart_Mirror "0.1")

# Generate PIO header
pico_generate_pio_header(Smart_Mirror ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Smart_Mirror 0)
pico_enable_stdio_usb(Smart_Mirror 1)

# Add the standard library to the build
target_link_libraries(Smart_Mirror pico_stdlib )

# Add the standard include files to the build
target_include_directories(Smart_Mirror PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/wifi
)
add_definitions(-DMBEDTLS_USER_CONFIG_FILE="mbedtls-config-changes.h") 

# Add any user requested libraries
target_link_libraries(Smart_Mirror 
        hardware_i2c
        hardware_pwm  
        hardware_adc
        pico_cyw43_arch_lwip_threadsafe_background
        example_lwip_http_util
        )

target_compile_definitions(Smart_Mirror PRIVATE
        WIFI_SSID=\"${WIFI_SSID}\"
        WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
        # By default verification is optional (MBEDTLS_SSL_VERIFY_OPTIONAL)
        # Make it required for this test
        ALTCP_MBEDTLS_AUTHMODE=MBEDTLS_SSL_VERIFY_REQUIRED
        )
pico_add_extra_outputs(Smart_Mirror)

