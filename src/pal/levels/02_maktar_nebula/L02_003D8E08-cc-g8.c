#include "names.h"
/* func_PAL_L02_003D8E08, the PAL copy of func_L02_003D4D68: the same C, where scale 0x384 - *(short *)(state + 0x32A). */
#include "common.h"

extern float vec_distance_xy(char *, void *);

extern int math_random_int_below(int);

extern float g_chainblade_debris_offset_a[4] SDATA(D_L02_001B02C0);
extern float g_chainblade_debris_offset_b[4] SDATA(D_L02_001B0200);
extern char g_chainblade_spawn_record_c[] SDATA(D_L02_001B0290);
extern char g_chainblade_spawn_record_a[] SDATA(D_L02_001B0230);
extern char g_chainblade_spawn_record_b[] SDATA(D_L02_001B0260);
extern int g_chainblade_landing_point __attribute__((sda));

int func_PAL_L02_003D8E08(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    short timer;
    int delta;

    if (vec_distance_xy(arg0 + 0x10, &g_chainblade_landing_point) > 18.0f) {
        return 0;
    }
    timer = *(short *)(state + 0x32E);
    if (timer < 0x1F4) {
        return 0;
    }
    if (timer < 0x385) {
        delta = (((int)(0x384 - *(short *)(state + 0x32A)) * 5 + 2) / 6);
        if (delta > 0) {
            if (math_random_int_below(delta) != 0) {
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
