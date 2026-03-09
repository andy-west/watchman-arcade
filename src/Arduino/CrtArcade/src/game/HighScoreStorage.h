#ifndef HIGH_SCORE_STORAGE_H
#define HIGH_SCORE_STORAGE_H

#define SAVE_HIGH_SCORE

class HighScoreStorage {
public:
    static const uint DEFAULT_HIGH_SCORE = 5000;

    static void initialize();
    static uint load();
    static void save(uint high_score);

private:
#ifdef SAVE_HIGH_SCORE
    static const uint MAGIC = 0x48534352;
    static const uint MAGIC_ADDRESS = 0;
    static const uint HIGH_SCORE_ADDRESS = sizeof(uint);
    static const uint STORAGE_SIZE = sizeof(uint) + sizeof(uint);
#endif
};

#endif
