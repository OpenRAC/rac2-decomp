#include "common.h"

/* func_US2_002D5D10, the v2.00 copy of func_002D50F0. */
extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern void text_draw_centered_small(s32, s32, u64, s32, s32);
extern char *GetLocalizedString(s32);
extern void gfx_draw_scaled_object_two_axes(s32, s32, f32, f32, f32, f32, f32);
extern void *table_find_by_id(s32, s32);
extern s32 g_resident_data_base;
extern s32 g_popup_simple_offset_a;
extern s32 g_popup_simple_y;
extern s32 g_popup_simple_offset_b;
extern f32 g_menu_alpha_scale;
extern s32 g_001ABAB0 __attribute__((sda));
extern s32 g_001ABAA8 __attribute__((sda));
extern s32 g_001ABAB8 __attribute__((sda));
extern f32 g_001ABAC0 __attribute__((sda));

s32 func_US2_002D5D10(void) {
    s32 s0;
    s32 s1;

    SetupGifPaging(0);
    if (g_resident_data_base != 0) {
        gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0x8B), 0x60442D00, (f32)g_001ABAB0, (f32)g_popup_simple_y, 1.0f, g_menu_alpha_scale, g_001ABAC0);
        gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0x8C), 0x55F0C070, (f32)g_001ABAB0, (f32)g_popup_simple_y, 1.0f, g_menu_alpha_scale, g_001ABAC0);
        gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0x8D), 0x80FFDE8D, (f32)g_001ABAB0, (f32)g_popup_simple_y, 1.0f, g_menu_alpha_scale, 0.0f);
        s1 = g_001ABAB0;
        s1 = s1 + g_001ABAA8;
        s0 = g_popup_simple_y;
        s0 = s0 + g_popup_simple_offset_a;
        text_draw_centered_small(s1, s0, (u64)0x80F0F0F0, GetLocalizedString(0x2BF7), -1);
        s1 = g_001ABAB0;
        s1 = s1 + g_001ABAB8;
        s0 = g_popup_simple_y;
        s0 = s0 + g_popup_simple_offset_b;
        text_draw_centered_small(s1, s0, (u64)0x80F0F0F0, GetLocalizedString(0x2BE5), -1);
    }
    DoGifPaging();
    return 0;
}
