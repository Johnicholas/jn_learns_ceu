# CFLAGS += $(shell pkg-config --cflags sdl)
# LDLIBS += $(shell pkg-config --libs sdl)

all: pong.html pong_ish.html

pong.html: pong.c
	emcc pong.c -o pong.html

pong_ish.html: pong_ish.c _ceu_app.c
	emcc pong_ish.c -o pong_ish.html

_ceu_app.c: pong_ish.ceu
	ceu pong_ish.ceu
