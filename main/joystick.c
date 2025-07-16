//joystick.c
#include "joystick.h"
#include "driver/gpio.h"
#include "driver/adc.h"

#define JOY_X_PIN      ADC1_CHANNEL_4  // GPIO32, update as needed
#define JOY_Y_PIN      ADC1_CHANNEL_5  // GPIO33
#define JOY_BTN_PIN    13              // Digital GPIO

#define LEFT_THRESH    2000
#define RIGHT_THRESH   3500
#define UP_THRESH      2000
#define DOWN_THRESH    3500

void joystick_init(void) {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(JOY_X_PIN, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(JOY_Y_PIN, ADC_ATTEN_DB_11);
    
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << JOY_BTN_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

joystick_direction_t joystick_get_direction(void) {
    int x = adc1_get_raw(JOY_X_PIN);
    int y = adc1_get_raw(JOY_Y_PIN);

    if (x < LEFT_THRESH) return JOY_LEFT;
    if (x > RIGHT_THRESH) return JOY_RIGHT;
    if (y < UP_THRESH) return JOY_UP;
    if (y > DOWN_THRESH) return JOY_DOWN;
    return JOY_NEUTRAL;
}

bool joystick_button_pressed(void) {
    return gpio_get_level(JOY_BTN_PIN) == 0; 
}
