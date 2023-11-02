#ifndef _CP_SNAKE_
#define _CP_SNAKE_
#include <Arduino.h>
#include "cp_struct.h"


// 0: right; 1: bottom; 2: left; 3: top
#define MOVE_UP 0
#define MOVE_RIGHT 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3



class CPSnake {
public:
  CPSnake();
  
public:  
  bool is_eat();
  snake_point* get_points();
  cp_point get_random_point();

  void init(cp_size screen_size);
  void random_point();
  void update_snake(int dir);
  void move_snake();
  void update_joystick(ps2_joystick joystick);
private:
  bool check_eat();

private:
  snake_point *spoints;
  cp_point r_point;
  int move_direction;
  bool eat;
  cp_size screen_size;
};
#endif