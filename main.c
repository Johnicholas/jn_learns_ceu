#include <stdio.h>
#include <assert.h>
#include "_ceu_app.h"
#include "_ceu_app.c"

#define PROGRAM "abracadabra"

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
          ceu_sys_go(&app, CEU_IN_A, (tceu_evtp)NULL);
          break;
        case 'b':
          ceu_sys_go(&app, CEU_IN_B, (tceu_evtp)NULL);
          break;
        case 'c':
          ceu_sys_go(&app, CEU_IN_C, (tceu_evtp)NULL);
          break;
        default:
          printf("From C:\t%c\n", PROGRAM[i]);
          break;
      }
    }
}


