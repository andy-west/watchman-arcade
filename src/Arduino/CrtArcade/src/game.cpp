#include <arduino.h>
#include "game.h"
#include "constants.h"
#include "input.h"
#include "video.h"
#include "graphics.h"
#include "title_screen_data.h"
#include "sprite_data.h"

uint game_mode;

uint level;
uint score;
uint player_x;
uint lives;
uint level_display_countdown;
uint alien_animation_countdown;
uint alien_animation_frame;
uint alien_direction;
uint game_ending_countdown;
bool is_game_ending;
uint game_over_countdown;
uint player_missile_x;
uint player_missile_y;
bool is_player_missile_active;
uint explosion_x;
uint explosion_y;
uint explosion_countdown;
bool is_explosion_visible;

byte shield_sprites[3][SHIELD_ARRAY_SIZE];

struct Alien aliens[ALIEN_COUNT];
struct Shield shields[SHIELD_COUNT];

UpdateFunction update_functions[] = {
  update_title,
  update_level_start,
  update_game,
  update_game_over
};

void update() {
  update_input();
  update_functions[game_mode]();
}

void update_title() {
  if (fire_pressed_this_frame) {
    game_mode = GAME_MODE_LEVEL_START;
    setup_game();
    setup_level();
  }
}

void setup_game() {
  level = 1;
  score = 0;
  lives = 3;
  game_over_countdown = GAME_OVER_TIME;
}

void setup_level() {
  player_x = PLAYER_BOUNDARY_SIDE;
  level_display_countdown = LEVEL_DISPLAY_TIME;
  alien_animation_countdown = ALIEN_ANIMATION_TIME;
  alien_animation_frame = 0;
  alien_direction = ALIEN_DIRECTION_RIGHT;
  is_game_ending = false;
  is_player_missile_active = false;
  is_explosion_visible = false;

  int i = 0;

  for (int y = 0; y < ALIEN_ROWS; y++) {
    uint points = (ALIEN_ROWS - y) * 10;

    for (int x = 0; x < ALIEN_COLUMNS; x++) {
      aliens[i] = {
        x * ALIEN_SPACING + ALIEN_MARGIN_SIDE,  // x
        y * ALIEN_SPACING + ALIEN_MARGIN_TOP,   // y
        y / 2,  // sprite_index
        true,   // exists
        points  // points
      };

      i++;
    }    
  }

  const int shield_positions[SHIELD_COUNT] = {
    SHIELD_MARGIN_SIDE,
    (SCREEN_WIDTH / 2) - (SHIELD_WIDTH / 2),
    SCREEN_WIDTH - SHIELD_WIDTH - SHIELD_MARGIN_SIDE
  };

  for (int i = 0; i < SHIELD_COUNT; i++) {
    shields[i].x = shield_positions[i];
    shields[i].y = SHIELD_Y;
    shields[i].exists = true;
    memcpy(shields[i].sprite, shield_sprite, SHIELD_ARRAY_SIZE);
  }
}

void update_level_start() {
  level_display_countdown--;

  if (level_display_countdown <= 0) {
    game_mode = GAME_MODE_PLAY_GAME;
  }
}

void update_game() {
  if (is_game_ending) {
    game_ending_countdown--;

    if (game_ending_countdown <= 0) {
      game_mode = GAME_MODE_GAME_OVER;
    }
  } else {
    if (left_pressed) {
      move_player_left();
    }

    if (right_pressed) {
      move_player_right();
    }

    update_player_missile();
    update_aliens();
    update_explosion();
  }
}

void move_player_left() {
  player_x--;

  if (player_x < PLAYER_BOUNDARY_SIDE) {
    player_x = PLAYER_BOUNDARY_SIDE;
  }
}

void move_player_right() {
  player_x++;

  const int max_player_x = SCREEN_WIDTH - PLAYER_WIDTH - PLAYER_BOUNDARY_SIDE;

  if (player_x > max_player_x) {
    player_x = max_player_x;
  }
}

void update_player_missile() {
  if (is_player_missile_active) {
    player_missile_y -= PLAYER_MISSILE_SPEED;

    if (player_missile_y <= CEILING_Y) {
      is_player_missile_active = false;
    }

    destroy_alien_if_hit();
  } else if (fire_pressed_this_frame) {
    player_missile_x = player_x + (PLAYER_WIDTH / 2);
    player_missile_y = PLAYER_Y - PLAYER_MISSILE_HEIGHT;
    is_player_missile_active = true;
  }
}

void destroy_alien_if_hit() {
  for (int i = 0; i < ALIEN_COUNT; i++) {
    if (aliens[i].exists) {
      // Check if the top pixel of the missile is inside the alien's bounding box (alien was hit).
      if (player_missile_x >= aliens[i].x && 
          player_missile_x < aliens[i].x + ALIEN_WIDTH &&
          player_missile_y >= aliens[i].y &&
          player_missile_y < aliens[i].y + ALIEN_HEIGHT) {    
            aliens[i].exists = false;
            score += aliens[i].points;
            is_player_missile_active = false;
            show_explosion(aliens[i].x, aliens[i].y);
            break;
          }
    }
  }
}

