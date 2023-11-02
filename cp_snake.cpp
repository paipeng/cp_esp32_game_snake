#include "cp_snake.h"

CPSnake::CPSnake(): spoints(NULL), r_point((cp_point){0,0}), move_direction(MOVE_UP), eat(false), screen_size((cp_size) {0, 0}) {
  spoints = init_snake_point_array();
}


bool CPSnake::check_eat() {
  return (r_point.x == spoints->position.x && r_point.y == spoints->position.y);
}

bool CPSnake::is_eat() {
  return eat;
}

snake_point* CPSnake::get_points() {
  return spoints;
}


void CPSnake::init(cp_size screen_size) {
  this->screen_size = screen_size;

  spoints->position.x = screen_size.width/2;
  spoints->position.y = screen_size.height/2;

  random_point();
}


void CPSnake::random_point() {
  r_point.x = random(screen_size.height)/20*20;
  r_point.y = random(screen_size.width)/20*20;
}

cp_point CPSnake::get_random_point()  {
  return r_point;
}

void CPSnake::update_snake() {
  snake_point *current_point = spoints;
  // get last point
  while (current_point->next != NULL) {
    current_point = current_point->next;
  }

  while (current_point->pre != NULL) {    
    current_point->position.x = current_point->pre->position.x;
    current_point->position.y = current_point->pre->position.y;
    current_point = current_point->pre;
  }

  if (move_direction == MOVE_UP) {
    spoints->position.y-=SNAKE_SIZE;
  } else if (move_direction == MOVE_RIGHT) {
    spoints->position.x+=SNAKE_SIZE;
  } else if (move_direction == MOVE_DOWN) {
    spoints->position.y+=SNAKE_SIZE;
  } else if (move_direction == MOVE_LEFT) {
    spoints->position.x-=SNAKE_SIZE;
  }

  if (spoints->position.x < 0) {
    spoints->position.x = 0;
  } else if (spoints->position.x >= screen_size.width) {
    spoints->position.x = screen_size.width - SNAKE_SIZE;
  }

  if (spoints->position.y < 0) {
    spoints->position.y = 0;
  } else if (spoints->position.y >= screen_size.height) {
    spoints->position.y = screen_size.height - SNAKE_SIZE;
  }
}

void CPSnake::update_joystick(ps2_joystick joystick) {
  if (joystick.x > 3000) {
    move_direction = MOVE_LEFT;
  } else if (joystick.x < 500) {
    move_direction = MOVE_RIGHT;
  } else if (joystick.y > 4000) {
    move_direction = MOVE_UP;
  } else if (joystick.y < 500) {
    move_direction = MOVE_DOWN;
  }
  update_snake();
}

