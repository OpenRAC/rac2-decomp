#include "common.h"
extern void *func_002A9640(void *, int, int);
extern float func_002A96A0(void *, void *);
extern float func_002AA2E8(float *, float, float);
extern void func_002A6C58(void *, int, int);
extern int func_002E5CF8(int, int, char *);
extern void func_002A7750(u8 *, int, int);
extern u8 *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void func_002A7398(void *, int, int);
/* Counts the object's fuse down. When it runs out the object explodes with a sound and effect and resets. */
void func_L07_003F67B8(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    float position[4] __attribute__((aligned(16)));
    float zero = 0.0f;
    float step = UpdateAimTargetStrength(moby, FindOwnedEffectSlot(moby, 0x10000, 0));
    u16 flags;
    ApproachValue((float *)(vars + 0x20), zero, step);
    if (*(float *)(vars + 0x20) <= zero) {
        SetDeathBits(moby, 0, 3);
        PlayMobySound(1, 0, (char *)moby);
        SetMobyState(moby, 1, -1);
        flags = *(u16 *)(moby + 0x34);
        moby[0xA8] = 255;
        flags |= 0x41;
        *(u32 *)(moby + 0x98) = 0;
        flags &= 0xEFFF;
        *(u16 *)(moby + 0x34) = flags;
        qcopy(position, moby + 0x10);
        position[2] += 0.5f;
        SpawnExplosion(moby + 0x10, 0, 0, 0, 0, 10, 20, 0, 1.0f, 20.0f, 1, 0, 0, 0);
        StartAnimationImmediate(moby, 2, 0);
    }
}
