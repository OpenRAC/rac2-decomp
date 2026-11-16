#include "names.h"
/* func_PAL_002D30C0, the PAL copy of func_002D2188 (src/game/002D2188-g8.c): HUD coordinates 306/308
   (USA 330/332), text 0xB60 (USA 0x2D4F), and the three bar draws in an inline helper, so each
   call reloads its 1.0f instead of sharing one register as USA does. */
#include "common.h"

extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern s32 text_draw_centered_small(s32, s32, u64, s32, s32);
extern char *GetLocalizedString(s32);
extern void AppendScreenRectPacket(s32, s32, s32, s32, u64, s32);
extern void DrawMenuNavigationFramesAndLabels(s32, s32);
extern void gfx_draw_scaled_object_two_axes(s32, s32, f32, f32, f32, f32, f32);
extern void *table_find_by_id(s32, s32);
extern s32 g_resident_data_base;
extern s32 g_screen_width;
extern f32 g_menu_alpha_scale;
extern f32 g_hud_scale;
extern s32 ref_PAL_002D30C0_01 __attribute__((sda));
extern s32 ref_PAL_002D30C0_02 __attribute__((sda));
extern struct { s16 text; s16 reserved; } g_page_viewer_text_table[] MACRO_ADDR;

/* The display mode word beside the HUD scale. */
extern s32 g_hud_mode;

/* A HUD coordinate scaled for the display and rounded to a whole pixel. The display-mode
   test has no effect on the result, but it is real: its load and compare go at flow2,
   after allocation, which leaves the saved but unused $s1 (as func_00326A10). */
static __inline__ s32 hud_coord(f32 value, f32 scale, f32 half, s32 active)
{
    f32 scaled = scale * value + half;
    s32 result = (s32)scaled;

    if (result != 0 && g_hud_mode == active)
        scaled = 1.0f;
    return result;
}

/* One bar of the HUD: the sprite for `id`, centred, in `color`. */
static __inline__ void draw_bar(s32 id, s32 color, f32 z)
{
    s32 r = table_find_by_id(g_resident_data_base + 0x8710, id);

    gfx_draw_scaled_object_two_axes(r, color, (f32)(g_screen_width / 2), (f32)ref_PAL_002D30C0_01, 1.0f, g_menu_alpha_scale, z);
}

s32 page_viewer_draw_short_pal(void) {
    f32 z, s, half;
    s32 r;
    s32 center, one;

    SetupGifPaging(0);
    z = 0.0f;
    one = 1;
    draw_bar(0xDE, 0x60442D00, z);
    draw_bar(0xDF, 0x60241700, z);
    draw_bar(0xE0, 0x55F0C070, z);
    DrawMenuNavigationFramesAndLabels(ref_PAL_002D30C0_02 != 0, ref_PAL_002D30C0_02 != 5);
    s = g_hud_scale;
    half = 0.5f;
    AppendScreenRectPacket(66, hud_coord(306.0f, s, half, one), 463, hud_coord(308.0f, s, half, one), 0x55F0C070, 0);
    center = g_screen_width / 2;
    text_draw_centered_small(center, 311, (u64)0x80F0F0F0, GetLocalizedString(g_page_viewer_text_table[ref_PAL_002D30C0_02].text), -1);
    text_draw_centered_small(0x1B0, 0x177, (u64)0x80F0F0F0, GetLocalizedString(0xB60), -1);
    DoGifPaging();
    return 0;
}
