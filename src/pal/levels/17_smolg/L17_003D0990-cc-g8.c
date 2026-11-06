/* func_PAL_L17_003D0990, the PAL copy of func_L17_003CC6A8: the same C, where the measured
   60.0f frame count becomes the 50 Hz (x * 300.0f + 2.0f) * 0.16666667f. */
#include "common.h"

/* This unit is built with -G8: every body here reaches a global through $gp. */

extern int func_00283CF0(f32);

extern s32 func_L17_00340DD0(f32, s32, s32, s32);

extern f32 D_L17_001B04B8 __attribute__((sda));

/* Counts the record's own timer down once, then hands the sub-object's four packed
   colour bytes and the measured scale to the level's own setter. */
void func_PAL_L17_003D0990(s32 a0)
{
    s32 obj = a0;
    u32 *p = *(u32 **)(obj + 0x68);
    u32 packed;
    s32 r;
    f32 f20;

    if (*(u8 *)(obj + 0x20) == 0) {
        u8 one = 1;

        *(u8 *)(obj + 0x30) = 0xFF;
        *(u16 *)(obj + 0x96) = one;
        *(u8 *)(obj + 0x20) = one;
    }
    {
        s32 v = (s32)*(u16 *)(obj + 0x96) - 1;

        *(u16 *)(obj + 0x96) = v;
        if ((u16)v != 0)
            return;
    }
    packed = p[3] << 24;
    packed |= p[2] << 16;
    packed |= p[1] << 8;
    packed |= p[0];
    f20 = *(f32 *)&p[4] * 210000.0f;
    r = func_00283CF0((D_L17_001B04B8 * 300.0f + 2.0f) * 0.16666667f);
    if (func_L17_00340DD0(f20, obj, packed, r) != 0)
        *(u16 *)(obj + 0x96) = func_00283CF0((D_L17_001B04B8 * 300.0f + 2.0f) * 0.16666667f);
    else
        *(u16 *)(obj + 0x96) = 1;
}
