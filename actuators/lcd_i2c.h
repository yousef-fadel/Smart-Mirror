#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

#define LCD_CHARACTER 1
#define LCD_COMMAND 0

#define MAX_LINES 2
#define MAX_CHARS 16

void i2c_write_byte(uint8_t val);

void lcd_init();
void lcd_set_cursor(int line, int position);
void lcd_string(const char *s);
void lcd_clear(void);
#endif