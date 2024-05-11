#include <malloc.h>
#include <stdint.h>

#include "food.h"
#include "snake.h"

int main(void) {
  Snake snake = create_snake();

  spaw_food(&snake);

  InitWindow(GRID_SIZE * 20, GRID_SIZE * 20, "raylib [core] example - basic window");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    update_food(&snake);
    update_snake(&snake);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
