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

extern f32 ref_L04_003A0C40_00;
extern f32 ref_L04_003A0C40_01;
extern f32 ref_L04_003A0C40_02;
extern f32 ref_L04_003A0C40_03;

/* Fills a 17 by 17 grid of points starting at the given position. */
void water_fill_grid_points(void *origin) {
    s32 row;
    s32 col;
    f32 *src_ptr;
    f32 *out_ptr;
    f32 src_val;
    f32 x_pos;
    f32 y_pos;
    s32 next_row;

    out_ptr = (f32 *)0x70002000;
    row = 0;
    y_pos = (*(f32 *)((s8 *)(origin) + (4))) + ref_L04_003A0C40_01;
    do {
        next_row = row + 1;
        x_pos = (*(f32 *)((s8 *)(origin) + (0))) + ref_L04_003A0C40_00;
        src_ptr = (f32 *)((s8 *)0x70000010 + next_row * 0x60);
        col = 0x10;
        do {
            *out_ptr = x_pos;
            col -= 1;
            out_ptr += 1;
            *out_ptr = y_pos;
            out_ptr += 1;
            src_val = *src_ptr;
            src_ptr += 1;
            *out_ptr = src_val + (*(f32 *)((s8 *)(origin) + (8)));
            out_ptr += 1;
            x_pos += ref_L04_003A0C40_02;
        } while (col >= 0);
        row = next_row;
        y_pos += ref_L04_003A0C40_03;
    } while (row < 0x11);
}
