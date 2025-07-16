// rgb_led.h
#pragma once

#include <stdint.h>

void rgb_led_init(void);
void rgb_led_set_color(uint8_t r, uint8_t g, uint8_t b);
void rgb_led_off(void);
