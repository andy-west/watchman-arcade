#include <arduino.h>
#include "video.h"
#include "constants.h"
#include "video_line_data.h"
#include "composite_video.pio.h"

PIO pio;
uint sm;
uint dma_channel;

byte frame_buffer_0[BYTES_PER_FRAME];
byte frame_buffer_1[BYTES_PER_FRAME];

byte* frame_buffers[] = { frame_buffer_0, frame_buffer_1 };
uint volatile display_buffer_index = 0;
uint volatile draw_buffer_index = 1;
byte volatile* display_buffer = frame_buffers[0];
byte volatile* draw_buffer = frame_buffers[1];
bool volatile is_ready_to_flip = true;
bool volatile was_frame_skipped = false;

void setup_video() {
    setup_frame_buffer(frame_buffer_0);
    setup_frame_buffer(frame_buffer_1);
    setup_pio();
    setup_dma(BYTES_PER_FRAME);
}

void setup_frame_buffer(byte* buf) {
    int offset = 0;

    copy_lines_to_buffer(buf, offset, equ_pulse_line, 3);
    copy_lines_to_buffer(buf, offset, vsync_line, 3);
    copy_lines_to_buffer(buf, offset, equ_pulse_line, 3);
    copy_lines_to_buffer(buf, offset, blank_line, 14);
    copy_lines_to_buffer(buf, offset, active_line, 240);
}

void copy_lines_to_buffer(byte* buf, int& offset, const byte* line, int count) {
    for (int i = 0; i < count; i++) {
        memcpy(buf + offset, line, BYTES_PER_LINE);
        offset += BYTES_PER_LINE;
    }
}

void setup_pio() {
    uint offset;
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&composite_video_program, &pio, &sm, &offset, SYNC_PIN, 2, true);
    hard_assert(success);
    composite_video_program_init(pio, sm, offset, SYNC_PIN, 2, BYTES_PER_SECOND);
}

void setup_dma(uint transfer_count) {
    dma_channel = dma_claim_unused_channel(true);
    dma_channel_config cfg = dma_channel_get_default_config(dma_channel);
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
    channel_config_set_read_increment(&cfg, true);
    channel_config_set_dreq(&cfg, pio_get_dreq(pio, sm, true));

    dma_channel_configure(
        dma_channel,
        &cfg,
        &pio->txf[sm],  // write_addr
        NULL,           // read_addr
        transfer_count,
        false           // trigger
    );

    // Configure DMA interrupt.
    dma_channel_set_irq0_enabled(dma_channel, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);

    // Call handler to set read address and trigger DMA.
    dma_handler();
}

void dma_handler() {
    // Clear the interrupt request.
    dma_hw->ints0 = 1u << dma_channel;

    if (is_ready_to_flip) {
        display_buffer_index = 1 - display_buffer_index;
        display_buffer = frame_buffers[display_buffer_index];
        draw_buffer_index = 1 - display_buffer_index;
        draw_buffer = frame_buffers[draw_buffer_index];
        is_ready_to_flip = false;
    }
    else {
        was_frame_skipped = true;
    }

    // Set read address and start transfer immediately.
    dma_channel_set_read_addr(dma_channel, display_buffer, true);
}
