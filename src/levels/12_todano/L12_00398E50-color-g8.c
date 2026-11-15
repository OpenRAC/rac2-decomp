#include "common.h"
extern f32 D_L12_001AF694 __attribute__((sda));
extern s32 D_L12_001AF68C __attribute__((sda)), D_L12_001AF690 __attribute__((sda));
extern s32 D_001A79F0 MACRO_ADDR;
extern f32 func_00283B98(f32, f32);
extern f32 func_00283198(f32);
extern s32 func_00283D38(s32, s32, f32);
extern void func_L12_003A6EF8(void *);
extern void func_002A0488(void *, s32, s32, s32);
/* Moby class 1060 update. Fades the moby's color back and forth between two colors. */
void func_L12_003A6F48(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    switch (object[0x20]) {
    case 0:
        *(f32 *)state *= 0.017453294f;
        object[0x20] = 1;
        break;
    case 1: {
        s32 color, alpha;
        s32 r, g, b;
        u32 packed;
        *(f32 *)state = FastAddRotations(*(f32 *)state, D_L12_001AF694 * 0.000290888245f);
        color = FastTweenColor(D_L12_001AF68C, D_L12_001AF690, FastSinOrCosB(*(f32 *)state) * 0.5f + 0.5f);
        b = (color >> 16) & 255;
        g = (color >> 8) & 255;
        r = color & 255;
        alpha = 0x38;
        if (gCurrentMapIndex == 0 || gCurrentMapIndex == 0x12) alpha = 0x20;
        packed = alpha << 24;
        packed |= b << 16;
        packed |= g << 8;
        packed |= r;
        *(u32 *)(state + 4) = packed;
        SyncObjectWithLevelSetting(object);
        set_moby_color(object, color & 255, (color >> 16) & 255, (u32)color >> 24);
        break;
    }
    }
}
