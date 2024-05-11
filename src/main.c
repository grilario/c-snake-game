#include <malloc.h>
#include <stdint.h>

#include "snake.h"

int main(void) {
  Snake snake = create_snake();

  InitWindow(GRID_SIZE * 20, GRID_SIZE * 20, "raylib [core] example - basic window");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    update_snake(&snake);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
