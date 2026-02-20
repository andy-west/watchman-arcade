#ifndef UFO_H
#define UFO_H

#include "../Graphics.h"
#include "../assets/SpriteData.h"
#include "Direction.h"
#include "Explosion.h"

class Game;
class PlayerMissile;

class Ufo {
public:
    static const uint Y = 20;
    static const uint POINTS = 150;
    static constexpr float SPAWN_INTERVAL_SECONDS = 25.0;
    static const uint SPAWN_INTERVAL_FRAMES = (uint)(SPAWN_INTERVAL_SECONDS * 60);

    bool is_active;

    Ufo(PlayerMissile* player_missile, Game* game, Graphics* graphics, SpriteData* sprite_data);
    void update();
    void draw();
    void launch(Direction direction);
    bool is_explosion_visible() const;

private:
    static constexpr float SPEED = 0.5;

    float x;

    Direction direction;

    PlayerMissile* player_missile;
    Game* game;
    Graphics* graphics;
    SpriteData* sprite_data;
    Explosion* explosion;

    void check_missile_hit();
    void deactivate();
};

#endif
