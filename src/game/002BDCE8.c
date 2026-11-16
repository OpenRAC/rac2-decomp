#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern char *part_alloc(int);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern unsigned char *g_part_tex_trail;

/* Spawns a spinning spark near position (jittered by up to jitter on each axis)
   turning about axis at a random speed between lo and hi, in either direction. */
char *SpawnSpinningSparkParticle(TI128 *position, int spin, TI128 *axis, int colour, int count,
                     float jitter, float lo, float hi, float size)
{
    char *p = part_alloc(0x17);
    char *m;
    if (p != 0) {
        *(TI128 *)(p + 0x10) = *position;
        *(int *)(p + 4) = colour | 0x20000000;
        m = p + 0x20;
        p[9] = FloatToInt(4.0f) + 0x70;
        p[3] = 0x48;
        *(float *)(p + 0xC) = size;
        p[1] = 0;
        p[8] = 0;
        p[2] = *g_part_tex_trail;
        *(float *)(p + 0x10) += math_random_signed_float_range(0.0f, jitter);
        *(float *)(p + 0x14) += math_random_signed_float_range(0.0f, jitter);
        *(float *)(p + 0x18) += math_random_signed_float_range(0.0f, jitter);
        *(float *)(p + 0x1C) = IntToFloat(count);
        *(short *)(p + 0xA) = 10;
        *(int *)(m + 4) = 0;
        *(int *)(p + 0x20) = colour;
        *(short *)(m + 8) = FloatToInt(math_random_int_below(2) ? (float)spin : (float)-spin);
        *(float *)(m + 0xC) = math_random_float_range(lo, hi);
        *(TI128 *)(m + 0x10) = *axis;
        *(float *)(m + 0x1C) = IntToFloat(0x1E);
    }
    return p;
}
