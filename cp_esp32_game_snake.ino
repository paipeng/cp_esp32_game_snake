#include "cp_struct.h"
#include "cp_gfx_display.h"
#include "cp_snake.h"
#include "cp_ps2_joystick.h"


CPSnake snake;
CPGFXDisplay display;
CPPS2Joystick joystick;
int game_over = 0;

void setup() {
  Serial.begin(115200);

  display.init();
  joystick.init();
  snake.init(display.get_size());

  game_over = 0;
  delay(5000); // 5 seconds
}


void loop() {
#if 1
  int event = joystick.readMove();
  if (event == BUTTON_DOWN) {
    Serial.println("reset");
    display.reset();
    snake.reset();
    display.update_draw(snake.get_points(), snake.get_random_point());
    delay(1000);
  } else {
    if (game_over == 0) {
      game_over = snake.update_snake(event);
      if (game_over == 0) {
        display.update_draw(snake.get_points(), snake.get_random_point());
      }
      delay(1000);
    } else {
      Serial.println("game_over");
      display.game_over();
      delay(5000);
    }

  }
#endif
}
