#ifndef PLAYER_H
#define PLAYER_H

#include "../Input.h"
#include "../Graphics.h"
#include "../assets/SpriteData.h"
#include "PlayerMissile.h"
#include "GameConstants.h"

class Game;
class Alien;
class Shield;

class Player {
public:
    static const uint Y = GameConstants::FLOOR_Y - SpriteData::PLAYER_HEIGHT;
    static const uint BOUNDARY_SIDE = 30;

    uint x;

    Player(Game* game, Input* input, Graphics* graphics, SpriteData* sprite_data, Alien* aliens[], Shield* shields[]);
    void update();
    void draw();
    void on_hit();
    bool is_temporarily_disabled() const;
    void deactivate_missile();
    PlayerMissile* get_missile() const;

private:
    Game* game;
    Input* input;
    Graphics* graphics;
    SpriteData* sprite_data;
    Alien** aliens;

    PlayerMissile* missile;

    bool is_hit_animating;
    uint hit_countdown;

    bool is_respawning;
    uint respawn_countdown;
    bool respawn_visible;
    uint respawn_blink_countdown;

    void animate_hit();
    void animate_respawn();
    void move_player_left();
    void move_player_right();
};

#endif
