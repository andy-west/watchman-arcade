#include <arduino.h>
#include "Debug.h"

void Debug::initialize() {
    #ifdef DEBUG
        Serial.begin(9600);

        while (!Serial) {
            delay(10);
        }
    #endif
}
