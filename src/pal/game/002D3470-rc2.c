#include "include_asm.h"

#include "common.h"
extern s32 D_001ABA68 __attribute__((sda));
extern s32 D_001ABA6C __attribute__((sda));
extern s32 D_001A8CFC;
extern s32 g_screen_width;
extern f32 D_001B23A8;
extern struct { s32 w0; s32 w1; s32 w2; } D_00138340;
void SetupGifPaging(s32);
void DoGifPaging(void);
void text_draw_right_aligned_small(s32, s32, u64, s32, s32);
s32 text_draw_centered_small(s32, s32, u64, s32, s32);
char *GetLocalizedString(s32);
s32 math_ping_pong_blend_values(s32, s32, s32, s32, s32);
void gfx_draw_scaled_object_two_axes(s32, s32, f32, f32, f32, f32, f32);
void *table_find_by_id(s32, s32);
void text_draw_small(s32, s32, u64, s32, s32);

s32 func_PAL_002D3470(void) {
    s32 s0;
    s32 s1;
    f32 zf;

    SetupGifPaging(0);
    zf = 0.0f;
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0xE5), 0x60442D00, (f32) (g_screen_width / 2), (f32) D_001ABA6C, 1.0f, D_001B23A8, zf);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0xE4), 0x55F0C070, (f32) (g_screen_width / 2), (f32) D_001ABA6C, 1.0f, D_001B23A8, zf);
    s1 = math_ping_pong_blend_values(0x60241700, 0x55F0C070, 0x19, 0, 0);
    if (D_001ABA68 > 0) {
        s0 = 0x80F0F0F0;
        if (!(D_00138340.w0 & 0x8000)) {
            s0 = s1;
        }
        gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0x4B), s0, 216.0f, 373.0f, 1.0f, D_001B23A8 * 0.8f, zf);
        text_draw_small(0x40, 0x171, 0x80F0F0F0, GetLocalizedString(0xE65), -1);
    }
    if (D_001ABA68 < 6) {
        s0 = 0x80F0F0F0;
        if (!(D_00138340.w0 & 0x2000)) {
            s0 = s1;
        }
        gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0x4A), s0, 295.0f, 373.0f, 1.0f, D_001B23A8 * 0.8f, zf);
        text_draw_right_aligned_small(0x1C1, 0x171, 0x80F0F0F0, GetLocalizedString(0xE66), -1);
    }
    text_draw_centered_small(g_screen_width / 2, 0x1D, 0x80F0F0F0, GetLocalizedString(0x1B62), -1);
    text_draw_centered_small(g_screen_width / 2, 0x173, 0x80F0F0F0, GetLocalizedString(0xB60), -1);
    DoGifPaging();
    return 0;
}
