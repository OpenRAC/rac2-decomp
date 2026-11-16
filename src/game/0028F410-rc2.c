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

extern void FastVecAdd(s8 *, s8 *, s8 *);
extern void FastVecSub(s8 *, s8 *, s8 *);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern s32 g_screen_offset_x;
extern s32 g_screen_offset_y;
extern s32 g_hud_sprite_color_word;
extern s8 *volatile g_dma_packet_cursor;

/* Draws a picture on the screen, turned by an angle around its centre. */
void DrawRotatedSprite(s32 tex_width, s32 tex_height, s64 texture_word, f32 center_x, f32 center_y, f32 half_height, f32 half_width, f32 angle) {
    s8 vec[0x68];
    s64 rt1 ;
    s64 ra1 ;
    s64 rt0 ;
    s64 r154 ;
    s32 s3;
    s32 s4;
    s32 t2;
    s8 *old_cursor;
    s8 *packet;
    s64 c1;
    s64 c2;
    s64 c3;
    s64 c4;

    *(f32 *)(vec + 0x20) = center_x;
    *(f32 *)(vec + 0x24) = center_y;
    *(f32 *)(vec + 0x0) = half_width * math_fast_sin_or_cos_b(angle);
    *(f32 *)(vec + 0x4) = half_width * math_fast_sin_or_cos_a(angle);
    *(f32 *)(vec + 0x10) = -half_height * math_fast_sin_or_cos_a(angle);
    *(f32 *)(vec + 0x14) = half_height * math_fast_sin_or_cos_b(angle);
    FastVecAdd(vec + 0x30, vec + 0x20, vec);
    FastVecSub(vec + 0x30, vec + 0x30, vec + 0x10);
    FastVecAdd(vec + 0x40, vec + 0x20, vec);
    FastVecAdd(vec + 0x40, vec + 0x40, vec + 0x10);
    FastVecSub(vec + 0x50, vec + 0x20, vec);
    FastVecSub(vec + 0x50, vec + 0x50, vec + 0x10);
    FastVecSub(vec + 0x60, vec + 0x20, vec);
    FastVecAdd(vec + 0x60, vec + 0x60, vec + 0x10);

    (*(s32 *)((s8 *)(g_dma_packet_cursor) + (0))) = 0x10000007;
    rt1 = ((s64)0xB400 << 48) | 0x8001;
    s3 = tex_width << 4;
    (*(s32 *)((s8 *)(g_dma_packet_cursor) + (4))) = 0;
    ra1 = ((((s64)0xA6A6 << 16) | 0xA6A6) << 11) | 0x106;
    r154 = 0x154;
    rt0 = ((s64)0x807F << 16) | 0x7F7F;
    s4 = tex_height << 20;
    t2 = s4 + s3;
    (*(s32 *)((s8 *)(g_dma_packet_cursor) + (8))) = 0;
    (*(s32 *)((s8 *)(g_dma_packet_cursor) + (0xC))) = 0x50000007;
    old_cursor = g_dma_packet_cursor;
    packet = old_cursor + 0x10;
    g_dma_packet_cursor = packet;
    (*(s64 *)((s8 *)(old_cursor) + (0x10))) = rt1;
    (*(s64 *)((s8 *)(packet) + (0x10))) = texture_word;
    (*(s64 *)((s8 *)(packet) + (0x28))) = s3;
    (*(s64 *)((s8 *)(packet) + (8))) = ra1;
    (*(s64 *)((s8 *)(packet) + (0x18))) = r154;
    (*(s64 *)((s8 *)(packet) + (0x20))) = rt0;
    c1 = ((s64)((s32)*(f32 *)(vec + 0x30) + g_screen_offset_x - 8)) | ((s64)((s32)*(f32 *)(vec + 0x34) + g_screen_offset_y - 8) << 16) | ((s64)g_hud_sprite_color_word << 32);
    (*(s64 *)((s8 *)(packet) + (0x38))) = t2;
    (*(s64 *)((s8 *)(packet) + (0x30))) = c1;
    c2 = ((s64)((s32)*(f32 *)(vec + 0x40) + g_screen_offset_x - 8)) | ((s64)((s32)*(f32 *)(vec + 0x44) + g_screen_offset_y - 8) << 16) | ((s64)g_hud_sprite_color_word << 32);
    (*(s64 *)((s8 *)(packet) + (0x48))) = 0;
    (*(s64 *)((s8 *)(packet) + (0x40))) = c2;
    c3 = ((s64)((s32)*(f32 *)(vec + 0x50) + g_screen_offset_x - 8)) | ((s64)((s32)*(f32 *)(vec + 0x54) + g_screen_offset_y - 8) << 16) | ((s64)g_hud_sprite_color_word << 32);
    (*(s64 *)((s8 *)(packet) + (0x50))) = c3;
    (*(s64 *)((s8 *)(packet) + (0x58))) = s4;
    c4 = ((s64)((s32)*(f32 *)(vec + 0x60) + g_screen_offset_x - 8)) | ((s64)((s32)*(f32 *)(vec + 0x64) + g_screen_offset_y - 8) << 16) | ((s64)g_hud_sprite_color_word << 32);
    (*(s64 *)((s8 *)(packet) + (0x68))) = 0;
    (*(s64 *)((s8 *)(packet) + (0x60))) = c4;
    g_dma_packet_cursor = (s8 *)g_dma_packet_cursor + 0x70;
}
