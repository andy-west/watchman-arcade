#ifndef PLAYER_H
#define PLAYER_H

#include "../Input.h"
#include "../Graphics.h"
#include "../assets/SpriteData.h"
#include "PlayerMissile.h"
#include "GameConstants.h"

class Game;
class Alien;

class Player {
public:
    static const uint Y = GameConstants::FLOOR_Y - SpriteData::PLAYER_HEIGHT;
    static const uint BOUNDARY_SIDE = 30;

    uint x;

    Player(Game* game, Input* input, Graphics* graphics, SpriteData* sprite_data, Alien* aliens[]);
    void update();
    void draw();

private:
    Game* game;
    Input* input;
    Graphics* graphics;
    SpriteData* sprite_data;
    Alien** aliens;

    PlayerMissile* missile;

    void move_player_left();
    void move_player_right();
};

#endif
