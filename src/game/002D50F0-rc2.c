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
extern void text_draw_centered_small(s32, s32, u64, s32, s32);
extern char *GetLocalizedString(s32);
extern void gfx_draw_scaled_object(s32, s32, f32, f32, f32, f32);
extern void *table_find_by_id(s32, s32);
extern s32 g_resident_data_base;
extern s32 g_popup_simple_offset_a;
extern s32 g_popup_simple_y;
extern s32 g_popup_simple_offset_b;
extern f32 g_menu_alpha_scale;
extern s32 g_001ABAB0 __attribute__((sda));
extern s32 g_001ABAA8 __attribute__((sda));
extern s32 g_001ABAB8 __attribute__((sda));
extern f32 g_001ABAC0 __attribute__((sda));

/* Draws a small pop-up menu box with three layered title images and two lines of text with button hints. */
s32 menu_popup_box_draw_simple(void) {
    s32 y_pos;
    s32 x_pos;

    SetupGifPaging(0);
    if (g_resident_data_base != 0) {
        gfx_draw_scaled_object(table_find_by_id(g_resident_data_base + 0x8710, 0x8B), 0x60442D00, (f32)g_001ABAB0, (f32)g_popup_simple_y, g_menu_alpha_scale, g_001ABAC0);
        gfx_draw_scaled_object(table_find_by_id(g_resident_data_base + 0x8710, 0x8C), 0x55F0C070, (f32)g_001ABAB0, (f32)g_popup_simple_y, g_menu_alpha_scale, g_001ABAC0);
        gfx_draw_scaled_object(table_find_by_id(g_resident_data_base + 0x8710, 0x8D), 0x80FFDE8D, (f32)g_001ABAB0, (f32)g_popup_simple_y, g_menu_alpha_scale, 0.0f);
        x_pos = g_001ABAB0;
        x_pos = x_pos + g_001ABAA8;
        y_pos = g_popup_simple_y;
        y_pos = y_pos + g_popup_simple_offset_a;
        text_draw_centered_small(x_pos, y_pos, (u64)0x80F0F0F0, GetLocalizedString(0x2D61), -1);
        x_pos = g_001ABAB0;
        x_pos = x_pos + g_001ABAB8;
        y_pos = g_popup_simple_y;
        y_pos = y_pos + g_popup_simple_offset_b;
        text_draw_centered_small(x_pos, y_pos, (u64)0x80F0F0F0, GetLocalizedString(0x2D4F), -1);
    }
    DoGifPaging();
    return 0;
}
