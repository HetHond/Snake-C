#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <stdio.h>
#include <time.h>

#include "context.h"
#include "snake.h"
#include "world.h"

#define WORLD_WIDTH 10
#define WORLD_HEIGHT 10

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

#define TARGET_UDP 4
#define TARGET_FPS 30

#define NS_PER_SECOND 1000000000LL
#define NS_PER_UPDATE (NS_PER_SECOND / TARGET_UDP)
#define NS_PER_FRAME (NS_PER_SECOND / TARGET_FPS)

// TODO: find out if i could make this static and/or const
struct Context context;

void initializeSDL() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL could not be initialized! SDL_Error: %s\n",
            SDL_GetError());
    exit(1);
  }

  context.window =
      SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  if (!context.window) {
    fprintf(stderr, "SDL Window could not be initialized! SDL_Error: %s\n",
            SDL_GetError());
    exit(1);
  }

  context.renderer = SDL_CreateRenderer(context.window, -1, 0);
  if (!context.renderer) {
    fprintf(stderr, "SDL Renderer could not be initialized! SDL_Error: %s\n",
            SDL_GetError());
    exit(1);
  }

  context.texture =
      SDL_CreateTexture(context.renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, WORLD_WIDTH, WORLD_HEIGHT);
  if (!context.texture) {
    fprintf(stderr, "SDL Texture could not be initialized! SDL_Error: %s\n",
            SDL_GetError());
    exit(1);
  }
};

void cleanupSDL() {
  SDL_DestroyWindow(context.window);
  SDL_DestroyRenderer(context.renderer);
  SDL_DestroyTexture(context.texture);
  SDL_Quit();
};

void update() {
  updateWorld(&context.world);
}

void render() {
  SDL_SetRenderTarget(context.renderer, context.texture);

  SDL_SetRenderDrawColor(context.renderer, 0x20, 0x20, 0x20, 0xFF);
  SDL_RenderClear(context.renderer);

  SDL_SetRenderDrawColor(context.renderer, 0xC8, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(context.renderer, &(SDL_Rect){context.world.fruitX, context.world.fruitY, 1, 1});

  SDL_SetRenderDrawColor(context.renderer, 0x00, 0xC8, 0x00, 0xFF);
  SDL_RenderFillRect(context.renderer, &(SDL_Rect){context.world.snake.x, context.world.snake.y, 1, 1});

  struct SnakeSegment *segment = context.world.snake.body;
  SDL_SetRenderDrawColor(context.renderer, 0x00, 0xFF, 0x00, 0xFF);
  while (segment != NULL) {
    SDL_RenderFillRect(context.renderer, &(SDL_Rect){segment->x, segment->y, 1, 1});
    segment = segment->next;
  }

  SDL_SetRenderTarget(context.renderer, NULL);
  SDL_RenderCopy(context.renderer, context.texture, NULL, NULL);
  SDL_RenderPresent(context.renderer);
}

int main() {
  initializeSDL();
  initializeWorld(&context.world, WORLD_WIDTH, WORLD_HEIGHT);

  SDL_Event e;
  int quit = 0;

  struct timespec lastTime, currentTime;
  clock_gettime(CLOCK_MONOTONIC, &currentTime);

  long long tickDeltaTime = 0;
  long long frameDeltaTime = 0;
  while (!quit) {
    // Handle events
    while (SDL_PollEvent(&e)) {
      // TODO: replace with switch
      if (e.type == SDL_QUIT) {
        quit = 1;
      } else if (e.type == SDL_KEYDOWN) {
        // TODO: also replace this with a switch
        switch (e.key.keysym.scancode) {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
          switchDir(&context.world.snake, UP);
          break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
          switchDir(&context.world.snake, LEFT);
          break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
          switchDir(&context.world.snake, DOWN);
          break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
          switchDir(&context.world.snake, RIGHT);
          break;
        default:
          break;
        }
      }
    }

    clock_gettime(CLOCK_MONOTONIC, &currentTime);
    long long elapsedTime = (currentTime.tv_sec - lastTime.tv_sec) * NS_PER_SECOND + (currentTime.tv_nsec - lastTime.tv_nsec);
    if (elapsedTime < 0) elapsedTime = 0;
    lastTime = currentTime;

    tickDeltaTime += elapsedTime;
    frameDeltaTime += elapsedTime;

    while (tickDeltaTime >= NS_PER_UPDATE) {
      update();
      tickDeltaTime -= NS_PER_UPDATE;
    }

    // TODO: maybe find a different way to achieve this
    if (context.world.gameover) {
      quit = 1;
      break;
    }

    if (frameDeltaTime >= NS_PER_FRAME) {
      render();
      frameDeltaTime = 0;
    }
  }

  destroySnake(&context.world.snake);
  cleanupSDL();
  return 0;
}
