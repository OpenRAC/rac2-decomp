/* Runs every frame for the enemy: counts down its timers, and counts up two frame counters. */
/* func_L18_00428048 (180 bytes; levels 18, 19, 20): the per-frame tick of an object's
   controller block: rearms its timer, steps two countdowns (func_00282978 returns a value;
   declaring the callees void moves the counter into $v0), and hands it on. */
#include "common.h"


extern int D_L18_001B1254 __attribute__((sda));
extern int D_L18_001B1258 __attribute__((sda));
extern int D_L18_001B125C __attribute__((sda));
extern f32 D_L18_001B12FC __attribute__((sda));

extern int func_002A7820(int, int);
extern int func_00282978(void *);
extern int func_00282948(void *);
extern void func_002B0990(char *, char *, int, int, float);

void func_L18_00428048(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (*(u8 *)(vars + 0x39A) != 0) {
        *(u8 *)(vars + 0x39A) = 0;
        if (*(s16 *)(vars + 0x390) < D_L18_001B1254) {
            *(s16 *)(vars + 0x390) = RandomIntRange(D_L18_001B1258, D_L18_001B125C);
        }
    }
    FastDecTimer(vars + 0x392);
    FastDecTimer(vars + 0x396);
    *(u16 *)(vars + 0x394) += 1;
    FastFloatHelperD(*(void **)(vars + 0x3A8));
    if (*(u16 *)(moby + 0x96) <= 0xFFFE) {
        *(u16 *)(moby + 0x96) += 1;
    }
    SetValueAndStartSmoothChange(moby, vars + 0x2C0, 1, 1, D_L18_001B12FC);
}
