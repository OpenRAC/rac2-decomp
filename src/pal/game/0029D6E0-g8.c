#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int g_notice_owner;

void func_PAL_0029D7D0(void)
{
    extern int g_notice_owner;
    extern void hud_update_record_timers(int);
    extern void level_run_callbacks(void);
    if (D_001A8CFC != 0) {
        if (g_notice_owner == 0) {
            hud_update_record_timers(1);
            level_run_callbacks();
        }
    }
}
