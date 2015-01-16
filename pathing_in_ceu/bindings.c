#include <assert.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h> // for rand
#include <math.h> // for sqrt

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

#include "_ceu_app.c"

int sizeof_CEU_Main = sizeof(CEU_Main);

