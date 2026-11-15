
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

struct T44 { s32 f[11]; };
extern s8 D_0013BBC8[];
extern s32 func_0012C680(s64,s32);
extern void func_0012C788(s64,s32);
extern u32 func_0012C878(s64,s32);
 
extern void func_0012C9C8(s64);
/* Handles extension and user data: while the next start code is 0x1B5 or 0x1B2, calls the
   extension handler selected from a table (ids above 10 use entry 0) or skips the user data. */
void func_0012CC88(s64 arg0) {
    struct T44 tab;
    s32 v;
    u32 idx;
    tab=*(struct T44 *)D_0013BBC8;
    func_0012C9C8(arg0);
    while ((v=func_0012C680(arg0,0x20))==0x1B5 || v==0x1B2) {
        if (v==0x1B5) {
            func_0012C788(arg0,0x20);
            idx=func_0012C878(arg0,4);
            idx=(idx>10)?0:idx;
            ((void (*)(s64))tab.f[idx])(arg0);
            func_0012C9C8(arg0);
        } else {
            func_0012C788(arg0,0x20);
            func_0012C9C8(arg0);
        }
    }
}
