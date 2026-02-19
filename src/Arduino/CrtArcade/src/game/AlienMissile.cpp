#include <arduino.h>
#include "AlienMissile.h"
#include "Player.h"
#include "Game.h"

AlienMissile::AlienMissile(Player* player, Game* game, Graphics* graphics, SpriteData* sprite_data) {
    this->player = player;
    this->game = game;
    this->graphics = graphics;
    this->sprite_data = sprite_data;

    is_active = false;
    source_alien_index = -1;
}

void AlienMissile::launch(uint start_x, uint start_y, int alien_index) {
    x = start_x;
    y = start_y;
    source_alien_index = alien_index;
    is_active = true;
}

void AlienMissile::update() {
    if (!is_active) {
        return;
    }

    y += SPEED;

    if (y >= GameConstants::FLOOR_Y) {
        deactivate();
        return;
    }

    if (x + SpriteData::ALIEN_MISSILE_WIDTH > player->x && x < player->x + SpriteData::PLAYER_WIDTH &&
        y + SpriteData::ALIEN_MISSILE_HEIGHT > Player::Y && y < Player::Y + SpriteData::PLAYER_HEIGHT) {
        hit_player();
    }
}

void AlienMissile::hit_player() {
    deactivate();
    player->on_hit();
}

void AlienMissile::deactivate() {
    is_active = false;
    source_alien_index = -1;
}

void AlienMissile::draw() {
    if (is_active) {
        graphics->draw_sprite(sprite_data->alien_missile_sprite, x, y);
    }
}
