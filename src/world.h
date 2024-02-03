#ifndef WORLD_H
#define WORLD_H

#include <ncurses.h>
#include "snake.h"

struct World {
  int width, height;
  int fruitX, fruitY;
  struct Snake snake;
  int gameover;
};

void initializeWorld(struct World*, int, int);
void shuffleFood(struct World*);

void updateWorld(struct World*);
void drawWorld(WINDOW* window, struct World*);

#endif