
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

extern f32 func_00282C10(f32);
extern f32 func_00282C48(f32);

s32 func_002A88A0(f32 *arg0, f32 *arg1, f32 fparg0, f32 fparg1, f32 fparg2) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f14;
    f32 temp_f1;
    f32 temp_f22;
    f32 temp_f2;
    f32 temp_f3;
    s32 var_v0;

    temp_f14 = fparg0 * (fparg2 * 4.0f);
    temp_f22 = (fparg1 * fparg1) - temp_f14;
    if (temp_f22 == 0.0f) {
        *arg0 = -fparg1 / (2.0f * fparg0);
        return 1;
    }
    temp_f0 = square_root(func_00282C48(temp_f22));
    temp_f2 = -fparg1;
    temp_f3 = 2.0f * fparg0;
    temp_f0_2 = (temp_f2 - temp_f0) / temp_f3;
    *arg0 = (temp_f2 + temp_f0) / temp_f3;
    *arg1 = temp_f0_2;
    temp_f1 = *arg0;
    if (temp_f1 < temp_f0_2) {
        *arg1 = temp_f1;
        *arg0 = temp_f0_2;
    }
    var_v0 = 0;
    if (temp_f22 > 0.0f) {
        var_v0 = 2;
    }
    return var_v0;
}
