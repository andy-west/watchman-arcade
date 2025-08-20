#ifndef GRAPHICS_H
#define GRAPHICS_H

extern void clear_screen(byte color);
extern void draw_screen(byte* screen_data);
extern void draw_sprite(byte* sprite, int x, int y);
extern void draw_text(const char* text, int x, int y);

#endif
