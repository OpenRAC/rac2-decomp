#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern float fast_vec_dist(char *, char *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);

void func_PAL_L02_003D8F90(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *dst = state + 0x2D0;
    char *src = state + 0x2C0;
    float v[4];

    if (fast_vec_dist(dst, src) < 1.0000001f) {
        *(TI128 *)dst = *(TI128 *)src;
    } else {
        FastVecSub(v, src, dst);
        vec_scale_to_length((char *)v, (char *)v, 1.0000001f);
        v[0] = v[0] * math_fast_sin_or_cos_a(*(float *)(state + 0x308)) -
               v[1] * math_fast_sin_or_cos_b(*(float *)(state + 0x308));
        v[1] = v[0] * math_fast_sin_or_cos_b(*(float *)(state + 0x308)) +
               v[1] * math_fast_sin_or_cos_a(*(float *)(state + 0x308));
        FastVecAdd(dst, dst, v);
    }
}
