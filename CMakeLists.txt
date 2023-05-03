cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico-prac C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# サブディレクトリを示す （ サブディレクトリには CMakeLists.txt が必要 ）
add_subdirectory(pico-prac)
add_subdirectory(pico-gpio)
add_subdirectory(pico-buzz)
add_subdirectory(pico-hid)

