/* func_L01_003B4480 in its own unit: it copies 128 bits, and the retail's copy keeps
   both addresses in registers, which is the compiler's opt-in grouped copy
   (-frac2-qcopy, config/cflags.txt). The flag changes every TImode copy in a unit,
   so the unit holds this function alone. */

#include "common.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef int V4 __attribute__((mode(TI)));

extern float func_002A89A8(void *a0, int a1, float f12);
extern int func_00278E78(void);
extern void func_002ACB48(float *v, float f);
extern float func_L01_003BAFB0(void);
extern float func_002A7878(float a, float b);
extern int func_002A77E0(int a);
extern void func_002C19D8(char *a0, int a1, int a2, float f12, float f13);
extern float func_00282DF0(void *a0);
extern void func_L01_003B4200(void *a0, int a1, int a2, int a3);

/* The float the second argument of func_002C19D8 points at. */
extern f32 D_L01_001AFE18[];

/* Makes bubbles rise from the object when the game is in the right mode, and a splash when the object is moving fast. */
void func_L01_003B4480(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float bubblePos[4];
    float value;
    int i;

    ProbeGroundHeightBelow(object + 0x10, 0, 0.5f);
    if (GetCollHitMaterial() != 3)
        return;
    {
        u8 *srcPos = object + 0x10;
        u8 *speedVec = state + 0xE0;
        i = 0;
        while (i >= 0) {
            *(V4 *)bubblePos = *(V4 *)srcPos;
            AddRandomOffsetToVector(bubblePos, 0.15f);
            bubblePos[2] = GetWaterHeight();
            value = RandomFloatRange(0.3f, 2.5f);
            SpawnDriftingParticle_002C19D8((char *)bubblePos, (int)D_L01_001AFE18,
                          (int)((((u32)RandomIntBelow(6) + 0x14) << 24) | 0x5060), value, 11000.0f);
            i--;
        }
        value = 0.0333333333f;
        if (value < FastVecLength(speedVec) || value < FastVecLength(state + 0x2F0))
            SpawnWaterSplashEffects_L01(object, 3, 10, 1);
    }
}
