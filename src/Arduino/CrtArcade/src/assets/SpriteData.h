#ifndef SPRITE_DATA_H
#define SPRITE_DATA_H

#include "../GlobalConstants.h"

class SpriteData {
public:
    static const byte ALIEN_WIDTH = 12;
    static const byte ALIEN_HEIGHT = 8;
    static const byte SHIELD_WIDTH = 22;
    static const byte SHIELD_HEIGHT = 16;
    static const byte SHIELD_DAMAGE_WIDTH = 5;
    static const byte SHIELD_DAMAGE_HEIGHT = 5;
    static const uint PLAYER_WIDTH = 13;
    static const uint PLAYER_HEIGHT = 8;
    static const uint PLAYER_MISSILE_WIDTH = 1;
    static const uint PLAYER_MISSILE_HEIGHT = 7;
    static const uint ALIEN_MISSILE_WIDTH = 3;
    static const uint ALIEN_MISSILE_HEIGHT = 7;
    static const uint EXPLOSION_WIDTH = 12;
    static const uint EXPLOSION_HEIGHT = 8;
    static const uint UFO_WIDTH = 14;
    static const uint UFO_HEIGHT = 7;

    byte* aliens[3][2] = {
        { alien_a_0, alien_a_1 },
        { alien_b_0, alien_b_1 },
        { alien_c_0, alien_c_1 }
    };

    byte alien_a_0[ALIEN_WIDTH * ALIEN_HEIGHT + 2] = {
        ALIEN_WIDTH, ALIEN_HEIGHT,
        0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0,
        0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 3,
        0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 3,
        0, 3, 3, 3, 3, 1, 3, 1, 3, 0, 0, 3,
        3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0,
        3, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0,
        3, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0,
        0, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 0
    };

    byte alien_a_1[ALIEN_WIDTH * ALIEN_HEIGHT + 2] = {
        ALIEN_WIDTH, ALIEN_HEIGHT,
        0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0,
        3, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0,
        3, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0,
        3, 0, 0, 3, 1, 3, 1, 3, 3, 3, 3, 0,
        0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3,
        0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 3,
        0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 3,
        0, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 0
    };

    byte alien_b_0[ALIEN_WIDTH * ALIEN_HEIGHT + 2] = {
        ALIEN_WIDTH, ALIEN_HEIGHT,
        0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0,
        0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0,
        0, 3, 3, 1, 3, 3, 3, 3, 1, 3, 3, 0,
        3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3,
        0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
        0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0,
        0, 0, 3, 3, 0, 3, 3, 0, 3, 3, 0, 0,
        0, 0, 3, 0, 3, 0, 0, 3, 0, 3, 0, 0
    };

    byte alien_b_1[ALIEN_WIDTH * ALIEN_HEIGHT + 2] = {
        ALIEN_WIDTH, ALIEN_HEIGHT,
        0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0,
        0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0,
        0, 3, 3, 1, 3, 3, 3, 3, 1, 3, 3, 0,
        3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3,
        0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
        0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0,
        0, 0, 3, 0, 3, 0, 0, 3, 0, 3, 0, 0,
        0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0
    };

    byte alien_c_0[ALIEN_WIDTH * ALIEN_HEIGHT + 2] = {
        ALIEN_WIDTH, ALIEN_HEIGHT,
        0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 0,
        3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3,
        3, 3, 0, 3, 3, 3, 3, 3, 3, 0, 3, 3,
        0, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 0,
        0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0,
        0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0,
        0, 0, 0, 3, 0, 3, 3, 0, 3, 0, 0, 0,
        0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0
    };

    byte alien_c_1[ALIEN_WIDTH * ALIEN_HEIGHT + 2] = {
        ALIEN_WIDTH, ALIEN_HEIGHT,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 0,
        3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3,
        3, 3, 0, 3, 3, 3, 3, 3, 3, 0, 3, 3,
        0, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 0,
        0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0,
        0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
        0, 0, 3, 0, 3, 0, 0, 3, 0, 3, 0, 0
    };

    byte shield[SHIELD_WIDTH * SHIELD_HEIGHT + 2] = {
        SHIELD_WIDTH, SHIELD_HEIGHT,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0,
        0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0,
        0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0,
        0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
        0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3,
        0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0
    };

    byte shield_damage_sprite[SHIELD_DAMAGE_WIDTH * SHIELD_DAMAGE_HEIGHT + 2] = {
        SHIELD_DAMAGE_WIDTH, SHIELD_DAMAGE_HEIGHT,
        0, 3, 0, 3, 0,
        3, 0, 0, 0, 3,
        0, 0, 0, 0, 0,
        3, 0, 0, 0, 3,
        0, 3, 0, 3, 0
    };

    byte player_sprite[PLAYER_WIDTH * PLAYER_HEIGHT + 2] = {
        PLAYER_WIDTH, PLAYER_HEIGHT,
        0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0,
        0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0
    };

    byte player_hit_sprite[PLAYER_WIDTH * PLAYER_HEIGHT + 2] = {
        PLAYER_WIDTH, PLAYER_HEIGHT,
        0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 3, 0,
        0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0,
        0, 0, 3, 0, 3, 3, 0, 3, 3, 0, 0, 0, 0,
        0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0,
        3, 0, 0, 0, 3, 0, 3, 3, 0, 0, 3, 3, 3,
        3, 3, 3, 0, 0, 3, 0, 3, 0, 3, 3, 3, 3,
        0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 0
    };

    byte player_missile_sprite[PLAYER_MISSILE_WIDTH * PLAYER_MISSILE_HEIGHT + 2] = {
        PLAYER_MISSILE_WIDTH, PLAYER_MISSILE_HEIGHT,
        3,
        3,
        3,
        3,
        3,
        3,
        3
    };

    byte alien_missile_sprite[ALIEN_MISSILE_WIDTH * ALIEN_MISSILE_HEIGHT + 2] = {
        ALIEN_MISSILE_WIDTH, ALIEN_MISSILE_HEIGHT,
        0, 3, 0,
        3, 0, 0,
        0, 3, 0,
        0, 0, 3,
        0, 3, 0,
        3, 0, 0,
        0, 3, 0
    };

    byte explosion_sprite[EXPLOSION_WIDTH * EXPLOSION_HEIGHT + 2] = {
        EXPLOSION_WIDTH, EXPLOSION_HEIGHT,
        0, 0, 3, 0, 0, 0, 3, 0, 0, 3, 0, 0,
        3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 3,
        0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0,
        0, 0, 3, 0, 3, 0, 0, 3, 0, 0, 0, 0,
        0, 0, 0, 0, 3, 0, 0, 3, 0, 3, 0, 0,
        0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0,
        3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 3,
        0, 0, 3, 0, 0, 3, 0, 0, 0, 3, 0, 0
    };

    byte ufo_sprite[UFO_WIDTH * UFO_HEIGHT + 2] = {
        UFO_WIDTH, UFO_HEIGHT,
        0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0,
        0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0,
        0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
        3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3,
        0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
        0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0,
        0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0
    };
};

#endif
