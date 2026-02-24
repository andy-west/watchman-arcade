#ifndef SHIELD_H
#define SHIELD_H

#include "../Graphics.h"
#include "../assets/SpriteData.h"

class Shield {
public:
    static const uint Y = 165;
    static const uint MARGIN_SIDE = 50;

    static SpriteData* sprite_data;

    int x;
    int y;
    byte sprite[SpriteData::SHIELD_WIDTH * SpriteData::SHIELD_HEIGHT + 2];
    bool exists;

    Shield(int x, int y, bool exists, Graphics* graphics);
    void restore_shield_sprite();
    void draw();
    bool check_hit(int missile_x, int missile_y, int missile_width, int missile_height);
    void damage(int hit_x, int hit_y);

private:
    Graphics* graphics;
};

#endif
