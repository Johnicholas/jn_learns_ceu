// Based on Chis Deleon's "Coding an HTML5 Game in 5 min 30 sec" https://www.youtube.com/watch?v=KoWqdEACyLI
// 
// Compile with emcc pong.c -o pong.html
//
// Works for me using emcc version 1.10 and google chrome.
//
#include <emscripten.h>
#include <SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>

// width of the screen
#define W 600

// height of the screen
#define H 450

SDL_Surface* screen;
TTF_Font* font;

// paddle thickness
#define PT 10

// paddle height
#define PH 100

// paddle 1
int p1x = 0;
int p1y = 40;

// paddle 2
int p2x = W - PT;
int p2y = 40;

// ball position
int bx = 50;
int by = 50;
// ball dimension
int bd = 6;
// x velocity of ball
int xv = 4;
// y velocity of ball
int yv = 4;

int score1 = 0;
int score2 = 0;

int ais = 2;

void reset() {
  bx = W / 2;
  by = H / 2;
  xv = 4;
  yv = 4;
}

void one_iter() {
  SDL_Event event;
  int mx, my;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_MOUSEMOTION: {
        SDL_MouseMotionEvent* m = (SDL_MouseMotionEvent*)&event;
        SDL_GetMouseState(&mx, &my);
        p1y = my;
        break;
      }
    }
  }

  // ball physics
  bx += xv;
  by += yv;
  if (by < 0 && yv < 0) {
    // bounce off top edge of screen
    yv = -yv;
  }
  if (by > H && yv > 0) {
    // bounce off bottom edge of the screen
    yv = -yv;
  }
  if (bx < 0) {
    // ball goes off left side of screen
    if (by > p1y && by < p1y + PH) {
      // bounce off the left paddle
      xv = -xv;
      int dy = by - (p1y + PH/2);
      yv = dy * 0.3;
    } else {
      // missed it
      score2++;
      reset();
    }
  }
  if (bx > W) {
    // ball goes off left side of screen
    if (by > p2y && by < p2y + PH) {
      // bounce off the left paddle
      xv = -xv;
      int dy = by - (p2y + PH/2);
      yv = dy * 0.3;
    } else {
      // missed it
      score1++;
      reset();
    }
  }

  if (p2y + PH/2 < by) {
    p2y += ais;
  } else {
    p2y -= ais;
  }

  boxRGBA(screen, 0, 0, W, H, 0, 0, 0, 0xff);
  boxRGBA(screen, 0, p1y, PT, p1y + PH, 0xff, 0xff, 0xff, 0xff);
  boxRGBA(screen, W - PT, p2y, W, p2y + PH, 0xff, 0xff, 0xff, 0xff);
  boxRGBA(screen, bx - bd / 2, by - bd / 2, bx + bd / 2, by + bd / 2, 0xff, 0xff, 0xff, 0xff);


  // TODO: Draw score1 at x=100, 100
  // TODO: Draw score2 at x = W - 100, 100

  SDL_UpdateRect(screen, 0, 0, 0, 0);
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(600, 450, 32, SDL_SWSURFACE);
  TTF_Init();
  font = TTF_OpenFont("sans-serif", 40);

  // void emscripten_set_main_loop(callback, fps, simulate_infinite_loop)
  emscripten_set_main_loop(one_iter, 0, 0);

  return 0;
}
