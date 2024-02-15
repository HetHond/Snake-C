#include "snake.h"

#include <stdio.h>
#include <stdlib.h>

void initializeSegment(struct SnakeSegment *self, int x, int y) {
  self->x = x;
  self->y = y;
};

void initializeSnake(struct Snake *snake, int initX, int initY,
                     enum Direction initDir) {
  snake->x = initX;
  snake->y = initY;
  snake->newDir = -1;
  snake->dir = initDir;

  // Allocate memory for the initial body segment
  struct SnakeSegment *initialSegment =
      (struct SnakeSegment *)malloc(sizeof(struct SnakeSegment));
  if (initialSegment == NULL) {
    fprintf(stderr, "Failed to allocate memory for snake body segment.\n");
    exit(EXIT_FAILURE);
  }

  initialSegment->x = initX;
  initialSegment->y = initY;
  switch (initDir) {
  case UP:
    initialSegment->y += 1;
    break;
  case DOWN:
    initialSegment->y -= 1;
    break;
  case LEFT:
    initialSegment->x += 1;
    break;
  case RIGHT:
    initialSegment->x -= 1;
    break;
  }

  // Link the body segment to the snake
  initialSegment->next = NULL;
  snake->body = initialSegment;
}

void destroySnake(struct Snake *snake) {
  // Free the linked list of snake segments
  struct SnakeSegment *current = snake->body;
  while (current != NULL) {
    struct SnakeSegment *temp = current;
    current = current->next;
    free(temp);
  }
};

void insertSegment(struct Snake *snake) {
  struct SnakeSegment *segment =
      (struct SnakeSegment *)malloc(sizeof(struct SnakeSegment));

  struct SnakeSegment *current = snake->body;
  while (current->next != NULL)
    current = current->next;
  current->next = segment;
  segment->x = current->x;
  segment->y = current->y;
  segment->next = NULL;
};

void switchDir(struct Snake *snake, enum Direction dir) {
  if (snake->newDir < 0 && dir % 2 != snake->dir % 2)
    snake->newDir = dir;
};

int insideSnake(struct Snake *snake, int x, int y) {
  struct SnakeSegment *segment = snake->body;
  while (segment != NULL) {
    if (segment->x == x && segment->y == y)
      return 1;
    segment = segment->next;
  }
  return 0;
};

void updateSnake(struct Snake *snake) {
  if (snake->newDir >= 0) {
    snake->dir = snake->newDir;
    snake->newDir = -1;
  }

  // move snake head
  int lastX = snake->x, lastY = snake->y;
  switch (snake->dir) {
  case UP:
    snake->y -= 1;
    break;
  case DOWN:
    snake->y += 1;
    break;
  case RIGHT:
    snake->x += 1;
    break;
  case LEFT:
    snake->x -= 1;
    break;
  default:
    break;
  }

  // move snake body
  struct SnakeSegment *segment = snake->body;
  while (segment != NULL) {
    int tmpX = segment->x, tmpY = segment->y;

    segment->x = lastX;
    segment->y = lastY;

    lastX = tmpX;
    lastY = tmpY;

    segment = segment->next;
  }
};
