#include "names.h"
/* SPDX-License-Identifier: MIT
 * MIT License
 *
 * Copyright (c) 2026 RC2 decomp contributions
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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

/* Draws a paged menu screen with a title, left and right page arrows (shown only when there is a page to go to) and the back and select hints. */
s32 menu_paged_screen_draw(void) {
    s32 arrow_color;
    s32 highlight_color;
    f32 depth;

    SetupGifPaging(0);
    depth = 0.0f;
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0xE5), 0x60442D00, (f32) (g_screen_width / 2), (f32) D_001ABA6C, 1.0f, D_001B23A8, depth);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0xE4), 0x55F0C070, (f32) (g_screen_width / 2), (f32) D_001ABA6C, 1.0f, D_001B23A8, depth);
    highlight_color = math_ping_pong_blend_values(0x60241700, 0x55F0C070, 0x19, 0, 0);
    if (D_001ABA68 > 0) {
        arrow_color = 0x80F0F0F0;
        if (!(D_00138340.w0 & 0x8000)) {
            arrow_color = highlight_color;
        }
        gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0x4B), arrow_color, 216.0f, 373.0f, 1.0f, D_001B23A8 * 0.8f, depth);
        text_draw_centered_small(0x53, 0x171, 0x80F0F0F0, GetLocalizedString(0x2F40), -1);
    }
    if (D_001ABA68 < 6) {
        arrow_color = 0x80F0F0F0;
        if (!(D_00138340.w0 & 0x2000)) {
            arrow_color = highlight_color;
        }
        gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC + 0x8710, 0x4A), arrow_color, 295.0f, 373.0f, 1.0f, D_001B23A8 * 0.8f, depth);
        text_draw_right_aligned_small(0x1C1, 0x171, 0x80F0F0F0, GetLocalizedString(0x2F41), -1);
    }
    text_draw_centered_small(g_screen_width / 2, 0x1D, 0x80F0F0F0, GetLocalizedString(0x3294), -1);
    text_draw_centered_small(g_screen_width / 2, 0x173, 0x80F0F0F0, GetLocalizedString(0x2D4F), -1);
    DoGifPaging();
    return 0;
}
