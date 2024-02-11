#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>

struct SnakeSegment {
  int x, y;
  struct SnakeSegment *next;
};

enum Direction { UP, RIGHT, DOWN, LEFT };

struct Snake {
  int x, y;
  enum Direction dir;
  struct SnakeSegment *body;
};

void initializeSegment(struct SnakeSegment *, int, int);
void initializeSnake(struct Snake *, int, int, enum Direction);
void destroySnake(struct Snake *);

void insertSegment(struct Snake *);
void switchDir(struct Snake *, enum Direction);
int insideSnake(struct Snake *, int, int);

void updateSnake(struct Snake *);
void drawSnake(WINDOW *window, struct Snake *);

#endif