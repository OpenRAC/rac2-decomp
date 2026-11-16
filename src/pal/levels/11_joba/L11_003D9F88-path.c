#include "include_asm.h"

#include "common.h"
extern void moby_set_state(u8 *, s32, s32);
extern s32 FloatToInt(f32);
extern float math_step_value_toward_target(void *, void *, f32, f32, f32, f32);
extern u8 *g_path_l11_table[];
extern s32 math_fast_float_d(void *);
extern void lerp_vector(void *, void *, void *, f32);

/* Moves a moby along a level 11 path back and forth. It waits at each end, then eases along the
   path points and flips direction when it arrives (PAL: 50 Hz timings). */
void path_l11_follower_update_pal(u8 *object) {
    u8 *moby = object;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *path;
    s32 i;
    f32 t;
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        if (*(s32 *)vars == -1) {
            *(u16 *)(moby + 0x34) |= 2;
            break;
        }
        *(u8 *)(moby + 0x30) = 255;
        moby_set_state(moby, 1, -1);
        qcopy(moby + 0x10, g_path_l11_table[*(s32 *)vars] + 0x10);
        *(f32 *)(vars + 0x10) = 0.0016000001f / (*(f32 *)(vars + 4) * *(f32 *)(vars + 4));
        *(s32 *)(vars + 0x1C) = (s32)(*(f32 *)(vars + 8) * 5e+01f);
        break;
    case 1:
        if (math_fast_float_d(vars + 0x1C)) {
            moby_set_state(moby, 2, -1);
            *(s32 *)(vars + 0x14) = (*(s32 *)(vars + 0x14) + 1) & 1;
        }
        break;
    case 2:
        path = g_path_l11_table[*(s32 *)vars];
        math_step_value_toward_target(vars + 0x18, vars + 0xC, (f32)*(s32 *)(vars + 0x14), *(f32 *)(vars + 0x10), *(f32 *)(vars + 0x10), 1.0f);
        i = FloatToInt(*(f32 *)(vars + 0x18) * (f32)(*(s32 *)path - 1));
        t = *(f32 *)(vars + 0x18) * (f32)(*(s32 *)path - 1) - (f32)i;
        if (i > *(s32 *)path - 2) {
            i = *(s32 *)path - 2;
            t = 1.0f;
        }
        lerp_vector(moby + 0x10, path + 0x10 + i * 16, path + 0x20 + i * 16, t);
        if (*(s32 *)(vars + 0x14) ? *(f32 *)(vars + 0x18) >= (f32)*(s32 *)(vars + 0x14) : *(f32 *)(vars + 0x18) <= (f32)*(s32 *)(vars + 0x14)) {
            moby_set_state(moby, 1, -1);
            *(s32 *)(vars + 0x1C) = (s32)(*(f32 *)(vars + 8) * 5e+01f);
        }
        break;
    }
}
