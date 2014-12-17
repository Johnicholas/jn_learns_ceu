#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_opengl.h"

#include <assert.h>

SDL_Renderer* REN;

#include "_ceu_app.h"
#include "_ceu_app.c"

int main (int argc, char *argv[])
{
  int err = SDL_Init(SDL_INIT_EVERYTHING);
  if (err != 0) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return err;
  }

  u32 ticks = SDL_GetTicks();

  char CEU_DATA[sizeof(CEU_Main)];
  tceu_app app;
  app.data = (tceu_org*) &CEU_DATA;
  app.init = &ceu_app_init;
  app.init(&app);
  ceu_sys_go(&app, CEU_IN_SDL_REDRAW, (tceu_evtp)NULL);
  SDL_RenderPresent(REN);
  char line[1024];
  while (fgets(line, 1024, stdin)) {
    int delta;
    int id;
    int x;
    int y;
    if (sscanf(line, "dt %d", &delta) == 1) {
      ticks = SDL_GetTicks();  
      int limit = ticks + delta / 10;
      while (ticks < limit) {
        ceu_sys_go(&app, CEU_IN_SDL_REDRAW, (tceu_evtp)0);
        SDL_RenderPresent(REN);
        u32 temp = SDL_GetTicks();
        if (ticks == temp) {
          temp += 1;      // force a minimum change
        }
        s32 dt = temp - ticks;
        ticks = temp;
        ceu_sys_go(&app, CEU_IN_SDL_DT, (tceu_evtp)dt);
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
    } else if (sscanf(line, "create %d %d %d", &id, &x, &y) == 3) {
	tceu__int__int__int args = { id, x, y };
	ceu_sys_go(&app, CEU_IN_CREATE, (tceu_evtp)(void*)&args);
    } else if (sscanf(line, "destroy %d", &id) == 1) {
    	ceu_sys_go(&app, CEU_IN_DESTROY, (tceu_evtp)id);
    } else if (sscanf(line, "move %d %d %d", &id, &x, &y) == 3) {
	tceu__int__int__int args = { id, x, y };
	ceu_sys_go(&app, CEU_IN_MOVE, (tceu_evtp)(void*)&args);
    } else if (sscanf(line, "place %d %d %d", &id, &x, &y) == 3) {
	tceu__int__int__int args = { id, x, y };
	ceu_sys_go(&app, CEU_IN_PLACE, (tceu_evtp)(void*)&args);
    } else {
      printf("I didn't understand: %s\n", line);
    }
  }
  SDL_Quit();
  return 0;
}

