#include "include_asm.h"
#include "names.h"

/* func_L02_003D4ED0 is a unit of its own: it needs the opt-in quadword-copy profile
   (-frac2-qcopy, #262), which gives retail's grouped `lq`/`sq` with register addresses. */

typedef int TI128 __attribute__((mode(TI)));

extern float func_00282E48(char *, char *);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(char *, char *, float);

extern void func_00282CC0(void *, void *, void *);

extern float func_00283180(float);

extern float func_00283198(float);

/* Moves the Chainblade's follow point towards its goal point, snapping to it when close and curving the path otherwise. */
void func_L02_003D4ED0(char *self) {
    char *state = *(char **)(self + 0x68);
    char *current = state + 0x2D0;
    char *goal = state + 0x2C0;
    float v[4];

    if (fast_vec_dist(current, goal) < 0.8333334f) {
        *(TI128 *)current = *(TI128 *)goal;
    } else {
        FastVecSub(v, goal, current);
        vec_scale_to_length((char *)v, (char *)v, 0.8333334f);
        v[0] = v[0] * FastSinOrCosA(*(float *)(state + 0x308)) -
               v[1] * FastSinOrCosB(*(float *)(state + 0x308));
        v[1] = v[0] * FastSinOrCosB(*(float *)(state + 0x308)) +
               v[1] * FastSinOrCosA(*(float *)(state + 0x308));
        FastVecAdd(current, current, v);
    }
}
