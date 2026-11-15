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

extern void func_00282A60(void *p, s32 c, s32 n);
extern u8 *D_001C4FAC;
extern s32 D_001A9720[];

typedef struct { s32 w[16]; } Tab32;

/* Shrinks a 4-bit map image into a 1-bit occlusion map. Each output bit is set when the sum of four samples is high enough. */
void func_00297BB0(u8 *occlusionOut)
{
    s32 rowSums[128];
    s32 nibbleWeights[16];
    u8 *src;
    u8 *dst;
    s32 row;
    s32 col;
    s32 cell;
    s32 group;

    dst = occlusionOut;
    src = D_001C4FAC;
    *(Tab32 *)nibbleWeights = *(Tab32 *)D_001A9720;
    for (row = 0; row < 0x200; row++) {
        if (row % 4 == 0) {
            ClearMemory(rowSums, 0, 0x200);
        }
        for (col = 0; col < 128; col += 2) {
            u8 packed = *src++;
            rowSums[col] += nibbleWeights[packed & 0xF];
            rowSums[col + 1] += nibbleWeights[packed >> 4];
        }
        if (row % 4 == 3) {
            for (cell = 0; cell < 128; cell++) {
                if (rowSums[cell] < 8) {
                    rowSums[cell] = 0;
                } else {
                    rowSums[cell] = 1 << (cell % 8);
                }
            }
            for (group = 0; group < 128; group += 8) {
                u8 *sumBytes = (u8 *)&rowSums[group];
                s32 t1 = sumBytes[0] | sumBytes[4];
                s32 t2 = sumBytes[8] | t1;
                s32 t3 = sumBytes[12] | t2;
                s32 t4 = sumBytes[16] | t3;
                s32 t5 = sumBytes[20] | t4;
                s32 t6 = sumBytes[24] | t5;
                s32 t7 = sumBytes[28] | t6;
                *dst++ = t7;
            }
        }
    }
    *occlusionOut &= 0xFE;
}
