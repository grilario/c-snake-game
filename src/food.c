#include <stdlib.h>

#include "food.h"
#include "raylib.h"
#include "raymath.h"

static Vector2 foodPosition = (Vector2){0, 0};

void spaw_food(Snake *snake) {
  int x = rand() % GRID_SIZE;
  int y = rand() % GRID_SIZE;

  // check if postion genereted is snake tail
  for (int i = 0; snake->tail.size > i; i++) {
    if (x == snake->tail.positions[i].x && y == snake->tail.positions[i].y) {
      int x = rand() % GRID_SIZE;
      int y = rand() % GRID_SIZE;

      i = 0;
    }
  }

  foodPosition.x = x;
  foodPosition.y = y;
}

bool snake_ate_food(Snake *snake) {
  Vector2 head = snake->tail.positions[0];

  return Vector2Equals(head, foodPosition);
}

void draw_food() { DrawRectangle(foodPosition.x * 20, foodPosition.y * 20, 20, 20, MAROON); }

void update_food(Snake *snake) {
  Vector2 lastTailPosition = snake->tail.positions[snake->tail.size - 1];

  if (snake_ate_food(snake)) {
    increase_tail(snake, lastTailPosition);
    spaw_food(snake);
  }

  draw_food();
}
