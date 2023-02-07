# CMake の最低要求バージョン
cmake_minimum_required(VERSION 3.13)

# cmake ファイルを参照する
include(pico_sdk_import.cmake)

# プロジェクトの名前を決める
project(pico-buzz C CXX ASM)

# C 11 を使うことを伝える
set(CMAKE_C_STANDARD 11)
# C++ 17 を使うことを伝える
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# include で指定したファイルのあるディレクトリを示す
include_directories(./lib)

# 吐き出す実行ファイルと使うソースコードを指定する
add_executable(buzzer
    src/main.cpp
    lib/melodict.cpp
    )

pico_add_extra_outputs(buzzer)

# 標準出力をするのに必要
pico_enable_stdio_usb(buzzer 1)
pico_enable_stdio_uart(buzzer 0)

# 使うライブラリの指定（ add_executable の後に記述する ）
target_link_libraries(buzzer hardware_pwm hardware_adc pico_stdlib)

