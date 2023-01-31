# pico-prac
# 概要
Raspberry Pi Pico の公式ドキュメント [Getting started with Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) の Chapter 8 で作成したプログラム。

# 動作環境
```
Ubuntu 20.04.5 LTS
CMake 3.16.3
GNU Make 4.2.1
gcc/g++ 9.4.0
```

# 使用方法
0. Raspberry Pi Pico の公式ドキュメント [Getting started with Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) にしたがって環境を構築してください。
1. 任意の場所にクローンします。
    ```
    git clone https://github.com/yazawakenichi/pico-prac
    ```
2. ビルドします。
    ```
    cd pico-prac
    mkdir build
    cd build
    cmake ..
    make
    ```
3. Raspberry Pi Pico のボード上にある BOOTSEL ボタンを押しながらパソコンと USB 接続します。
4. `build` ディレクトリ内にできた `pico-prac.uf2` ファイルを `RPI-RP2` ストレージにコピーします。
    ```
    cp ./pico-prac.uf2 /media/$USERNAME/RPI-RP2
    ```
5. シリアル通信の出力を見ると Hello, World! が無限に出力されていることがわかると思う。


