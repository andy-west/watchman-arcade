#ifndef ALIEN_H
#define ALIEN_H

#include "../Graphics.h"
#include "../assets/SpriteData.h"
#include "Direction.h"
#include "Shield.h"
#include "Game.h"

class Alien {
public:
    static constexpr float ANIMATION_SECONDS = 0.5;
    static const uint ANIMATION_TIME = ANIMATION_SECONDS * 60;

    static const int MARGIN_TOP = 50;
    static const int MARGIN_SIDE = 20;
    static const int SPACING = 16;

    static uint animation_frame;
    static uint animation_countdown;
    static Direction direction;
    static SpriteData* sprite_data;

    int x;
    int y;
    int sprite_index;
    bool exists;
    uint points;

    Alien(int x, int y, int sprite_index, bool exists, uint points, Graphics* graphics, Game* game);
    void move(Direction &new_direction);
    void move_down(Shield* shields[]);
    void draw();

private:
    static const uint MOVE_SPEED = 2;
    static const uint MOVE_DOWN_SPEED = 10;
    static const uint MAX_Y = 182;

    Graphics* graphics;
    Game* game;
};

#endif
