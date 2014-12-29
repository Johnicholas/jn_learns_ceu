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

static Queue outstanding_tasks;

void start_remote_task(int details, int reply_to) {
  printf("Starting a remote task working on %d, will reply to %d\n", details, reply_to);
  push(&outstanding_tasks, reply_to);
}

#include "_ceu_app.h"
#include "_ceu_app.c"

#define PROGRAM "abaabbaaabbbaaaabbbbaaaaabbbbbaaaaaabbbbbbaaaaaaabbbbbbb"

int main (int argc, char *argv[])
{
    int i;
    char CEU_DATA[sizeof(CEU_Main)];
    tceu_app app;
    app.data = (tceu_org*) &CEU_DATA;
    app.init = &ceu_app_init;

    app.init(&app);
    int details = 123;
    int reply_to;

    for (i = 0; i < sizeof(PROGRAM) && PROGRAM[i]; i += 1) {
      switch (PROGRAM[i]) {
        case 'a':
          ceu_sys_go(&app, CEU_IN_USER_TASK, (tceu_evtp)details++);
          break;
        case 'b':
          reply_to = pop(&outstanding_tasks);
          printf("Remote task done, replying to %d\n", reply_to);
          ceu_sys_go(&app, CEU_IN_REMOTE_WORKER_DONE, (tceu_evtp)reply_to);
          break;
        default:
          printf("From C: %c\n", PROGRAM[i]);
          break;
      }
    }
}


