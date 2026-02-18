#include "src/Debug.h"
#include "src/video/Video.h"
#include "src/Graphics.h"
#include "src/game/game.h"

Video* video = nullptr;
Graphics* graphics = nullptr;
Game* game = nullptr;

void setup() {
    Debug::initialize();

    video = new Video();
    graphics = new Graphics(video);
    game = new Game(graphics);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    video->wait_for_buffer_flip();

    game->update();
    game->draw();

    video->is_buffer_ready_to_flip = true;
}
