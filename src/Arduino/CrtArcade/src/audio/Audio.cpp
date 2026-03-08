#include <arduino.h>
#include <hardware/pwm.h>
#include <hardware/timer.h>
#include <hardware/irq.h>
#include "Audio.h"
#include "../game/SoundEffect.h"

static CommandQueue command_queue;
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

    process_commands();

    float mix = 0.0f;

    for (uint i = 0; i < AudioConstants::CHANNEL_COUNT; i++) {
        if (channels[i].is_active) {
            float sample = (float)channels[i].data[channels[i].position] - 128.0f;
            sample *= channels[i].volume / 255.0f;
            mix += sample;
            channels[i].position++;

            if (channels[i].position >= channels[i].size) {
                if (channels[i].loop) {
                    channels[i].position = 0;
                }
                else {
                    channels[i].is_active = false;
                }
            }
        }
    }

    mix += 128.0f;

    if (mix < 0.0f) {
        mix = 0.0f;
    }
    else if (mix > 255.0f) {
        mix = 255.0f;
    }

    next_sample = (byte)mix;
}

void Audio::process_commands() {
    AudioCommand cmd;

    while (command_queue.dequeue(cmd)) {
        if (cmd.channel >= AudioConstants::CHANNEL_COUNT) {
            continue;
        }

        if (cmd.type == AudioCommandType::PLAY) {
            if (cmd.sound_index >= SoundData::SOUND_COUNT) {
                continue;
            }

            channels[cmd.channel].data = sound_data->sounds[cmd.sound_index];
            channels[cmd.channel].size = sound_data->sound_sizes[cmd.sound_index];
            channels[cmd.channel].position = 0;
            channels[cmd.channel].volume = cmd.volume;
            channels[cmd.channel].loop = cmd.loop;
            channels[cmd.channel].is_active = true;
        }
        else if (cmd.type == AudioCommandType::STOP) {
            channels[cmd.channel].is_active = false;
        }
    }
}

void Audio::play(SoundEffect effect, byte channel, byte volume, bool loop) {
    AudioCommand cmd;
    cmd.type = AudioCommandType::PLAY;
    cmd.sound_index = (byte)effect;
    cmd.channel = channel;
    cmd.volume = volume;
    cmd.loop = loop;
    command_queue.enqueue(cmd);
}

void Audio::stop(byte channel) {
    AudioCommand cmd;
    cmd.type = AudioCommandType::STOP;
    cmd.channel = channel;
    command_queue.enqueue(cmd);
}

void Audio::stop_all() {
    for (uint i = 0; i < AudioConstants::CHANNEL_COUNT; i++) {
        stop(i);
    }
}
