#include "include_asm.h"

#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;
extern u8 g_hero_state[];
extern u32 g_pad_pressed_flags;
extern s32 g_hero_frozen_flag MACRO_ADDR;
extern void set_hero_animation_pal(s32, s32, float);
extern u8 *func_PAL_L18_0042D088(u8 *, s32);
#define H ((Hero *)D_00189E20)

void func_PAL_L18_002C3E10(void)
{
    u8 *object;
    object = H->ptr[0x2290 / 4];
    if (*(s16 *)(object + 0xAA) != 0xEC0) {
        if ((g_pad_pressed_flags & 0x80) && g_hero_frozen_flag == 0 && H->h[0x1E0 / 2] == 0 && H->i[0x2294 / 4] != 0x6F) {
            H->b[0x22B8] = 1;
            H->b[0x22BA] = 1;
            if (object[0x43] != 11) {
                set_hero_animation_pal(11, 1, 4.0f);
                H->f[0xC20 / 4] = 3.0f;
            }
        } else if (H->i[0xC28 / 4] & 2) {
            H->b[0x22B8] = 0;
            H->b[0x22BA] = 0;
            if (H->i[0x2294 / 4] == 0x8E) set_hero_animation_pal(14, 0, 7.0f);
            else set_hero_animation_pal(13, 0, 7.0f);
        }
    }
    object = H->ptr[0x2290 / 4];
    if (object[0x42] == 11 || (*(u64 *)(object + 0x40) & 0xFFFF0000ULL) == 0x0BFF0000ULL) {
        H->f[0xC20 / 4] = 3.0f;
        if (*(s16 *)(object + 0xAA) == 0xEE1) {
            if (H->i[0x1D8 / 4] > 2) {
                if (H->i[0x1D8 / 4] % 5 == 0) func_PAL_L18_0042D088(object, 0);
                if ((H->i[0x1D8 / 4] + 2) % 5 == 0) func_PAL_L18_0042D088(H->ptr[0x2290 / 4], 1);
            }
        } else if (*(s16 *)(object + 0xAA) == 0xED4 && H->i[0x1D8 / 4] % 5 != 0) {
            func_PAL_L18_0042D088(object, 0);
        }
    }
}
