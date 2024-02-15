#include <stdlib.h>

#include "snake.h"
#include "world.h"

void initializeWorld(struct World *world, int width, int height) {
  world->gameover = 0;

  world->width = width;
  world->height = height;

  int snakeX = width / 2 - 1;
  int snakeY = height / 2;
  int snakeDir = 1;

  initializeSnake(&world->snake, snakeX, snakeY, snakeDir);

  shuffleFood(world);
};

void shuffleFood(struct World *world) {
  do {
    world->fruitX = rand() % world->width;
    world->fruitY = rand() % world->height;
  } while (insideSnake(&world->snake, world->fruitX, world->fruitY));
};

void updateWorld(struct World *world) {
  if (world->gameover) {
    return;
  }

  updateSnake(&world->snake);

  // check if the snake should die
  struct Snake *snake = &world->snake;
  if (snake->x >= world->width || snake->x < 0 || snake->y >= world->height ||
      snake->y < 0 || insideSnake(snake, snake->x, snake->y)) {
    world->gameover = 1;
    return;
  }

  if (snake->x == world->fruitX && snake->y == world->fruitY) {
    insertSegment(snake);
    shuffleFood(world);
  }
};
