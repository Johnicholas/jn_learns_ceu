with_ceu: with_ceu.c _ceu_app.h _ceu_app.c
	gcc with_ceu.c -lcurses -o with_ceu

_ceu_app.h _ceu_app.c: curses.ceu
	ceu curses.ceu

just_c: just_c.c
	gcc just_c.c -lcurses -o just_c
