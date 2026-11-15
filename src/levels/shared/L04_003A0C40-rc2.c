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
void func_L04_003A0C40(void *origin) {
    s32 row;
    s32 col;
    f32 *srcPtr;
    f32 *outPtr;
    f32 srcVal;
    f32 xPos;
    f32 yPos;
    s32 nextRow;

    outPtr = (f32 *)0x70002000;
    row = 0;
    yPos = (*(f32 *)((s8 *)(origin) + (4))) + ref_L04_003A0C40_01;
    do {
        nextRow = row + 1;
        xPos = (*(f32 *)((s8 *)(origin) + (0))) + ref_L04_003A0C40_00;
        srcPtr = (f32 *)((s8 *)0x70000010 + nextRow * 0x60);
        col = 0x10;
        do {
            *outPtr = xPos;
            col -= 1;
            outPtr += 1;
            *outPtr = yPos;
            outPtr += 1;
            srcVal = *srcPtr;
            srcPtr += 1;
            *outPtr = srcVal + (*(f32 *)((s8 *)(origin) + (8)));
            outPtr += 1;
            xPos += ref_L04_003A0C40_02;
        } while (col >= 0);
        row = nextRow;
        yPos += ref_L04_003A0C40_03;
    } while (row < 0x11);
}
