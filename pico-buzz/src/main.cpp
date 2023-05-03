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

//! GPIO
#include "pico/stdlib.h"
//! PWM
#include "hardware/pwm.h"
//! ADC
#include "hardware/adc.h"
//! UART
#include <stdio.h>
//! sleep_ms
#include <unistd.h>
//! MeloDict
#include "melodict.hpp"

//! PWM MACROS
#define FREQ_CTRL 1
#define PWM_OUT_PIN 16
//! system main clock システムメインクロック : 125 MHz
#define SYSCLOCK 125000000
//! PWM Optical Resolution 分解能
#define WRAP 10000

//! 周波数の最小値
#define FREQ_MIN 2
//! 周波数の最大値
#define FREQ_MAX 12000

//! ローパスフィルタ
#define LPF_GAMMA 0.99

//! 分解能変換マクロ
#if FREQ_CTRL
#define RESC(X) rescale(X, 4096, 0, FREQ_MAX, FREQ_MIN)
#else
#define RESC(X) rescale(X, 4096, 0, 1000, 0)
#endif

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

/**
 * @fn
 * @brief 単位の違う２つのデータ量を対応させる
 * 例えば
 * 0 ~ 4095 を返すアナログセンサが 100 を返した時、
 * 3 ~ 5 V の電圧ではいくらなのかは以下で計算できる
 * vref = rescale(100, 4095, 0, 5, 3);
 * 
 * @param in 
 * @param in_max 
 * @param in_min 
 * @param out_max 
 * @param out_min 
 * @return float 
 */
float rescale(int16_t in, int16_t in_max, int16_t in_min, int16_t out_max, int16_t out_min)
{
    float out;
    out = out_min + (out_max - out_min) * (in - in_min) / (float) (in_max - in_min);
    return out;
}

float low_pass_filter(float val, float pre_val, float gamma)
{
    return (float) val * (1 - gamma) + pre_val * gamma;
}

int main()
{
    //! stdio を初期化する
    stdio_init_all();

    //! ADC を初期化する
    adc_init();

    //! PWM_OUT_PIN を PWM として設定する
    gpio_set_function(PWM_OUT_PIN, GPIO_FUNC_PWM);

    //! ADC 0 を ADC_IN_PIN につなげる
    adc_select_input(0);

    //! どの PWM スライス（論理番号）が GPIO PWM_OUT_PIN に接続されているかを返す
    uint slice_num = pwm_gpio_to_slice_num(PWM_OUT_PIN);

    //! PWM 分解能を設定する
    pwm_set_wrap(slice_num, WRAP);

    //! PWM 分周比を設定する
#if FREQ_CTRL
    float freq = RESC(adc_read());
    float duty = 50;
#else
    float freq = 440;
    float duty = RESC(adc_read());
    melo2freq("hoge");
    pwm_set_clkdiv(slice_num, (float) freq2clkdiv(freq));
#endif


    //! デューティ比の設定
    pwm_set_chan_level(slice_num, PWM_CHAN_A, duty * 100);

    //! PWM を出力する
    pwm_set_enabled(slice_num, true);

    while(true)
    {
        uint16_t adc_val;
        adc_val = adc_read();
#if FREQ_CTRL
        pwm_set_clkdiv(slice_num, (float) freq2clkdiv(freq));
#else
        //! デューティ比の設定
        pwm_set_chan_level(slice_num, PWM_CHAN_A, duty * 100);
#endif

        sleep_ms(1);
#if FREQ_CTRL
        freq = low_pass_filter(RESC(adc_val), freq, LPF_GAMMA);
#else
        duty = low_pass_filter(RESC(adc_val), freq, LPF_GAMMA);
#endif
        printf("ADC : %4d, RESC : %4f\r\n", adc_val, low_pass_filter(RESC(adc_val), freq, LPF_GAMMA));
    }
}
