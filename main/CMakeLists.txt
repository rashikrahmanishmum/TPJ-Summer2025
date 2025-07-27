set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

idf_component_register(
    SRCS
        "main.c"
        "i2c-lcd.c"
        "joystick.c"
        "touch_sensor.c"
        "shake_sensor.c"
        "ultrasonic.c"
        "vibration_motor.c"
        "dfplayer.c"
        "rgb_led.c"
    INCLUDE_DIRS "."
)
