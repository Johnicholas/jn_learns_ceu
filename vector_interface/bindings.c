#include <assert.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h> // for rand

int rand_between(int min, int max) {
  return rand() % (max - min) + min;
}

void quit() {
  endwin();
  exit(1);
}

void draw_screen(char* data, int rows, int cols) {
  int row, col;
  for (row = 0; row < rows; row += 1) {
    move(row, 0);
    for (col = 0; col < cols; col += 1) {
      addch(data[row*cols+col]);
    }
  }
}

extern void path_screen(char* map, int rows, int cols, int startrow, int startcol, int destrow, int destcol);

#include "_ceu_app.c"


