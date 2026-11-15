#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_002833F0(u8 *, u8 *);
extern void func_00282CC0(u8 *, u8 *, u8 *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
extern float func_002A7878(float, float);
extern float func_002A89A8(void *, int, float);
extern void func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern int func_002E5CF8(int, int, void *);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern void func_0029F338(void *);

/* Updates a falling Siberius debris piece (moby class 4776): it drifts down, hurts what it touches, then bursts into an effect and disappears. */
void func_L07_00410C50(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    TI128 effect;
    float length, ratio;
    switch (moby[0x20]) {
    case 0:
        *(unsigned short *)(moby + 0x34) |= 0x100;
        euler_rotation_basis(moby + 0xc0, moby + 0xf0);
        if (*(int *)(vars + 0xc) == 1) FastVecScale(moby + 0xe0, moby + 0xe0, 2.0f);
        else if (*(int *)(vars + 0xc) == -1) FastVecScale(moby + 0xe0, moby + 0xe0, 0.5f);
        if (*(int *)(vars + 0x24) == 0) {
            *(int *)(vars + 0x10) = 0;
            *(int *)(vars + 0x14) = 0;
            *(float *)(vars + 0x18) = -(RandomFloatRange(3.0f, 6.0f) * 0.016666668f);
        } else FastVecScale(vars + 0x10, vars + 0x10, 0.016666668f);
        *(float *)(vars + 4) = RandomFloatRange(13.0f, 20.0f) * 0.00027777778f;
        length = FastVecLength(moby + 0xe0);
        ratio = *(float *)(moby + 0x2c) / *(float *)(*(char **)(moby + 0x24) + 0x24);
        ratio *= length * -10.0f;
        *(float *)(vars + 0x20) = ratio;
        if (*(float *)(vars + 8) == 0.0f)
            *(float *)(vars + 8) = ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (FindOwnedEffectSlot(moby, 0x4010000, 0) && !*(int *)vars)
            SetMobyState(moby, 2, -1);
        moby[0xa8] = 255;
        break;
    case 2:
        FastVecAdd(moby + 0x10, moby + 0x10, vars + 0x10);
        *(float *)(vars + 0x18) -= *(float *)(vars + 4);
        if (*(int *)(vars + 0x24)) {
            ComputeMobyLocalPoint(moby, &effect, 0.0f, 0.0f, *(float *)(vars + 0x20));
            SweepCollisionFromObject(moby, &effect, 0x4010000, 0, 1, 0, 2.0f * (*(float *)(moby + 0x2c) / *(float *)(*(char **)(moby + 0x24) + 0x24)), 8.0f, 1.0f);
        }
        if (*(float *)(moby + 0x18) + *(float *)(vars + 0x20) < *(float *)(vars + 8))
            SetMobyState(moby, 4, -1);
        break;
    case 4:
        PlayMobySound(0, 0, moby);
        if (moby[0x31]) {
            effect = 0;
            ((float *)&effect)[2] = 0.050000004f;
            SpawnDebrisForMaskedParts(moby, 3, &effect, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        }
        MarkMobySpawned(moby);
        break;
    }
}
