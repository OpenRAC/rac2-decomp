#include "include_asm.h"
#include "names.h"

/* func_PAL_L02_003ED0D8, the PAL copy of func_L02_003E8CE8: the same C and the same unit flags,
   where the spring's 1/3600 becomes 1/2500 and the damping divisor takes PAL's 50 Hz scale,
   (x * 5 + 2) / 6, in floats. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char pad000[0xE0];
    float vecE0[4];
    unsigned char pad0F0[0x5C0 - 0xF0];
    char *target5C0;
} Player003ED0D8;

extern char *g_moby_l02_pool[3] __attribute__((sda));
extern float D_L02_001B0C00 __attribute__((sda));
extern float D_L02_001B0C04 __attribute__((sda));
extern float D_L02_001B0C08 __attribute__((sda));
extern float D_L02_001B0C0C __attribute__((sda));
extern Player003ED0D8 g_hero_state;

extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float ApproachValue(float *, float, float);

void func_PAL_L02_003ED0D8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *target = g_moby_l02_pool[0] + (*(int *)state << 8);
    float pos[4];
    float vec[4];
    float diff[4];
    float spring[4];
    float damp[4];
    float step;
    float *q;
    float a;
    float b;

    *(TI128 *)pos = *(TI128 *)(arg0 + 0x10);
    pos[2] += D_L02_001B0C00;
    if (g_hero_state.target5C0 == target) {
        FastVecSub(vec, g_hero_state.vecE0, pos);
        step = FastVecLength(vec);
        ApproachValue(&step, 0.1f, D_L02_001B0C04);
        vec_scale_to_length(vec, vec, step);
        FastVecAdd(vec, vec, pos);
    } else {
        *(TI128 *)vec = *(TI128 *)pos;
    }
    q = vec;
    FastVecSub(diff, target + 0x10, q);
    a = FastVecLength(diff);
    b = FastVecLength(state + 0x10);
    a = a * 0.00040000002f;
    b = b / ((D_L02_001B0C0C * 5.0f + 2.0f) * 0.16666667f);
    vec_scale_to_length(spring, diff, -(D_L02_001B0C08 * a));
    vec_scale_to_length(damp, state + 0x10, -b);
    FastVecAdd(state + 0x10, state + 0x10, spring);
    FastVecAdd(state + 0x10, state + 0x10, damp);
    FastVecAdd(target + 0x10, target + 0x10, state + 0x10);
}
