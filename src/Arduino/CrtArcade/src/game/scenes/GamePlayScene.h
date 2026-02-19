#ifndef GAME_PLAY_SCENE_H
#define GAME_PLAY_SCENE_H

#include "../GameConstants.h"
#include "../../Input.h"
#include "../../Graphics.h"
#include "../../assets/SpriteData.h"

class Game;
class Alien;
class Shield;
class Player;
class AlienMissile;

class GamePlayScene {
public:
    GamePlayScene(Game* game, Input* input, Graphics* graphics, SpriteData* sprite_data);
    void reset_level();
    void update();
    void draw();

private:
    const uint TEXT_MARGIN = 20;

    Game* game;
    Input* input;
    Graphics* graphics;
    SpriteData* sprite_data;
    Alien* aliens[GameConstants::ALIEN_COUNT] = {};
    Shield* shields[GameConstants::SHIELD_COUNT] = {};
    Player* player;

    AlienMissile* alien_missiles[2] = {};
    uint alien_fire_countdown;
    int last_firing_alien_index;

    void create_aliens();
    void create_shields();
    void create_alien_missiles();
    void update_alien_missiles();
    void try_fire_alien_missile();
    int get_bottom_alien_in_column(int column);
    int choose_random_shooter(int avoid_alien_index);
    void update_aliens();
    uint get_alien_animation_time();
    uint get_remaining_alien_count();
    void move_aliens();
    void move_aliens_down();
    void draw_status();
    void draw_score();
    void draw_lives();
    void draw_aliens();
    void draw_shields();
    void draw_alien_missiles();
};

#endif
