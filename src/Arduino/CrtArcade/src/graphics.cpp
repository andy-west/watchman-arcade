#include <arduino.h>
#include "Graphics.h"
#include "video/VideoConstants.h"

Graphics::Graphics(Video* video) {
    this->video = video;
}

void Graphics::clear_screen(byte color) {
    uint buffer_pos = VideoConstants::VIDEO_START_LINE * VideoConstants::BYTES_PER_LINE
        + VideoConstants::VIDEO_START_BYTE;

    for (int y = 0; y < VideoConstants::SCREEN_HEIGHT; y++) {
        memset((void*)&video->draw_buffer[buffer_pos], color, VideoConstants::SCREEN_WIDTH);
        buffer_pos += VideoConstants::BYTES_PER_LINE;
    }
}

void Graphics::draw_screen(byte* screen_data) {
    uint buffer_pos = VideoConstants::VIDEO_START_LINE * VideoConstants::BYTES_PER_LINE
        + VideoConstants::VIDEO_START_BYTE;

    for (int sy = 0; sy < VideoConstants::SCREEN_HEIGHT; sy++) {
        byte* src = &screen_data[sy * VideoConstants::SCREEN_WIDTH];
        byte* dst = (byte*)&video->draw_buffer[buffer_pos];

        memcpy(dst, src, VideoConstants::SCREEN_WIDTH);

        buffer_pos += VideoConstants::BYTES_PER_LINE;
    }
}

void Graphics::draw_sprite(byte* sprite, int x, int y) {
    byte width = sprite[0];
    byte height = sprite[1];
    byte* sprite_data = &sprite[2];

    uint buffer_pos = (y + VideoConstants::VIDEO_START_LINE) * VideoConstants::BYTES_PER_LINE
        + (x + VideoConstants::VIDEO_START_BYTE);

    for (int sy = 0; sy < height; sy++) {
        int sprite_pos = sy * width;

        for (int sx = 0; sx < width; sx++) {
            byte color = sprite_data[sprite_pos + sx];

            if (color != VideoConstants::COLOR_TRANSPARENT) {
                video->draw_buffer[buffer_pos + sx] = color;
            }
        }

        buffer_pos += VideoConstants::BYTES_PER_LINE;
    }
}

void Graphics::draw_text(const char* text, int x, int y) {
    int char_x = x;

    while (*text) {
        byte* char_data = font_data.font[(byte)*text];

        if (char_data) {
            uint buffer_pos = (y + VideoConstants::VIDEO_START_LINE) * VideoConstants::BYTES_PER_LINE
                + (char_x + VideoConstants::VIDEO_START_BYTE);

            // Copy each row of the character data to the buffer.
            for (int row = 0; row < GlobalConstants::FONT_HEIGHT; row++) {
                byte* src = &char_data[row * GlobalConstants::FONT_WIDTH];
                byte* dst = (byte*)&video->draw_buffer[buffer_pos];

                memcpy(dst, src, GlobalConstants::FONT_WIDTH);

                buffer_pos += VideoConstants::BYTES_PER_LINE;
            }
        }

        // Move cursor to the next character position (8 pixels to the right).
        char_x += GlobalConstants::FONT_WIDTH;

        // Move to the next character in the string.
        text++;
    }
}
