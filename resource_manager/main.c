#include <stdio.h>
#include <assert.h>
typedef struct {
  int rep[100]; // 100 is practically infinite
  int total_pushed;
  int total_popped;
} Queue;

void push(Queue* q, int to_push) {
  q->rep[q->total_pushed++] = to_push;
}

int pop(Queue* q) {
  return q->rep[q->total_popped++];
}

int empty(Queue* q) {
  return q->total_pushed == q->total_popped;
}

void init(Queue* q) {
  q->total_pushed = 0;
  q->total_popped = 0;
}

#include "_ceu_app.h"
#include "_ceu_app.c"

#define PROGRAM "aaabbbcccddd"

int main (int argc, char *argv[])
{
    int i;
    char CEU_DATA[sizeof(CEU_Main)];
    tceu_app app;
    app.data = (tceu_org*) &CEU_DATA;
    app.init = &ceu_app_init;

    app.init(&app);

    for (i = 0; i < sizeof(PROGRAM); i += 1) {
      switch (PROGRAM[i]) {
        case 'a':
          ceu_sys_go(&app, CEU_IN_USER_TASK, (tceu_evtp)123);
          break;
        case 'b':
          ceu_sys_go(&app, CEU_IN_USER_TASK, (tceu_evtp)234);
          break;
        case 'c':
          ceu_sys_go(&app, CEU_IN_REMOTE_WORKER_DONE, (tceu_evtp)1);
          break;
        case 'd':
          ceu_sys_go(&app, CEU_IN_REMOTE_WORKER_DONE, (tceu_evtp)2);
          break;
        default:
          printf("From C: %c\n", PROGRAM[i]);
          break;
      }
    }
}


