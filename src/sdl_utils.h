#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include "context.h"

void initializeSDL(struct Context *context, int windowWidth, int windowHeight,
                   int worldWidth, int worldHeight);
void cleanupSDL(struct Context *context);

#endif
