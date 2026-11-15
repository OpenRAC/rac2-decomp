
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

extern s32 func_0011D450(s8 *a0, u32 a1, s32 a2);
extern s8 D_00140140[];
extern s32 D_00134744;

/* Binds RPC client D_00140140 to server 0x80000003, retrying with a short delay until it is
   ready; sets D_00134744 to 0 and returns 0, or returns -1 if binding fails. */
s32 func_0011E740(void) {
    s32 var_v0;
    s32 ret;

    goto loop_3;
block_1:
    var_v0 = 0x100000;
    do {
        var_v0 -= 1;
    } while (var_v0 != -1);
loop_3:
    if (func_0011D450(D_00140140, 0x80000003, 0) < 0) {
        ret = -1;
    } else {
        if ((*(s32 *)((char *)(D_00140140) + (0x24))) == 0) {
            goto block_1;
        }
        D_00134744 = 0;
        ret = 0;
    }
    return ret;
}
