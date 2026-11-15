
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

extern s32 func_001234F0(f32);
extern s32 func_00131430(s64);
extern s32 func_00122B00(s32, s64);
extern s32 func_00122DA8(s32, s32);
extern f32 func_00123298(s32);
extern void ref_L19_0041C3D8_00(void *, s32, s32);

/* On its first frame, works out a value from the object's turn and stores it in the object's data, then moves to state 1. */
void func_L19_0041C3D8(void *moby) {
    void *vars;
    s32 value;

    vars = (*(void **)((char *)(moby) + (0x68)));
    if ((*(u8 *)((char *)(moby) + (0x20))) == 0) {
        value = FloatToDouble((*(f32 *)((char *)(moby) + (0xC))));
        (*(f32 *)((char *)(vars) + (0x10))) = DoubleToFloat(DivideDoubles(value, MultiplyDoubles(func_00131430((s64)0x8000 << 47), (s64)0x8120 << 47)));
        ref_L19_0041C3D8_00(moby, 1, -1);
    }
}
