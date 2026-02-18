#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "../Graphics.h"
#include "../assets/SpriteData.h"

class Game;

class Explosion {
public:
    Explosion(Graphics* graphics, SpriteData* sprite_data);

    bool is_visible;

    void update();
    void draw();
    void show(uint x, uint y);

private:
    Graphics* graphics;
    SpriteData* sprite_data;

    uint x;
    uint y;
    uint countdown;
};

#endif
