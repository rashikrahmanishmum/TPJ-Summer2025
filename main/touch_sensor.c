#include "touch_sensor.h"
#include "driver/gpio.h"

#define TOUCH_PIN 4

void touch_sensor_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << TOUCH_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

bool is_touch_detected(void) {
    return gpio_get_level(TOUCH_PIN);  // HIGH when touched
}
