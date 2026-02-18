#include <arduino.h>
#include "Player.h"
#include "Game.h"

Player::Player(Game* game, Input* input, Graphics* graphics, SpriteData* sprite_data, Alien* aliens[]) {
    this->game = game;
    this->input = input;
    this->graphics = graphics;
    this->sprite_data = sprite_data;
    this->aliens = aliens;

    this->missile = new PlayerMissile(this, aliens, game, input, graphics, sprite_data);
}

void Player::update() {
    if (input->left_pressed) {
        move_player_left();
    }

    if (input->right_pressed) {
        move_player_right();
    }

    missile->update();
}

void Player::move_player_left() {
    x--;

    if (x < BOUNDARY_SIDE) {
        x = BOUNDARY_SIDE;
    }
}

void Player::move_player_right() {
    x++;

    const int MAX_X = VideoConstants::SCREEN_WIDTH - SpriteData::PLAYER_WIDTH - Player::BOUNDARY_SIDE;

    if (x > MAX_X) {
        x = MAX_X;
    }
}

void Player::draw() {
    graphics->draw_sprite(sprite_data->player_sprite, x, Y);
    missile->draw();
}
