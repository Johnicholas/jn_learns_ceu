#include <assert.h>
#include <stdio.h>

#include "_ceu_app.h"

s32 WCLOCK_nxt = CEU_WCLOCK_INACTIVE;
#define ceu_out_wclock_set(us) WCLOCK_nxt = us;

#include "_ceu_app.c"

int main (int argc, char *argv[])
{
    byte CEU_DATA[sizeof(CEU_Main)];
    memset(CEU_DATA, 0, sizeof(CEU_Main));
    tceu_app app;
    app.data = (tceu_org*) &CEU_DATA;
    app.init = &ceu_app_init;
    app.init(&app);
    // one
    if (WCLOCK_nxt != CEU_WCLOCK_INACTIVE) {
      s32 dt = WCLOCK_nxt;
      printf("dt %d\n", dt / 1000);
      ceu_sys_go(&app, CEU_IN__WCLOCK, &dt);
    }
    // two
    if (WCLOCK_nxt != CEU_WCLOCK_INACTIVE) {
      s32 dt = WCLOCK_nxt;
      printf("dt %d\n", dt / 1000);
      ceu_sys_go(&app, CEU_IN__WCLOCK, &dt);
    }
    ceu_sys_go(&app, CEU_IN_FOO, NULL);
    // three
    if (WCLOCK_nxt != CEU_WCLOCK_INACTIVE) {
      s32 dt = WCLOCK_nxt;
      printf("dt %d\n", dt / 1000);
      ceu_sys_go(&app, CEU_IN__WCLOCK, &dt);
    }
    // four
    assert(!app.isAlive);
    return app.ret;
}
