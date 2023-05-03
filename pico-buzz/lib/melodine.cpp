#include "melodine.hpp"

using namespace std;

class Buzzer
{
public:
    Buzzer(pin, wrap = 10000, sysclock = 125000000)
    {
        _sysclock = sysclock;
        _wrap = wrap;
        _pin = pin;
    }

    float freq2clkdiv(float freq_Hz)
    {
        return (float) (_sysclock / ((_wrap + 1) * (float) freq_Hz));
    }

    //! 音を鳴らす
    void beep(float freq, float time)
    {
        time = time / 2;
        //! 周波数を設定する
        pwm_set_clkdiv(slice_num, freq);
        //! 出力開始
        pwm_set_enabled(slice_num, true);
        sleep(time);
        //! 出力停止
        pwm_set_enabled(slice_num, false);
        sleep(time);
    }

private:
    //! システムクロック
    unsigned int _sysclock;
    unsigned int _wrap;
    unsigned short int _pin;
};

class MeloDine
{
public:
    //! コンストラクタ
    MeloDine(unsigned short int pin, unsigned int wrap = 10000, unsigned int sysclock = 125000000)
    {
        buzzer(pin, wrap, sysclock);
        for(uint16_t index = 0; index < ARRAY_LENGTH; index++)
        {
            height_array[index] = "";
        }
        for(uint16_t index = 0; index < ARRAY_LENGTH; index++)
        {
            length_array[index] = "";
        }
        end_of_melodine = 0;
    }

    //! 登録した楽譜をブザーで再生する
    bool play()
    {
        uint16_t height_size, length_size;

        for(uint16_t index = 0; index < ARRAY_LENGTH; height_index++)
        {
            uint16_t time;
            string height, length;
            float freq;

            //! 楽譜から音符を文字列として取り出す
            height = height_array[height_index];
            length = length_array[length_index];
            //! 文字列を適切な値に変換する
            freq = melo2freq(height);
            time = melo2sign(length);
            //! 音を鳴らす
            beep(freq, time);
            sleep(time)
        }
        return false;
    }

    //! 音符を楽譜に登録する
    bool add_melody(string height, string length)
    {
        //! 配列の要素外を指定しそうになったら関数を強制終了
        if(end_of_melodine >= ARRAY_LENGTH)
        {
            return true;
        }
        height_array[end_of_melodine] = height;
        length_array[end_of_melodine] = length;
        end_of_melodine++;
        return false;
    }

private:
    string height_array[ARRAY_LENGTH];
    string length_array[ARRAY_LENGTH];
    uint16_t end_of_melodine;
    Buzzer buzzer;
};

