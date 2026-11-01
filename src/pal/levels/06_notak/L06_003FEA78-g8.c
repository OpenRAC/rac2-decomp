#include "include_asm.h"

#include "common.h"
extern void func_002C9828(char *, int, float *, float *, int, float);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_002A7878(float, float);
extern float D_L06_001AFCA0 __attribute__((sda));

/* Advance a moving object's path and keep its spacing from the next object. */
void func_PAL_L06_00401D78(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    char *next;
    float phase, pathPosition;
    int length;
    func_002C9828(*(char **)(state + 0x30), *(int *)(state + 0x40),
                 (float *)(moby + 0x10), (float *)(moby + 0xF0), 0, *(float *)(state + 0x10));
    phase = func_00283B98(*(float *)(state + 0x4C), *(float *)(state + 0x50));
    *(float *)(state + 0x4C) = phase;
    *(float *)(moby + 0x18) += D_L06_001AFCA0 * func_00283198(phase);
    length = **(int **)(state + 0x30);
    pathPosition = *(float *)(state + 0x10) + *(float *)(state + 0x14);
    *(float *)(state + 0x10) = pathPosition;
    if ((float)length <= pathPosition)
        *(float *)(state + 0x10) = pathPosition - (float)length;
    if (*(float *)(state + 0x14) > *(float *)(state + 0x38))
        *(float *)(state + 0x14) -= *(float *)(state + 0x18);
    else
        *(float *)(state + 0x14) += *(float *)(state + 0x18);
    next = *(char **)(state + 0x34);
    if (next && next != moby) {
        char *other = *(char **)(next + 0x68);
        float nextSpeed;
        float gap = *(float *)(other + 0x10) - *(float *)(state + 0x10);
        float ownSpeed;
        if (gap < 0.0f)
            gap += (float)**(int **)(state + 0x30);
        nextSpeed = *(float *)(other + 0x38);
        ownSpeed = *(float *)(state + 0x38);
        if (nextSpeed < ownSpeed) {
            float difference = ownSpeed - nextSpeed;
            float deceleration = *(float *)(state + 0x18);
            float nextMargin = *(float *)(other + 0x1C);
            float ownMargin = *(float *)(state + 0x1C);
            deceleration += deceleration;
            /* The shared source line preserves the measured debug-label padding. */
            difference *= difference; if (gap < difference / deceleration + nextMargin + ownMargin) {
                *(float *)(other + 0x38) = ownSpeed;
                *(float *)(state + 0x38) = nextSpeed;
            }
        }
        if (*(unsigned char *)(*(char **)(state + 0x34) + 0x20) == 2 &&
            gap < *(float *)(state + 0x1C) * 3.0f) {
            *(float *)(state + 0x5C) = *(float *)(state + 0x38);
            *(int *)(state + 0x38) = 0;
        }
        if (*(unsigned char *)(*(char **)(state + 0x34) + 0x20) == 3) {
            *(float *)(state + 0x38) = *(float *)(state + 0x5C);
            *(char **)(state + 0x34) = *(char **)(other + 0x34);
        }
        if (*(float *)(state + 0x38) != 0.0f)
            return;
        if (*(float *)(other + 0x38) == 0.0f)
            return;
        *(float *)(state + 0x38) = *(float *)(other + 0x38);
    } else {
        float random = func_002A7878(*(float *)(state + 8), *(float *)(state + 0xC));
        *(float *)(state + 0x38) = (*(float *)(state + 0x60) * (0.020000001f)) * random;
    }
}
