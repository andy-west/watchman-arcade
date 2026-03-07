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
    byte volume = 255;
    bool loop = false;
};

struct CommandQueue {
    static const uint CAPACITY = 8;
    volatile AudioCommand commands[CAPACITY];
    volatile uint head = 0;
    volatile uint tail = 0;

    bool enqueue(const AudioCommand& cmd) {
        uint next_head = (head + 1) % CAPACITY;

        if (next_head == tail) {
            return false;
        }

        commands[head].sound_index = cmd.sound_index;
        commands[head].channel = cmd.channel;
        commands[head].volume = cmd.volume;
        commands[head].loop = cmd.loop;
        commands[head].type = cmd.type;
        __dmb();
        head = next_head;
        return true;
    }

    bool dequeue(AudioCommand& cmd) {
        if (tail == head) {
            return false;
        }

        cmd.type = commands[tail].type;
        cmd.sound_index = commands[tail].sound_index;
        cmd.channel = commands[tail].channel;
        cmd.volume = commands[tail].volume;
        cmd.loop = commands[tail].loop;
        __dmb();
        tail = (tail + 1) % CAPACITY;
        return true;
    }
};

#endif
