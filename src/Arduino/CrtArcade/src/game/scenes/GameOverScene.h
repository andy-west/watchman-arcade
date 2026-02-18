#ifndef GAME_OVER_SCENE_H
#define GAME_OVER_SCENE_H

#include "../../Graphics.h"

class Game;

class GameOverScene {
public:
    GameOverScene(Game* game, Graphics* graphics);
    void reset();
    void update();
    void draw();

private:
    uint game_over_countdown;

    Game* game;
    Graphics* graphics;
};

#endif
