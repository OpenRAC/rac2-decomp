#include "common.h"

/* func_US2_002D5A44, the v2.00 copy of func_002D4E48. */

extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern void text_draw_right_aligned_small(s32, s32, u64, s32, s32);
extern void text_draw_centered_small(s32, s32, u64, s32, s32);
extern char *GetLocalizedString(s32);
extern void gfx_draw_scaled_object_two_axes(s32, s32, f32, f32, f32, f32, f32);
extern void *table_find_by_id(s32, s32);
extern s32 g_resident_data_base;
extern s32 g_popup_text_offset_y;
extern s32 g_popup_box_y;
extern s32 g_popup_right_text_offset_y;
extern f32 g_menu_alpha_scale;
extern s32 g_popup_box_x __attribute__((sda));
extern s32 g_popup_text_offset_x __attribute__((sda));
extern s32 g_popup_right_text_offset_x __attribute__((sda));

s32 func_US2_002D5A44(void) {
    s32 s0;
    s32 s1;
    f32 zero;

    SetupGifPaging(0);
    if (g_resident_data_base != 0) {
        zero = 0.0f;
        gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0x96), 0x60442D00, (f32)g_popup_box_x, (f32)g_popup_box_y, 1.0f, g_menu_alpha_scale, zero);
        gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0x97), 0x60241700, (f32)g_popup_box_x, (f32)g_popup_box_y, 1.0f, g_menu_alpha_scale, zero);
        gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0x98), 0x55F0C070, (f32)g_popup_box_x, (f32)g_popup_box_y, 1.0f, g_menu_alpha_scale, zero);
        s1 = g_popup_box_x;
        s1 = s1 + g_popup_text_offset_x;
        s0 = g_popup_box_y;
        s0 = s0 + g_popup_text_offset_y;
        text_draw_centered_small(s1, s0, (u64)0x80F0F0F0, GetLocalizedString(0x2BF8), -1);
        s1 = g_popup_box_x;
        s1 = s1 + g_popup_right_text_offset_x;
        s0 = g_popup_box_y;
        s0 = s0 + g_popup_right_text_offset_y;
        text_draw_right_aligned_small(s1, s0, (u64)0x80F0F0F0, GetLocalizedString(0x2BE5), -1);
    }
    DoGifPaging();
    return 0;
}
