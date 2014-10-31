void open();

#include <cassert>
#include "_ceu_app.h"
#include "_ceu_app.c"
#include <iostream>

void open() {
  std::cout << "Correct! Opening the door...\n";
}

#define PROGRAM "43212341234"

int main (int argc, char *argv[])
{
  int i;
  char CEU_DATA[sizeof(CEU_Main)];
  tceu_app app;
  app.data = (tceu_org*) &CEU_DATA;
  app.init = &ceu_app_init;

  app.init(&app);

  for (i = 0; i < sizeof(PROGRAM); i += 1) {
    int digit = PROGRAM[i] - '0';
    if (digit >= 0 and digit < 10) {
      std::cout << "Pressing " << PROGRAM[i] << "...\n";
      ceu_sys_go(&app, CEU_IN_PRESS, (tceu_evtp)digit);
    }
  }
  return 0;
}


