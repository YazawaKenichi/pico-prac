#include "main.h"

//! すべてのボタンの状態を返す関数
uint8_t button_read()
{
    bool sw1, sw2;
    uint8_t button_code;

    sw1 = gpio_get(SW1) ? 0 : 1;
    sw2 = gpio_get(SW2) ? 0 : 1;

    button_code = (SW1 << 1) | (SW2 << 0);
    return button_code;
}

uint8_t button_count(uint32_t const button)
{
    uint8_t res = 0;
    for(uint8_t cnt = sizeof(button) - 1; cnt >= 0; cnt--)
    {
        res += (button & 1 << cnt) ? 1 : 0;
    }
    return res;
}

void set_string(char *string, uint8_t len, uint8_t btn)
{
    uint8_t keycount = 0;

    if(len > button_count(btn))
    {
        if(btn & 0b01)
        {
            *(string + keycount) = HID_KEY_R;
            keycount++;
        }
        if(btn & 0b10)
        {
            *(string + keycount) = HID_KEY_SHIFT_LEFT;
            keycount++;
        }
    }
}

void hid_task(void)
{
    const uint32_t interval_ms = 10;
    static uint32_t start_ms = 0;
    uint32_t const btn = button_read();
    char string[8] = {0};
    uint8_t len = sizeof(string) / sizeof(char);

    if(board_millis() - start_ms < interval_ms)
    {
        return ;
    }

    start_ms += interval_ms;

    set_string(string, len, btn);

    if(btn)
    {
        if(tud_suspended())
        {
            tud_remote_wakeup();
        }
        else
        {
            send_hid_report(string, btn);
        }
    }
}

void init(void)
{
    board_init();
    tusb_init();
    gpio_init(SW1);
    gpio_init(SW2);
    gpio_set_dir(SW1, GPIO_IN);
    gpio_set_dir(SW2, GPIO_IN);
}

/*---------- MAIN ----------*/
int main(void)
{
    init();

    while(1)
    {
        tud_task();
        led_blinking_task();

        hid_task();
        sleep_ms(1);
    }

    return 0;
}

