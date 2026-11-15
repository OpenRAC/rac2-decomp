#include "common.h"

extern short D_L00_001B28B0[];
extern short D_L00_001B28C0[];
extern short D_L00_001B28C8[];
extern int D_L00_001B28D0 __attribute__((nosda));
extern int D_L00_001B28D4 __attribute__((nosda));
extern int D_L00_001AFA18 __attribute__((sda));
extern int D_L00_001AFA1C __attribute__((sda));
extern float D_L00_001B28D8 __attribute__((sda));

/* Resets the four slots of each of three short tables and clears the paired latches. */
void jitter_trail_reset_slots(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        D_L00_001B28B0[i] = 2;
        D_L00_001B28C0[i] = 2;
        D_L00_001B28C8[i] = 1;
    }
    D_L00_001B28D0 = D_L00_001AFA18;
    D_L00_001B28D4 = D_L00_001AFA1C;
    D_L00_001B28D8 = 1.0f;
}
