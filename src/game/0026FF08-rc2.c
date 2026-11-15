
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

extern f32 func_00283CE0(s32);
extern s8 D_001B5200[];

/* Starts a camera transition of the kind selected by arg1, storing its target and timing in the camera state. */
void func_0026FF08(s32 arg0, s32 arg1, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    f32 temp_f1;

    switch (arg1) {
    case 0: {
        s8 *p = D_001B5200;
        (*(s8 *)((char *)(p) + (0x3E9))) = 1;
        (*(f32 *)((char *)(p) + (0x3D4))) = fparg0;
        (*(s8 *)((char *)(p) + (0x3E8))) = 0;
        return;
    }
    case 1:
    case 2:
        if (arg0 == 0) {
            s8 *q = D_001B5200;
            (*(f32 *)((char *)(q) + (0x3D4))) = fparg0;
            (*(s8 *)((char *)(q) + (0x3E8))) = 0;
        } else {
            s8 *r = D_001B5200;
            (*(s16 *)((char *)(r) + (0x3EA))) = arg0;
            temp_f1 = 1.0f / IntToFloat(arg0);
            (*(s8 *)((char *)(r) + (0x3E8))) = arg1;
            (*(f32 *)((char *)(r) + (0x3F0))) = (*(f32 *)((char *)(r) + (0x3D8)));
            (*(f32 *)((char *)(r) + (0x3EC))) = temp_f1;
        }
        {
            s8 *t = D_001B5200;
            (*(s8 *)((char *)(t) + (0x3E9))) = 1;
        }
        break;
    case 3: {
        s8 *u = D_001B5200;
        (*(s8 *)((char *)(u) + (0x3E8))) = arg1;
        (*(f32 *)((char *)(u) + (0x3D4))) = fparg0;
        (*(s8 *)((char *)(u) + (0x3E9))) = 1;
        (*(f32 *)((char *)(u) + (0x3DC))) = fparg1;
        (*(f32 *)((char *)(u) + (0x3E0))) = fparg2;
        (*(f32 *)((char *)(u) + (0x3E4))) = fparg3;
        break;
    }
    }
}
