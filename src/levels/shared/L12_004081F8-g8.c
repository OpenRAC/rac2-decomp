#include "include_asm.h"
#include "common.h"

extern int D_L12_001B1520 __attribute__((sda));
extern int D_L12_001B1524 __attribute__((sda));
extern int D_L12_001B1558 __attribute__((sda));
extern int D_L12_001B155C __attribute__((sda));
extern f32 D_L12_001B1560 __attribute__((sda));
extern f32 D_L12_001B1564 __attribute__((sda));
extern s32 func_002A7820(s32, s32);
extern f32 func_002A7940(void);
extern void ref_L12_004081F8_00(u8 *, int, f32, int, int, f32, f32, int, u8 *);

/* The func_L16_003E70E0 pair of glow layers with the sizes scaled by the level's factors. */
/* Draws the two glow layers around a blast projectile. */
void func_L12_004081F8(u8 *moby) {
    ref_L12_004081F8_00(moby + 0x10, D_L12_001B1520, D_L12_001B1560 * *(f32 *)(moby + 0x2C),
                        RandomIntRange(0x5F, 0x6F), D_L12_001B1558, RandomAngle(),
                        1.0f, 2, moby);
    {
        f32 size = D_L12_001B1560 * *(f32 *)(moby + 0x2C) * D_L12_001B1564;

        ref_L12_004081F8_00(moby + 0x10, D_L12_001B1524, size,
                            RandomIntRange(0x6F, 0x7F), D_L12_001B155C,
                            RandomAngle(), 1.0f, 2, moby);
    }
}
