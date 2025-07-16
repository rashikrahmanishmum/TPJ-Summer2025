//joystick.h
#include <stdbool.h>
#ifndef JOYSTICK_H
#define JOYSTICK_H

typedef enum {
    JOY_NEUTRAL,
    JOY_UP,
    JOY_DOWN,
    JOY_LEFT,
    JOY_RIGHT
} joystick_direction_t;

void joystick_init(void);
joystick_direction_t joystick_get_direction(void);
bool joystick_button_pressed(void);

#endif
