#include "common.h"


typedef int V4 __attribute__((mode(TI)));
extern float func_002A89A8(void *a0, int a1, float f12);
extern int func_00278E78(void);
extern void func_002ACB48(float *v, float f);
extern float func_L01_003BAFB0(void);
extern float func_002A7878(float a, float b);
extern int func_002A77E0(int a);
extern void func_002C19D8(char *a0, int a1, int a2, float f12, float f13);
extern float func_00282DF0(void *a0);
extern f32 D_L01_001AFE18[];

/* Same body as func_L01_003B4480, with this function's own callees. */
/* Makes bubbles while the object moves and spawns a splash when it is fast enough. */
void func_L01_003DBF38(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    float bubblePos[4];
    float size;
    int i;

    ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
    if (GetCollHitMaterial() != 3)
        return;
    {
        u8 *objPos = moby + 0x10;
        u8 *velocityVec = state + 0x190;
        i = 0;
        while (i >= 0) {
            *(V4 *)bubblePos = *(V4 *)objPos;
            AddRandomOffsetToVector(bubblePos, 0.1f);
            bubblePos[2] = GetWaterHeight();
            size = RandomFloatRange(0.2f, 2.0f);
            SpawnDriftingParticle_002C19D8((char *)bubblePos, (int)D_L01_001AFE18,
                          (int)((((u32)RandomIntBelow(6) + 0x14) << 24) | 0x5060), size, 10000.0f);
            i--;
        }
        if (0.0333333333f < FastVecLength(velocityVec))
            SpawnWaterSplashEffects_L01_2(moby, 3, 10, 1);
    }
}
