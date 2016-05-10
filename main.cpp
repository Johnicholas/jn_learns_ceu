#include <stdio.h>
#include <assert.h>

#define ceu_out_assert(X) assert(X)
#define ceu_out_log(X) printf(X)

#include "_ceu_app.h"
#include "_ceu_app.c"

#define PROGRAM "bac"

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
          ceu_sys_go(&app, CEU_IN_A, NULL);
          break;
        case 'b':
          ceu_sys_go(&app, CEU_IN_B, NULL);
          break;
        case 'c':
          ceu_sys_go(&app, CEU_IN_C, NULL);
          break;
        default:
          printf("From C++: %c\n", PROGRAM[i]);
          break;
      }
    }
}
