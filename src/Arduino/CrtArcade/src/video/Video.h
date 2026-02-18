#ifndef VIDEO_H
#define VIDEO_H

#include "VideoConstants.h"
#include "VideoLineData.h"

class Video {
public:
    uint dma_channel;

    byte* frame_buffers[2] = { frame_buffer_0, frame_buffer_1 };
    uint volatile display_buffer_index = 0;
    uint volatile draw_buffer_index = 1;
    byte volatile* display_buffer = frame_buffers[0];
    byte volatile* draw_buffer = frame_buffers[1];
    bool volatile is_buffer_ready_to_flip = true;
    bool volatile was_frame_skipped = false;

    Video();
    void wait_for_buffer_flip();

private:
    PIO pio;
    uint sm;

    byte frame_buffer_0[VideoConstants::BYTES_PER_FRAME];
    byte frame_buffer_1[VideoConstants::BYTES_PER_FRAME];

    VideoLineData line_data;

    void setup_frame_buffer(byte* buf);
    void copy_lines_to_buffer(byte* buf, int& offset, const byte* line, int count);
    void setup_pio();
    void setup_dma(uint transfer_count);
};

#endif
