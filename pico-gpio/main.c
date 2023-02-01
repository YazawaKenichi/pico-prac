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

#define LED_GPIO 15
#define SWITCH_GPIO 16

int main()
{
    //! GPIO の初期化
    gpio_init(LED_GPIO);
    //! 使用する全ピンをいちいち記述する必要がある
    gpio_init(SWITCH_GPIO);
    //! GPIO が IN か OUT か決める
    gpio_set_dir(LED_GPIO, GPIO_OUT);
    //! プルアップかプルダウンはプログラムで調整する ( 内部プルアップはありません )
    gpio_set_dir(SWITCH_GPIO, GPIO_IN);
    while(true)
    {
        //! GPIO の出力
        gpio_put(LED_GPIO, !gpio_get(SWITCH_GPIO));
        sleep_ms(1);
    }
}
