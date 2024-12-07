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
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
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

# Add executable. Default name is the project name, version 0.1

add_executable(Smart_Mirror 
    Smart_Mirror.c 
    actuators/lcd_i2c.c 
    actuators/lcd_i2c.h 
    actuators/wiper.c 
    actuators/wiper.h 
    actuators/led.h 
    actuators/led.c 
    sensors/light_sensor.c 
    sensors/light_sensor.h 
    sensors/ir_sensor.h 
    sensors/ir_sensor.c 
    sensors/ultra_sonic_sensor.c 
    sensors/ultra_sonic_sensor.h
)

pico_set_program_name(Smart_Mirror "Smart_Mirror")
pico_set_program_version(Smart_Mirror "0.1")

# Generate PIO header
pico_generate_pio_header(Smart_Mirror ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Smart_Mirror 0)
pico_enable_stdio_usb(Smart_Mirror 1)

# Add the standard library to the build
target_link_libraries(Smart_Mirror
        pico_stdlib )

# Add the standard include files to the build
target_include_directories(Smart_Mirror PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

FILE(GLOB FreeRTOS_src FreeRTOS-Kernel/*.c)
add_library( FreeRTOS STATIC
	${FreeRTOS_src}
	FreeRTOS-Kernel/portable/GCC/ARM_CM0/port.c
	FreeRTOS-Kernel/portable/MemMang/heap_4.c
)
target_include_directories( FreeRTOS PUBLIC
		FreeRTOS-Kernel/include
		include/
		FreeRTOS-Kernel/portable/GCC/ARM_CM0
        sensors/
	)
    
# Add any user requested libraries
target_link_libraries(Smart_Mirror 
        hardware_i2c
        hardware_pwm  
        hardware_adc
        FreeRTOS
        pico_cyw43_arch_none
        )

pico_add_extra_outputs(Smart_Mirror)

