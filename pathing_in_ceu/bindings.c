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

#include "_ceu_app.c"

int sizeof_CEU_Main = sizeof(CEU_Main);

