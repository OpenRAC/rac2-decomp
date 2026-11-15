
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
#ifndef NULL
#define NULL 0
#endif

extern s32 func_00115AC0(void *dst, s8 *src, s32 n);
extern void func_0011AC40(s32 h);
extern s32 func_0011AC70(s32 h);
extern void func_0011CEC8(s32 a, s32 b);
extern s32 func_0011D620(void *a, s32 b, s32 c, void *d, s32 e, void *f, s32 g, s32 h, s32 i);

extern s32 D_00137E6C;
extern s32 D_00137E68;
extern s8 D_00141B00[];
extern s8 D_00141BB0[];
extern s8 D_001430C0[];

/* Fills the request record D_00141BB0 (five ints and a path string of up to 0x3FF characters)
   and sends it by RPC; returns -0x64 if uninitialised, -0xC8 if the lock fails and -0xD2 if
   the string is empty. */
s32 func_00127E40(s32 arg0, s32 arg1, s8 *arg2, s32 arg3, s32 arg4, s32 arg5) {
    s8 *g;
    s8 *rec;
    s32 r;

    g = D_00141B00;
    if (*(s32 *)(g + 0x24) == 0) {
        return -0x64;
    }
    if (func_0011AC70(D_00137E6C) < 0) {
        return -0xC8;
    }
    if (arg2 == NULL || *arg2 == 0) {
        func_0011AC40(D_00137E6C);
        return -0xD2;
    }
    *(s32 *)D_00141BB0 = arg0;
    rec = D_00141BB0;
    *(s32 *)(rec + 4) = arg1;
    *(s32 *)(rec + 8) = arg3;
    *(s32 *)(rec + 0xC) = arg4;
    *(s32 *)(rec + 0x10) = arg5;
    func_00115AC0(rec + 0x14, arg2, 0x3FF);
    rec[0x413] = 0;
    if (arg4 >= 0) {
        func_0011CEC8(arg5, arg4 << 6);
    }
    r = func_0011D620(g, 13, 1, rec, 0x414, D_001430C0, 4, 0, 0);
    if (r == 0) {
        D_00137E68 = 13;
    } else {
        func_0011AC40(D_00137E6C);
    }
    return r;
}
