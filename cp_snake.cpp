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


void CPSnake::update_snake(int dir) {
  
  eat = check_eat();
  if (eat) {
    snake_point_array_push_at_begin(spoints, r_point);
    random_point();
  } else {
    move_snake();
    // random
  }
  //tft.drawRect(r_point.x, r_point.y, SNAKE_SIZE, SNAKE_SIZE, ILI9341_RED);
  //draw_snake();
}

void CPSnake::move_snake() {
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
}

void CPSnake::update_joystick(ps2_joystick joystick) {
  int move_x = 0;
  int move_y = 0;
  if (joystick.x > 3500) {
    move_x = -1;
  } else if (joystick.x < 1000) {
    move_x = 1;
  }
  if (joystick.y > 3500) {
    move_y = -1;
  } else if (joystick.y < 1000) {
    move_y = 1;
  }


  if (move_x == -1) {
    move_direction = MOVE_LEFT;
  } else if (move_x == 1) {
    move_direction = MOVE_RIGHT;
  } else if (move_y == -1) {
    move_direction = MOVE_UP;
  } else if (move_y == 1) {
    move_direction = MOVE_DOWN;
  }

  move_snake();
}

