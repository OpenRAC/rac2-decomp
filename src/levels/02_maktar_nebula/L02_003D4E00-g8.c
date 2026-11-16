#include "include_asm.h"
#include "names.h"

/* func_L02_003D4E00 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern int g_chainblade_landing_point __attribute__((sda));

extern float vec_distance_xy(char *, void *);

/* (out, source vector, 13.0f, 45.0f, 0.2f, 0.2f): its own draft is nonmatching/levels/func_L02_003D5E40.c. */
extern void PlacePointWithPolarJitter(char *, float *, float, float, float, float);

/* Moves the Chainblade's wander goal to a random spot near the target, and back to the arena centre if it strays too far. */
void chainblade_pick_wander_goal(char *self) {
    char *state = *(char **)(self + 0x68);
    float vec[4];

    *(TI128 *)vec = *(TI128 *)(*(char **)(state + 0x30C) + 0x10);
    vec[2] += 1.0f;
    *(TI128 *)(state + 0x2C0) = *(TI128 *)(self + 0x10);
    PlacePointWithPolarJitter(state + 0x2C0, vec, 13.0f, 45.0f, 0.2f, 0.2f);
    if (vec_distance_xy(state + 0x2C0, &g_chainblade_landing_point) > 10.0f) {
        *(TI128 *)(state + 0x2C0) = *(TI128 *)&g_chainblade_landing_point;
        *(float *)(state + 0x2C8) += 1.0f;
    }
}
