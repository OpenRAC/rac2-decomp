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

extern s8 D_00222AE0[];
extern s8 D_002222E0[];
extern s8 D_00189EA0[];
extern s32 func_002ACBC8(s32 a0, s32 a1);

void func_00303AC8(void *arg0) {
    void *s0;
    s32 a1;
    s32 a2;
    s32 q;
    s32 sh;
    s8 *a0;
    s8 *a3;
    s8 *tmp;

    s0 = (*(void **)((s8 *)(arg0) + (0x68)));
    a1 = (*(s32 *)((s8 *)(s0) + (0x44)));
    if (a1 != -1 && IsPointInCuboid((s32)D_00189EA0, a1) != 0 && !((*(u32 *)((s8 *)(s0) + (0x4C))) & 4)) {
        sh = (*(s32 *)((s8 *)(s0) + (0x40))) << 10;
        tmp = (s8 *)D_00222AE0;
        tmp += 8;
        a3 = tmp + sh;
        a0 = D_002222E0;
        for (a1 = 0; a1 < 0x40; a1++) {
            *(f32 *)a3 = (*(f32 *)((s8 *)(s0) + (0x70))) + (*(f32 *)((s8 *)(s0) + (4)));
            a2 = (*(s32 *)((s8 *)(s0) + (0x4C)));
            if (~a2 & 0x10) {
                if ((a1 % 8 != 0 && a1 % 8 != 7) || ((a2 ^ 1) & 1)) {
                    q = a1 / 8;
                    if ((q != 0 && q != 7) || !((*(s32 *)((s8 *)(s0) + (0x4C))) & 2)) {
                        *(f32 *)a3 += *(f32 *)a0 * (*(f32 *)((s8 *)(s0) + (0x34)));
                    }
                }
            }
            a0 += 0x20;
            a3 += 0x10;
        }
    }
}
