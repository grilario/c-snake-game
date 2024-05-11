#include <stdint.h>

#include "raylib.h"

#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_VELOCITY 0.8
#define SNAKE_FIRST_DIRECTION RIGHT
#define GRID_SIZE 20

typedef struct Tail {
  uint32_t size;
  Vector2 *positions;
} Tail;

typedef enum Direction { UP, LEFT, RIGHT, DOWN } Direction;

typedef struct Snake {
  Direction direction;
  Tail tail;
} Snake;

Snake create_snake();
void move_snake(Snake *snake);
void draw_snake(Snake *snake);
void change_snake_direction(Snake *snake, Direction lastDirectionMovement, Direction direction);
void increase_tail(Snake *snake, Vector2 lastTailPosition);

void update_snake(Snake *snake);

#endif
