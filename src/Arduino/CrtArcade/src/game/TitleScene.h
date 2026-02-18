#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "../Input.h"
#include "../Graphics.h"
#include "../assets/TitleScreen.h"

class Game;

class TitleScene {
public:
    TitleScene(Game* game, Input* input, Graphics* graphics);
    void update();
    void draw();

private:
    Game* game;
    Input* input;
    Graphics* graphics;

    TitleScreen title_screen;
};

#endif
