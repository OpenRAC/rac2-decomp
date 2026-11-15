#include "common.h"

/* func_US2_002D5A44, the v2.00 copy of func_002D4E48. */

extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern void text_draw_right_aligned_small(s32, s32, u64, s32, s32);
extern void text_draw_centered_small(s32, s32, u64, s32, s32);
extern s32 GetLocalizedString(s32);
extern void gfx_draw_scaled_object_two_axes(s32, s32, f32, f32, f32, f32, f32);
extern s32 table_find_by_id(s32, s32);
extern s32 D_001A8CFC;
extern s32 D_001ABA8C;
extern s32 D_001ABA94;
extern s32 D_001ABA9C;
extern f32 D_001B23A8;
extern s32 D_001ABA90 __attribute__((sda));
extern s32 D_001ABA88 __attribute__((sda));
extern s32 D_001ABA98 __attribute__((sda));

s32 func_US2_002D5A44(void) {
    s32 s0;
    s32 s1;
    f32 zero;

    SetupGifPaging(0);
    if (D_001A8CFC != 0) {
        zero = 0.0f;
        gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0x96), 0x60442D00, (f32)D_001ABA90, (f32)D_001ABA94, 1.0f, D_001B23A8, zero);
        gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0x97), 0x60241700, (f32)D_001ABA90, (f32)D_001ABA94, 1.0f, D_001B23A8, zero);
        gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0x98), 0x55F0C070, (f32)D_001ABA90, (f32)D_001ABA94, 1.0f, D_001B23A8, zero);
        s1 = D_001ABA90;
        s1 = s1 + D_001ABA88;
        s0 = D_001ABA94;
        s0 = s0 + D_001ABA8C;
        text_draw_centered_small(s1, s0, (u64)0x80F0F0F0, GetLocalizedString(0x2BF8), -1);
        s1 = D_001ABA90;
        s1 = s1 + D_001ABA98;
        s0 = D_001ABA94;
        s0 = s0 + D_001ABA9C;
        text_draw_right_aligned_small(s1, s0, (u64)0x80F0F0F0, GetLocalizedString(0x2BE5), -1);
    }
    DoGifPaging();
    return 0;
}
