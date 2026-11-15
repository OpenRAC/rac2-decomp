
/* SPDX-License-Identifier: MIT
 * MIT License
 * 
 * Copyright (c) 2026 Forja contributors
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

extern s8 D_00141B00[];
extern s8 D_00141B80[];
extern s8 D_001430C0[];
extern s32 D_00137E6C;
extern s32 D_00137E68;
extern s32 func_0011AC40(s32);
extern s32 func_0011AC70(s32);
extern s32 func_0011D620(s32, s32, s32, s32, s32, s32, s32, s32, s32);

/* Sends a two-int request (RPC function 0x10) with the block D_00141B80; returns -0x64 if
   uninitialised and -0xC8 if the lock fails. */
s32 func_00127F90(s32 arg0, s32 arg1) {
    s8 *base = D_00141B00;
    s8 *blk;
    s32 a1 = arg1;
    s32 a0;
    s32 r;

    if (*(s32 *)(base + 0x24) == 0) {
        return -0x64;
    }
    a0 = arg0;
    if (func_0011AC70(D_00137E6C) < 0) {
        return -0xC8;
    }
    blk = D_00141B80;
    *(s32 *)(blk + 4) = a0;
    *(s32 *)(blk + 8) = a1;
    r = func_0011D620((s32)base, 0x10, 1, (s32)blk, 0x30, (s32)D_001430C0, 4, 0, 0);
    if (r == 0) {
        D_00137E68 = 0x10;
    } else {
        func_0011AC40(D_00137E6C);
    }
    return r;
}
