#include <stdio.h>

int random_plusminus(int center, int plusminus) {
  return center - plusminus + rand() % (plusminus * 2);
}

static int total_pushed;
static int total_popped;
static int buffer[1024]; // 1024 is basically infinity

int empty() {
  return total_pushed == total_popped;
}

void push(int value) {
  buffer[total_pushed++] = value;
}

int pop() {
  return buffer[total_popped++];
}

#include "_ceu_app.h"

s32 WCLOCK_nxt = CEU_WCLOCK_INACTIVE;
#define ceu_out_wclock_set(us) WCLOCK_nxt = us;

#include "_ceu_app.c"

int main (int argc, char *argv[])
{
    byte CEU_DATA[sizeof(CEU_Main)];
    memset(CEU_DATA, 0, sizeof(CEU_Main));
    tceu_app app;
    app.data = (tceu_org*) &CEU_DATA;
    app.init = &ceu_app_init;
    app.init(&app);
    while (app.isAlive) {
        printf("dt %d\n", WCLOCK_nxt / 1000);
	ceu_sys_go(&app, CEU_IN__WCLOCK, (tceu_evtp)WCLOCK_nxt);
    }
    return app.ret;
}
