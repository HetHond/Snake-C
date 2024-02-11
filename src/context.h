#ifndef STATE_H
#define STATE_H

#include "world.h"
#include <ncurses.h>

struct Context {
  struct World world;
  WINDOW *window;
};

#endif