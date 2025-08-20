//#define DEBUG

#ifdef DEBUG
  #define debug_print(...) Serial.print(__VA_ARGS__)
  #define debug_println(...) Serial.println(__VA_ARGS__)
#else
  #define debug_print(...)
  #define debug_println(...)
#endif

#include "src/constants.h"
#include "src/input.h"
#include "src/video.h"
#include "src/game.h"

void setup() {

#ifdef DEBUG
  Serial.begin(9600);

  while (!Serial) {
    delay(10);
  }
#endif

  setup_input();
  setup_video();

  game_mode = GAME_MODE_TITLE;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // Wait until the buffer is flipped from the previous frame.
  while (is_ready_to_flip);

  if (was_frame_skipped) {
    debug_println("Frame skipped.");
  }

  update();
  draw();

  is_ready_to_flip = true;
}
