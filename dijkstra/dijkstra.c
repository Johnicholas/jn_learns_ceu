// Adapted from Rosetta Code
#include <assert.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "_ceu_app.h"
#include "_ceu_app.c"

int main(int argc, char* argv) {
  byte CEU_DATA[sizeof(CEU_Main)];
  memset(CEU_DATA, 0, sizeof(CEU_Main));
  tceu_app app;
  app.data = (tceu_org*) &CEU_DATA;
  app.init = &ceu_app_init;
  int ret = ceu_go_all(&app);
  printf("*** END: %d\n", ret);
  return ret;
}

