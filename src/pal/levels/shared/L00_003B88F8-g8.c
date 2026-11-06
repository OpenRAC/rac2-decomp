#include "common.h"

extern short D_L00_001B28B0[];
extern short D_L00_001B28C0[];
extern short D_L00_001B28C8[];
extern int D_L00_001B28D0 __attribute__((nosda));
extern int D_L00_001B28D4 __attribute__((sda));
extern int D_L00_001AFA18 __attribute__((sda));
extern int D_L00_001AFA1C __attribute__((sda));
extern float D_L00_001B28D8 __attribute__((nosda));

/* func_PAL_L00_003B88F8, the PAL copy of func_L00_003B4E88: the same C, with both latches scaled to 50 Hz. */
void func_PAL_L00_003B88F8(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        D_L00_001B28B0[i] = 2;
        D_L00_001B28C0[i] = 2;
        D_L00_001B28C8[i] = 1;
    }
    D_L00_001B28D0 = ((s32)(D_L00_001AFA18) * 5 + 2) / 6;
    D_L00_001B28D4 = ((s32)(D_L00_001AFA1C) * 5 + 2) / 6;
    D_L00_001B28D8 = 1.0f;
}
