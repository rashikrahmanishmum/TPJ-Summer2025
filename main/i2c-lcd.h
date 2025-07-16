//i2c-lcd.h
#pragma once

#include "driver/i2c.h"

#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_SDA_IO 8
#define I2C_MASTER_SCL_IO 9
#define I2C_MASTER_FREQ_HZ 100000

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

void i2c_master_init(void);
void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_print(const char *str);
