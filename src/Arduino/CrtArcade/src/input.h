#ifndef INPUT_H
#define INPUT_H

class Input {
public:
    bool left_pressed = false;
    bool right_pressed = false;
    bool fire_pressed = false;

    bool prev_left_pressed = false;
    bool prev_right_pressed = false;
    bool prev_fire_pressed = false;

    bool left_pressed_this_frame = false;
    bool right_pressed_this_frame = false;
    bool fire_pressed_this_frame = false;

    Input();
    void update();

private:
    const uint LEFT_PIN = 13;
    const uint RIGHT_PIN = 14;
    const uint FIRE_PIN = 15;
};

#endif
