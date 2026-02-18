#ifndef LEVEL_START_SCREEN_H
#define LEVEL_START_SCREEN_H

#include "../../Graphics.h"

class Game;

class LevelStartScene {
public:
    LevelStartScene(Game* game, Graphics* graphics);
    void reset(uint level_number);
    void update();
    void draw();

private:
    uint start_screen_countdown;

    Game* game;
    Graphics* graphics;
};

#endif
