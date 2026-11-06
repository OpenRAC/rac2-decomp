/* func_PAL_002BE9A8, the PAL copy of func_002BDCE8: the same C, where 10 becomes 8, 30 becomes 25,
   and the spin is multiplied by 1.2f, written out in each arm of its sign test. */
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
char *func_PAL_002BE9A8(TI128 *position, int spin, TI128 *axis, int colour, int count,
                     float jitter, float lo, float hi, float size)
{
    char *p = func_002B9030(0x17);
    char *m;
    if (p != 0) {
        *(TI128 *)(p + 0x10) = *position;
        *(int *)(p + 4) = colour | 0x20000000;
        m = p + 0x20;
        p[9] = func_00283CF0(4.0f) + 0x70;
        p[3] = 0x48;
        *(float *)(p + 0xC) = size;
        p[1] = 0;
        p[8] = 0;
        p[2] = *D_001F259C;
        *(float *)(p + 0x10) += func_002A78D8(0.0f, jitter);
        *(float *)(p + 0x14) += func_002A78D8(0.0f, jitter);
        *(float *)(p + 0x18) += func_002A78D8(0.0f, jitter);
        *(float *)(p + 0x1C) = func_00283CE0(count);
        *(short *)(p + 0xa) = 8;
        *(int *)(m + 4) = 0;
        *(int *)(p + 0x20) = colour;
        if (func_002A77E0(2)) {
            *(short *)(m + 8) = func_00283CF0((float)spin * 1.2f);
        } else {
            *(short *)(m + 8) = func_00283CF0((float)-spin * 1.2f);
        }
        *(float *)(m + 0xC) = func_002A7878(lo, hi);
        *(TI128 *)(m + 0x10) = *axis;
        *(float *)(m + 0x1C) = func_00283CE0(0x19);
    }
    return p;
}
