#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

#include "snake.h"
#include "state.h"
#include "world.h"

struct State state;

void handleKeyPressed(int keyChar) {
  switch (keyChar) {
    case KEY_UP:
    case 'w':
      switchDir(&state.world.snake, UP);
      break;
    case KEY_DOWN:
    case 's':
      switchDir(&state.world.snake, DOWN);
      break;
    case KEY_LEFT:
    case 'a':
      switchDir(&state.world.snake, LEFT);
      break;
    case KEY_RIGHT:
    case 'd':
      switchDir(&state.world.snake, RIGHT);
      break;
    case 'q':
      state.world.gameover = 1;
      break;
    case ' ':
      insertSegment(&state.world.snake);
      break;
  }
}

int main() {
  int worldWidth = 10, worldHeight = 10;
  
  srand(time(0)); 
  initializeWorld(&state.world, worldWidth, worldHeight);
  
  initscr();
  // initialize color terminal
  if (!has_colors()) {
    endwin();
    printf("Your terminal does not support color.\n");
    return 1;
  }
  start_color();
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  noecho();        // Don't echo any keypresses
  curs_set(FALSE); // Don't display a cursor
  nodelay(stdscr, TRUE); // stdscr is the default window provided by ncurses
  keypad(stdscr, TRUE);

  int screenWidth, screenHeight;
  getmaxyx(stdscr, screenHeight, screenWidth);
  
  int winWidth = worldWidth*2+2, winHeight = worldHeight+2;
  WINDOW *win = newwin(winHeight, winWidth, screenHeight/2 - winHeight/2, screenWidth/2 - winWidth/2);
  refresh();
  
  int ch = 0;
int ch = 0;
  while (ch != 'q') {
    // window stuff
    wclear(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "Snake");
    // end window stuff
    
    handleKeyPressed(getch());
    
    updateSnake(&state.world.snake);
    updateWorld(&state.world);
    
    if (state.world.gameover) break;
    
    drawWorld(win, &state.world);
    drawSnake(win, &state.world.snake);
    
    // refreshing the window
    wrefresh(win);
    sleep(175);
  }
  
  endwin();
  return 0;
}
