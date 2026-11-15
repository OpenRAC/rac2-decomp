#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern unsigned char *D_001F259C;

/* Spawns a spinning spark near position (jittered by up to jitter on each axis)
   turning about axis at a random speed between lo and hi, in either direction. */
char *func_002BDCE8(TI128 *position, int spin, TI128 *axis, int colour, int count,
                     float jitter, float lo, float hi, float size)
{
    char *p = AllocParticle(0x17);
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
        p[2] = *D_001F259C;
        *(float *)(p + 0x10) += RandomSignedFloatRange(0.0f, jitter);
        *(float *)(p + 0x14) += RandomSignedFloatRange(0.0f, jitter);
        *(float *)(p + 0x18) += RandomSignedFloatRange(0.0f, jitter);
        *(float *)(p + 0x1C) = IntToFloat(count);
        *(short *)(p + 0xA) = 10;
        *(int *)(m + 4) = 0;
        *(int *)(p + 0x20) = colour;
        *(short *)(m + 8) = FloatToInt(RandomIntBelow(2) ? (float)spin : (float)-spin);
        *(float *)(m + 0xC) = RandomFloatRange(lo, hi);
        *(TI128 *)(m + 0x10) = *axis;
        *(float *)(m + 0x1C) = IntToFloat(0x1E);
    }
    return p;
}
