#ifndef AUDIO_COMMAND_H
#define AUDIO_COMMAND_H

enum class AudioCommandType : byte {
    NONE,
    PLAY,
    STOP
};

struct AudioCommand {
    AudioCommandType type = AudioCommandType::NONE;
    byte sound_index = 0;
    byte channel = 0;
};

#endif
