#ifndef VIDEO_CONSTANTS_H
#define VIDEO_CONSTANTS_H

class VideoConstants {
public:
    static const uint BYTES_PER_LINE = 310;
    static const uint LINES_PER_FRAME = 263;
    static const uint BYTES_PER_FRAME = BYTES_PER_LINE * LINES_PER_FRAME;
    static constexpr float FRAMES_PER_SECOND = 59.94;
    static const uint BYTES_PER_SECOND = (int)(BYTES_PER_FRAME * FRAMES_PER_SECOND);

    static const uint VIDEO_START_LINE = 23;
    static const uint VIDEO_START_BYTE = 46;

    static const uint SCREEN_WIDTH = 256;
    static const uint SCREEN_HEIGHT = 240;

    static const uint COLOR_TRANSPARENT = 0;
    static const uint COLOR_BLACK = 1;
    static const uint COLOR_GRAY = 2;
    static const uint COLOR_WHITE = 3;

    static const uint COMPOSITE_VIDEO_PIN = 0;
};

#endif
