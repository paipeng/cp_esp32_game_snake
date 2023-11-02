#ifndef _CP_STRUCT_H_
#define _CP_STRUCT_H_

#include <Arduino.h>
#define DEBUG 1


#define SNAKE_SIZE 20

typedef struct _ps2_joystick {
  int x;
  int y;
  int k;
} ps2_joystick;

typedef struct _cp_size {
  int width;
  int height;
} cp_size;

typedef struct _cp_point {
  int x;
  int y;
} cp_point;



typedef struct _snake_point {
  cp_point position;
  int color;

  struct _snake_point* pre;
  struct _snake_point* next;
} snake_point;

#ifdef __cplusplus
extern "C" {
#endif
snake_point* init_snake_point_array();
void snake_point_array_push(snake_point* spoints, cp_point p);
void snake_point_array_push_at_begin(snake_point* spoints, cp_point p);
void free_snake_point_array(snake_point* spoints);

#ifdef __cplusplus
}
#endif
#endif