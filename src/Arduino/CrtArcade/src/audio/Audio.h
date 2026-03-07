#ifndef AUDIO_H
#define AUDIO_H

#include "AudioConstants.h"
#include "AudioCommand.h"
#include "../assets/SoundData.h"
#include "../game/SoundEffect.h"

class Audio {
public:
    Audio();
    void update();

    static void play(SoundEffect effect, byte channel, byte volume = 128, bool loop = false);
    static void stop(byte channel);

private:
    struct Channel {
        byte* data = nullptr;
        uint size = 0;
        uint position = 0;
        bool is_active = false;
        byte volume = 255;
        bool loop = false;
    };

    SoundData* sound_data;
    Channel channels[AudioConstants::CHANNEL_COUNT];

    void process_commands();
    void setup_pwm();
    void setup_timer();
};

#endif
