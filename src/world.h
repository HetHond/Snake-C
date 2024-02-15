#ifndef WORLD_H
#define WORLD_H

#include "snake.h"

struct World {
  int width, height;
  int fruitX, fruitY;
  // TODO: maybe move snake out of the world struct
  struct Snake snake;
  int gameover;
};

void initializeWorld(struct World *, int, int);
void shuffleFood(struct World *);

void updateWorld(struct World *);

#endif
