#include <malloc.h>

#include "raylib.h"
#include "raymath.h"

#include "snake.h"

Snake create_snake() {
  Snake snake;

  snake.syrup.positions = (Vector2 *)calloc(1, sizeof(Vector2 *));
  snake.syrup.size = 1;
  snake.direction = SNAKE_FIRST_DIRECTION;

  return snake;
}

void draw_snake(Snake *snake) {
  DrawRectangle(snake->syrup.positions[0].x * 20, snake->syrup.positions[0].y * 20, 20, 20, RED);
}

void move_snake(Snake *snake) {
  for (int i = 0; snake->syrup.size > i; i++) {
    if (i == 0) {
      switch (snake->direction) {
      case UP:
        snake->syrup.positions[i] = Vector2Add(snake->syrup.positions[i], (Vector2){0, -1});

        if (snake->syrup.positions[i].y < 0) {
          snake->syrup.positions[i].y = GRID_SIZE - 1;
        }

        break;
      case LEFT:
        snake->syrup.positions[i] = Vector2Add(snake->syrup.positions[i], (Vector2){-1, 0});

        if (snake->syrup.positions[i].x < 0) {
          snake->syrup.positions[i].x = GRID_SIZE - 1;
        }

        break;
      case RIGHT:
        snake->syrup.positions[i] = Vector2Add(snake->syrup.positions[i], (Vector2){1, 0});

        if (snake->syrup.positions[i].x > GRID_SIZE - 1) {
          snake->syrup.positions[i].x = 0;
        }

        break;
      case DOWN:
        snake->syrup.positions[i] = Vector2Add(snake->syrup.positions[i], (Vector2){0, 1});

        if (snake->syrup.positions[i].y > GRID_SIZE - 1) {
          snake->syrup.positions[i].y = 0;
        }

        break;
      }
    }
  };
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

void update_snake(Snake *snake) {
  static float lastMove = 0;
  static Direction lastDirectionMovement = SNAKE_FIRST_DIRECTION;

  lastMove += GetFrameTime();

  if (lastMove > SNAKE_VELOCITY) {
    move_snake(snake);

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
