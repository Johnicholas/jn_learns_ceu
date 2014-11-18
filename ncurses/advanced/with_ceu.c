#include "_ceu_app.h"

s32 WCLOCK_nxt = CEU_WCLOCK_INACTIVE;
#define ceu_out_wclock_set(us) WCLOCK_nxt = us;

#include "_ceu_app.c"

int main()
{
    char CEU_DATA[sizeof(CEU_Main)];
    tceu_app app;
    app.data = (tceu_org*) &CEU_DATA;
    app.init = &ceu_app_init;

    app.init(&app);
    ceu_sys_go(&app, CEU_IN_START, (tceu_evtp)0);
    while (app.isAlive) {
        if (WCLOCK_nxt == CEU_WCLOCK_INACTIVE) {
          nocbreak();
        } else {
          halfdelay(WCLOCK_nxt / 100000);
        }
        int ch = getch();
        if (ch == ERR) {
          ceu_sys_go(&app, CEU_IN__WCLOCK, (tceu_evtp)(WCLOCK_nxt));
	} else {
    	  ceu_sys_go(&app, CEU_IN_GETCH, (tceu_evtp)ch);
	}
    }
    return 0;
}

