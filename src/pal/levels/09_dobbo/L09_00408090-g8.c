#include "names.h"
/* func_PAL_L09_00408090, the PAL copy of func_L09_004031D8: the same C, where D_L09_001B13C0 is read as
   a word and scaled to 50 Hz, both in the test and in the store to 0x26C. */
#include "common.h"

extern s32 g_dobbo_timer_value __attribute__((sda));
extern void func_2EA110(char *p);

/* Ticks the object's two timers and its age counter, refilling the timers when needed (PAL: 50 Hz timings). */
void dobbo_tick_timers_age_pal(char *moby) {
    char *self = moby;
    char *vars = *(char **)(self + 0x68);
    u16 age;
    if (*(s16 *)(vars + 0x270) != 0
        || (*(s32 *)(vars + 0x234) == 1
            && *(s16 *)(vars + 0x26C) < ((s32)(g_dobbo_timer_value / 2) * 5 + 2) / 6)) {
        *(u16 *)(vars + 0x26C) = ((s32)(g_dobbo_timer_value) * 5 + 2) / 6;
        *(s16 *)(vars + 0x270) = 0;
    }
    func_2EA110(vars + 0x26C);
    func_2EA110(vars + 0x26E);
    age = *(u16 *)(self + 0x96);
    if (age < 0xFFFF) {
        *(u16 *)(self + 0x96) = age + 1;
    }
}
