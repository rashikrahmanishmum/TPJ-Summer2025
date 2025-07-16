//i2c-lcd.c
#include "i2c-lcd.h"
#include "freertos/task.h"
#include <string.h>

#define LCD_BACKLIGHT 0x08
#define ENABLE 0x04

static void lcd_write_nibble(uint8_t nibble, uint8_t mode);
static void lcd_write_cmd(uint8_t cmd);
static void lcd_write_data(uint8_t data);

void i2c_master_init(void) {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ
    };
    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}

void lcd_send(uint8_t val, uint8_t mode) {
    uint8_t high = val & 0xF0;
    uint8_t low = (val << 4) & 0xF0;
    lcd_write_nibble(high, mode);
    lcd_write_nibble(low, mode);
}

static void lcd_write_nibble(uint8_t nibble, uint8_t mode) {
    uint8_t data = nibble | LCD_BACKLIGHT | mode;
    uint8_t data_e = data | ENABLE;

    i2c_master_write_to_device(I2C_MASTER_NUM, LCD_ADDR, &data_e, 1, (10));
    vTaskDelay(pdMS_TO_TICKS(1));
    i2c_master_write_to_device(I2C_MASTER_NUM, LCD_ADDR, &data, 1, pdMS_TO_TICKS(10));
    vTaskDelay(pdMS_TO_TICKS(1));
}

void lcd_write_cmd(uint8_t cmd) {
    lcd_send(cmd, 0x00);
}

void lcd_write_data(uint8_t data) {
    lcd_send(data, 0x01);
}

void lcd_init(void) {
    vTaskDelay(pdMS_TO_TICKS(50));
    lcd_write_nibble(0x30, 0x00);
    vTaskDelay(pdMS_TO_TICKS(5));
    lcd_write_nibble(0x30, 0x00);
    vTaskDelay(pdMS_TO_TICKS(1));
    lcd_write_nibble(0x30, 0x00);
    lcd_write_nibble(0x20, 0x00); // Set 4-bit mode

    lcd_write_cmd(0x28); // 2 line, 5x8 dots
    lcd_write_cmd(0x0C); // Display ON
    lcd_write_cmd(0x06); // Entry mode
    lcd_clear();
}

void lcd_clear(void) {
    lcd_write_cmd(0x01);
    vTaskDelay(pdMS_TO_TICKS(2));
}

void lcd_set_cursor(uint8_t col, uint8_t row) {
    static uint8_t row_offsets[] = { 0x00, 0x40 };
    lcd_write_cmd(0x80 | (col + row_offsets[row]));
}

void lcd_print(const char *str) {
    while (*str) {
        lcd_write_data(*str++);
    }
}