void show_explosion(int x, int y) {
  explosion_x = x;
  explosion_y = y;
  explosion_countdown = EXPLOSION_TIME;
  is_explosion_visible = true;
}

void update_aliens() {
  alien_animation_countdown--;

  if (alien_animation_countdown <= 0) {
    alien_animation_countdown += ALIEN_ANIMATION_TIME;
    alien_animation_frame = 1 - alien_animation_frame;
    move_aliens();
  }
}

void move_aliens() {
  uint new_alien_direction = alien_direction;

  for (int i = 0; i < ALIEN_COUNT; i++) {
    if (aliens[i].exists) {
      if (alien_direction == ALIEN_DIRECTION_RIGHT) {
        aliens[i].x += ALIEN_MOVE_SPEED;

        if (aliens[i].x >= SCREEN_WIDTH - ALIEN_WIDTH - ALIEN_MARGIN_SIDE) {
          new_alien_direction = ALIEN_DIRECTION_LEFT;
        }
      } else {
        aliens[i].x -= ALIEN_MOVE_SPEED;

        if (aliens[i].x <= ALIEN_MARGIN_SIDE) {
          new_alien_direction = ALIEN_DIRECTION_RIGHT;
        }
      }
    }
  }

  if (new_alien_direction != alien_direction) {
    alien_direction = new_alien_direction;
    move_aliens_down();
  }
}

void move_aliens_down() {
  for (int i = 0; i < ALIEN_COUNT; i++) {
    if (aliens[i].exists) {
      aliens[i].y += ALIEN_MOVE_DOWN_SPEED;

      // Remove shields if aliens get too low.
      if (aliens[i].y + ALIEN_HEIGHT >= SHIELD_Y) {
        for (int i = 0; i < SHIELD_COUNT; i++) {
          shields[i].exists = false;
        }
      }

      // Game ends if aliens reach bottom.
      if (aliens[i].y >= ALIEN_MAX_Y) {
        game_ending_countdown = GAME_ENDING_TIME;
        is_game_ending = true;
      }
    }
  }
}

void update_explosion() {
  if (is_explosion_visible) {
    explosion_countdown--;

    if (explosion_countdown <= 0) {
      is_explosion_visible = false;
    }
  }
}

void update_game_over() {
  game_over_countdown--;

  if (game_over_countdown <= 0) {
    game_mode = GAME_MODE_TITLE;
  }
}

DrawFunction draw_functions[] = {
  draw_title,
  draw_level_start,
  draw_game,
  draw_game_over
};

void draw() {
  draw_functions[game_mode]();
}

void draw_title() {
  draw_screen(title_screen_data);
  draw_text("PRESS FIRE TO START", 52, 190);
}

void draw_level_start() {
  clear_screen(COLOR_BLACK);
  draw_text("LEVEL", 96, 100);
  char level_string[5];
  itoa(level, level_string, 10);
  draw_text(level_string, 96 + (6 * FONT_SIZE), 100);
  draw_text("START", 96 + (1 * FONT_SIZE), 116);
}

void draw_game() {
  clear_screen(COLOR_BLACK);

  // Print six-digit score.
  draw_text("SCORE", 20, 20);
  char score_string[7];
  sprintf(score_string, "%06d", score);
  draw_text(score_string, 20 + (6 * FONT_SIZE), 20);

  // Print number of lives.
  uint lives_text_x = SCREEN_WIDTH - 20 - (7 * FONT_SIZE);
  draw_text("LIVES", lives_text_x, 20);
  char lives_string[2];
  itoa(lives, lives_string, 10);
  draw_text(lives_string, lives_text_x + (6 * FONT_SIZE), 20);

  for (int i = 0; i < ALIEN_COUNT; i++) {
    if (aliens[i].exists) {
      draw_sprite(alien_sprites[aliens[i].sprite_index][alien_animation_frame], aliens[i].x, aliens[i].y);
    }
  }

  for (int i = 0; i < SHIELD_COUNT; i++) {
    if (shields[i].exists) {
      draw_sprite(shields[i].sprite, shields[i].x, shields[i].y);
    }
  }

  draw_sprite(player_sprite, player_x, PLAYER_Y);

  if (is_player_missile_active) {
    draw_sprite(player_missile_sprite, player_missile_x, player_missile_y);
  }

  if (is_explosion_visible) {
    draw_sprite(explosion_sprite, explosion_x, explosion_y);
  }
}

void draw_game_over() {
  clear_screen(COLOR_BLACK);
  draw_text("GAME OVER", 96, 100);
}
