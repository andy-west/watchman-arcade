#include <arduino.h>
#include "GameOverScene.h"
#include "../Game.h"
#include "../../video/VideoConstants.h"

GameOverScene::GameOverScene(Game* game, Graphics* graphics) {
    this->game = game;
    this->graphics = graphics;
}

void GameOverScene::reset() {
    const float GAME_OVER_SECONDS = 3.0;
    const uint GAME_OVER_TIME = GAME_OVER_SECONDS * 60;

    game_over_countdown = GAME_OVER_TIME;
}

void GameOverScene::update() {
    game_over_countdown--;

    if (game_over_countdown <= 0) {
        game->current_state = GameState::TITLE_SCREEN;
    }
}

void GameOverScene::draw() {
    graphics->clear_screen(VideoConstants::COLOR_BLACK);
    graphics->draw_text("GAME OVER", 96, 100);
}
