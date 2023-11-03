#include "cp_ps2_joystick.h"


CPPS2Joystick::CPPS2Joystick() {
  // init joystick
  
}

void CPPS2Joystick::init() {
  pinMode(BUTTON, INPUT);
}

ps2_joystick CPPS2Joystick::readAnalog() {
  // x,y: 0-4095 (right - left; center 2877)
  // k: 1 unpressed; 0: pressed
  ps2_joystick joystick;
  joystick.x = analogRead(VRX);
  joystick.y = analogRead(VRY);
  joystick.k = digitalRead(BUTTON);  
#if 1
  Serial.print("Joystick: ");
  Serial.printf("x: %4d y: %4d button: %d", joystick.x, joystick.y, joystick.k);
  Serial.println("");
#endif
  return joystick; 
}

int CPPS2Joystick::readMove() {
  ps2_joystick joystick = readAnalog();
  if (joystick.k == 1) {
    return BUTTON_DOWN;
  }
  
  if (joystick.x > 3000) {
    return MOVE_LEFT;
  } else if (joystick.x < 500) {
    return MOVE_RIGHT;
  } else if (joystick.y > 4000) {
    return MOVE_UP;
  } else if (joystick.y < 500) {
    return MOVE_DOWN;
  } else {
    return MOVE_NONE;
  }
}