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
  CEU_Main data;
  tceu_app app;
  app.data = (tceu_org*)&data;
  app.init = &ceu_app_init;
  app.init(&app);
  u32 ticks = SDL_GetTicks();
  while (app.isAlive) {
    // TODO: surrounding the ceu_sys_go(...REDRAW...) line with stuff like this is a hack
    // I just don't understand how to get it done on the Ceu side
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = data.ren_w;
    r.h = data.ren_h;
    SDL_SetRenderDrawColor(data.ren, 0, 0, 0, 255); // black
    SDL_RenderFillRect(data.ren, &r);
    ceu_sys_go(&app, CEU_IN_SDL_REDRAW, (tceu_evtp)0);
    SDL_RenderPresent(data.ren);
    
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

