#include "cp_ps2_joystick.h"


CPPS2Joystick::CPPS2Joystick() {
  // init joystick
  
}

void CPPS2Joystick::init() {
  pinMode(BUTTON, INPUT);

  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
}

ps2_joystick CPPS2Joystick::readAnalog() {
  ps2_joystick joystick;
#if 0
  // x,y: 0-4095 (right - left; center 2877)
  // k: 1 unpressed; 0: pressed
  joystick.x = analogRead(VRX);
  joystick.y = analogRead(VRY);
  joystick.k = digitalRead(BUTTON);  
#else
  joystick.left = 1 - digitalRead(BUTTON_LEFT);
  joystick.right = 1 - digitalRead(BUTTON_RIGHT);
  joystick.k = 1 - digitalRead(BUTTON_RESET);
#endif
#if 1
  Serial.print("Joystick: ");
  Serial.printf("x: %4d y: %4d button: %d left: %d right: %d", joystick.x, joystick.y, joystick.k, joystick.left, joystick.right);
  Serial.println("");
#endif
  return joystick; 
}

int CPPS2Joystick::readMove() {
  ps2_joystick joystick = readAnalog();
  if (joystick.k == 1) {
    return BUTTON_DOWN;
  }
#if 0  
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
#else
  if (joystick.left == 1) {
    return MOVE_LEFT;
  } else if (joystick.right == 1) {
    return MOVE_RIGHT;
  }
#endif
}