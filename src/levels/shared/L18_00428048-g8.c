#include "names.h"
/* Runs every frame for the enemy: counts down its timers, and counts up two frame counters. */
/* func_L18_00428048 (180 bytes; levels 18, 19, 20): the per-frame tick of an object's
   controller block: rearms its timer, steps two countdowns (func_00282978 returns a value;
   declaring the callees void moves the counter into $v0), and hands it on. */
#include "common.h"


extern int D_L18_001B1254 __attribute__((sda));
extern int D_L18_001B1258 __attribute__((sda));
extern int D_L18_001B125C __attribute__((sda));
extern f32 D_L18_001B12FC __attribute__((sda));

extern int math_random_int_range(int, int);
extern int FastDecTimer(void *);
extern int math_fast_float_d(void *);
extern void value_set_and_smooth(char *, char *, int, int, float);

void enemy_tick_timers(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (*(u8 *)(vars + 0x39A) != 0) {
        *(u8 *)(vars + 0x39A) = 0;
        if (*(s16 *)(vars + 0x390) < D_L18_001B1254) {
            *(s16 *)(vars + 0x390) = math_random_int_range(D_L18_001B1258, D_L18_001B125C);
        }
    }
    FastDecTimer(vars + 0x392);
    FastDecTimer(vars + 0x396);
    *(u16 *)(vars + 0x394) += 1;
    math_fast_float_d(*(void **)(vars + 0x3A8));
    if (*(u16 *)(moby + 0x96) <= 0xFFFE) {
        *(u16 *)(moby + 0x96) += 1;
    }
    value_set_and_smooth(moby, vars + 0x2C0, 1, 1, D_L18_001B12FC);
}
