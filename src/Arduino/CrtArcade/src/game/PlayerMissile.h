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
class Shield;
class Ufo;

class PlayerMissile {
public:
    uint x;
    uint y;

    bool is_active;

    PlayerMissile(Player* player, Alien* aliens[], Shield* shields[], Game* game, Input* input, Graphics* graphics, SpriteData* sprite_data);
    void set_ufo(Ufo* ufo);
    void update();
    void update_explosion();
    void draw();
    void deactivate();
    bool is_explosion_visible() const;

private:
    const uint SPEED = 2;

    Player* player;
    Alien** aliens;
    Shield** shields;
    Game* game;
    Input* input;
    Graphics* graphics;
    SpriteData* sprite_data;
    Ufo* ufo;

    Explosion* explosion;

    void destroy_alien_if_hit();
    bool check_shield_hit();
};

#endif
