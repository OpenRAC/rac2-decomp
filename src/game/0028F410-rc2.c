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

extern s32 FastVecAdd(s8 *, s8 *, s8 *);
extern s32 FastVecSub(s8 *, s8 *, s8 *);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern s32 g_screen_offset_x;
extern s32 g_screen_offset_y;
extern s32 D_001B187C;
extern s8 *volatile g_dma_packet_cursor;

/* Draws a picture on the screen, turned by an angle around its centre. */
void DrawRotatedSprite(s32 texWidth, s32 texHeight, s64 textureWord, f32 centerX, f32 centerY, f32 halfHeight, f32 halfWidth, f32 angle) {
    s8 vec[0x68];
    s64 rt1 ;
    s64 ra1 ;
    s64 rt0 ;
    s64 r154 ;
    s32 s3;
    s32 s4;
    s32 t2;
    s8 *oldCursor;
    s8 *packet;
    s64 c1;
    s64 c2;
    s64 c3;
    s64 c4;

    *(f32 *)(vec + 0x20) = centerX;
    *(f32 *)(vec + 0x24) = centerY;
    *(f32 *)(vec + 0x0) = halfWidth * math_fast_sin_or_cos_b(angle);
    *(f32 *)(vec + 0x4) = halfWidth * math_fast_sin_or_cos_a(angle);
    *(f32 *)(vec + 0x10) = -halfHeight * math_fast_sin_or_cos_a(angle);
    *(f32 *)(vec + 0x14) = halfHeight * math_fast_sin_or_cos_b(angle);
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
    s3 = texWidth << 4;
    (*(s32 *)((s8 *)(g_dma_packet_cursor) + (4))) = 0;
    ra1 = ((((s64)0xA6A6 << 16) | 0xA6A6) << 11) | 0x106;
    r154 = 0x154;
    rt0 = ((s64)0x807F << 16) | 0x7F7F;
    s4 = texHeight << 20;
    t2 = s4 + s3;
    (*(s32 *)((s8 *)(g_dma_packet_cursor) + (8))) = 0;
    (*(s32 *)((s8 *)(g_dma_packet_cursor) + (0xC))) = 0x50000007;
    oldCursor = g_dma_packet_cursor;
    packet = oldCursor + 0x10;
    g_dma_packet_cursor = packet;
    (*(s64 *)((s8 *)(oldCursor) + (0x10))) = rt1;
    (*(s64 *)((s8 *)(packet) + (0x10))) = textureWord;
    (*(s64 *)((s8 *)(packet) + (0x28))) = s3;
    (*(s64 *)((s8 *)(packet) + (8))) = ra1;
    (*(s64 *)((s8 *)(packet) + (0x18))) = r154;
    (*(s64 *)((s8 *)(packet) + (0x20))) = rt0;
    c1 = ((s64)((s32)*(f32 *)(vec + 0x30) + g_screen_offset_x - 8)) | ((s64)((s32)*(f32 *)(vec + 0x34) + g_screen_offset_y - 8) << 16) | ((s64)D_001B187C << 32);
    (*(s64 *)((s8 *)(packet) + (0x38))) = t2;
    (*(s64 *)((s8 *)(packet) + (0x30))) = c1;
    c2 = ((s64)((s32)*(f32 *)(vec + 0x40) + g_screen_offset_x - 8)) | ((s64)((s32)*(f32 *)(vec + 0x44) + g_screen_offset_y - 8) << 16) | ((s64)D_001B187C << 32);
    (*(s64 *)((s8 *)(packet) + (0x48))) = 0;
    (*(s64 *)((s8 *)(packet) + (0x40))) = c2;
    c3 = ((s64)((s32)*(f32 *)(vec + 0x50) + g_screen_offset_x - 8)) | ((s64)((s32)*(f32 *)(vec + 0x54) + g_screen_offset_y - 8) << 16) | ((s64)D_001B187C << 32);
    (*(s64 *)((s8 *)(packet) + (0x50))) = c3;
    (*(s64 *)((s8 *)(packet) + (0x58))) = s4;
    c4 = ((s64)((s32)*(f32 *)(vec + 0x60) + g_screen_offset_x - 8)) | ((s64)((s32)*(f32 *)(vec + 0x64) + g_screen_offset_y - 8) << 16) | ((s64)D_001B187C << 32);
    (*(s64 *)((s8 *)(packet) + (0x68))) = 0;
    (*(s64 *)((s8 *)(packet) + (0x60))) = c4;
    g_dma_packet_cursor = (s8 *)g_dma_packet_cursor + 0x70;
}
