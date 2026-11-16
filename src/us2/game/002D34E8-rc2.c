#include "include_asm.h"

#include "common.h"
extern s32 g_scroll_list_repeat_timer __attribute__((sda));
extern s32 g_paged_screen_title_y __attribute__((sda));
extern s32 g_resident_data_base;
extern s32 g_screen_width;
extern f32 g_menu_alpha_scale;
extern struct { s32 w0; s32 w1; s32 w2; } g_pad_menu_flags;
void SetupGifPaging(s32);
void DoGifPaging(void);
void text_draw_right_aligned_small(s32, s32, u64, s32, s32);
s32 text_draw_centered_small(s32, s32, u64, s32, s32);
char *GetLocalizedString(s32);
s32 math_ping_pong_blend_values(s32, s32, s32, s32, s32);
void gfx_draw_scaled_object_two_axes(s32, s32, f32, f32, f32, f32, f32);
void *table_find_by_id(s32, s32);
void text_draw_small(s32, s32, u64, s32, s32);

/* Draws the paged screen with up and down arrows shown when there are more pages in that direction. */
s32 menu_paged_screen_draw_us2(void) {
    s32 color;
    s32 pulse_color;
    f32 depth;

    SetupGifPaging(0);
    depth = 0.0f;
    gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0xE5), 0x60442D00, (f32) (g_screen_width / 2), (f32) g_paged_screen_title_y, 1.0f, g_menu_alpha_scale, depth);
    gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0xE4), 0x55F0C070, (f32) (g_screen_width / 2), (f32) g_paged_screen_title_y, 1.0f, g_menu_alpha_scale, depth);
    pulse_color = math_ping_pong_blend_values(0x60241700, 0x55F0C070, 0x19, 0, 0);
    if (g_scroll_list_repeat_timer > 0) {
        color = 0x80F0F0F0;
        if (!(g_pad_menu_flags.w0 & 0x8000)) {
            color = pulse_color;
        }
        gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0x4B), color, 216.0f, 373.0f, 1.0f, g_menu_alpha_scale * 0.8f, depth);
        text_draw_small(0x40, 0x171, 0x80F0F0F0, GetLocalizedString(0x2DD6), -1);
    }
    if (g_scroll_list_repeat_timer < 6) {
        color = 0x80F0F0F0;
        if (!(g_pad_menu_flags.w0 & 0x2000)) {
            color = pulse_color;
        }
        gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0x4A), color, 295.0f, 373.0f, 1.0f, g_menu_alpha_scale * 0.8f, depth);
        text_draw_right_aligned_small(0x1C1, 0x171, 0x80F0F0F0, GetLocalizedString(0x2DD7), -1);
    }
    text_draw_centered_small(g_screen_width / 2, 0x1D, 0x80F0F0F0, GetLocalizedString(0x312A), -1);
    text_draw_centered_small(g_screen_width / 2, 0x173, 0x80F0F0F0, GetLocalizedString(0x2BE5), -1);
    DoGifPaging();
    return 0;
}
