#ifndef STATE_H
#define STATE_H

#include <stdbool.h>

#include <SDL2/SDL.h>
#include "world.h"

struct Context {
  struct World world;

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  bool shouldQuit;
};

#endif