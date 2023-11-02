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
  joystick.init();
  snake.init(display.get_size());

  delay(5000); // 5 seconds
}


void loop() {
#if 1
  snake.update_joystick(joystick.readAnalog());
  display.update_draw(snake.get_points(), snake.get_random_point());
#endif
  delay(1000);
}
