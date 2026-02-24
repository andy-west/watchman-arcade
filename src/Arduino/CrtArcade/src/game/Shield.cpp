#include <arduino.h>
#include <arduino.h>
#include "Shield.h"
#include "GameConstants.h"

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

bool Shield::check_hit(int missile_x, int missile_y, int missile_width, int missile_height) {
    if (!exists) {
        return false;
    }

    if (missile_x + missile_width <= x || missile_x >= x + SpriteData::SHIELD_WIDTH ||
        missile_y + missile_height <= y || missile_y >= y + SpriteData::SHIELD_HEIGHT) {
        return false;
    }

    // Check if missile overlaps any non-transparent pixel in the shield sprite.
    int local_x_start = missile_x - x;
    int local_y_start = missile_y - y;
    int local_x_end = local_x_start + missile_width;
    int local_y_end = local_y_start + missile_height;

    if (local_x_start < 0) local_x_start = 0;
    if (local_y_start < 0) local_y_start = 0;
    if (local_x_end > SpriteData::SHIELD_WIDTH) local_x_end = SpriteData::SHIELD_WIDTH;
    if (local_y_end > SpriteData::SHIELD_HEIGHT) local_y_end = SpriteData::SHIELD_HEIGHT;

    byte* sprite_pixels = &sprite[2];

    for (int ly = local_y_start; ly < local_y_end; ly++) {
        for (int lx = local_x_start; lx < local_x_end; lx++) {
            if (sprite_pixels[ly * SpriteData::SHIELD_WIDTH + lx] != 0) {
                return true;
            }
        }
    }

    return false;
}

void Shield::damage(int hit_x, int hit_y) {
    // Convert hit position to shield-local coordinates and center the damage sprite on it.
    int local_x = hit_x - x - (SpriteData::SHIELD_DAMAGE_WIDTH / 2);
    int local_y = hit_y - y - (SpriteData::SHIELD_DAMAGE_HEIGHT / 2);

    byte* sprite_pixels = &sprite[2];
    byte* damage_pixels = &sprite_data->shield_damage_sprite[2];

    for (int dy = 0; dy < SpriteData::SHIELD_DAMAGE_HEIGHT; dy++) {
        int sy = local_y + dy;

        if (sy < 0 || sy >= SpriteData::SHIELD_HEIGHT) {
            continue;
        }

        for (int dx = 0; dx < SpriteData::SHIELD_DAMAGE_WIDTH; dx++) {
            int sx = local_x + dx;

            if (sx < 0 || sx >= SpriteData::SHIELD_WIDTH) {
                continue;
            }

            // Where the damage sprite is transparent, clear the shield pixel.
            if (damage_pixels[dy * SpriteData::SHIELD_DAMAGE_WIDTH + dx] == 0) {
                sprite_pixels[sy * SpriteData::SHIELD_WIDTH + sx] = 0;
            }
        }
    }
}
