#include <arduino.h>
#include "TitleScene.h"
#include "Game.h"

TitleScene::TitleScene(Game* game, Input* input, Graphics* graphics) {
    this->game = game;
    this->input = input;
    this->graphics = graphics;
}

void TitleScene::update() {
    if (input->fire_pressed_this_frame) {
        game->current_state = GameState::LEVEL_START;
        game->reset();
    }
}

void TitleScene::draw() {
    graphics->draw_screen(title_screen.data);
    graphics->draw_text("PRESS FIRE TO START", 52, 190);
}
