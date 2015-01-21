#include <assert.h>
#include <stdio.h>

extern "C" {

#include "_ceu_app.h"

extern void ceu_app_init(tceu_app*);
extern int sizeof_CEU_Main;

}

int main (int argc, char *argv[])
{
    char data[sizeof_CEU_Main];
    tceu_app app;
    app.data = (tceu_org*) data;
    app.init = &ceu_app_init;
    app.init(&app);
    assert(app.isAlive);
    while (app.isAlive) {
      ceu_sys_go(&app, CEU_IN_DRAW, NULL);
      ceu_sys_go(&app, CEU_IN_UPDATE, NULL);
    }
    return app.ret;
}


