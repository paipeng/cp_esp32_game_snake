#include "cp_snake.h"

CPSnake::CPSnake(): spoints(NULL), r_point((cp_point){0,0}), move_direction(MOVE_UP), eat(false), screen_size((cp_size) {0, 0}) {
  
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

  reset();
}

void CPSnake::reset() {
  if (spoints) {
    free_snake_point_array(spoints);
  }
  spoints = init_snake_point_array();
  spoints->position.x = screen_size.width/2;
  spoints->position.y = screen_size.height/2;

  random_point();
}

void CPSnake::random_point() {
  r_point.x = random(screen_size.width)/20*20;
  r_point.y = random(screen_size.height)/20*20;
}

cp_point CPSnake::get_random_point()  {
  return r_point;
}

int CPSnake::update_snake(int move_dir) {
#if 0  
  if (move_dir != MOVE_NONE && move_dir != BUTTON_DOWN) {
    switch (move_direction) {
      case MOVE_UP:
      case MOVE_DOWN:
        if (move_dir == MOVE_RIGHT || move_dir == MOVE_LEFT) {
          move_direction = move_dir;
        }
        break;
      case MOVE_RIGHT:
      case MOVE_LEFT:
        if (move_dir == MOVE_UP || move_dir == MOVE_DOWN) {
          move_direction = move_dir;
        }
        break;
    }
  }
#else
  switch (move_direction) {
    case MOVE_UP:
      move_direction = move_dir;
      break;
    case MOVE_DOWN:
      if (move_dir == MOVE_RIGHT) {
        move_direction = MOVE_LEFT;
      } else if (move_dir == MOVE_LEFT) {
        move_direction = MOVE_RIGHT;
      }
      break;
    case MOVE_RIGHT:
      if (move_dir == MOVE_RIGHT) {
        move_direction = MOVE_DOWN;
      } else if (move_dir == MOVE_LEFT) {
        move_direction = MOVE_UP;
      }
      break;
    case MOVE_LEFT:
      if (move_dir == MOVE_RIGHT) {
        move_direction = MOVE_UP;
      } else if (move_dir == MOVE_LEFT) {
        move_direction = MOVE_DOWN;
      }
      break;
  }
#endif
  snake_point *current_point = spoints;
  // get last point
  cp_point last_point;
  while (current_point->next != NULL) {
    current_point = current_point->next;
  }

  last_point = current_point->position;

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
    return 1;
  } else if (spoints->position.x >= screen_size.width) {
    spoints->position.x = screen_size.width - SNAKE_SIZE;
    return 1;
  }

  if (spoints->position.y < 0) {
    spoints->position.y = 0;
    return 1;
  } else if (spoints->position.y >= screen_size.height) {
    spoints->position.y = screen_size.height - SNAKE_SIZE;
    return 1;
  }

  eat = check_eat();
  if (eat) {
    Serial.println("eat food!");
    snake_point_array_push(spoints, last_point);
    random_point();
  } else {
  }
  return 0;
}


