#include "cp_struct.h"
#include "cp_gfx_display.h"
#include "cp_snake.h"

#define VRX 32
#define VRY 33
#define BUTTON 35

CPSnake snake;
CPGFXDisplay display;

ps2_joystick readAnalog() {
  // x,y: 0-4095 (right - left; center 2877)
  // k: 1 unpressed; 0: pressed
  ps2_joystick joystick;
  joystick.x = analogRead(VRX);
  joystick.y = analogRead(VRY);
  joystick.k = digitalRead(BUTTON);  
#if DEBUG
  Serial.print("Joystick: ");
  Serial.printf("x: %4d y: %4d button: %d", joystick.x, joystick.y, joystick.k);
  Serial.println("");
#endif
  return joystick; 
}

void setup() {
  Serial.begin(115200);
  // init joystick
  pinMode(BUTTON, INPUT);

  display.init();
  snake.init(display.get_size());

  delay(1000); // 5 seconds
}


void loop() {
  ps2_joystick joystick = readAnalog();
  snake.update_joystick(joystick);
  display.update_draw(snake.get_points(), snake.get_random_point());
  delay(10);
}
