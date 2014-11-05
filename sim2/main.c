#include <stdio.h>

#include "ceu_types.h"
#include "_ceu_app.h"
#include "_ceu_app.c"

int main (int argc, char *argv[])
{
    byte CEU_DATA[sizeof(CEU_Main)];
    tceu_app app;
    app.data = (tceu_org*) &CEU_DATA;
    app.init = &ceu_app_init;

    return ceu_go_all(&app);
}
