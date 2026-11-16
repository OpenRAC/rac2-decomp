#include "common.h"
extern void moby_set_state(u8 *, s32, s32);
extern s32 FloatToInt(f32);
extern float math_step_value_toward_target(void *, void *, f32, f32, f32, f32);
extern u8 *g_path_l11_table[];
extern s32 math_fast_float_d(void *);
extern void lerp_vector(void *, void *, void *, f32);
/* Moves the object along a stored path, waits at each end, then goes back the other way. */
void path_l11_follower_update(u8 *moby_arg) {
    u8 *moby = moby_arg;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *path;
    s32 segment;
    f32 blend;
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        if (*(s32 *)vars == -1) {
            *(u16 *)(moby + 0x34) |= 2;
            break;
        }
        *(u8 *)(moby + 0x30) = 255;
        moby_set_state(moby, 1, -1);
        qcopy(moby + 0x10, g_path_l11_table[*(s32 *)vars] + 0x10);
        *(f32 *)(vars + 0x10) = 0.0011111111380159855f / (*(f32 *)(vars + 4) * *(f32 *)(vars + 4));
        *(s32 *)(vars + 0x1C) = (s32)(*(f32 *)(vars + 8) * 60.0f);
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
        segment = FloatToInt(*(f32 *)(vars + 0x18) * (f32)(*(s32 *)path - 1));
        blend = *(f32 *)(vars + 0x18) * (f32)(*(s32 *)path - 1) - (f32)segment;
        if (segment > *(s32 *)path - 2) {
            segment = *(s32 *)path - 2;
            blend = 1.0f;
        }
        lerp_vector(moby + 0x10, path + 0x10 + segment * 16, path + 0x20 + segment * 16, blend);
        if (*(s32 *)(vars + 0x14) ? *(f32 *)(vars + 0x18) >= (f32)*(s32 *)(vars + 0x14) : *(f32 *)(vars + 0x18) <= (f32)*(s32 *)(vars + 0x14)) {
            moby_set_state(moby, 1, -1);
            *(s32 *)(vars + 0x1C) = (s32)(*(f32 *)(vars + 8) * 60.0f);
        }
        break;
    }
}
