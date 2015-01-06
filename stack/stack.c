#include <stdio.h>

void a() {
  printf("start a\n");
}

void b() {
  printf("start b\n");
}

void x() {
  printf("start x\n");
}

void y() {
  printf("start y\n");
}

void z() {
  printf("start z\n");
}

#include "_ceu_app.h"
#include "_ceu_app.c"

int main(int argc, char* argv[]) {
  CEU_Main data;
  tceu_app app;
  app.data = (tceu_org*)&data;
  app.init = &ceu_app_init;
  app.init(&app);
  char line[1024];
  while (fgets(line, 1024, stdin)) {
    char opcode;
    if (sscanf(line, "%c", &opcode) != 1) {
      printf("I didn't recognize that.\n");
      break;
    } else {
      printf("%c done\n", opcode);
    }
    switch (opcode) {
      case 'a': ceu_sys_go(&app, CEU_IN_A_DONE, (tceu_evtp)0); break;
      case 'b': ceu_sys_go(&app, CEU_IN_B_DONE, (tceu_evtp)0); break;
      case 'c': ceu_sys_go(&app, CEU_IN_C_DONE, (tceu_evtp)0); break;
      case 'x': ceu_sys_go(&app, CEU_IN_X_DONE, (tceu_evtp)0); break;
      case 'y': ceu_sys_go(&app, CEU_IN_Y_DONE, (tceu_evtp)0); break;
      case 'z': ceu_sys_go(&app, CEU_IN_Z_DONE, (tceu_evtp)0); break;
    }
  }
  printf("all done!\n");
  return 0;
}

