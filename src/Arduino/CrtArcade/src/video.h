#ifndef VIDEO_H
#define VIDEO_H

extern byte *frame_buffers[];
extern volatile uint display_buffer_index;
extern volatile uint draw_buffer_index;
extern volatile byte *display_buffer;
extern volatile byte *draw_buffer;
extern volatile bool is_ready_to_flip;
extern volatile bool was_frame_skipped;

extern void setup_video();

void setup_frame_buffer(byte *buf);
void copy_lines_to_buffer(byte *buf, int &offset, const byte *line, int count);
void setup_pio();
void setup_dma(uint transfer_count);
void dma_handler();

#endif
