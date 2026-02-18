#include <arduino.h>
#include "Shield.h"

SpriteData* Shield::sprite_data = nullptr;

Shield::Shield(int x, int y, bool exists, Graphics* graphics) {
    this->x = x;
    this->y = y;
    this->exists = exists;
    this->graphics = graphics;

    restore_shield_sprite();
}

void Shield::restore_shield_sprite() {
    memcpy(sprite, sprite_data->shield, SpriteData::SHIELD_WIDTH * SpriteData::SHIELD_HEIGHT + 2);
}

void Shield::draw() {
    if (exists) {
        graphics->draw_sprite(sprite, x, y);
    }
}
