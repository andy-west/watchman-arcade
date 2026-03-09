#include <arduino.h>
#include "HighScoreStorage.h"

#ifdef SAVE_HIGH_SCORE

#include <EEPROM.h>

void HighScoreStorage::initialize() {
    EEPROM.begin(STORAGE_SIZE);
}

uint HighScoreStorage::load() {
    uint magic;
    EEPROM.get(MAGIC_ADDRESS, magic);

    if (magic != MAGIC) {
        return DEFAULT_HIGH_SCORE;
    }

    uint high_score;
    EEPROM.get(HIGH_SCORE_ADDRESS, high_score);

    return high_score;
}

void HighScoreStorage::save(uint high_score) {
    uint magic = MAGIC;
    EEPROM.put(MAGIC_ADDRESS, magic);
    EEPROM.put(HIGH_SCORE_ADDRESS, high_score);
    EEPROM.commit();
}

#else

void HighScoreStorage::initialize() {
}

uint HighScoreStorage::load() {
    return DEFAULT_HIGH_SCORE;
}

void HighScoreStorage::save(uint high_score) {
}

#endif
