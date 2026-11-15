#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern TI128 D_L11_001BAAF0;

extern f32 D_00189EA0[];

extern void func_00282CF0(void *out, const void *in, const void *matrix);

extern f32 func_00282DB0(const void *a, const void *b);

extern f32 func_00282E80(void *obj, const void *matrix);

extern void func_00282F20(void *out, const void *in, f32 scale);

/* Measures the actor's distance to the level's helper and reports whether it is
   past the level's threshold. */
s32 func_L11_00442B60(u8 *arg) {
    Vector a;
    Vector b;
    Vector c;
    s32 result;

    qcopy(&a,&D_L11_001BAAF0);
    a.f[2] = 0;
    vec_scale_to_length(&a, &a, 1.0f);
    result = 0;
    FastVecSub(&b, arg + 0x10, D_00189EA0);
    b.f[2] = 0;
    vec_scale_to_length(&b, &b, 1.0f);
    FastVecSub(&c, arg + 0x10, D_00189EA0);
    c.f[2] = 0;
    vec_scale_to_length(&c, &c, 1.0f);
    if (FastVecDot(&a,&c) > 0.81915f) {
        if (vec_distance_xy(arg + 0x10, D_00189EA0) > 30.0f) {
            result = 1;
        }
    }
    return result;
}
