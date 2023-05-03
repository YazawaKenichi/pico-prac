/**
 * @file main.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-02-02
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#include "hardware/gpio.h"
//! sleep_ms
#include <stdlib.h>

#define LED1 0
#define LED2 1
#define SW1 3
#define SW2 6

int main()
{
    //! GPIO の初期化
    gpio_init(LED1);
    gpio_init(LED2);
    //! 使用する全ピンをいちいち記述する必要がある
    gpio_init(SW1);
    gpio_init(SW2);
    //! GPIO が IN か OUT か決める
    gpio_set_dir(LED1, GPIO_OUT);
    gpio_set_dir(LED2, GPIO_OUT);
    //! プルアップかプルダウンは回路で調整する ( 内部プルアップはありません )
    gpio_set_dir(SW1, GPIO_IN);
    gpio_set_dir(SW2, GPIO_IN);

    while(true)
    {
        //! GPIO の出力
        gpio_put(LED1, gpio_get(SW1));
        gpio_put(LED2, gpio_get(SW2));
        sleep_ms(1);
    }
}
