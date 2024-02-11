#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

#include "context.h"
#include "snake.h"
#include "world.h"

struct Context context;
int shouldQuit = 0;

void handleKeyPressed(int keyChar) {
  switch (keyChar) {
  case KEY_UP:
  case 'w':
    switchDir(&context.world.snake, UP);
    break;
  case KEY_DOWN:
  case 's':
    switchDir(&context.world.snake, DOWN);
    break;
  case KEY_LEFT:
  case 'a':
    switchDir(&context.world.snake, LEFT);
    break;
  case KEY_RIGHT:
  case 'd':
    switchDir(&context.world.snake, RIGHT);
    break;
  case 'q':
    context.world.gameover = 1;
    break;
  case ' ':
    insertSegment(&context.world.snake);
    break;
  }
}

void initializeScreen() {
  initscr();
  // initialize color terminal
  if (!has_colors()) {
    endwin();
    printf("Your terminal does not support color.\n");
    exit(1);
  }
  start_color();
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  noecho();              // Don't echo any keypresses
  curs_set(FALSE);       // Don't display a cursor
  nodelay(stdscr, TRUE); // stdscr is the default window provided by ncurses
  keypad(stdscr, TRUE);

  int screenWidth, screenHeight;
  getmaxyx(stdscr, screenHeight, screenWidth);

  int winWidth = context.world.width * 2 + 2,
      winHeight = context.world.height + 2;
  context.window = newwin(winHeight, winWidth, screenHeight / 2 - winHeight / 2,
                          screenWidth / 2 - winWidth / 2);
  refresh();
}

void drawGame() {
  wclear(context.window);
  box(context.window, 0, 0);
  mvwprintw(context.window, 0, 1, "Snake");

  drawWorld(context.window, &context.world);
  drawSnake(context.window, &context.world.snake);

  wrefresh(context.window);
}

void updateGame() {
  handleKeyPressed(getch());

  updateSnake(&context.world.snake);
  updateWorld(&context.world);

  if (context.world.gameover)
    shouldQuit = 1;
}

void cleanup() {
  struct SnakeSegment *current = context.world.snake.body;
  struct SnakeSegment *previous = NULL;
  while (current != NULL) {
    previous = current;
    current = current->next;
    free(previous);
  }
  // delwin(context.window);
}

int main() {
  int worldWidth = 10, worldHeight = 10;

  srand(time(0));
  initializeWorld(&context.world, worldWidth, worldHeight);
  initializeScreen();

  while (true) {
    updateGame();
    if (shouldQuit)
      break;

    drawGame();
    sleep(175);
  }

  cleanup();
  endwin();
  return 0;
}
