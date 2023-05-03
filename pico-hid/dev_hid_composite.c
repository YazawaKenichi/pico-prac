/**
 * @file dev_hid_composite.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-02-23
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#include "dev_hid_composite.h"

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

/*---------- Device Callbacks ----------*/
void tud_mount_cb(void)
{
    blink_interval_ms = BLINK_MOUNTED;
}

void tud_umount_cb(void)
{
    blink_interval_ms = BLINK_NOT_MOUNTED;
}

void tud_suspend_cb(bool remote_wakeup_en)
{
    (void) remote_wakeup_en;
    blink_interval_ms = BLINK_SUSPENDED;
}

void tud_resume_cb(void)
{
    blink_interval_ms = BLINK_MOUNTED;
}

/*---------- USB HID ----------*/
static void send_hid_report(uint8_t *keycode, uint32_t btn)
{
    static bool has_keyboard_key = false;

    if(!tud_hid_ready())
    {
        return ;
    }

    if(btn)
    {
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
    }
    else
    {
        if(has_keyboard_key)
        {
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        }
        has_keyboard_key = true;
    }
}

void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint8_t len)
{
    (void) instance;
    (void) len;

    uint8_t next_report_id = report[0] + 1;

    if(next_report_id < REPORT_ID_COUNT)
    {
        //! これ無いほうが都合が良いので一旦消す
        // send_hid_report(report_id, board_button_read());
    }
}

/*
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t buffer, uint16_t reqlen);
{
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint8_t bufsize)
{
    (void) instance;

    if(report_type == HID_REPORT_TYPE_OUTPUT)
    {
        if(report_id == REPORT_ID_KEYBOARD)
        {
            uint8_t const kbd_leds = buffer[0];

            if(bufsiez < 1)
            {
                return ;
            }

            if(kbd_leds & KEYBOARD_LED_CAPSLOCK)
            {
                blink_interval_ms = 0;
                board_led_write(true);
            }
            else
            {
                board_led_write(false);
                blink_interval_ms = BLINK_MOUNTED;
            }
        }
    }
}
*/

void led_blinking_task(void)
{
    static uint32_t start_ms = 0;
    static bool led_state = false;

    if(!blink_interval_ms)
    {
        return ;
    }

    if(board_millis() - start_ms < blink_interval_ms)
    {
        return ;
    }
    start_ms += blink_interval_ms;
    board_led_write(led_state);
    led_state = 1 - led_state;
}







