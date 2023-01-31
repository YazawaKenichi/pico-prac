#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

//! オンボード LED は Pico の GP25 に接続されています。Pico W 用に構築している場合、LED は CYW43_WL_GPIO_LED_PIN に接続されています。 詳細については、Pico Examples GitHub リポジトリの Pico W 点滅の例を参照してください。
const uint LED_PIN = 25;

int main()
{
    //! これらの行と文字列は、picotool を使用して表示されるバイナリに変換されます。付録 B を参照してください。
    bi_decl(bi_program_description("This is a test binary."));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while(1)
    {
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        gpio_put(LED_PIN, 1);
        puts("Hello, World!\r\n");
        sleep_ms;
    }
}

