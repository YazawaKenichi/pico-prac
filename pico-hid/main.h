#ifndef __MAIN_H__
#define __MAIN_H__

#include "dev_hid_composite.h"
#include "hardware/gpio.h"
#include <stdlib.h>
#include "pico/stdio.h"
#include <stdint.h>

#define SW1 3
#define SW2 6

uint8_t button_read();
uint8_t button_count(uint32_t const button);
void set_string(char *, uint8_t, uint8_t btn);
void hid_task(void);
void init(void);
int main();

#endif
