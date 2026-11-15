#include "common.h"
extern f32 D_L12_001AF694 __attribute__((sda));
extern s32 D_L12_001AF68C __attribute__((sda)), D_L12_001AF690 __attribute__((sda));
extern s32 g_current_map_index MACRO_ADDR;
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern s32 FastTweenColor(s32, s32, f32);
extern void moby_sync_level_setting(void *);
extern void set_moby_color(void *, s32, s32, s32);
/* Moby class 1060 update. Fades the moby's color back and forth between two colors. */
void color_l12_fade_update(u8 *object)
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
        color = FastTweenColor(D_L12_001AF68C, D_L12_001AF690, math_fast_sin_or_cos_b(*(f32 *)state) * 0.5f + 0.5f);
        b = (color >> 16) & 255;
        g = (color >> 8) & 255;
        r = color & 255;
        alpha = 0x38;
        if (g_current_map_index == 0 || g_current_map_index == 0x12) alpha = 0x20;
        packed = alpha << 24;
        packed |= b << 16;
        packed |= g << 8;
        packed |= r;
        *(u32 *)(state + 4) = packed;
        moby_sync_level_setting(object);
        set_moby_color(object, color & 255, (color >> 16) & 255, (u32)color >> 24);
        break;
    }
    }
}
