#include <arduino.h>
#include "Ufo.h"
#include "PlayerMissile.h"
#include "Game.h"
#include "../video/VideoConstants.h"

Ufo::Ufo(PlayerMissile* player_missile, Game* game, Graphics* graphics, SpriteData* sprite_data) {
    this->player_missile = player_missile;
    this->game = game;
    this->graphics = graphics;
    this->sprite_data = sprite_data;

    is_active = false;
    explosion = new Explosion(graphics, sprite_data);
}

void Ufo::update() {
    if (is_active) {
        if (direction == Direction::RIGHT) {
            x += SPEED;

            if (x + SpriteData::UFO_WIDTH >= VideoConstants::SCREEN_WIDTH) {
                deactivate();
                return;
            }
        }
        else {
            x -= SPEED;

            if (x <= 0) {
                deactivate();
                return;
            }
        }

        check_missile_hit();
    }

    explosion->update();
}

void Ufo::draw() {
    if (is_active) {
        graphics->draw_sprite(sprite_data->ufo_sprite, (int)x, Y);
    }

    explosion->draw();
}

void Ufo::launch(Direction direction) {
    this->direction = direction;

    if (direction == Direction::RIGHT) {
        x = 0;
    }
    else {
        x = VideoConstants::SCREEN_WIDTH - SpriteData::UFO_WIDTH;
    }

    is_active = true;
}

void Ufo::check_missile_hit() {
    if (!player_missile->is_active) {
        return;
    }

    uint missile_x = player_missile->x;
    uint missile_y = player_missile->y;

    if (missile_x >= x && missile_x < x + SpriteData::UFO_WIDTH &&
        missile_y >= Y && missile_y < Y + SpriteData::UFO_HEIGHT) {
        game->score += POINTS;
        player_missile->deactivate();
        explosion->show((int)x + (SpriteData::UFO_WIDTH / 2) - (SpriteData::EXPLOSION_WIDTH / 2), Y);
        deactivate();
    }
}

void Ufo::deactivate() {
    is_active = false;
}

bool Ufo::is_explosion_visible() const {
    return explosion->is_visible;
}
