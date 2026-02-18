#include <arduino.h>
#include "Input.h"

Input::Input() {
    pinMode(LEFT_PIN, INPUT_PULLUP);
    pinMode(RIGHT_PIN, INPUT_PULLUP);
    pinMode(FIRE_PIN, INPUT_PULLUP);
}

void Input::update() {
    prev_left_pressed = left_pressed;
    left_pressed = !digitalRead(LEFT_PIN);
    left_pressed_this_frame = left_pressed && !prev_left_pressed;

    prev_right_pressed = right_pressed;
    right_pressed = !digitalRead(RIGHT_PIN);
    right_pressed_this_frame = right_pressed && !prev_right_pressed;

    prev_fire_pressed = fire_pressed;
    fire_pressed = !digitalRead(FIRE_PIN);
    fire_pressed_this_frame = fire_pressed && !prev_fire_pressed;
}
