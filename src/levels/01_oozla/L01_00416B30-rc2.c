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

extern s32 ref_L01_00416B30_00(s32);

/* Sets up the gold bolt glow values and brightness steps. */
void func_L01_00416B30(void *moby) {
    s32 *vars  = *(s32 **)((u8 *)moby + 0x68);
    f32 *valuePtr  = (f32 *)((u8 *)vars + 0x20);
    s32 count  = 3;
    s32 *slotPtr ;
    s32 brightness ;

    do {
        count--;
        *valuePtr = (f32)ref_L01_00416B30_00(0xFF);
        valuePtr++;
    } while (count >= 0);

    *(f32 *)((u8 *)vars + 0x30) = -1.0f;
    count = 3;
    *(f32 *)((u8 *)vars + 0x34) = -2.25f;
    slotPtr = (s32 *)((u8 *)vars + 0x4C);
    *(f32 *)((u8 *)vars + 0x38) = 1.25f;
    brightness = 0xFF;
    *(f32 *)((u8 *)vars + 0x3C) = 2.5f;

    do {
        *slotPtr = brightness;
        count--;
        slotPtr--;
        brightness -= 0x40;
    } while (count >= 0);

    *(volatile f32 *)((u8 *)vars + 0x5C) = 2.5f;
    *(volatile f32 *)((u8 *)vars + 0x58) = 3.0f;
    *(volatile f32 *)((u8 *)vars + 0x50) = 2.5f;
    *(volatile f32 *)((u8 *)vars + 0x54) = 3.0f;
}
