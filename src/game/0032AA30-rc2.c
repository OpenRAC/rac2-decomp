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
#ifndef NULL
#define NULL 0
#endif

extern s8 D_002359E0[];
extern s8 D_00189E20[];
extern f32 D_001B0594 __attribute__((sda));
extern f32 D_001B0598 __attribute__((sda));
extern void func_00282C88(void *);
extern s32 func_002A7820(s32, s32);
extern void *func_002C2210(void *, s32, s32, s32, s32, void *, s32, f32, f32, f32);
extern s32 func_00283CF0(f32);
extern void func_002FE8D8(s32, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);

void func_0032AA30(void) {
    s8 sp0[16];
    s8 sp10[16];
    s32 s4;
    s32 s3;
    s8 *s1;
    s8 *s0;
    s8 *p;
    f32 t;

    s4 = 0;
    func_00282C88(sp0);
    do {
        s3 = func_002A7820(0, 0x6F) << 24;
        s1 = D_002359E0 + s4 * 16;
        s0 = func_002C2210(s1, 0xC, s3 | 0x7F2020, 0, 1, sp0, 0, D_001B0594 * 0.5f, D_001B0594, 0.0f);
        if (s0 != NULL) {
            *(s8 *)(s0 + 9) = (s8)(FloatToInt(4.0f) + 0x70);
        }
        t = D_001B0598;
        s0 = func_002C2210(s1, 0xC, s3 | 0xFF4040, 1, 1, sp0, 0, t * 0.5f, t, 0.0f);
        if (s0 != NULL) {
            *(s8 *)(s0 + 9) = (s8)(FloatToInt(4.0f) + 0x70);
        }
        s4 += 1;
        p = D_00189E20;
        func_002FE8D8(*(s32 *)(p + 0x2290) + 0x10, sp10);
        vec_scale_to_length(sp10, sp10, -0.00277777785f);
        FastVecAdd(s1, s1, sp10);
    } while (s4 < 0x32);
}
