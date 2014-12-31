#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_opengl.h"

#include <assert.h>

#include "_ceu_app.h"
#include "_ceu_app.c"

int main (int argc, char *argv[])
{
  int err = SDL_Init(SDL_INIT_EVERYTHING);
  if (err != 0) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return err;
  }
  char CEU_DATA[sizeof(CEU_Main)];
  tceu_app app;
  app.data = (tceu_org*) &CEU_DATA;
  app.init = &ceu_app_init;
  app.init(&app);
  u32 ticks = SDL_GetTicks();
  while (app.isAlive) {
    ceu_sys_go(&app, CEU_IN_SDL_REDRAW, (tceu_evtp)0);
    u32 temp = SDL_GetTicks();
    if (ticks == temp) {
      temp += 1;      // force a minimum change
    }
    s32 dt = temp - ticks;
    ticks = temp;
    ceu_sys_go(&app, CEU_IN_SDL_DT, (tceu_evtp)(dt));
    ceu_sys_go(&app, CEU_IN__WCLOCK, (tceu_evtp)(dt*5000));
    // clear the event queue
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        ceu_sys_go(&app, CEU_IN_SDL_QUIT, (tceu_evtp)0);
        SDL_Quit();
        return 0;
      }
    }
  }
  SDL_Quit();
  return 0;
}

