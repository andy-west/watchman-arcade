#include <arduino.h>
#include "Alien.h"
#include "GameConstants.h"
#include "../video/VideoConstants.h"

uint Alien::animation_frame = 0;
uint Alien::animation_countdown = 0;
Direction Alien::direction = Direction::RIGHT;
SpriteData* Alien::sprite_data = nullptr;

Alien::Alien(int x, int y, int sprite_index, bool exists, uint points, Graphics* graphics, Game* game) {
    this->x = x;
    this->y = y;
    this->sprite_index = sprite_index;
    this->exists = exists;
    this->points = points;
    this->graphics = graphics;
    this->game = game;
}

void Alien::move(Direction &new_direction) {
    if (exists) {
        if (direction == Direction::RIGHT) {
            x += MOVE_SPEED;

            if (x >= VideoConstants::SCREEN_WIDTH - SpriteData::ALIEN_WIDTH - MARGIN_SIDE) {
                new_direction = Direction::LEFT;
            }
        }
        else {
            x -= MOVE_SPEED;

            if (x <= MARGIN_SIDE) {
                new_direction = Direction::RIGHT;
            }
        }
    }
}

void Alien::move_down(Shield* shields[]) {
    if (exists) {
        y += MOVE_DOWN_SPEED;

        // Remove shields if aliens get too low.
        if (y + SpriteData::ALIEN_HEIGHT >= Shield::Y) {
            for (int i = 0; i < GameConstants::SHIELD_COUNT; i++) {
                shields[i]->exists = false;
            }
        }

        // Game ends if aliens reach bottom.
        if (y >= MAX_Y) {
            game->end();
        }
    }
}

void Alien::draw() {
    if (exists) {
        graphics->draw_sprite(sprite_data->aliens[sprite_index][animation_frame], x, y);
    }
}
