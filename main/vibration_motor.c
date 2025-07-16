#include "vibration_motor.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define VIBRATION_PIN 16

void vibration_motor_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << VIBRATION_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
    gpio_set_level(VIBRATION_PIN, 0);
}

void trigger_vibration(int duration_ms) {
    gpio_set_level(VIBRATION_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(duration_ms));
    gpio_set_level(VIBRATION_PIN, 0);
}
