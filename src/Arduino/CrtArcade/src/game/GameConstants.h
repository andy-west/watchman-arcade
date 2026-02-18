#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include "../video/VideoConstants.h"

class GameConstants {
public:
    static const uint CEILING_Y = 40;
    static const uint FLOOR_Y = VideoConstants::SCREEN_HEIGHT - 40;

    static const uint ALIEN_ROWS = 6;
    static const uint ALIEN_COLUMNS = 10;
    static const uint ALIEN_COUNT = ALIEN_ROWS * ALIEN_COLUMNS;

    static const uint SHIELD_COUNT = 3;
};

#endif
