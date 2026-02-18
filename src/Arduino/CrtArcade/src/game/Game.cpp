#include <arduino.h>
#include "Game.h"
#include "GameConstants.h"
#include "scenes/GamePlayScene.h"
#include "../GlobalConstants.h"
#include "../video/VideoConstants.h"

Game::Game(Graphics* graphics) {
    this->graphics = graphics;

    input = new Input();
    sprite_data = new SpriteData();
    level_start_scene = new LevelStartScene(this, graphics);
    title_scene = new TitleScene(this, input, graphics);
    game_play_scene = new GamePlayScene(this, input, graphics, sprite_data);
    game_over_scene = new GameOverScene(this, graphics);
}

void Game::update() {
    input->update();

    switch(current_state) {
        case GameState::TITLE_SCREEN: title_scene->update(); break;
        case GameState::LEVEL_START: level_start_scene->update(); break;
        case GameState::GAME_PLAY: game_play_scene->update(); break;
        case GameState::GAME_OVER: game_over_scene->update(); break;
    }
}

void Game::draw() {
    switch(current_state) {
        case GameState::TITLE_SCREEN: title_scene->draw(); break;
        case GameState::LEVEL_START: level_start_scene->draw(); break;
        case GameState::GAME_PLAY: game_play_scene->draw(); break;
        case GameState::GAME_OVER: game_over_scene->draw(); break;
    }
}

void Game::reset() {
    score = 0;
    lives = 3;
    reset_level(1);
    game_over_scene->reset();
}

void Game::reset_level(uint level_number) {
    this->level_number = level_number;
    level_start_scene->reset(level_number);
    game_play_scene->reset_level();
}

void Game::end() {
    game_ending_countdown = GAME_ENDING_TIME;
    is_game_ending = true;
}
