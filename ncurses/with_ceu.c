#define CEU_DEBUG_TRAILS
#include <stdio.h>

#include "_ceu_app.h"
#include "_ceu_app.c"

int main()
{
    char CEU_DATA[sizeof(CEU_Main)];
    tceu_app app;
    app.data = (tceu_org*) &CEU_DATA;
    app.init = &ceu_app_init;

    app.init(&app);
    while (app.isAlive) {
    	ceu_sys_go(&app, CEU_IN_GETCH, (tceu_evtp)getch());
    }
    return 0;
}

