/* func_PAL_L02_003D8E08, the PAL copy of func_L02_003D4D68: the same C, where scale 0x384 - *(short *)(state + 0x32A). */
#include "common.h"

extern float func_00282E80(char *, void *);

extern int func_002A77E0(int);

extern float D_L02_001B02C0[4] SDATA(D_L02_001B02C0);
extern float D_L02_001B0200[4] SDATA(D_L02_001B0200);
extern char D_L02_001B0290[] SDATA(D_L02_001B0290);
extern char D_L02_001B0230[] SDATA(D_L02_001B0230);
extern char D_L02_001B0260[] SDATA(D_L02_001B0260);
extern int D_L02_001B01B0 __attribute__((sda));

int func_PAL_L02_003D8E08(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    short timer;
    int delta;

    if (func_00282E80(arg0 + 0x10, &D_L02_001B01B0) > 18.0f) {
        return 0;
    }
    timer = *(short *)(state + 0x32E);
    if (timer < 0x1F4) {
        return 0;
    }
    if (timer < 0x385) {
        delta = (((int)(0x384 - *(short *)(state + 0x32A)) * 5 + 2) / 6);
        if (delta > 0) {
            if (func_002A77E0(delta) != 0) {
                return 0;
            }
        }
    }
    *(short *)(state + 0x32A) = 0;
    *(short *)(state + 0x32E) = 0;
    return 1;
}

/* Spawns the particle bursts of one joint (func_L02_003D46B8 calls it for joints 2 and 3, the
 * second mirrored): the joint's position and matrix give the origin and the emission axis,
 * the length of the state's vector at +0x1B0 sets a 0..1 strength, and two offset points (the
 * first pulled horizontally towards D_L02_001BA500) emit D_L02_001B02B0 particles and a
 * strength-scaled number of particle pairs. The random term is an argument of each velocity
 * call, as in retail: hoisted into its own statement, the second loop's preheader copies swap
 * places. */
