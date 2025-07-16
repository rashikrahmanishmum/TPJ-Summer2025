#include "ultrasonic.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TRIG_PIN 6
#define ECHO_PIN 7
#define TIMEOUT_US 30000  // 30 ms max wait to avoid infinite loop

void ultrasonic_init(void) {
    gpio_config_t trig_conf = {
        .pin_bit_mask = (1ULL << TRIG_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config_t echo_conf = {
        .pin_bit_mask = (1ULL << ECHO_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&trig_conf);
    gpio_config(&echo_conf);

    gpio_set_level(TRIG_PIN, 0);  // Ensure trigger is LOW initially
    vTaskDelay(pdMS_TO_TICKS(50)); // Let the sensor settle
}

float ultrasonic_get_distance_cm(void) {
    uint64_t start_time = 0, end_time = 0;

    // Send 10us trigger pulse
    gpio_set_level(TRIG_PIN, 0);
    ets_delay_us(2);
    gpio_set_level(TRIG_PIN, 1);
    ets_delay_us(10);
    gpio_set_level(TRIG_PIN, 0);

    // Wait for ECHO HIGH with timeout
    int timeout = TIMEOUT_US;
    while (gpio_get_level(ECHO_PIN) == 0 && timeout-- > 0) {
        start_time = esp_timer_get_time();
    }
    if (timeout <= 0) return -1.0;  // Timeout error

    // Wait for ECHO LOW with timeout
    timeout = TIMEOUT_US;
    while (gpio_get_level(ECHO_PIN) == 1 && timeout-- > 0) {
        end_time = esp_timer_get_time();
    }
    if (timeout <= 0) return -1.0;  // Timeout error

    uint64_t pulse_duration = end_time - start_time; // in microseconds
    float distance_cm = (pulse_duration * 0.0343f) / 2.0f; // Sound speed in air

    return distance_cm;
}
