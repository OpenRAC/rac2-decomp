/* functional: high. Plain integer and float conversions in place of MMI and VU0 macro code. */
#include "common.h"

/* Unpacks a packed keyframe (three vectors of four halfwords) into three vectors of four words:
   rotation in Q15; translation unsigned Q12, its fourth word the raw value << 3; scale as plain
   integers, its fourth word the raw value. */
void func_00283AF0(void *source, void *destination)
{
    short *in = source;
    float *out = destination;
    int i;

    for (i = 0; i < 4; i++) {
        out[i] = (float)in[i] * (1.0f / 32768.0f);
    }
    for (i = 0; i < 3; i++) {
        out[4 + i] = (float)((int)(unsigned short)in[4 + i] << 3) * (1.0f / 32768.0f);
    }
    ((int *)out)[7] = (int)(unsigned short)in[7] << 3;
    for (i = 0; i < 3; i++) {
        out[8 + i] = (float)in[8 + i];
    }
    ((int *)out)[11] = in[11];
}
