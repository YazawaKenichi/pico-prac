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

target_link_libraries(buzzer hardware_pwm pico_stdlib)
