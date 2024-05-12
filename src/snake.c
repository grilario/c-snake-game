#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"

#include "snake.h"

Snake create_snake() {
  Snake snake;

  snake.tail.positions = (Vector2 *)calloc(1, sizeof(Vector2 *));
  snake.tail.size = 1;
  snake.direction = SNAKE_FIRST_DIRECTION;

  return snake;
}

void draw_snake(Snake *snake) {
  for (int i = 0; snake->tail.size > i; i++) {
    DrawRectangle(snake->tail.positions[i].x * 20, snake->tail.positions[i].y * 20, 20, 20, RED);
  }
}

void move_snake(Snake *snake) {
  for (int i = snake->tail.size - 1; i >= 0; i--) {
    if (i == 0) {
      switch (snake->direction) {
      case UP:
        snake->tail.positions[i] = Vector2Add(snake->tail.positions[i], (Vector2){0, -1});

        if (snake->tail.positions[i].y < 0) {
          snake->tail.positions[i].y = GRID_SIZE - 1;
        }

        break;
      case LEFT:
        snake->tail.positions[i] = Vector2Add(snake->tail.positions[i], (Vector2){-1, 0});

        if (snake->tail.positions[i].x < 0) {
          snake->tail.positions[i].x = GRID_SIZE - 1;
        }

        break;
      case RIGHT:
        snake->tail.positions[i] = Vector2Add(snake->tail.positions[i], (Vector2){1, 0});

        if (snake->tail.positions[i].x > GRID_SIZE - 1) {
          snake->tail.positions[i].x = 0;
        }

        break;
      case DOWN:
        snake->tail.positions[i] = Vector2Add(snake->tail.positions[i], (Vector2){0, 1});

        if (snake->tail.positions[i].y > GRID_SIZE - 1) {
          snake->tail.positions[i].y = 0;
        }

        break;
      }

      return;
    }

    snake->tail.positions[i].x = snake->tail.positions[i - 1].x;
    snake->tail.positions[i].y = snake->tail.positions[i - 1].y;
  };
}

void increase_tail(Snake *snake, Vector2 lastTailPosition) {
  int newSize = snake->tail.size + 1;

  snake->tail.positions = realloc(snake->tail.positions, sizeof(Vector2) * newSize);
  snake->tail.size = newSize;

  snake->tail.positions[newSize - 1] = lastTailPosition;
}

void change_snake_direction(Snake *snake, Direction lastDirectionMovement, Direction direction) {
  if (lastDirectionMovement == RIGHT && direction == LEFT)
    return;
  if (lastDirectionMovement == UP && direction == DOWN)
    return;
  if (lastDirectionMovement == LEFT && direction == RIGHT)
    return;
  if (lastDirectionMovement == DOWN && direction == UP)
    return;

  snake->direction = direction;
}

bool is_colliding_with_itself(Snake *snake) {
  Vector2 head = snake->tail.positions[0];

  for (int i = 1; snake->tail.size > i; i++) {
    if (Vector2Equals(head, snake->tail.positions[i]))
      return true;
  }

  return false;
}

void update_snake(Snake *snake) {
  static float lastMove = 0;
  static Direction lastDirectionMovement = SNAKE_FIRST_DIRECTION;

  lastMove += GetFrameTime();

  if (lastMove > SNAKE_VELOCITY) {

    move_snake(snake);

    if (is_colliding_with_itself(snake)) {
      return CloseWindow();
    }

    lastMove = 0;
    lastDirectionMovement = snake->direction;
  }

  // Update movement direction
  bool upIsPressed = IsKeyPressed(KEY_UP);
  bool downIsPressed = IsKeyPressed(KEY_DOWN);
  bool leftIsPressed = IsKeyPressed(KEY_LEFT);
  bool rightIsPressed = IsKeyPressed(KEY_RIGHT);

  Direction *direction = NULL;
  direction = (enum Direction *)malloc(sizeof(enum Direction));

  *direction = snake->direction;

  if (!leftIsPressed && !rightIsPressed) {
    if (downIsPressed && !upIsPressed) {
      *direction = DOWN;
    } else if (upIsPressed && !downIsPressed) {
      *direction = UP;
    }
  } else if (!downIsPressed && !upIsPressed) {
    if (leftIsPressed && !rightIsPressed) {
      *direction = LEFT;
    } else if (rightIsPressed && !leftIsPressed) {
      *direction = RIGHT;
    }
  }

  if (direction != NULL) {
    change_snake_direction(snake, lastDirectionMovement, *direction);
  }

  free(direction);

  draw_snake(snake);
}
