#include "cp_ps2_joystick.h"


CPPS2Joystick::CPPS2Joystick() {
  // init joystick
  pinMode(BUTTON, INPUT);
}
ps2_joystick CPPS2Joystick::readAnalog() {
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