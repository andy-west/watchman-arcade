#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "scenes/TitleScene.h"
#include "scenes/LevelStartScene.h"
#include "scenes/GamePlayScene.h"
#include "scenes/GameOverScene.h"
#include "../Input.h"
#include "../Graphics.h"
#include "../assets/SpriteData.h"

class World;

class Game {
public:
    GameState current_state = GameState::TITLE_SCREEN;
    uint level_number;
    uint score;
    uint lives;
    bool is_game_ending;
    uint game_ending_countdown;

    Game(Graphics* graphics);

    void update();
    void draw();

    void reset();
    void reset_level(uint level_number);
    void end();

private:
    static constexpr float GAME_ENDING_SECONDS = 3.0;
    static const uint GAME_ENDING_TIME = GAME_ENDING_SECONDS * 60;

    Graphics* graphics;
    SpriteData* sprite_data;

    Input* input;
    TitleScene* title_scene;
    LevelStartScene* level_start_scene;
    GamePlayScene* game_play_scene;
    GameOverScene* game_over_scene; 
};

#endif
