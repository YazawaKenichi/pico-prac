/**
 * @file lcd.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-02-21
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#include "lcd.h"

void lcd_toggle_enable(uint8_t val)
{
    //! LCD ディスプレイの Enable ピンをトグルする
#define DELAY_US 600
    sleep_us(DELAY_US);
    i2c_write_byte(val | LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
    i2c_write_byte(val & ~LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
}

void lcd_send_byte(uint8_t val, int mode)
{
    uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    i2c_write_byte(high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

void lcd_clear(void)
{
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_COMMAND);
}

void lcd_set_cursor(int line, int position)
{
    int val = (line == 0) ? 0x80 + position : 0xC0 + position;
    lcd_send_byte(val, LCD_COMMAND);
}

static void inline lcd_char(char val)
{
    lcd_send_byte(val, LCD_CHARACTER);
}

void lcd_string(const char *s)
{
    while(*s)
    {
        lcd_char(*s++);
    }
}

void lcd_init()
{
    lcd_send_byte(0b0011100, LCD_COMMAND);
    lcd_send_byte(, LCD_COMMAND);
    lcd_send_byte(, LCD_COMMAND);
    lcd_send_byte(, LCD_COMMAND);

    lcd_send_byte(LCD_ENTRYMODEST | LCD_ENTRYLEFT, LCD_COMMAND);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
    lcd_clear();
}

