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

extern void mem_clear(void *p, s32 c, s32 n);
extern u8 *D_001C4FAC;
extern s32 D_001A9720[];

typedef struct { s32 w[16]; } Tab32;

/* Shrinks a 4-bit map image into a 1-bit occlusion map. Each output bit is set when the sum of four samples is high enough. */
void map_build_occlusion_from_image(u8 *occlusion_out)
{
    s32 row_sums[128];
    s32 nibble_weights[16];
    u8 *src;
    u8 *dst;
    s32 row;
    s32 col;
    s32 cell;
    s32 group;

    dst = occlusion_out;
    src = D_001C4FAC;
    *(Tab32 *)nibble_weights = *(Tab32 *)D_001A9720;
    for (row = 0; row < 0x200; row++) {
        if (row % 4 == 0) {
            mem_clear(row_sums, 0, 0x200);
        }
        for (col = 0; col < 128; col += 2) {
            u8 packed = *src++;
            row_sums[col] += nibble_weights[packed & 0xF];
            row_sums[col + 1] += nibble_weights[packed >> 4];
        }
        if (row % 4 == 3) {
            for (cell = 0; cell < 128; cell++) {
                if (row_sums[cell] < 8) {
                    row_sums[cell] = 0;
                } else {
                    row_sums[cell] = 1 << (cell % 8);
                }
            }
            for (group = 0; group < 128; group += 8) {
                u8 *sum_bytes = (u8 *)&row_sums[group];
                s32 t1 = sum_bytes[0] | sum_bytes[4];
                s32 t2 = sum_bytes[8] | t1;
                s32 t3 = sum_bytes[12] | t2;
                s32 t4 = sum_bytes[16] | t3;
                s32 t5 = sum_bytes[20] | t4;
                s32 t6 = sum_bytes[24] | t5;
                s32 t7 = sum_bytes[28] | t6;
                *dst++ = t7;
            }
        }
    }
    *occlusion_out &= 0xFE;
}
