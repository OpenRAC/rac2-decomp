#include "include_asm.h"
#include "common.h"
extern s8 D_0022AA10[];
extern void gfx_draw_lightning_bolt(s32 a, s32 b);
extern void gfx_draw_billboard_quad(void *o, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14);
extern f32 math_random_float_range(f32 a, f32 b);

void func_PAL_00317EF8(s32 arg0) {
    s32 i;
    s32 q;
    s8 *p;
    s8 *base;

    base = D_0022AA10;
    p = base + 0x30;
    q = (s32) base;
    for (i = 0; i < 3; i++) {
        if ((*(s32 *)((s8 *)(p) + (0x5C))) == arg0) {
            gfx_draw_lightning_bolt(arg0, q);
            if ((*(s32 *)((s8 *)(p) + (0x64))) == 0) {
                gfx_draw_billboard_quad(p, 0x31, 0x3F007F00, 1, math_random_float_range(0.125f, 0.25f) * 5.0f, 1.25f, 0.0f);
                gfx_draw_billboard_quad(p, 0x31, 0x5F7F7F7F, 1, math_random_float_range(0.0625f, 0.125f) * 5.0f, 1.24f, 0.0f);
                gfx_draw_billboard_quad(p, 0xB, 0x10003F00, 1, math_random_float_range(0.15f, 0.35f) * 5.0f, 1.23f, 0.0f);
            }
        }
        p += 0xA0;
        q += 0xA0;
    }
}
