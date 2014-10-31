main: main.cpp _ceu_app.h _ceu_app.c
	g++ main.cpp -o main

_ceu_app.h _ceu_app.c: hello.ceu
	ceu hello.ceu
