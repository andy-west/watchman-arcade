#include <arduino.h>
#include <hardware/pwm.h>
#include <hardware/timer.h>
#include <hardware/irq.h>
#include "Audio.h"
#include "../game/SoundEffect.h"

static volatile AudioCommand pending_command;
static Audio* audio_instance = nullptr;

static volatile bool sample_ready = false;
static volatile byte next_sample = 128;

static void timer_isr() {
    hw_clear_bits(&timer_hw->intr, 1u << 0);

    pwm_set_gpio_level(AudioConstants::AUDIO_PIN, next_sample);
    sample_ready = true;

    timer_hw->alarm[0] = timer_hw->timerawl + (1000000 / AudioConstants::SAMPLE_RATE);
}

Audio::Audio() {
    audio_instance = this;
    sound_data = new SoundData();

    setup_pwm();
    setup_timer();
}

void Audio::setup_pwm() {
    gpio_set_function(AudioConstants::AUDIO_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(AudioConstants::AUDIO_PIN);

    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_wrap(&cfg, AudioConstants::PWM_WRAP);
    pwm_config_set_clkdiv(&cfg, 1.0f);
    pwm_init(slice, &cfg, true);

    pwm_set_gpio_level(AudioConstants::AUDIO_PIN, 128);
}

void Audio::setup_timer() {
    hw_set_bits(&timer_hw->inte, 1u << 0);
    irq_set_exclusive_handler(TIMER0_IRQ_0, timer_isr);
    irq_set_enabled(TIMER0_IRQ_0, true);

    timer_hw->alarm[0] = timer_hw->timerawl + (1000000 / AudioConstants::SAMPLE_RATE);
}

void Audio::update() {
    if (!sample_ready) {
        return;
    }

    sample_ready = false;

    process_command();

    int mix = 0;

    for (uint i = 0; i < AudioConstants::CHANNEL_COUNT; i++) {
        if (channels[i].is_active) {
            mix += (int)channels[i].data[channels[i].position] - 128;
            channels[i].position++;

            if (channels[i].position >= channels[i].size) {
                channels[i].is_active = false;
            }
        }
    }

    mix += 128;

    if (mix < 0) {
        mix = 0;
    }
    else if (mix > 255) {
        mix = 255;
    }

    next_sample = (byte)mix;
}

void Audio::process_command() {
    AudioCommandType type = pending_command.type;

    if (type == AudioCommandType::NONE) {
        return;
    }

    byte channel = pending_command.channel;
    byte sound_index = pending_command.sound_index;

    pending_command.type = AudioCommandType::NONE;

    if (channel >= AudioConstants::CHANNEL_COUNT) {
        return;
    }

    if (type == AudioCommandType::PLAY) {
        if (sound_index >= SoundData::SOUND_COUNT) {
            return;
        }

        channels[channel].data = sound_data->sounds[sound_index];
        channels[channel].size = sound_data->sound_sizes[sound_index];
        channels[channel].position = 0;
        channels[channel].is_active = true;
    }
    else if (type == AudioCommandType::STOP) {
        channels[channel].is_active = false;
    }
}

void Audio::play(SoundEffect effect, byte channel) {
    pending_command.sound_index = (byte)effect;
    pending_command.channel = channel;
    __dmb();
    pending_command.type = AudioCommandType::PLAY;
}

void Audio::stop(byte channel) {
    pending_command.channel = channel;
    __dmb();
    pending_command.type = AudioCommandType::STOP;
}
