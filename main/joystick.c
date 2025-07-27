#include "joystick.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"

#define JOY_X_CHANNEL  ADC_CHANNEL_0  // GPIO11
#define JOY_Y_CHANNEL  ADC_CHANNEL_1  // GPIO12
#define JOY_BTN_PIN    13             // Digital input

#define LEFT_THRESH    2000
#define RIGHT_THRESH   7500
#define UP_THRESH      2000
#define DOWN_THRESH    7500

static adc_oneshot_unit_handle_t adc_handle;

void joystick_init(void) {
    // === ADC Setup ===
    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE
    };
    adc_oneshot_new_unit(&unit_cfg, &adc_handle);

    adc_oneshot_chan_cfg_t chan_cfg = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_11
    };
    adc_oneshot_config_channel(adc_handle, JOY_X_CHANNEL, &chan_cfg);
    adc_oneshot_config_channel(adc_handle, JOY_Y_CHANNEL, &chan_cfg);

    // === Joystick Button Setup ===
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
    int x = 0, y = 0;
    adc_oneshot_read(adc_handle, JOY_X_CHANNEL, &x);
    adc_oneshot_read(adc_handle, JOY_Y_CHANNEL, &y);

    if (x < LEFT_THRESH) return JOY_LEFT;
    if (x > RIGHT_THRESH) return JOY_RIGHT;
    if (y < UP_THRESH) return JOY_UP;
    if (y > DOWN_THRESH) return JOY_DOWN;
    return JOY_NEUTRAL;
}

bool joystick_button_pressed(void) {
    return gpio_get_level(JOY_BTN_PIN) == 0;
}
