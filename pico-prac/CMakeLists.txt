cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_prac C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(prac
    main.c
    )

pico_enable_stdio_usb(prac 1)
pico_enable_stdio_uart(prac 1)

pico_add_extra_outputs(prac)

target_link_libraries(prac pico_stdlib)

