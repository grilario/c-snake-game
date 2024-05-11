#include <stdint.h>

#include "raylib.h"

#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_VELOCITY 0.8
#define SNAKE_FIRST_DIRECTION RIGHT
#define GRID_SIZE 20

typedef struct Syrup {
  uint32_t size;
  Vector2 *positions;
} Syrup;

typedef enum Direction { UP, LEFT, RIGHT, DOWN } Direction;

typedef struct Snake {
  Direction direction;
  Syrup syrup;
} Snake;

Snake create_snake();
void move_snake(Snake *snake);
void draw_snake(Snake *snake);
void change_snake_direction(Snake *snake, Direction lastDirectionMovement, Direction direction);

void update_snake(Snake *snake);

#endif
