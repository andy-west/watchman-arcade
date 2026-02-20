#include <arduino.h>
#include "GamePlayScene.h"
#include "../Alien.h"
#include "../Shield.h"
#include "../Player.h"
#include "../AlienMissile.h"
#include "../Ufo.h"
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
    ufo = new Ufo(player->get_missile(), game, graphics, sprite_data);
    player->get_missile()->set_ufo(ufo);
    ufo_next_direction = Direction::LEFT;
}

void GamePlayScene::reset_level() {
    create_aliens();
    create_alien_missiles();
    create_shields();

    player->x = Player::BOUNDARY_SIDE;
    game->is_game_ending = false;

    ufo->is_active = false;
    ufo_spawn_countdown = Ufo::SPAWN_INTERVAL_FRAMES;
    ufo_next_direction = Direction::LEFT;

    alien_fire_countdown = (uint)(0.5f * 60);
    last_firing_alien_index = -1;

    for (uint i = 0; i < AlienMissile::MAX_ACTIVE; i++) {
        if (alien_missiles[i] != nullptr) {
            alien_missiles[i]->is_active = false;
            alien_missiles[i]->source_alien_index = -1;
        }
    }
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

void GamePlayScene::create_alien_missiles() {
    for (uint i = 0; i < AlienMissile::MAX_ACTIVE; i++) {
        if (alien_missiles[i] != nullptr) {
            delete alien_missiles[i];
        }

        alien_missiles[i] = new AlienMissile(player, game, graphics, sprite_data);
    }
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

        update_ufo();

        if (player->is_temporarily_disabled()) {
            player->deactivate_missile();

            for (uint i = 0; i < AlienMissile::MAX_ACTIVE; i++) {
                if (alien_missiles[i] != nullptr) {
                    alien_missiles[i]->is_active = false;
                    alien_missiles[i]->source_alien_index = -1;
                }
            }

            return;
        }

        update_aliens();
        update_alien_missiles();
    }
}

void GamePlayScene::update_alien_missiles() {
    for (uint i = 0; i < AlienMissile::MAX_ACTIVE; i++) {
        alien_missiles[i]->update();
    }

    alien_fire_countdown--;

    if (alien_fire_countdown <= 0) {
        try_fire_alien_missile();
        alien_fire_countdown = ALIEN_FIRE_INTERVAL_FRAMES;
    }
}

void GamePlayScene::try_fire_alien_missile() {
    int active_count = 0;

    for (uint i = 0; i < AlienMissile::MAX_ACTIVE; i++) {
        if (alien_missiles[i]->is_active) {
            active_count++;
        }
    }

    if (active_count >= (int)AlienMissile::MAX_ACTIVE) {
        return;
    }

    int avoid = -1;

    if (active_count == 1) {
        for (uint i = 0; i < AlienMissile::MAX_ACTIVE; i++) {
            if (alien_missiles[i]->is_active) {
                avoid = alien_missiles[i]->source_alien_index;
                break;
            }
        }
    }

    int shooter_index = -1;

    if (random(0, 2) == 0) {
        int targeted_index = get_alien_above_player();

        if (targeted_index >= 0 && targeted_index != avoid) {
            shooter_index = targeted_index;
        }
    }

    if (shooter_index < 0) {
        shooter_index = choose_random_shooter(avoid);
    }

    if (shooter_index < 0) {
        return;
    }

    Alien* shooter = aliens[shooter_index];
    uint start_x = shooter->x + (SpriteData::ALIEN_WIDTH / 2) - (SpriteData::ALIEN_MISSILE_WIDTH / 2);
    uint start_y = shooter->y + SpriteData::ALIEN_HEIGHT;

    for (uint i = 0; i < AlienMissile::MAX_ACTIVE; i++) {
        if (!alien_missiles[i]->is_active) {
            alien_missiles[i]->launch(start_x, start_y, shooter_index);
            last_firing_alien_index = shooter_index;
            break;
        }
    }
}

int GamePlayScene::choose_random_shooter(int avoid_alien_index) {
    const int MAX_TRIES = 16;

    for (int t = 0; t < MAX_TRIES; t++) {
        int column = random(0, (int)GameConstants::ALIEN_COLUMNS);
        int shooter_index = get_bottom_alien_in_column(column);

        if (shooter_index >= 0 && shooter_index != avoid_alien_index) {
            return shooter_index;
        }
    }

    for (int column = 0; column < (int)GameConstants::ALIEN_COLUMNS; column++) {
        int shooter_index = get_bottom_alien_in_column(column);

        if (shooter_index >= 0 && shooter_index != avoid_alien_index) {
            return shooter_index;
        }
    }

    return -1;
}

int GamePlayScene::get_bottom_alien_in_column(int column) {
    int best_index = -1;
    int best_y = -9999;

    for (int row = 0; row < (int)GameConstants::ALIEN_ROWS; row++) {
        int i = (row * GameConstants::ALIEN_COLUMNS) + column;
        Alien* alien = aliens[i];

        if (alien != nullptr && alien->exists) {
            if (alien->y > best_y) {
                best_y = alien->y;
                best_index = i;
            }
        }
    }

    return best_index;
}

int GamePlayScene::get_alien_above_player() {
    int player_center_x = (int)player->x + (int)(SpriteData::PLAYER_WIDTH / 2);
    int best_index = -1;
    int best_y = -1;

    for (int i = 0; i < (int)GameConstants::ALIEN_COUNT; i++) {
        Alien* alien = aliens[i];

        if (alien != nullptr && alien->exists) {
            if (player_center_x >= alien->x && player_center_x < alien->x + (int)SpriteData::ALIEN_WIDTH) {
                if (alien->y > best_y) {
                    best_y = alien->y;
                    best_index = i;
                }
            }
        }
    }

    return best_index;
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

void GamePlayScene::update_ufo() {
    bool was_active = ufo->is_active;

    ufo->update();

    if (was_active && !ufo->is_active) {
        ufo_spawn_countdown = Ufo::SPAWN_INTERVAL_FRAMES;
    }

    if (!ufo->is_active && !ufo->is_explosion_visible()) {
        ufo_spawn_countdown--;

        if (ufo_spawn_countdown <= 0) {
            ufo->launch(ufo_next_direction);
            ufo_next_direction = (ufo_next_direction == Direction::LEFT) ? Direction::RIGHT : Direction::LEFT;
        }
    }
}

void GamePlayScene::draw() {
    graphics->clear_screen(VideoConstants::COLOR_BLACK);
    draw_status();
    draw_aliens();
    draw_shields();
    draw_alien_missiles();
    draw_ufo();
    player->draw();
}

void GamePlayScene::draw_status() {
    if (ufo->is_active || ufo->is_explosion_visible()) {
        return;
    }

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

void GamePlayScene::draw_alien_missiles() {
    for (uint i = 0; i < AlienMissile::MAX_ACTIVE; i++) {
        alien_missiles[i]->draw();
    }
}

void GamePlayScene::draw_ufo() {
    ufo->draw();
}
