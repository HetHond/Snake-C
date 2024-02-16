#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "sdl_utils.h"
#include "rendering.h"
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

static struct Context context;

void handleEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      context.shouldQuit = true;
      break;
    case SDL_KEYDOWN:
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
      break;
    }
  }
}

void update() {
  updateWorld(&context.world);
}

void loop() {
  initializeWorld(&context.world, WORLD_WIDTH, WORLD_HEIGHT);
  initializeSDL(&context, WINDOW_WIDTH, WINDOW_HEIGHT, WORLD_WIDTH,
                WORLD_HEIGHT);
  
  struct timespec lastTimestamp, currentTimestamp;
  long long tickDeltaTime = 0, frameDeltaTime = 0;
  clock_gettime(CLOCK_MONOTONIC, &currentTimestamp);
  lastTimestamp = currentTimestamp;

  context.shouldQuit = false;
  while (!context.shouldQuit) {
    handleEvents();
    
    clock_gettime(CLOCK_MONOTONIC, &currentTimestamp);
    long long elapsedTime = (currentTimestamp.tv_sec - lastTimestamp.tv_sec) * NS_PER_SECOND + (currentTimestamp.tv_nsec - lastTimestamp.tv_nsec);
    if (elapsedTime < 0) elapsedTime = 0;
    lastTimestamp = currentTimestamp;

    tickDeltaTime += elapsedTime;
    frameDeltaTime += elapsedTime;
    
    while (tickDeltaTime >= NS_PER_UPDATE) {
      update();
      tickDeltaTime -= NS_PER_UPDATE;
    }
    
    // TODO: find a better place for doing this
    if (context.world.gameover) {
      context.shouldQuit = true;
      break;
    }

    if (frameDeltaTime >= NS_PER_FRAME) {
      render(&context);
      frameDeltaTime = 0;
    }
  }
  
  destroySnake(&context.world.snake);
  cleanupSDL(&context);
}