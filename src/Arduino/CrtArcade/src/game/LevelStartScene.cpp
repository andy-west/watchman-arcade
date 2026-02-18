#include <arduino.h>
#include "LevelStartScene.h"
#include "Game.h"
#include "../video/VideoConstants.h"

LevelStartScene::LevelStartScene(Game* game, Graphics* graphics) {
    this->game = game;
    this->graphics = graphics;
}

void LevelStartScene::reset(uint level_number) {
    const float LEVEL_NUMBER_DISPLAY_SECONDS = 3.0;
    const uint LEVEL_NUMBER_DISPLAY_FRAMES = LEVEL_NUMBER_DISPLAY_SECONDS * 60;

    start_screen_countdown = LEVEL_NUMBER_DISPLAY_FRAMES;
}

void LevelStartScene::update() {
    start_screen_countdown--;

    if (start_screen_countdown <= 0) {
        game->current_state = GameState::GAME_PLAY;
    }
}

void LevelStartScene::draw() {
    const uint LEVEL_LABEL_CHARACTERS = 6;
    const uint LEVEL_NUMBER_DIGITS = 4;

    graphics->clear_screen(VideoConstants::COLOR_BLACK);
    graphics->draw_text("LEVEL ", 96, 100);
    char level_string[LEVEL_NUMBER_DIGITS + 1];
    itoa(game->level_number, level_string, 10);
    graphics->draw_text(level_string, 96 + (LEVEL_LABEL_CHARACTERS * GlobalConstants::FONT_WIDTH), 100);
    graphics->draw_text(" START", 96, 116);
}
