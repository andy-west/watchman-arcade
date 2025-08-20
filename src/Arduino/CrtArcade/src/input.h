#ifndef INPUT_H
#define INPUT_H

extern bool left_pressed;
extern bool right_pressed;
extern bool fire_pressed;

extern bool prev_left_pressed;
extern bool prev_right_pressed;
extern bool prev_fire_pressed;

extern bool left_pressed_this_frame;
extern bool right_pressed_this_frame;
extern bool fire_pressed_this_frame;

extern void setup_input();
extern void update_input();

#endif
