#include <emscripten.h>
#include <SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>

SDL_Surface* screen;
TTF_Font* font;

#include "ceu_types.h"

s32 WCLOCK_nxt;
#define ceu_out_wclock_set(us) WCLOCK_nxt = us;
#define ceu_out_assert(X) assert(X)
#define ceu_out_log(X) printf("%s\n", X)

#include "_ceu_app.c"

static byte CEU_DATA[sizeof(CEU_Main)];
static tceu_app app;

void one_iter() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_MOUSEMOTION: {
        SDL_MouseMotionEvent* m = (SDL_MouseMotionEvent*)&event;
        tceu__int__int payload;
        SDL_GetMouseState(&payload._1, &payload._2);
        ceu_sys_go(&app, CEU_IN_SDL_MOUSEMOTION, &payload);
        break;
      }
    }
  }

  if (WCLOCK_nxt != CEU_WCLOCK_INACTIVE) {
    s32 dt_us = 16000;
    ceu_sys_go(&app, CEU_IN__WCLOCK, &dt_us);
    while (WCLOCK_nxt <= 0) {
      dt_us = 0;
      ceu_sys_go(&app, CEU_IN__WCLOCK, &dt_us);
    }
  }

  ceu_sys_go(&app, CEU_IN_SDL_REDRAW, 0);
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  WCLOCK_nxt = CEU_WCLOCK_INACTIVE;
  screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
  TTF_Init();
  font = TTF_OpenFont("sans-serif", 40);

  memset(CEU_DATA, 0, sizeof(CEU_Main));
  app.data = (tceu_org*) &CEU_DATA;
  app.init = &ceu_app_init;
  app.init(&app);

  // void emscripten_set_main_loop(callback, fps, simulate_infinite_loop)
  emscripten_set_main_loop(one_iter, 0, 0);

  return 0;
}
