#include <emscripten.h>
#include <SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>

SDL_Surface* screen;
TTF_Font* font;

#include "ceu_types.h"

#define ceu_out_assert(X) assert(X)
#define ceu_out_log(X) printf("%s\n", X)

#include "_ceu_app.c"

static byte CEU_DATA[sizeof(CEU_Main)];
static tceu_app app;

void one_iter() {
  SDL_Event event;
  int mx, my;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_MOUSEMOTION: {
        SDL_MouseMotionEvent* m = (SDL_MouseMotionEvent*)&event;
        SDL_GetMouseState(&mx, &my);
        ceu_sys_go(&app, CEU_IN_MOUSEMOTION, 0);
        break;
      }
    }
  }
  s32 dt_us = 16000;
  ceu_sys_go(&app, CEU_IN__WCLOCK, &dt_us);
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(W, H, 32, SDL_SWSURFACE);
  TTF_Init();
  font = TTF_OpenFont("sans-serif", 40);

  // void emscripten_set_main_loop(callback, fps, simulate_infinite_loop)
  emscripten_set_main_loop(one_iter, 0, 0);

  return 0;
}
