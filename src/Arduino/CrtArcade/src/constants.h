#ifndef CONSTANTS_H
#define CONSTANTS_H

/*
    Horizontal sync pulse (sync tip) 4.7us / 23 bytes / 4.71us actual
    Back porch 4.7us / 23 bytes / 4.71us actual
    Active video 52.6us / 256 bytes / 52.42us actual
    Front porch 1.5us / 8 bytes / 1.64us actual
    -----------------------------------------
    Total 63.5us / 310 bytes / 63.48us actual

    Equalization pulse 2.35us/ 11 bytes / 2.25us actual
    Start of second eq pulse 31.75us / 155 bytes / 31.74us actual

    0.2048us / byte

    310 bytes per line
    310 x 263 lines = 81,530 bytes per frame
    81,530 x 59.94 fps = 4,886,908 bytes per second
    125,000,000 clock frequency / 4,886,908 = 25.58

    One frame:
    3 lines equalization pulses
    3 lines vsync
    3 lines equalization pulses
    14 blank lines
    240 lines video

    Active video:
    Lines 23-262
    Bytes 46-301
*/

const uint BYTES_PER_LINE = 310;
const uint LINES_PER_FRAME = 263;
const uint BYTES_PER_FRAME = BYTES_PER_LINE * LINES_PER_FRAME;
const float FRAMES_PER_SECOND = 59.94;
const uint BYTES_PER_SECOND = (int)(BYTES_PER_FRAME * FRAMES_PER_SECOND);

const uint VIDEO_START_LINE = 23;
const uint VIDEO_START_BYTE = 46;

const uint SCREEN_WIDTH = 256;
const uint SCREEN_HEIGHT = 240;

const uint COLOR_TRANSPARENT = 0;
const uint COLOR_BLACK = 1;
const uint COLOR_GRAY = 2;
const uint COLOR_WHITE = 3;

const uint SYNC_PIN = 0;
const uint DATA_PIN = 1;

const uint LEFT_PIN = 13;
const uint RIGHT_PIN = 14;
const uint FIRE_PIN = 15;

const uint FONT_SIZE = 8;

#endif
