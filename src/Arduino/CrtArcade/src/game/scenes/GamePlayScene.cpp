#include <arduino.h>
#include "GamePlayScene.h"
#include "../Alien.h"
#include "../Shield.h"
#include "../Player.h"
#include "../GameConstants.h"
#include "../../video/VideoConstants.h"
#include "../../GlobalConstants.h"

GamePlayScene::GamePlayScene(Game* game, Input* input, Graphics* graphics, SpriteData* sprite_data) {
    this->game = game;
    this->input = input;
    this->graphics = graphics;
    this->sprite_data = sprite_data;

    Alien::sprite_data = sprite_data;
    Shield::sprite_data = sprite_data;

    player = new Player(game, input, graphics, sprite_data, aliens);
}

void GamePlayScene::reset_level() {
    create_aliens();
    create_shields();
    player->x = Player::BOUNDARY_SIDE;
    game->is_game_ending = false;
}

void GamePlayScene::create_aliens() {
    int i = 0;

    for (int y = 0; y < GameConstants::ALIEN_ROWS; y++) {
        uint points = (GameConstants::ALIEN_ROWS - y) * 10;

        for (int x = 0; x < GameConstants::ALIEN_COLUMNS; x++) {
            if (aliens[i] != nullptr) {
                delete aliens[i];
            }

            aliens[i] = {
                new Alien(x * Alien::SPACING + Alien::MARGIN_SIDE,
                    y * Alien::SPACING + Alien::MARGIN_TOP,
                    y / 2,  // sprite_index
                    true,   // exists
                    points,
                    graphics,
                    game)
            };

            i++;
        }
    }

    Alien::animation_frame = 0;
    Alien::animation_countdown = get_alien_animation_time();
    Alien::direction = Direction::RIGHT;
}

void GamePlayScene::create_shields() {
    const int shield_positions[GameConstants::SHIELD_COUNT] = {
        Shield::MARGIN_SIDE,
        (VideoConstants::SCREEN_WIDTH / 2) - (SpriteData::SHIELD_WIDTH / 2),
        VideoConstants::SCREEN_WIDTH - SpriteData::SHIELD_WIDTH - Shield::MARGIN_SIDE
    };

    for (int i = 0; i < GameConstants::SHIELD_COUNT; i++) {
        if (shields[i] != nullptr) {
            delete shields[i];
        }

        shields[i] = new Shield(shield_positions[i], Shield::Y, true, graphics);
    }
}

void GamePlayScene::update() {
    if (game->is_game_ending) {
        game->game_ending_countdown--;

        if (game->game_ending_countdown <= 0) {
            game->current_state = GameState::GAME_OVER;
        }
    }
    else {
        player->update();
        update_aliens();
    }
}

void GamePlayScene::update_aliens() {
    Alien::animation_countdown--;

    if (Alien::animation_countdown <= 0) {
        Alien::animation_countdown += get_alien_animation_time();
        Alien::animation_frame = 1 - Alien::animation_frame;
        move_aliens();
    }
}

uint GamePlayScene::get_alien_animation_time() {
    uint remaining = get_remaining_alien_count();
    uint time = (Alien::ANIMATION_TIME * remaining) / GameConstants::ALIEN_COUNT;

    if (time < 1) {
        time = 1;
    }

    return time;
}

uint GamePlayScene::get_remaining_alien_count() {
    uint remaining = 0;

    for (int i = 0; i < GameConstants::ALIEN_COUNT; i++) {
        if (aliens[i]->exists) {
            remaining++;
        }
    }

    return remaining;
}

void GamePlayScene::move_aliens() {
    Direction new_direction = Alien::direction;

    for (int i = 0; i < GameConstants::ALIEN_COUNT; i++) {
        aliens[i]->move(new_direction);
    }

    if (new_direction != Alien::direction) {
        Alien::direction = new_direction;
        move_aliens_down();
    }
}

void GamePlayScene::move_aliens_down() {
    for (int i = 0; i < GameConstants::ALIEN_COUNT; i++) {
        aliens[i]->move_down(shields);
    }
}

void GamePlayScene::draw() {
    graphics->clear_screen(VideoConstants::COLOR_BLACK);
    draw_status();
    draw_aliens();
    draw_shields();
    player->draw();
}

void GamePlayScene::draw_status() {
    draw_score();
    draw_lives();
}

void GamePlayScene::draw_score() {
    const uint SCORE_LABEL_CHARACTERS = 6;
    const uint SCORE_DIGITS = 6;

    graphics->draw_text("SCORE ", TEXT_MARGIN, TEXT_MARGIN);
    char score_string[SCORE_DIGITS + 1];
    sprintf(score_string, "%0*d", SCORE_DIGITS, game->score);
    graphics->draw_text(score_string,
        TEXT_MARGIN + (SCORE_LABEL_CHARACTERS * GlobalConstants::FONT_WIDTH),
        TEXT_MARGIN);
}

void GamePlayScene::draw_lives() {
    const uint LIVES_LABEL_CHARACTERS = 6;
    const uint LIVES_DIGITS = 1;

    uint lives_text_x = VideoConstants::SCREEN_WIDTH - TEXT_MARGIN -
        ((LIVES_LABEL_CHARACTERS + LIVES_DIGITS) * GlobalConstants::FONT_WIDTH);
    graphics->draw_text("LIVES ", lives_text_x, TEXT_MARGIN);
    char lives_string[LIVES_DIGITS + 1];
    itoa(game->lives, lives_string, 10);
    graphics->draw_text(lives_string,
        lives_text_x + (LIVES_LABEL_CHARACTERS * GlobalConstants::FONT_WIDTH),
        TEXT_MARGIN);
}

void GamePlayScene::draw_aliens() {
    for (int i = 0; i < GameConstants::ALIEN_COUNT; i++) {
        aliens[i]->draw();
    }
}

void GamePlayScene::draw_shields() {
    for (int i = 0; i < GameConstants::SHIELD_COUNT; i++) {
        shields[i]->draw();
    }
}
