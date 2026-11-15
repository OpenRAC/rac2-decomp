#include "names.h"
typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
extern u8 *D_L11_001B359C;
extern int D_L11_001A8FF4;
extern int D_L11_001B30C8;
extern int D_L11_001B2AAC __attribute__((sda));
extern float D_L11_001B2AA0 __attribute__((sda));
extern float D_L11_001B2AA4 __attribute__((sda));
extern float D_L11_001B2AA8 __attribute__((sda));
extern float D_L11_001B2AB0 __attribute__((sda));
extern int func_L02_00400B00(u8 *);
extern int func_00283DB8(float *, float);
extern void func_L02_0042ED48(u8 *);
extern int func_002B3868(u8 *);
extern int func_002A77E0(int);
extern void func_002A7470(u8 *, int, int, int);
extern void func_002A7750(u8 *, int, int);
extern u8 *func_L11_004417E8(u8 *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00283B98(float, float);

/* Updates an arena crowd member (moby class 4718): it switches between idle, cheering and clapping as the crowd excitement rises and falls. */
void func_L11_00474920(u8 *object) {
    float bounds[4];
    float center[4];
    int *state = *(int **)(object + 0x68);
    u8 *target;
    float level, angle, heading, delta;
    int animation;
    if (!IsMobyStateAtLeast2(gMobyTable_L11 + *state * 0x100)) return;
    *(Quadword *)center = 0;
    center[0] = *(float *)(object + 0x10);
    center[1] = *(float *)(object + 0x14);
    center[2] = *(float *)(object + 0x18);
    center[3] = 5.0f;
    *(Quadword *)bounds = *(Quadword *)center;
    if (FastMathHelperA(bounds, 255.0f) <= 0 || D_L11_001A8FF4) {
        *(unsigned short *)(object + 0x32) = 0;
        return;
    }
    *(unsigned short *)(object + 0x32) = 255;
    StartIdleAnimationVariant(object);
    target = (u8 *)(*state * 0x100 + (int)gMobyTable_L11);
    level = *(float *)(*(u8 **)(target + 0x68) + 0x14C);
    switch (object[0x20]) {
    case 1:
        if (SetFirstPendingFlag(object) && object[0x43] != RandomIntBelow(2)) {
            animation = RandomIntBelow(2);
            StartAnimationBlended(object, animation, 0, 10);
        }
        if (level > D_L11_001B2AA8 && !RandomIntBelow(60)) {
            SetMobyState(object, 2, -1);
        } else if (level < D_L11_001B2AA0 && !RandomIntBelow(60)) {
            SetMobyState(object, 3, -1);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(object)) {
            if (object[0x43] != RandomIntBelow(2) + 2) {
                animation = RandomIntBelow(2);
                StartAnimationBlended(object, animation + 2, 0, 10);
            }
            return;
        }
        if (level < D_L11_001B2AA4 && !RandomIntBelow(60)) SetMobyState(object, 1, -1);
        break;
    case 3:
        angle = ((float)(D_L11_001B30C8 % D_L11_001B2AAC) * -6.2831855f) / (float)D_L11_001B2AAC + 3.1415927f;
        delta = *(float *)(object + 0x10) - *(float *)GetArenaCenterPoint(target);
        target = GetArenaCenterPoint(gMobyTable_L11 + *state * 0x100);
        heading = FastMatrixHelperA(delta, *(float *)(object + 0x14) - *(float *)(target + 4));
        if (FastDiffRots(heading, angle) < D_L11_001B2AB0 ||
            FastDiffRots(heading, FastAddRotations(angle, 3.1415927f)) < D_L11_001B2AB0) {
            if (object[0x43] != 4) StartAnimationBlended(object, 4, 0, 10);
        } else if ((object[0x60] & 2) && object[0x43] != RandomIntBelow(2)) {
            animation = RandomIntBelow(2);
            StartAnimationBlended(object, animation, 0, 10);
        }
        if (level > D_L11_001B2AA4 && !RandomIntBelow(60)) SetMobyState(object, 1, -1);
        break;
    }
}
