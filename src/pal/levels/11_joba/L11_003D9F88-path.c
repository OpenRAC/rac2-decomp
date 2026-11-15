#include "include_asm.h"

#include "common.h"
extern void moby_set_state(u8 *, s32, s32);
extern s32 FloatToInt(f32);
extern void math_step_value_toward_target(void *, void *, f32, f32, f32, f32);
extern u8 *D_L11_001FF580[];
extern s32 math_fast_float_d(void *);
extern void lerp_vector(void *, void *, void *, f32);

void func_PAL_L11_003D9F88(u8 *arg0) {
    u8 *s1 = arg0;
    u8 *s0 = *(u8 **)(s1 + 0x68);
    u8 *s2;
    s32 i;
    f32 t;
    switch (*(u8 *)(s1 + 0x20)) {
    case 0:
        if (*(s32 *)s0 == -1) {
            *(u16 *)(s1 + 0x34) |= 2;
            break;
        }
        *(u8 *)(s1 + 0x30) = 255;
        moby_set_state(s1, 1, -1);
        qcopy(s1 + 0x10, D_L11_001FF580[*(s32 *)s0] + 0x10);
        *(f32 *)(s0 + 0x10) = 0.0016000001f / (*(f32 *)(s0 + 4) * *(f32 *)(s0 + 4));
        *(s32 *)(s0 + 0x1C) = (s32)(*(f32 *)(s0 + 8) * 5e+01f);
        break;
    case 1:
        if (math_fast_float_d(s0 + 0x1C)) {
            moby_set_state(s1, 2, -1);
            *(s32 *)(s0 + 0x14) = (*(s32 *)(s0 + 0x14) + 1) & 1;
        }
        break;
    case 2:
        s2 = D_L11_001FF580[*(s32 *)s0];
        math_step_value_toward_target(s0 + 0x18, s0 + 0xC, (f32)*(s32 *)(s0 + 0x14), *(f32 *)(s0 + 0x10), *(f32 *)(s0 + 0x10), 1.0f);
        i = FloatToInt(*(f32 *)(s0 + 0x18) * (f32)(*(s32 *)s2 - 1));
        t = *(f32 *)(s0 + 0x18) * (f32)(*(s32 *)s2 - 1) - (f32)i;
        if (i > *(s32 *)s2 - 2) {
            i = *(s32 *)s2 - 2;
            t = 1.0f;
        }
        lerp_vector(s1 + 0x10, s2 + 0x10 + i * 16, s2 + 0x20 + i * 16, t);
        if (*(s32 *)(s0 + 0x14) ? *(f32 *)(s0 + 0x18) >= (f32)*(s32 *)(s0 + 0x14) : *(f32 *)(s0 + 0x18) <= (f32)*(s32 *)(s0 + 0x14)) {
            moby_set_state(s1, 1, -1);
            *(s32 *)(s0 + 0x1C) = (s32)(*(f32 *)(s0 + 8) * 5e+01f);
        }
        break;
    }
}
