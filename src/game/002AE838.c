#include "names.h"
/* func_002AE838: normalises a byte-colour vector: subtracts (127, 127, 127, 0) from the
 * vector func_002830F0 builds and scales it by w * 0.0001 into the first argument.
 * func_00282D30 takes (dst, src, scale), and the scale is read before the subtraction,
 * as in retail. The (127, 127, 127, 0) vector is written through its float fields, so
 * its address is rebuilt at the call instead of being held in a saved register. */
typedef __attribute__((mode(TI))) int TI;

extern void FastVectorFromPackedChars(void *dst, float *src);
extern void FastVecSub(void *dst, void *a, void *b);
extern void FastVecScale(void *dst, void *src, float scale);

/* Turns a packed colour value into a small vector centred on zero and scaled down. */
void vec_decode_byte_color(void *result, void *source)
{
    struct { float x, y, z, w; } color;
    union { TI q; float f[4]; } bias;
    float scale;

    bias.q = 0;
    bias.f[0] = 127.0f;
    bias.f[1] = 127.0f;
    bias.f[2] = 127.0f;
    FastVectorFromPackedChars(&color, *(float **)source);
    scale = color.w * 0.0001f;
    FastVecSub(&color, &color, &bias);
    FastVecScale(result, &color, scale);
}
