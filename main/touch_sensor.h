#ifndef TOUCH_VIBRATION_H
#define TOUCH_VIBRATION_H

void touch_vibration_init(void);
bool is_touch_detected(void);
void trigger_vibration(int duration_ms);

#endif
