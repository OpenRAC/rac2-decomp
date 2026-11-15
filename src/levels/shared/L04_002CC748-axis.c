/* The default-profile sibling of L04_002CC748.c: this body's two quadword copies
   are a separate lq and sq, not the grouped copy that file's -frac2-qcopy emits. */
#include "common.h"

typedef int L04Quad __attribute__((mode(TI)));

extern void func_00283788(void *dst, void *a, void *b);
extern void func_002AB6D8(f32 *src, f32 *out);
extern f32 func_00283180(f32 angle);
extern f32 func_00283198(f32 angle);
extern void func_L03_002EFB60(void *dst, void *src, f32 scale);
extern void func_L04_0030FA30(void *dst, void *a, void *b);
extern void func_00283388(void *dst);

/* Builds the rotation by angle about axis, I + sin(angle) K + (1 - cos(angle)) K K
   with K the skew matrix of axis, and hands it to func_002AB6D8 with this
   function's own copy of rotation. Both vectors are copied on entry, the way
   16-byte arguments passed by value arrive. */
/* Turns an object by an angle around an axis. */
void func_L04_00344568(f32 angle, void *axis, void *rotation) {
    union { L04Quad q; f32 f[4]; } axis_copy, rotation_copy;
    f32 skew[16];
    f32 square[16];
    f32 sine[16];
    f32 cosine[16];
    f32 result[16];
    f32 x;
    f32 y;
    f32 z;
    f32 *out = rotation_copy.f;

    axis_copy.q = *(L04Quad *)axis;
    z = axis_copy.f[2];
    y = axis_copy.f[1];
    x = axis_copy.f[0];
    rotation_copy.q = *(L04Quad *)rotation;

    /* K, written a column at a time */
    skew[0] = 0;
    skew[4] = -z;
    skew[8] = y;
    skew[12] = 0;
    skew[1] = z;
    skew[5] = 0;
    skew[9] = -x;
    skew[13] = 0;
    skew[2] = -y;
    skew[6] = x;
    skew[10] = 0;
    skew[14] = 0;
    skew[3] = 0;
    skew[7] = 0;
    skew[11] = 0;
    skew[15] = 0;

    multiply_matrix(square, skew, skew);
    func_L03_002EFB60(cosine, square, 1.0f - FastSinOrCosA(angle));
    func_L03_002EFB60(sine, skew, FastSinOrCosB(angle));
    ProcessLevelDrawHelper(sine, sine, cosine);
    set_identity_matrix(cosine);
    ProcessLevelDrawHelper(result, sine, cosine);
    GetEulerAnglesFromMatrix(result, out);
}
