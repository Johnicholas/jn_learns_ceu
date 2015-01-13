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

#include "_ceu_app.c"

extern void ceu_app_init (tceu_app* app);

int main (int argc, char *argv[])
{
    byte CEU_DATA[sizeof(CEU_Main)];
    memset(CEU_DATA, 0, sizeof(CEU_Main));
    tceu_app app;
    app.data = (tceu_org*) &CEU_DATA;
    app.init = &ceu_app_init;
    initscr();
    cbreak();
    noecho();
    halfdelay(1);
    keypad(stdscr, TRUE);
    app.init(&app);
    assert(app.isAlive);
    while (app.isAlive) {
      ceu_sys_go(&app, CEU_IN_DRAW, NULL);
      tceu__char payload = { getch() };
      ceu_sys_go(&app, CEU_IN_UPDATE, &payload);
    }
    endwin();
    return app.ret;
}
