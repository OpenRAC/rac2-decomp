#include "include_asm.h"

#include "common.h"
typedef u64 TI128 __attribute__((mode(TI)));
extern u8 *g_hero_moby;
extern f32 g_saved_hold_float;
extern u64 GetEffectTextureDescriptor(int);
extern u8 g_font_print_data[];
extern u8 g_screen_update_index;
extern s32 g_screen_update_headers[];
extern s32 g_screen_update_param;
extern u8 *g_moby_array __attribute__((sda));
extern u8 *g_moby_array_end __attribute__((sda));
extern u8 *g_moby_array __attribute__((sda));
extern u32 g_moby_l08_group_lists[];
extern f32 mat_fast_helper_a(f32, f32);
extern f32 vec_length_xy(void *);
extern u8 *g_hero_moby;

s32 part_fill_effect_record_pal(u8 *p, s32 a1, s32 a2, u8 *out, f32 f1, f32 f2) {
    u8 *q;
    if (p == 0)
        return -1;
    q = *(u8 **)(p + 0x24);
    if (q == 0)
        return -1;
    if (*(s32 *)(q + 0x28) == 0)
        return -1;
    *(u32 *)(out + 0x1C) = (u32)p;
    *(f32 *)(out + 0x14) = f2 * 0.020000001f;
    *(f32 *)(out + 0x10) = f1 * 0.020000001f;
    *(TI128 *)out = *(TI128 *)(p + 0x10);
    *(s32 *)(out + 0x18) = a2;
    *(s32 *)(out + 0x20) = a1;
    return 1;
}

