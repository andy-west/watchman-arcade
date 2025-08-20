#ifndef SPRITE_DATA_H
#define SPRITE_DATA_H

const uint ALIEN_WIDTH = 12;
const uint ALIEN_HEIGHT = 8;
const uint PLAYER_WIDTH = 13;
const uint PLAYER_HEIGHT = 8;
const uint SHIELD_WIDTH = 22;
const uint SHIELD_HEIGHT = 16;
const uint PLAYER_MISSILE_WIDTH = 1;
const uint PLAYER_MISSILE_HEIGHT = 7;
const uint ALIEN_MISSILE_WIDTH = 3;
const uint ALIEN_MISSILE_HEIGHT = 7;

extern byte *alien_sprites[3][2];

extern byte alien_a_0[];
extern byte alien_a_1[];
extern byte alien_b_0[];
extern byte alien_b_1[];
extern byte alien_c_0[];
extern byte alien_c_1[];

extern byte explosion_sprite[];
extern byte spaceship_sprite[];
extern byte player_sprite[];
extern byte player_hit_sprite[];
extern byte shield_sprite[];
extern byte player_missile_sprite[];
extern byte alien_missile_sprite[];
extern byte shield_destruction_sprite[];

#endif
