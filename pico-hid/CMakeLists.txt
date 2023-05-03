# Cmake Version
cmake_minimum_required(VERSION 3.13)

# pico_sdk_import.cmake
include(pico_sdk_import.cmake)

# Project Name
project(pico_hid C CXX ASM)

# Settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(hid)

target_sources(hid PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/main.c
    ${CMAKE_CURRENT_LIST_DIR}/dev_hid_composite.c
    ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
    )

target_include_directories(hid PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )

pico_add_extra_outputs(hid)

target_link_libraries(hid PUBLIC pico_stdlib tinyusb_device tinyusb_board)
