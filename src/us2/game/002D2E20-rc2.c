#include "include_asm.h"

#include "common.h"
extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern void text_draw_centered_small(s32, s32, u64, s32, s32);
extern s32 GetLocalizedString(s32);
extern void DrawMenuNavigationFramesAndLabels(s32, s32);
extern void gfx_draw_scaled_object_two_axes(s32, s32, f32, f32, f32, f32, f32);
extern s32 table_find_by_id(s32, s32);
extern s32 D_001A8CFC;
extern s32 g_screen_width;
extern f32 D_001B23A8;
extern s32 g_001ABA5C __attribute__((sda));
extern s32 g_001ABA58 __attribute__((sda));

s32 func_US2_002D2E20(void) {
    f32 z;
    s32 r;

    SetupGifPaging(0);
    z = 0.0f;
    r = table_find_by_id(D_001A8CFC + 0x8710, 0xDE);
    gfx_draw_scaled_object_two_axes(r, 0x60442D00, (f32)(g_screen_width / 2), (f32)g_001ABA5C, 1.0f, D_001B23A8, z);
    r = table_find_by_id(D_001A8CFC + 0x8710, 0xDF);
    gfx_draw_scaled_object_two_axes(r, 0x60241700, (f32)(g_screen_width / 2), (f32)g_001ABA5C, 1.0f, D_001B23A8, z);
    r = table_find_by_id(D_001A8CFC + 0x8710, 0xE0);
    gfx_draw_scaled_object_two_axes(r, 0x55F0C070, (f32)(g_screen_width / 2), (f32)g_001ABA5C, 1.0f, D_001B23A8, z);
    DrawMenuNavigationFramesAndLabels(g_001ABA58 != 0, g_001ABA58 != 0x11);
    text_draw_centered_small(0x1B0, 0x177, (u64)0x80F0F0F0, GetLocalizedString(0x2BE5), -1);
    DoGifPaging();
    return 0;
}
