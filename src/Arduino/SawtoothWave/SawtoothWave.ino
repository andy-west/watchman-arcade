// Pins represent a 5-bit number in the range of 0 to 31 (2^5 - 1).
const int NUM_PINS = 5;
const int pins[NUM_PINS] = { 4, 3, 2, 1, 0 };

void setup() {
  initializeOutputPins();
}

void initializeOutputPins() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }
}

void loop() {

  /*

    Output values in a continuous loop from 0-31 to form a sawtooth pattern similar to this:

     /| /| /| /| /| /| /| /|
    / |/ |/ |/ |/ |/ |/ |/ |

  */

  for (int i = 0; i < 32; i++) {
    writeValueToPins(i);  
    delay(10);
  }
}

void writeValueToPins(int value) {
    for (int bit = 0; bit < NUM_PINS; bit++) {
        int bitValue = value & (1 << bit);
        digitalWrite(pins[bit], bitValue);
    }
}
