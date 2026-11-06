
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

/* func_US2_002CC908, the USA v2.00 copy of func_002CB950: the same C, where
 * case 4 also sets a v2.00-only flag. */

/* The resident table already holds the retail label addresses. The unused
 * label list keeps each C branch available; it is not read by the program. */
extern void *D_0026CCE0[];

struct S18A000 {
    s16 a;
    s8 pad[10];
};
extern struct S18A000 D_0018A000;
extern s32 D_001AA420;
extern s32 D_001AA428;
extern s8 D_0025BA90[];
extern s32 D_US2_001F29B4[];
extern void func_0028B338(s32);
extern void func_002B49C0(s32);
extern s32 func_002B49E0(s32, s32, s32, s32, s32);
extern s32 func_002D5B38(s32, s8 *);

s32 func_US2_002CC908(s32 arg0) {
    s32 r;

    r = 0;
    {
    static void *volatile rc2_labels[] = {&&rc2_case_0, &&rc2_case_1, &&rc2_case_2, &&rc2_case_3, &&rc2_case_4};
    u32 rc2_selector = (u32)(arg0);
    if (rc2_selector > 4U) goto rc2_switch_end;
goto *D_0026CCE0[rc2_selector];

    rc2_case_0:
        D_0018A000.a = 10;
        r = 1;
        goto rc2_switch_end;
    rc2_case_1:
        r = 1;
        D_0018A000.a = 10;
        if (D_001AA420 != 0) {
            func_0028B338(0);
            ((void (*)(s32))D_001AA420)(0);
            func_0028B338(1);
        }
        goto rc2_switch_end;
    rc2_case_2:
        r = 1;
        D_0018A000.a = 10;
        if (D_001AA428 != 0) {
            func_0028B338(0);
            ((void (*)(s32))D_001AA428)(0);
            func_0028B338(1);
        }
        goto rc2_switch_end;
    rc2_case_3:
        r = func_002D5B38(3, D_0025BA90);
        goto rc2_switch_end;
    rc2_case_4:
        if (func_002B49E0(4, 2, 8, 4, 0) == 0) {
            func_002B49C0(3);
            D_US2_001F29B4[0] = 1;
            r = 1;
        }
        goto rc2_switch_end;
    
rc2_switch_end: ;
}
    return r;
}
