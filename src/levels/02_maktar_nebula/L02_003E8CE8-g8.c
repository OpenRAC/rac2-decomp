#include "include_asm.h"
#include "names.h"

/* func_L02_003E8CE8 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it;
   -g gives the two nops retail has before its `div.s` (a -g unit's line labels). */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char pad000[0xE0];
    float vecE0[4];
    unsigned char pad0F0[0x5C0 - 0xF0];
    char *target5C0;
} Player003E8CE8;

extern char *D_L02_001B359C[3] __attribute__((sda));
extern float D_L02_001B0C00 __attribute__((sda));
extern float D_L02_001B0C04 __attribute__((sda));
extern float D_L02_001B0C08 __attribute__((sda));
extern float D_L02_001B0C0C __attribute__((sda));
extern Player003E8CE8 D_00189E20;

extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002AA2E8(float *, float, float);

/* Steers the entity named by the state's first word toward the actor's position (lifted by
   D_L02_001B0C00): when it is the entity the player holds, the offset is first eased through
   func_002AA2E8; the entity's position then gets a spring term (distance times 1/3600 times
   D_L02_001B0C08) and a damping term (the speed over D_L02_001B0C0C) added to the velocity at
   state+0x10, and the velocity added to the position. */
void func_L02_003E8CE8(char *actor) {
    char *state = *(char **)(actor + 0x68);
    char *target = gMobyPool_L02[0] + (*(int *)state << 8);
    float pos[4];
    float vec[4];
    float diff[4];
    float spring[4];
    float damp[4];
    float step;
    float *goal;
    float distance;
    float speed;

    *(TI128 *)pos = *(TI128 *)(actor + 0x10);
    pos[2] += D_L02_001B0C00;
    if (gHeroState.target5C0 == target) {
        FastVecSub(vec, gHeroState.vecE0, pos);
        step = FastVecLength(vec);
        ApproachValue(&step, 0.1f, D_L02_001B0C04);
        vec_scale_to_length(vec, vec, step);
        FastVecAdd(vec, vec, pos);
    } else {
        *(TI128 *)vec = *(TI128 *)pos;
    }
    goal = vec;
    FastVecSub(diff, target + 0x10, goal);
    distance = FastVecLength(diff);
    speed = FastVecLength(state + 0x10);
    distance = distance * 0.00027777778f;
    speed = speed / D_L02_001B0C0C;
    vec_scale_to_length(spring, diff, -(D_L02_001B0C08 * distance));
    vec_scale_to_length(damp, state + 0x10, -speed);
    FastVecAdd(state + 0x10, state + 0x10, spring);
    FastVecAdd(state + 0x10, state + 0x10, damp);
    FastVecAdd(target + 0x10, target + 0x10, state + 0x10);
}
