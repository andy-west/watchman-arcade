#ifndef ALIEN_MISSILE_H
#define ALIEN_MISSILE_H

#include "../Graphics.h"
#include "../assets/SpriteData.h"
#include "GameConstants.h"

class Game;
class Player;
class Alien;
class Shield;

class AlienMissile {
public:
    static const uint MAX_ACTIVE = 2;

    uint x;
    float y;

    AlienMissile(Player* player, Shield* shields[], Game* game, Graphics* graphics, SpriteData* sprite_data);

    bool is_active;
    int source_alien_index;

    void update();
    void draw();
    void launch(uint start_x, uint start_y, int alien_index);

private:
    static constexpr float SPEED = 0.5;

    Player* player;
    Shield** shields;
    Game* game;
    Graphics* graphics;
    SpriteData* sprite_data;

    void deactivate();
    void hit_player();
    bool check_shield_hit();
};

#endif
