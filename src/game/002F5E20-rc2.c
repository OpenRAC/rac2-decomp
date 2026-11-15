
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

extern s32  D_001B2208;

extern s32  D_001B221C;

extern s32  D_001B220C;

extern s32  D_001B2210;

extern s32  D_001B2214;

extern s32 D_001B2218 __attribute__((sda));
extern u8 D_00188660[];
extern s16 D_001A63F0[];
extern void func_0011AEA0(s32 a);
extern void func_00133710(s32 a, s32 b, s32 c, s32 d, s32 e);
extern void func_0027D330(s32 a);
extern void func_00288EA0(void);
extern void func_002B7170(void);
extern void func_002E5FE0(void);

void func_002F5E20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u8 *p;

    p = D_00188660;
    p[0x6B] = p[0x6B] | 8;
    func_00133710(2, 0, 0, 0, 0);
    func_0011AEA0(0);
    func_002E5FE0();
    func_002B7170();
    D_001B2208 = arg0;
    D_001B221C = (s32) D_001A63F0[0];
    D_001B220C = arg1;
    D_001B2210 = arg2;
    D_001B2214 = arg3;
    D_001B2218 = arg4;
    FadeToBlack(4);
    func_00288EA0();
}
