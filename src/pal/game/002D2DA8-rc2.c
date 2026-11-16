#include "include_asm.h"

#include "common.h"
extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern int text_draw_centered_small(s32, s32, u64, s32, s32);
extern char *GetLocalizedString(s32);
extern void DrawMenuNavigationFramesAndLabels(s32, s32);
extern void gfx_draw_scaled_object_two_axes(s32, s32, f32, f32, f32, f32, f32);
extern void *table_find_by_id(s32, s32);
extern s32 g_resident_data_base;
extern s32 g_screen_width;
extern f32 g_menu_alpha_scale;
extern s32 g_001ABA5C __attribute__((sda));
extern s32 g_001ABA58 __attribute__((sda));

/* Draws the 18-page viewer with its title and left and right page arrows. (PAL) */
s32 page_viewer_draw_long_pal(void) {
    f32 depth;
    s32 sprite;

    SetupGifPaging(0);
    depth = 0.0f;
    sprite = table_find_by_id(g_resident_data_base + 0x8710, 0xDE);
    gfx_draw_scaled_object_two_axes(sprite, 0x60442D00, (f32)(g_screen_width / 2), (f32)g_001ABA5C, 1.0f, g_menu_alpha_scale, depth);
    sprite = table_find_by_id(g_resident_data_base + 0x8710, 0xDF);
    gfx_draw_scaled_object_two_axes(sprite, 0x60241700, (f32)(g_screen_width / 2), (f32)g_001ABA5C, 1.0f, g_menu_alpha_scale, depth);
    sprite = table_find_by_id(g_resident_data_base + 0x8710, 0xE0);
    gfx_draw_scaled_object_two_axes(sprite, 0x55F0C070, (f32)(g_screen_width / 2), (f32)g_001ABA5C, 1.0f, g_menu_alpha_scale, depth);
    DrawMenuNavigationFramesAndLabels(g_001ABA58 != 0, g_001ABA58 != 0x11);
    text_draw_centered_small(0x1B0, 0x177, (u64)0x80F0F0F0, GetLocalizedString(0xB60), -1);
    DoGifPaging();
    return 0;
}
