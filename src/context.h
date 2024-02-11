#ifndef STATE_H
#define STATE_H

#include <ncurses.h>
#include "world.h"

struct Context {
  struct World world;
  WINDOW* window;
};

#endif