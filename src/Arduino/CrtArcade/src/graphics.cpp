#include <arduino.h>
#include "constants.h"
#include "video.h"
#include "font_data.h"

void clear_screen(byte color) {
    uint buffer_pos = VIDEO_START_LINE * BYTES_PER_LINE + VIDEO_START_BYTE;

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        memset((void*)&draw_buffer[buffer_pos], color, SCREEN_WIDTH);
        buffer_pos += BYTES_PER_LINE;
    }
}

void draw_screen(byte* screen_data) {
    uint buffer_pos = VIDEO_START_LINE * BYTES_PER_LINE + VIDEO_START_BYTE;

    for (int sy = 0; sy < SCREEN_HEIGHT; sy++) {
        byte* src = &screen_data[sy * SCREEN_WIDTH];
        byte* dst = (byte*)&draw_buffer[buffer_pos];

        memcpy(dst, src, SCREEN_WIDTH);

        buffer_pos += BYTES_PER_LINE;
    }
}

void draw_sprite(byte* sprite, int x, int y) {
    byte width = sprite[0];
    byte height = sprite[1];
    byte* sprite_data = &sprite[2];

    uint buffer_pos = (y + VIDEO_START_LINE) * BYTES_PER_LINE + (x + VIDEO_START_BYTE);

    for (int sy = 0; sy < height; sy++) {
        int sprite_pos = sy * width;

        for (int sx = 0; sx < width; sx++) {
            byte color = sprite_data[sprite_pos + sx];

            if (color != COLOR_TRANSPARENT) {
                draw_buffer[buffer_pos + sx] = color;
            }
        }

        buffer_pos += BYTES_PER_LINE;
    }
}

void draw_text(const char* text, int x, int y) {
    int char_x = x;

    while (*text) {
        byte* char_data = font[(byte)*text];

        if (char_data) {
            uint buffer_pos = (y + VIDEO_START_LINE) * BYTES_PER_LINE + (char_x + VIDEO_START_BYTE);

            // Copy each row of the character data to the buffer.
            for (int row = 0; row < 8; row++) {
                byte* src = &char_data[row * 8];
                byte* dst = (byte*)&draw_buffer[buffer_pos];

                memcpy(dst, src, 8);

                buffer_pos += BYTES_PER_LINE;
            }
        }

        // Move cursor to the next character position (8 pixels to the right).
        char_x += 8;

        // Move to the next character in the string.
        text++;
    }
}
