#include "include_asm.h"
#include "common.h"

extern int D_L16_001B1460 __attribute__((sda));
extern int D_L16_001B1464 __attribute__((sda));
extern int D_L16_001B1498 __attribute__((sda));
extern int D_L16_001B149C __attribute__((sda));
extern f32 D_L16_001B14A0 __attribute__((sda));
extern f32 D_L16_001B14A4 __attribute__((sda));
extern s32 func_002A7820(s32, s32);
extern f32 func_002A7940(void);
extern void func_L16_00405818(u8 *, int, f32, int, int, f32, f32, int, u8 *);

/* The level-16 copy of func_L12_004081F8: the func_L16_003E70E0 pair of glow layers with the sizes scaled by the level's factors. */
/* Draws two glow layers at the object's position with random brightness. */
void func_L16_004056A8(u8 *object) {
    DrawBeamQuadsAndGlows(object + 0x10, D_L16_001B1460, D_L16_001B14A0 * *(f32 *)(object + 0x2C),
                        RandomIntRange(0x5F, 0x6F), D_L16_001B1498, RandomAngle(),
                        1.0f, 2, object);
    {
        f32 size = D_L16_001B14A0 * *(f32 *)(object + 0x2C) * D_L16_001B14A4;

        DrawBeamQuadsAndGlows(object + 0x10, D_L16_001B1464, size,
                            RandomIntRange(0x6F, 0x7F), D_L16_001B149C,
                            RandomAngle(), 1.0f, 2, object);
    }
}
