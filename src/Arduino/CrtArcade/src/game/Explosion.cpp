#include <arduino.h>
#include "Explosion.h"

Explosion::Explosion(Graphics* graphics, SpriteData* sprite_data) {
    this->graphics = graphics;
    this->sprite_data = sprite_data;

    is_visible = false;
}

void Explosion::update() {
    if (is_visible) {
        countdown--;

        if (countdown <= 0) {
            is_visible = false;
        }
    }
}

void Explosion::draw() {
    if (is_visible) {
        graphics->draw_sprite(sprite_data->explosion_sprite, x, y);
    }
}

void Explosion::show(uint x, uint y) {
    const float EXPLOSION_SECONDS = 0.25;
    const uint EXPLOSION_TIME = EXPLOSION_SECONDS * 60;

    this->x = x;
    this->y = y;
    countdown = EXPLOSION_TIME;
    is_visible = true;
}
