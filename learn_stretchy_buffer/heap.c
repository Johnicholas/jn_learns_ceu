// Adapted from Rosetta Code
#include <assert.h>
#define _GNU_SOURCE
#include <stdio.h>
#include "stretchy_buffer.h"

#include "_ceu_app.h"
#include "_ceu_app.c"

void insert(heap* container, CEU_T* elem) {
  int i = ++container->size;
  if (container->size < sb_count(container->backing)) {
    container->backing[container->size] = elem;
  } else {
    sb_push(container->backing, elem);
  }
  while (i > 1) {
    int parent = i >> 1;
    if (container->backing[i]->cost < container->backing[parent]->cost) {
      CEU_T* temp = container->backing[i]; 
      container->backing[i] = container->backing[parent];
      container->backing[parent] = temp;
    } else {
      break;
    }
    i = parent;
  }
}

void deletemin(heap* container) {
  int i = 1;

  container->backing[1] = container->backing[container->size];
  container->size = container->size - 1;
  int child = i << 1;
  while (child <= container->size) {
    if (child + 1 <= container->size && container->backing[child]->cost > container->backing[child+1]->cost) {
      child = child + 1;
    }
    if (container->backing[child]->cost < container->backing[i]->cost) {
      CEU_T* temp = container->backing[child];
      container->backing[child] = container->backing[i];
      container->backing[i] = temp;
    } else {
      break;
    }
    i = child;
  }
}

int main(int argc, char* argv) {
  byte CEU_DATA[sizeof(CEU_Main)];
  memset(CEU_DATA, 0, sizeof(CEU_Main));
  tceu_app app;
  app.data = (tceu_org*) &CEU_DATA;
  app.init = &ceu_app_init;
  app.init(&app);
  while (app.isAlive) {
    ceu_sys_go(&app, CEU_IN_TICK, NULL);
  }
  return app.ret;
}

