/**
 * @file dev_hid_composite.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-02-23
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

enum
{
    BLINK_NOT_MOUNTED = 250,
    BLINK_MOUNTED = 1000,
    BLINK_SUSPENDED = 2500,
};

/* ---------- Device Callbacks ---------- */
void tud_mount_cb(void);
void tud_umout_cb(void);
void tud_suspend_cb(bool);
void tud_resume_cb(void);

/* ---------- USB HID ---------- */
static void send_hid_report(uint8_t *, uint32_t);
void tud_hid_report_complete_cb(uint8_t, uint8_t const*, uint8_t);
// uint16_t tud_hid_get_report_cb(uint8_t, uint8_t, hid_report_type_t, uint8_t, uint16_t);
// void tud_hid_set_report_cb(uint8_t, uint8_t, hid_report_type_t, uint8_t const*, uint8_t);
void led_blinking_task(void);

/**
 *      *** USAGE ***
 * void hid_task(void)
 * {
 *      ...
 *      send_hid_report(REPORT_ID_KEYBOARD, btn);
 *      ...
 * }
 * 
 * int main(void)
 * {
 *      board_init();
 *      tsub_init();
 * 
 *      while(1)
 *      {
 *          tud_task();
 *          led_blinking_task();
 * 
 *          hid_task();
 *          sleep_ms(1);
 *      }
 * 
 *      return 0;
 * }
 * 
 */


