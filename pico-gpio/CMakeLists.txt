#CMake のヴァージョン設定
cmake_minimum_required(VERSION 3.13)

# pico_sdk_import.cmake を参照する
include(pico_sdk_import.cmake)

# プロジェクト名を決める
# 人まとまりのソースコードに付ける名前
project(pico_gpio C CXX ASM)

# 変数設定？
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# gpio 実行ファイルを main.c から作成する
# コンパイルして出来上がる実行プログラムの名称と、そのソース。
add_executable(gpio
    main.c
    )

# コンパイルしたときのいろいろな実行ファイル名を設定する
pico_add_extra_outputs(gpio)

# gpio.out をコンパイルするときにリンクするライブラリを列挙
# pico_stdlib は標準ライブラリ
target_link_libraries(gpio pico_stdlib)
