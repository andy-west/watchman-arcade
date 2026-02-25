#include <arduino.h>
#include "PlayerMissile.h"
#include "Player.h"
#include "Alien.h"
#include "Shield.h"
#include "Game.h"
#include "Explosion.h"
#include "Ufo.h"

PlayerMissile::PlayerMissile(Player* player, Alien* aliens[], Shield* shields[], Game* game, Input* input, Graphics* graphics, SpriteData* sprite_data) {
    this->player = player;
    this->aliens = aliens;
    this->shields = shields;
    this->game = game;
    this->input = input;
    this->graphics = graphics;
    this->sprite_data = sprite_data;

    is_active = false;
    ufo = nullptr;
    explosion = new Explosion(graphics, sprite_data);
}

void PlayerMissile::set_ufo(Ufo* ufo) {
    this->ufo = ufo;
}

void PlayerMissile::update() {
    if (is_active) {
        y -= SPEED;

        if (y <= (ufo != nullptr && ufo->is_active ? Ufo::Y : GameConstants::CEILING_Y)) {
            is_active = false;
        }

        if (check_shield_hit()) {
            return;
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

void PlayerMissile::deactivate() {
    is_active = false;
    explosion->is_visible = false;
}

void PlayerMissile::update_explosion() {
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

bool PlayerMissile::check_shield_hit() {
    for (int i = 0; i < GameConstants::SHIELD_COUNT; i++) {
        if (shields[i]->check_hit(x, y, SpriteData::PLAYER_MISSILE_WIDTH, SpriteData::PLAYER_MISSILE_HEIGHT)) {
            int hit_x = x + SpriteData::PLAYER_MISSILE_WIDTH / 2;
            int hit_y = y;
            shields[i]->damage(hit_x, hit_y);
            is_active = false;
            return true;
        }
    }

    return false;
}

bool PlayerMissile::is_explosion_visible() const {
    return explosion->is_visible;
}

void PlayerMissile::draw() {
    if (is_active) {
        graphics->draw_sprite(sprite_data->player_missile_sprite, x, y);
    }

    explosion->draw();
}
