#include "common.h"

extern u8 D_00189EA0[];
extern u32 D_001A79F0 MACRO_ADDR;
extern s32 D_002A0D50[];
extern f32 func_00282E48(u8 *, u8 *);
extern void func_L00_00321878(u8 *, s32, s32, s32, s32, s32, f32);

/* Spawns bolts from an object; the amount grows with the level, and the bolts are picked up automatically when the player is close. */
void func_L00_00326110(u8 *object, s32 multiplier, f32 height) {
    s32 mode = 1;
    u32 level;
    s32 amount;

    if (fast_vec_dist(object + 0x10, gHeroPosition) < 7.0f)
        mode = 3;
    level = gCurrentMapIndex;
    if (level > 25)
        level = 25;
    amount = D_002A0D50[level] * multiplier - 1;
    SpawnBoltPickups_L00(object, amount, amount, mode, -1, 0, height);
}
