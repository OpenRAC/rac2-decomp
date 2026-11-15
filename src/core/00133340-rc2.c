
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

extern void func_00132DF0(s32 a0, s32 a1, void *a2, s32 a3, s64 t0);

/* Queues sound command 0x2C with eight ints, packing the third/fifth and fourth/sixth
   arguments as halfword pairs, plus two extra callback arguments. */
void func_00133340(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s64 arg11) {
    s32 buf[8];
    s32 p02;
    s32 p13;

    p13 = ((u32)arg5 << 16) | (arg3 & 0xFFFF);
    p02 = ((u32)arg4 << 16) | (arg2 & 0xFFFF);
    buf[0] = arg0;
    buf[1] = arg1;
    buf[2] = p02;
    buf[3] = p13;
    buf[4] = arg6;
    buf[5] = arg7;
    buf[6] = arg8;
    buf[7] = arg9;
    func_00132DF0(0x2C, 0x20, buf, arg10, arg11);
}
