#include "common.h"

extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern s32 text_draw_centered_small(s32, s32, u64, s32, s32);
extern s32 GetLocalizedString(s32);
extern void AppendScreenRectPacket(s32, s32, s32, s32, u64, s32);
extern void DrawMenuNavigationFramesAndLabels(s32, s32);
extern void gfx_draw_scaled_object_two_axes(s32, s32, f32, f32, f32, f32, f32);
extern s32 table_find_by_id(s32, s32);
extern s32 D_001A8CFC;
extern s32 g_screen_width;
extern f32 D_001B23A8;
extern f32 D_001B23A4;
extern s32 ref_002D2188_01 __attribute__((sda));
extern s32 ref_002D2188_02 __attribute__((sda));
extern struct { s16 text; s16 reserved; } D_001ABD68[] MACRO_ADDR;

/* The display mode word beside the HUD scale. */
extern s32 D_001B23A0;

/* A HUD coordinate scaled for the display and rounded to a whole pixel. The display-mode
   test has no effect on the result, but it is real: its load and compare go at flow2,
   after allocation, which leaves the saved but unused $s1 (as func_00326A10). */
static __inline__ s32 hud_coord(f32 value, f32 scale, f32 half, s32 active)
{
    f32 scaled = scale * value + half;
    s32 result = (s32)scaled;

    if (result != 0 && D_001B23A0 == active)
        scaled = 1.0f;
    return result;
}

/* Draws the six-page viewer with its title, arrows, divider line and the text of the current page. */
s32 page_viewer_draw_short(void) {
    f32 z, scaleY, half;
    s32 sprite;
    s32 center, one;

    SetupGifPaging(0);
    z = 0.0f;
    one = 1;
    sprite = table_find_by_id(D_001A8CFC + 0x8710, 0xDE);
    gfx_draw_scaled_object_two_axes(sprite, 0x60442D00, (f32)(g_screen_width / 2), (f32)ref_002D2188_01, 1.0f, D_001B23A8, z);
    sprite = table_find_by_id(D_001A8CFC + 0x8710, 0xDF);
    gfx_draw_scaled_object_two_axes(sprite, 0x60241700, (f32)(g_screen_width / 2), (f32)ref_002D2188_01, 1.0f, D_001B23A8, z);
    sprite = table_find_by_id(D_001A8CFC + 0x8710, 0xE0);
    gfx_draw_scaled_object_two_axes(sprite, 0x55F0C070, (f32)(g_screen_width / 2), (f32)ref_002D2188_01, 1.0f, D_001B23A8, z);
    DrawMenuNavigationFramesAndLabels(ref_002D2188_02 != 0, ref_002D2188_02 != 5);
    scaleY = D_001B23A4;
    half = 0.5f;
    AppendScreenRectPacket(66, hud_coord(330.0f, scaleY, half, one), 463, hud_coord(332.0f, scaleY, half, one), 0x55F0C070, 0);
    center = g_screen_width / 2;
    text_draw_centered_small(center, 311, (u64)0x80F0F0F0, GetLocalizedString(D_001ABD68[ref_002D2188_02].text), -1);
    text_draw_centered_small(0x1B0, 0x177, (u64)0x80F0F0F0, GetLocalizedString(0x2D4F), -1);
    DoGifPaging();
    return 0;
}
