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

/* Fills a sound/effect record with the owner object, its position and two speeds. Returns -1 if the owner has no usable data. */
s32 part_fill_effect_record_pal(u8 *owner, s32 value_a, s32 value_b, u8 *out, f32 speed_a, f32 speed_b) {
    u8 *data;
    if (owner == 0)
        return -1;
    data = *(u8 **)(owner + 0x24);
    if (data == 0)
        return -1;
    if (*(s32 *)(data + 0x28) == 0)
        return -1;
    *(u32 *)(out + 0x1C) = (u32)owner;
    *(f32 *)(out + 0x14) = speed_b * 0.020000001f;
    *(f32 *)(out + 0x10) = speed_a * 0.020000001f;
    *(TI128 *)out = *(TI128 *)(owner + 0x10);
    *(s32 *)(out + 0x18) = value_b;
    *(s32 *)(out + 0x20) = value_a;
    return 1;
}

