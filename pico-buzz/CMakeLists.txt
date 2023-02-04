cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico-buzz C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(buzzer
    main.cpp
    )

pico_add_extra_outputs(buzzer)

# 標準出力に必要
pico_enable_stdio_usb(buzzer 1)
pico_enable_stdio_uart(buzzer 0)

target_link_libraries(buzzer hardware_pwm hardware_adc pico_stdlib)

