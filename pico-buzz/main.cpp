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

#include <string>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define FREQ_CTRL 1
#define PWM_OUT_PIN 16
//! system main clock システムメインクロック : 125 MHz
#define SYSCLOCK 125000000
//! PWM Optical Resolution 分解能
#define WRAP 10000

//! 周波数の最小値
#define FREQ_MIN 80
//! 周波数の最大値
#define FREQ_MAX 1600
//! 周波数のステップ量
#define FREQ_STEP 20

using namespace std;

/**
 * @brief メインクロックと PWM 分解能から、周波数を与えると分周比を計算する関数
 * 
 * @param freq_Hz 
 * @return uint8_t 
 */
float freq2clkdiv(float freq_Hz)
{
    return (float) (SYSCLOCK / ((WRAP + 1) * (float) freq_Hz));
}

void musicscale2freq(string musicscale)
{
    sleep_ms(1000);
}

int main()
{
    //! PWM_OUT_PIN を PWM として設定する
    gpio_set_function(PWM_OUT_PIN, GPIO_FUNC_PWM);

    //! どの PWM スライス（論理番号）が GPIO PWM_OUT_PIN に接続されているかを返す
    uint slice_num = pwm_gpio_to_slice_num(PWM_OUT_PIN);

    //! PWM 分解能を設定する
    pwm_set_wrap(slice_num, WRAP);

    //! PWM 分周比を設定する
#if FREQ_CTRL
    float freq = FREQ_MIN;
    float duty = 50;
#else
    float freq = 440;
    float duty = 0;
    pwm_set_clkdiv(slice_num, (float) freq2clkdiv(freq));
#endif


    //! デューティ比の設定
    pwm_set_chan_level(slice_num, PWM_CHAN_A, duty * 100);

    //! PWM を出力する
    pwm_set_enabled(slice_num, true);

    while(true)
    {
#if FREQ_CTRL
        pwm_set_clkdiv(slice_num, (float) freq2clkdiv(freq));
#endif

        //! デューティ比の設定
        pwm_set_chan_level(slice_num, PWM_CHAN_A, duty * 100);

        sleep_ms(1000);
#if FREQ_CTRL
        freq += FREQ_STEP;
        if(freq >= FREQ_MAX)
            freq = FREQ_MIN;
#else
        duty += 1;
        if(duty >= WRAP)
            duty = 0;
#endif
    }
}
