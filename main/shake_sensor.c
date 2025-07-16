#include "shake_sensor.h"
#include "driver/gpio.h"
#include <stdbool.h>

#define SHAKE_PIN 38  // Update if needed

void shake_sensor_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << SHAKE_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

bool is_shaken(void) {
    return gpio_get_level(SHAKE_PIN) == 0;  // LOW = shaken
}
