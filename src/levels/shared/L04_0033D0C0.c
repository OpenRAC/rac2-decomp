#include "common.h"
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_L04_0033CC00(char *,char *,float *,float *,float);
/* Looks at a point 100 units in front of an object and passes it on. */
void func_L04_0033D0C0(char *srcMoby, char *otherMoby)
{
    float ahead[4];
    float result[4];
    float *src = (float *)(srcMoby + 0x10);

    qcopy(ahead, src);
    {
        float x = ahead[0] + FastSinOrCosA(*(float *)(srcMoby + 0xF8)) * 100.0f;
        float angle = *(float *)(srcMoby + 0xF8);
        ahead[0] = x;
        ahead[1] += FastSinOrCosB(angle) * 100.0f;
    }
    MoveMobyTowardTarget(srcMoby, otherMoby, ahead, result, 1.0f);
}
