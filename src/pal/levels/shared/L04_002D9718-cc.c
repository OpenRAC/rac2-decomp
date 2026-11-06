/* func_PAL_L04_002D9718, the PAL copy of func_L04_002D9780: the same C, where lit 0.024f becomes 0.0288f. */

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

extern s8 D_00189E20[];
extern s8 D_0018A070[];
extern f32 ref_L04_002D9780_00(void *, void *, void *, s32);
extern void ref_L04_002D9780_01(void *, f32, f32);
extern void ref_L04_002D9780_02(void *, void *, f32, f32, f32, f32);

void func_PAL_L04_002D9718(void) {
    s8 *b;
    s8 *c;
    s8 *p;

    s32 a3;
    s32 t1;
    s8 *d;
    s8 *bb;
    f32 r;

    b = D_00189E20;
    if ((*(u8 *)((char *)(b) + (0x22B4))) == 0) {
        (*(f32 *)((char *)(b) + (0x258))) = 0.8f;
        (*(f32 *)((char *)(b) + (0x25C))) = 0.7f;
        (*(f32 *)((char *)(b) + (0x260))) = 0.45f;
    }
    a3 = (*(s32 *)((char *)(b) + (0x229C)));
    if (a3 == 4) {
        c = D_00189E20;
        if ((*(s16 *)((char *)(c) + (0x4AC))) < (*(s32 *)((char *)(c) + (0x1B8))) && (*(u8 *)((char *)(c) + (0x49E))) == 0) {
            (*(f32 *)((char *)(c) + (0x25C))) = (*(f32 *)((char *)(c) + (0x4B8)));
        }
    } else {
        t1 = (*(s32 *)((char *)(b) + (0x2294)));
        if (t1 == 6) {
            (*(f32 *)((char *)(b) + (0x25C))) = 0.5f;
        } else if (t1 == 4) {
            (*(f32 *)((char *)(b) + (0x258))) = 0.35000002f;
        } else if ((u32)(a3 - 0x11) < 2U) {
            (*(s32 *)((char *)(b) + (0x25C))) = 0;
            (*(s32 *)((char *)(b) + (0x258))) = 0;
        } else {
            if ((*(u8 *)((char *)(b) + (0x1492))) != 0 && (*(s32 *)((char *)(b) + (0x340))) != 0) {
                (*(f32 *)((char *)(b) + (0x258))) = 0.8f;
                (*(f32 *)((char *)(b) + (0x25C))) = 0.9f;
            } else {
                b = D_00189E20;
                if ((*(s32 *)((char *)(b) + (0x2294))) == 0x7C) {
                    (*(f32 *)((char *)(b) + (0x260))) = 0.8f;
                }
            }
        }
    }
    p = D_00189E20;
    if ((*(u8 *)((char *)(p) + (0x287))) == 0 || (*(s32 *)((char *)(p) + (0x22A4))) == 0x12 || (*(s32 *)((char *)(p) + (0x22B0))) == 0x12 || ((*(u8 *)((char *)(p) + (0x22B4))) == 0 && (*(f32 *)((char *)(p) + (0x254))) < 0.53f) || (*(s32 *)((char *)(p) + (0x229C))) == 0x11 || (*(u8 *)((char *)(p) + (0x1494))) != 0 || ((r = ref_L04_002D9780_00(p + 0x240, p + 0x80, b, a3)), ((*(f32 *)((char *)(p) + (0x264))) * 0.5f) < r)) {
        d = D_0018A070;
        bb = d - 0x250;
        ref_L04_002D9780_01(d, (*(f32 *)((char *)(bb) + (0x258))), 0.024f);
        ref_L04_002D9780_01(d + 4, (*(f32 *)((char *)(bb) + (0x25C))), 0.024f);
        ref_L04_002D9780_02(d + 0x14, d + 0x18, (*(f32 *)((char *)(bb) + (0x260))), 0.028800001f, 0.43200004f, 0.080000006f);
    }
}
