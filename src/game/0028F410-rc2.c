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

extern s32 func_00282CC0(s8 *, s8 *, s8 *);
extern s32 func_00282CF0(s8 *, s8 *, s8 *);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern s32 D_001A7350;
extern s32 D_001A7354;
extern s32 D_001B187C;
extern s8 *volatile D_001B22A8;

/* Draws a picture on the screen, turned by an angle around its centre. */
void func_0028F410(s32 texWidth, s32 texHeight, s64 textureWord, f32 centerX, f32 centerY, f32 halfHeight, f32 halfWidth, f32 angle) {
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
    *(f32 *)(vec + 0x0) = halfWidth * FastSinOrCosB(angle);
    *(f32 *)(vec + 0x4) = halfWidth * FastSinOrCosA(angle);
    *(f32 *)(vec + 0x10) = -halfHeight * FastSinOrCosA(angle);
    *(f32 *)(vec + 0x14) = halfHeight * FastSinOrCosB(angle);
    FastVecAdd(vec + 0x30, vec + 0x20, vec);
    FastVecSub(vec + 0x30, vec + 0x30, vec + 0x10);
    FastVecAdd(vec + 0x40, vec + 0x20, vec);
    FastVecAdd(vec + 0x40, vec + 0x40, vec + 0x10);
    FastVecSub(vec + 0x50, vec + 0x20, vec);
    FastVecSub(vec + 0x50, vec + 0x50, vec + 0x10);
    FastVecSub(vec + 0x60, vec + 0x20, vec);
    FastVecAdd(vec + 0x60, vec + 0x60, vec + 0x10);

    (*(s32 *)((s8 *)(gDmaPacketCursor) + (0))) = 0x10000007;
    rt1 = ((s64)0xB400 << 48) | 0x8001;
    s3 = texWidth << 4;
    (*(s32 *)((s8 *)(gDmaPacketCursor) + (4))) = 0;
    ra1 = ((((s64)0xA6A6 << 16) | 0xA6A6) << 11) | 0x106;
    r154 = 0x154;
    rt0 = ((s64)0x807F << 16) | 0x7F7F;
    s4 = texHeight << 20;
    t2 = s4 + s3;
    (*(s32 *)((s8 *)(gDmaPacketCursor) + (8))) = 0;
    (*(s32 *)((s8 *)(gDmaPacketCursor) + (0xC))) = 0x50000007;
    oldCursor = gDmaPacketCursor;
    packet = oldCursor + 0x10;
    gDmaPacketCursor = packet;
    (*(s64 *)((s8 *)(oldCursor) + (0x10))) = rt1;
    (*(s64 *)((s8 *)(packet) + (0x10))) = textureWord;
    (*(s64 *)((s8 *)(packet) + (0x28))) = s3;
    (*(s64 *)((s8 *)(packet) + (8))) = ra1;
    (*(s64 *)((s8 *)(packet) + (0x18))) = r154;
    (*(s64 *)((s8 *)(packet) + (0x20))) = rt0;
    c1 = ((s64)((s32)*(f32 *)(vec + 0x30) + gScreenOffsetX - 8)) | ((s64)((s32)*(f32 *)(vec + 0x34) + gScreenOffsetY - 8) << 16) | ((s64)D_001B187C << 32);
    (*(s64 *)((s8 *)(packet) + (0x38))) = t2;
    (*(s64 *)((s8 *)(packet) + (0x30))) = c1;
    c2 = ((s64)((s32)*(f32 *)(vec + 0x40) + gScreenOffsetX - 8)) | ((s64)((s32)*(f32 *)(vec + 0x44) + gScreenOffsetY - 8) << 16) | ((s64)D_001B187C << 32);
    (*(s64 *)((s8 *)(packet) + (0x48))) = 0;
    (*(s64 *)((s8 *)(packet) + (0x40))) = c2;
    c3 = ((s64)((s32)*(f32 *)(vec + 0x50) + gScreenOffsetX - 8)) | ((s64)((s32)*(f32 *)(vec + 0x54) + gScreenOffsetY - 8) << 16) | ((s64)D_001B187C << 32);
    (*(s64 *)((s8 *)(packet) + (0x50))) = c3;
    (*(s64 *)((s8 *)(packet) + (0x58))) = s4;
    c4 = ((s64)((s32)*(f32 *)(vec + 0x60) + gScreenOffsetX - 8)) | ((s64)((s32)*(f32 *)(vec + 0x64) + gScreenOffsetY - 8) << 16) | ((s64)D_001B187C << 32);
    (*(s64 *)((s8 *)(packet) + (0x68))) = 0;
    (*(s64 *)((s8 *)(packet) + (0x60))) = c4;
    gDmaPacketCursor = (s8 *)gDmaPacketCursor + 0x70;
}
