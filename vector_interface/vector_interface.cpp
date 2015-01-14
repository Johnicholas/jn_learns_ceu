#include <assert.h>
#include <ctype.h>
#include <curses.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <vector>
#include <iostream>
#include "micropather.h"
using namespace micropather;

const int drow[4] = { 1, 0, -1,  0 };
const int dcol[4] = { 0, 1,  0, -1 }; 

class Dungeon : public Graph {
public:
  // Constructor
  Dungeon(char* map, int rows, int cols) :
    map(map),
    rows(rows),
    cols(cols)
  {
  }
  // From Graph
  float LeastCostEstimate(void* from, void* dest) {
    int fromrow = (int)from / cols;
    int fromcol = (int)from - fromrow * cols;
    int destrow = (int)dest / cols;
    int destcol = (int)dest - destrow * cols;
    int deltarows = destrow - fromrow;
    int deltacols = destcol - fromcol;
    return sqrt(deltarows*deltarows + deltacols*deltacols); 
  }
  // From Graph
  void AdjacentCost(void* node, MPVector<StateCost>* neighbors) {
    int row = (int)node / cols;
    int col = (int)node - row * cols;
    for (int i = 0; i < 4; i += 1) {
      int nrow = row + drow[i];
      int ncol = col + dcol[i];
      if (map[nrow*cols+ncol] != '#') {
        StateCost statecost = { (void*)(nrow*cols+ncol), 1.0f };
        neighbors->push_back( statecost );    
      }
    }
  }
  // from Graph
  void PrintStateInfo(void*) {
    // TODO
  }

private:
  char* map;
  int rows;
  int cols;
};

extern "C" {

#include "_ceu_app.h"

extern void ceu_app_init (tceu_app* app);

void path_screen(char* map, int rows, int cols, int startrow, int startcol, int destrow, int destcol) {
  for (int row = 0; row < rows; row += 1) {
    for (int col = 0; col < cols; col += 1) {
      if (map[row*cols+col] == '_') {
        map[row*cols+col] = '.';
      }
    }
  }
  Dungeon d(map, rows, cols);
  MicroPather m(&d, 2000);
  MPVector<void*> path;
  float total;
  void* start = (void*)(startrow*cols+startcol);
  void* dest = (void*)(destrow*cols+destcol);
  int result = m.Solve(start, dest, &path, &total);
  if (result == MicroPather::SOLVED) {
    for (int i = 0; i < path.size(); i += 1) {
      int row = (int)path[i] / cols;
      int col = (int)path[i] - row * cols;
      if (map[row*cols + col] == '.') {
        map[row*cols + col] = '_';
      }
    }
    fprintf(stderr, "end\n");
  } else {
    fprintf(stderr, "notsolved\n");
  }
}

static char data[2048];

}

int main (int argc, char *argv[])
{
    tceu_app app;
    app.data = (tceu_org*) &data;
    app.init = &ceu_app_init;
    initscr();
    cbreak();
    noecho();
    halfdelay(1);
    keypad(stdscr, TRUE);
    app.init(&app);
    assert(app.isAlive);
    while (app.isAlive) {
      ceu_sys_go(&app, CEU_IN_DRAW, NULL);
      tceu__char payload = { getch() };
      ceu_sys_go(&app, CEU_IN_UPDATE, (void*)&payload);
    }
    endwin();
    return app.ret;
}


