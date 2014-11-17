// based on examples from
// "Introduction to the Unix Curses"
// by Norman Matloff
#include <curses.h>

int r, c, nrows, ncols;

void draw(char dc)
{
  move(r, c);
  delch();
  insch(dc);
  refresh();
  r++;
  if (r == nrows) {
    r = 0;
    c++;
    if (c == ncols) c = 0;
  }
}

int main()
{
  int i;
  char d;
  WINDOW* wnd;

  wnd = initscr();
  cbreak();
  noecho();
  getmaxyx(wnd, nrows, ncols);
  clear();
  refresh();

  r = 0;
  c = 0;
  while (1) {
    d = getch();
    if (d == 'q') break;
    draw(d);
  }
  endwin();
}

