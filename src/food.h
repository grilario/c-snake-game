#include "snake.h"

#ifndef FOOD_H
#define FOOD_H

void spaw_food(Snake *snake);
void draw_food();
bool snake_ate_food(Snake *snake);
void update_food(Snake *snake);

#endif
