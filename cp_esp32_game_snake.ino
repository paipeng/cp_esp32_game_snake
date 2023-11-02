#include "cp_struct.h"
#include "cp_gfx_display.h"
#include "cp_snake.h"
#include "cp_ps2_joystick.h"


CPSnake snake;
CPGFXDisplay display;
CPPS2Joystick joystick;


void setup() {
  Serial.begin(115200);

  display.init();
  snake.init(display.get_size());

  delay(1000); // 5 seconds
}


void loop() {
  snake.update_joystick(joystick.readAnalog());
  display.update_draw(snake.get_points(), snake.get_random_point());
  delay(10);
}
