#include "rendering.h"
#include "context.h"

void render(struct Context *context) {
  SDL_SetRenderTarget(context->renderer, context->texture);

  SDL_SetRenderDrawColor(context->renderer, 0x20, 0x20, 0x20, 0xFF);
  SDL_RenderClear(context->renderer);

  SDL_SetRenderDrawColor(context->renderer, 0xC8, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(
      context->renderer,
      &(SDL_Rect){context->world.fruitX, context->world.fruitY, 1, 1});

  SDL_SetRenderDrawColor(context->renderer, 0x00, 0xC8, 0x00, 0xFF);
  SDL_RenderFillRect(
      context->renderer,
      &(SDL_Rect){context->world.snake.x, context->world.snake.y, 1, 1});

  struct SnakeSegment *segment = context->world.snake.body;
  SDL_SetRenderDrawColor(context->renderer, 0x00, 0xFF, 0x00, 0xFF);
  while (segment != NULL) {
    SDL_RenderFillRect(context->renderer,
                       &(SDL_Rect){segment->x, segment->y, 1, 1});
    segment = segment->next;
  }

  SDL_SetRenderTarget(context->renderer, NULL);
  SDL_RenderCopy(context->renderer, context->texture, NULL, NULL);
  SDL_RenderPresent(context->renderer);
};