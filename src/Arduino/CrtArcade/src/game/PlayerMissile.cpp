#include <arduino.h>
#include "PlayerMissile.h"
#include "Player.h"
#include "Alien.h"
#include "Game.h"
#include "Explosion.h"

PlayerMissile::PlayerMissile(Player* player, Alien* aliens[], Game* game, Input* input, Graphics* graphics, SpriteData* sprite_data) {
    this->player = player;
    this->aliens = aliens;
    this->game = game;
    this->input = input;
    this->graphics = graphics;
    this->sprite_data = sprite_data;

    is_active = false;
    explosion = new Explosion(graphics, sprite_data);
}

void PlayerMissile::update() {
    if (is_active) {
        y -= SPEED;

        if (y <= GameConstants::CEILING_Y) {
            is_active = false;
        }

        destroy_alien_if_hit();
    }
    else if (input->fire_pressed_this_frame) {
        x = player->x + (SpriteData::PLAYER_WIDTH / 2);
        y = Player::Y - SpriteData::PLAYER_MISSILE_HEIGHT;
        is_active = true;
    }

    explosion->update();
}

void PlayerMissile::destroy_alien_if_hit() {
    for (int i = 0; i < GameConstants::ALIEN_COUNT; i++) {
        Alien* alien = aliens[i];

        if (alien->exists) {
            // Check if the top pixel of the missile is inside the alien's bounding box (alien was hit).
            if (x >= alien->x && x < alien->x + SpriteData::ALIEN_WIDTH &&
                y >= alien->y && y < alien->y + SpriteData::ALIEN_HEIGHT) {
                    alien->exists = false;
                    game->score += alien->points;
                    is_active = false;
                    explosion->show(alien->x, alien->y);
                    break;
            }
        }
    }
}

void PlayerMissile::draw() {
    if (is_active) {
        graphics->draw_sprite(sprite_data->player_missile_sprite, x, y);
    }

    explosion->draw();
}
