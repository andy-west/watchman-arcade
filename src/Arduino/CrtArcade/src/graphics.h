#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "video/Video.h"
#include "assets/FontData.h"

class Graphics {
public:
    Graphics(Video* video);
    void clear_screen(byte color);
    void draw_screen(byte* screen_data);
    void draw_sprite(byte* sprite, int x, int y);
    void draw_text(const char* text, int x, int y);

private:
    Video* video;
    FontData font_data;
};

#endif
