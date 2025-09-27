#ifndef GAME_H
#define GAME_H

#include "constants.h"
#include "sprite_data.h"

const uint GAME_MODE_TITLE = 0;
const uint GAME_MODE_LEVEL_START = 1;
const uint GAME_MODE_PLAY_GAME = 2;
const uint GAME_MODE_GAME_OVER = 3;

const float LEVEL_DISPLAY_SECONDS = 3.0;
const uint LEVEL_DISPLAY_TIME = LEVEL_DISPLAY_SECONDS * 60;

const float ALIEN_ANIMATION_SECONDS = 0.5;
const uint ALIEN_ANIMATION_TIME = ALIEN_ANIMATION_SECONDS * 60;

const uint ALIEN_DIRECTION_LEFT = 0;
const uint ALIEN_DIRECTION_RIGHT = 1;
const uint ALIEN_MOVE_SPEED = 2;
const uint ALIEN_MOVE_DOWN_SPEED = 10;
const uint ALIEN_MAX_Y = 182;

const int ALIEN_MARGIN_TOP = 50;
const int ALIEN_MARGIN_SIDE = 20;
const int ALIEN_SPACING = 16;

const uint ALIEN_ROWS = 6;
const uint ALIEN_COLUMNS = 10;
const uint ALIEN_COUNT = ALIEN_ROWS * ALIEN_COLUMNS;

const uint CEILING_Y = 40;
const uint FLOOR_Y = SCREEN_HEIGHT - 40;

const uint PLAYER_Y = FLOOR_Y - PLAYER_HEIGHT;
const uint PLAYER_BOUNDARY_SIDE = 30;

const float GAME_ENDING_SECONDS = 3.0;
const uint GAME_ENDING_TIME = GAME_ENDING_SECONDS * 60;

const float GAME_OVER_SECONDS = 3.0;
const uint GAME_OVER_TIME = GAME_OVER_SECONDS * 60;

const uint SHIELD_Y = 165;
const uint SHIELD_MARGIN_SIDE = 50;
const uint SHIELD_ARRAY_SIZE = SHIELD_WIDTH * SHIELD_HEIGHT + 2;
const uint SHIELD_COUNT = 3;

const uint PLAYER_MISSILE_SPEED = 2;

const uint ALIEN_MISSILE_SPEED = 2;
const uint ALIEN_MISSILE_MAX_Y = FLOOR_Y - ALIEN_MISSILE_HEIGHT;

const float EXPLOSION_SECONDS = 0.25;
const uint EXPLOSION_TIME = EXPLOSION_SECONDS * 60;

struct Alien {
    int x;
    int y;
    int sprite_index;
    bool exists;
    uint points;
};

struct AlienMissile {
    int x;
    int y;
    int sprite_index;
    bool exists;
    uint points;
};

struct Shield {
    int x;
    int y;
    byte sprite[SHIELD_ARRAY_SIZE];
    bool exists;
};

typedef void (*UpdateFunction)();
typedef void (*DrawFunction)();

extern uint game_mode;

extern void update();
extern void draw();

void update_title();
void update_level_start();
void update_game();
void update_game_over();

void draw_title();
void draw_level_start();
void draw_game();
void draw_game_over();

void setup_game();
void setup_level();
void move_player_left();
void move_player_right();
void update_player_missile();
void destroy_alien_if_hit();
void show_explosion(int x, int y);
void update_aliens();
uint get_remaining_alien_count();
uint get_alien_animation_time();
void move_aliens();
void move_aliens_down();
void update_explosion();

#endif
