#include "common.h"
/* Same measured hero view used by func_L00_002B3D10. */
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; } MovementHero;
extern u8 D_00189E20[];
extern float D_001A7DB0[] MACRO_ADDR;
extern void func_L00_002B39F0(int, float);
/* Calls a hero helper, then if a hero speed value is above zero, recomputes it from the hero timer. */
void func_L01_002B46A0(void)
{
    ResolveStickInputToDirection(0, 1.0f);
    if (0.0f < ((MovementHero *)gHeroState)->f[0x1b0 / 4])
        ((MovementHero *)gHeroState)->f[0x1b0 / 4] = D_001A7DB0[4] * (((MovementHero *)gHeroState)->f[0x24b8 / 4] * 0.016666668f);
}
