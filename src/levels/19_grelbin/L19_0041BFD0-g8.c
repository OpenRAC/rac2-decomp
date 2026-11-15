#include "common.h"

extern void func_002A7750(void *, int, int);
extern int D_L19_001B1D20 __attribute__((sda));
extern int D_L19_001B2508;
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern float func_002A89A8(void *, int, float);
extern float func_002A78D8(float, float);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_002A7470(void *, int, int, int);
extern int func_002B0ED8(void *, void *, int);
extern void func_L19_0041C328(void *);
extern int func_002B3BA8(void *, int, float, float, void *, int);

/* Sets up a Y.E.T.I. on its first frame (speed, turning and size). Returns 1 when the Y.E.T.I. is done and should be removed. */
int func_L19_0041BFD0(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    if (*(u8 *)(moby + 0x20) == 0) {
        gActiveYetiCount = 0;
        *(u8 *)(vars + 0x48) = FloatToInt(15.0f);
        *(u8 *)(vars + 0x4A) = FloatToInt(14.4f);
        *(u8 *)(vars + 0x29) = 1;
        if (RandomIntBelow(2)) *(u16 *)(moby + 0x34)|=0x8000;
        *(float *)(moby + 0x2C)*=1.45f;
        *(float *)(moby + 0x18) = ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34)|1)&0xEFFF;
        *(u8 *)(moby + 0x31) = 0;
        *(int *)(moby + 0x98) = 0;
        *(int *)(vars + 0x268) = 0;
        *(float *)(vars + 0x270) = RandomSignedFloatRange(5.0f, 25.0f)*0.0174532942474f;
        qcopy(vars + 0x210, moby + 0x10);
        *(u8 *)(vars + 0x150) = 25;
        *(int *)(vars + 0x188) = 3;
        *(u8 *)(vars + 0x156) = 9;
        *(u8 *)(vars + 0x151) = 14;
        *(float *)(vars + 0x17C) = 0.15f;
        *(float *)(vars + 0x30) = 1.5f;
        *(float *)(vars + 0x170) = 0.5f;
        *(float *)(vars + 0x174) = 0.5f;
        *(u8 *)(vars + 0x1B7) = 1;
        *(u8 *)(vars + 0x2E) = 1;
        if (*(short *)(vars + 0x24) == 0) {
            *(short *)(vars + 0x24) = 1;
            *(float *)(vars + 0x20) = 1.0f;
        }
        *(float *)(vars + 0x84) = 0.5f;
        *(float *)(vars + 0x54) = 0.8f;
        *(float *)(vars + 0x50) = 1.0f;
        *(float *)(vars + 0x58) = 0.75f;
        *(float *)(vars + 0x5C) = 0.75f;
        *(float *)(vars + 0x60) = 1.57079648972f;
        *(float *)(vars + 0x80) = 0.52359885f;
        SetControllerSpeedLimits(moby, 0.0033333334f, 0.10000001f, 0.00698131788522f, 0.8377582f);
        SetMobyState(moby, 1, 0);
        if (*(u8 *)(moby + 0x43) != 12) StartAnimationBlended(moby, 12, 0, 0);
    }
    if (*(u8 *)(vars + 0x2E) == 2) {
        gActiveYetiCount--;
        return 1;
    }
    if (ApplyDamageToObject(moby, vars + 0x140, 0)) MarkGroupEntities(moby);
    if (gFrameCounter_L19 >= 6) {
        *(int *)(vars + 0x278) = SelectAimTarget_002B3BA8(moby, *(int *)(vars + 0x228), *(float *)(vars + 0x22C), 10.0f, vars + 0x210, 0);
        *(int *)(vars + 0x27C) = SelectAimTarget_002B3BA8(moby, *(int *)(vars + 0x220), *(float *)(vars + 0x224), 10.0f, vars + 0x210, 0);
    }
    return 0;
}
