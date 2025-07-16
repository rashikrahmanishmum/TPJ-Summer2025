#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "joystick.h"
#include "ultrasonic.h"
#include "touch_sensor.h"
#include "shake_sensor.h"
#include "vibration_motor.h"
#include "i2c-lcd.h"
#include "dfplayer.h"

void app_main(void) {
    // === Initialize all modules ===
    joystick_init();
    ultrasonic_init();
    touch_sensor_init();
    shake_sensor_init();
    vibration_motor_init();
    i2c_master_init();
    lcd_init();
    dfplayer_init();

    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Component Test");

    while (1) {
        // === Joystick Direction Test ===
        joystick_direction_t dir = joystick_get_direction();
        lcd_set_cursor(0, 0);
        switch (dir) {
            case JOY_UP:    lcd_print("Direction: UP     "); break;
            case JOY_DOWN:  lcd_print("Direction: DOWN   "); break;
            case JOY_LEFT:  lcd_print("Direction: LEFT   "); break;
            case JOY_RIGHT: lcd_print("Direction: RIGHT  "); break;
            default:        lcd_print("Direction: NEUTRAL"); break;
        }

        // === Joystick Button Test (Beep) ===
        if (joystick_button_pressed()) {
            dfplayer_beep();
        }

        // === Touch Sensor Test (Beep) ===
        if (touch_sensor_is_touched()) {
            dfplayer_beep();
        }

        // === Shake Sensor Test (Vibrate) ===
        if (shake_sensor_is_shaken()) {
            vibration_motor_on();
            vTaskDelay(pdMS_TO_TICKS(500));
            vibration_motor_off();
        }

        // === Ultrasonic Distance Test ===
        float distance = ultrasonic_get_distance_cm();
        char dist_buf[16];
        snprintf(dist_buf, sizeof(dist_buf), "Dist: %.1f cm", distance);
        lcd_set_cursor(0, 1);
        lcd_print(dist_buf);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
