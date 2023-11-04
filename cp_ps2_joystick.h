#ifndef _CP_PS2_JOYSTICK_
#define _CP_PS2_JOYSTICK_
#include <Arduino.h>
#include "cp_struct.h"

#define VRX 32
#define VRY 33
#define BUTTON 35

#define BUTTON_LEFT 25
#define BUTTON_RIGHT 26
#define BUTTON_RESET 27

class CPPS2Joystick {
public:
  CPPS2Joystick();
  void init();
  ps2_joystick readAnalog();
  int readMove();
};

#endif
