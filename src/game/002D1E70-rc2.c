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

extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern int text_draw_centered_small(s32, s32, u64, s32, s32);
extern char *GetLocalizedString(s32);
extern void DrawMenuNavigationFramesAndLabels(s32, s32);
extern void gfx_draw_scaled_object_two_axes(s32, s32, f32, f32, f32, f32, f32);
extern void *table_find_by_id(s32, s32);
extern s32 D_001A8CFC;
extern s32 g_screen_width;
extern f32 D_001B23A8;
extern s32 g_001ABA5C __attribute__((sda));
extern s32 g_001ABA58 __attribute__((sda));

/* Draws the 18-page viewer with its title and left and right page arrows. */
s32 page_viewer_draw_long(void) {
    f32 z;
    s32 sprite;

    SetupGifPaging(0);
    z = 0.0f;
    sprite = table_find_by_id(D_001A8CFC + 0x8710, 0xDE);
    gfx_draw_scaled_object_two_axes(sprite, 0x60442D00, (f32)(g_screen_width / 2), (f32)g_001ABA5C, 1.0f, D_001B23A8, z);
    sprite = table_find_by_id(D_001A8CFC + 0x8710, 0xDF);
    gfx_draw_scaled_object_two_axes(sprite, 0x60241700, (f32)(g_screen_width / 2), (f32)g_001ABA5C, 1.0f, D_001B23A8, z);
    sprite = table_find_by_id(D_001A8CFC + 0x8710, 0xE0);
    gfx_draw_scaled_object_two_axes(sprite, 0x55F0C070, (f32)(g_screen_width / 2), (f32)g_001ABA5C, 1.0f, D_001B23A8, z);
    DrawMenuNavigationFramesAndLabels(g_001ABA58 != 0, g_001ABA58 != 0x11);
    text_draw_centered_small(0x1B0, 0x177, (u64)0x80F0F0F0, GetLocalizedString(0x2D4F), -1);
    DoGifPaging();
    return 0;
}
