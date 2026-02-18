#ifndef PLAYER_MISSILE_H
#define PLAYER_MISSILE_H

#include "../Input.h"
#include "../Graphics.h"
#include "../assets/SpriteData.h"
#include "GameConstants.h"

class Game;
class Player;
class Alien;
class Explosion;

class PlayerMissile {
public:
    uint x;
    uint y;

    PlayerMissile(Player* player, Alien* aliens[], Game* game, Input* input, Graphics* graphics, SpriteData* sprite_data);
    void update();
    void draw();

private:
    const uint SPEED = 2;

    Player* player;
    Alien** aliens;
    Game* game;
    Input* input;
    Graphics* graphics;
    SpriteData* sprite_data;

    bool is_active;
    Explosion* explosion;

    void destroy_alien_if_hit();
};

#endif
