#include <arduino.h>
#include "Video.h"
#include "../Debug.h"
#include "composite_video.pio.h"

Video* instance = nullptr;
void dma_handler();

Video::Video() {
    instance = this;

    setup_frame_buffer(frame_buffer_0);
    setup_frame_buffer(frame_buffer_1);
    setup_pio();
    setup_dma(VideoConstants::BYTES_PER_FRAME);
}

void Video::wait_for_buffer_flip() {
    while (is_buffer_ready_to_flip);

    if (was_frame_skipped) {
        debug_println("Frame skipped.");
    }
}

void Video::setup_frame_buffer(byte* buf) {
    int offset = 0;

    copy_lines_to_buffer(buf, offset, line_data.equ_pulse_line, 3);
    copy_lines_to_buffer(buf, offset, line_data.vsync_line, 3);
    copy_lines_to_buffer(buf, offset, line_data.equ_pulse_line, 3);
    copy_lines_to_buffer(buf, offset, line_data.blank_line, 14);
    copy_lines_to_buffer(buf, offset, line_data.active_line, 240);
}

void Video::copy_lines_to_buffer(byte* buf, int& offset, const byte* line, int count) {
    for (int i = 0; i < count; i++) {
        memcpy(buf + offset, line, VideoConstants::BYTES_PER_LINE);
        offset += VideoConstants::BYTES_PER_LINE;
    }
}

void Video::setup_pio() {
    uint offset;
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(
        &composite_video_program, &pio, &sm, &offset, VideoConstants::COMPOSITE_VIDEO_PIN, 2, true);
    hard_assert(success);
    composite_video_program_init(pio, sm, offset, VideoConstants::COMPOSITE_VIDEO_PIN, 2, VideoConstants::BYTES_PER_SECOND);
}

void Video::setup_dma(uint transfer_count) {
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
    dma_hw->ints0 = 1u << instance->dma_channel;

    if (instance->is_buffer_ready_to_flip) {
        instance->display_buffer_index = 1 - instance->display_buffer_index;
        instance->display_buffer = instance->frame_buffers[instance->display_buffer_index];
        instance->draw_buffer_index = 1 - instance->display_buffer_index;
        instance->draw_buffer = instance->frame_buffers[instance->draw_buffer_index];
        instance->is_buffer_ready_to_flip = false;
    }
    else {
        instance->was_frame_skipped = true;
    }

    // Set read address and start transfer immediately.
    dma_channel_set_read_addr(instance->dma_channel, instance->display_buffer, true);
}
