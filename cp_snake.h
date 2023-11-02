#ifndef _CP_SNAKE_
#define _CP_SNAKE_
#include <Arduino.h>
#include "cp_struct.h"





class CPSnake {
public:
  CPSnake();
  
public:  
  bool is_eat();
  snake_point* get_points();
  cp_point get_random_point();

  void init(cp_size screen_size);
  void random_point();
  void update_snake();
  void update_move(int move_dir);
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