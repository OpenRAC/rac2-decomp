#include "common.h"
typedef int Snapshot128 __attribute__((mode(TI)));
extern u8 D_L01_002A4D50[],D_00189EA0[];
extern float D_L01_001B0420 __attribute__((sda));
extern float D_L01_001B0424 __attribute__((sda));
extern float D_L01_001B0428 __attribute__((sda));
extern float D_L01_001B042C __attribute__((sda));
extern float D_L01_001B0430 __attribute__((sda));
extern float D_L01_001B0434 __attribute__((sda));
extern void func_0026FEB8(void *,int,int);
extern float func_L01_003BAFB0(void);
extern float func_002A7940(void);
extern void func_002A7750(void *,int,int);
extern void func_002AEF28(void *,void *,void *,float,float,float);
extern float func_L01_003CE7D8(float *,float *,float,float,float,float);
extern float func_00282E80(void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
/* Initializes a floating object and keeps its motion above the water surface. */
/* Drifts on the water, bobbing with the waves. It is nudged aside when the hero gets close. */
void func_L01_003CE868(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    float snapshots[2][4] __attribute__((aligned(16)));
    float pushVec[4] __attribute__((aligned(16)));
    float waterHeight, heroDistance, delta;

    if (!vars) {
        STUB_printf(D_L01_002A4D50, *(s16 *)(moby + 0xAA), *(s16 *)(moby + 0xB2));
        return;
    }
    switch (moby[0x20]) {
    case 0:
        if (GetWaterHeight() > 0.0f) {
            *(float *)(vars + 0x20) = RandomAngle();
            *(float *)(vars + 0x24) = RandomAngle();
            *(float *)(vars + 0x28) = 0.02f;
            qcopy(vars, moby + 0x10);
            SetMobyState(moby, 1, -1);
        }
        break;
    case 1:
        /* Retail takes two position snapshots before updating movement. */
        *(Snapshot128 *)snapshots[0] = *(Snapshot128 *)(moby + 0x10);
        *(Snapshot128 *)snapshots[1] = *(Snapshot128 *)snapshots[0];
        waterHeight = GetWaterHeight();
        ScaleOwnerWordsByAngles(moby, vars + 0x20, vars + 0x24, D_L01_001B0420,
                      D_L01_001B0424 * 0.00029088825f,
                      D_L01_001B0428 * 0.00029088825f);
        StepDampedSpring((float *)(moby + 0x10), (float *)(vars + 0x10), *(float *)vars,
                          D_L01_001B042C * 0.00027777778f, D_L01_001B0430, 3.0f);
        StepDampedSpring((float *)(moby + 0x14), (float *)(vars + 0x14), *(float *)(vars + 4),
                          D_L01_001B042C * 0.00027777778f, D_L01_001B0430, 3.0f);
        heroDistance = vec_distance_xy(moby + 0x10, gHeroPosition);
        if (heroDistance < D_L01_001B0434 &&
            *(float *)(gHeroPosition + 8) < *(float *)(moby + 0x18) + 0.8f) {
            FastVecSub(pushVec, moby + 0x10, gHeroPosition);
            pushVec[2] = 0;
            vec_scale_to_length(pushVec, pushVec, (D_L01_001B0434 - heroDistance) * 0.08f);
            FastVecAdd(moby + 0x10, moby + 0x10, pushVec);
        }
        delta = waterHeight + *(float *)(vars + 0x28) - *(float *)(moby + 0x18);
        if (delta > 0.050000004f)
            delta = 0.050000004f;
        else if (delta < -0.050000004f)
            delta = -0.050000004f;
        *(float *)(moby + 0x18) += delta;
        break;
    }
}
