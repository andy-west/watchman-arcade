#include <arduino.h>
#include "Player.h"
#include "Game.h"
#include "../video/VideoConstants.h"

Player::Player(Game* game, Input* input, Graphics* graphics, SpriteData* sprite_data, Alien* aliens[]) {
    this->game = game;
    this->input = input;
    this->graphics = graphics;
    this->sprite_data = sprite_data;
    this->aliens = aliens;

    this->missile = new PlayerMissile(this, aliens, game, input, graphics, sprite_data);

    is_hit_animating = false;
    hit_countdown = 0;

    is_respawning = false;
    respawn_countdown = 0;
    respawn_visible = true;
    respawn_blink_countdown = 0;
}

void Player::update() {
    if (is_hit_animating) {
        animate_hit();
        return;
    }

    if (is_respawning) {
        animate_respawn();
        return;
    }

    if (input->left_pressed) {
        move_player_left();
    }

    if (input->right_pressed) {
        move_player_right();
    }

    missile->update();
}

void Player::animate_hit() {
    hit_countdown--;

    if (hit_countdown <= 0) {
        is_hit_animating = false;

        if (game->lives <= 0) {
            game->end();
        }
        else {
            x = Player::BOUNDARY_SIDE;
            is_respawning = true;
            respawn_countdown = (uint)(1.5f * 60);
            respawn_visible = true;
            respawn_blink_countdown = 16;
        }
    }
}

void Player::animate_respawn() {
    respawn_countdown--;
    respawn_blink_countdown--;

    if (respawn_blink_countdown <= 0) {
        respawn_blink_countdown = 16;
        respawn_visible = !respawn_visible;
    }

    if (respawn_countdown <= 0) {
        is_respawning = false;
        respawn_visible = true;
    }
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
    if (is_hit_animating) {
        if ((hit_countdown / 4) % 2 == 0) {
            graphics->draw_sprite(sprite_data->player_sprite, x, Y);
        }
        else {
            graphics->draw_sprite(sprite_data->player_hit_sprite, x, Y);
        }
    }
    else if (!is_respawning || respawn_visible) {
        graphics->draw_sprite(sprite_data->player_sprite, x, Y);
    }

    missile->draw();
}

void Player::on_hit() {
    if (is_hit_animating || is_respawning || game->is_game_ending) {
        return;
    }

    game->lives--;
    is_hit_animating = true;
    hit_countdown = (uint)(1.0f * 60);
}
