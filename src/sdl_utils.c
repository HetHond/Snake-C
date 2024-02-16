#include <stdio.h>

#include "sdl_utils.h"
#include "context.h"

void initializeSDL(struct Context *context, int windowWidth, int windowHeight,
                   int worldWidth, int worldHeight) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL could not be initialized! SDL_Error: %s\n",
            SDL_GetError());
    exit(1);
  }

  context->window =
      SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 0);
  if (!context->window) {
    fprintf(stderr, "SDL Window could not be initialized! SDL_Error: %s\n",
            SDL_GetError());
    exit(1);
  }

  context->renderer = SDL_CreateRenderer(context->window, -1, 0);
  if (!context->renderer) {
    fprintf(stderr, "SDL Renderer could not be initialized! SDL_Error: %s\n",
            SDL_GetError());
    exit(1);
  }

  context->texture =
      SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, worldWidth, worldHeight);
  if (!context->texture) {
    fprintf(stderr, "SDL Texture could not be initialized! SDL_Error: %s\n",
            SDL_GetError());
    exit(1);
  }
}

void cleanupSDL(struct Context *context) {
  SDL_DestroyWindow(context->window);
  SDL_DestroyRenderer(context->renderer);
  SDL_DestroyTexture(context->texture);
  SDL_Quit();
}