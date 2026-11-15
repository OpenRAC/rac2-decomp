
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
struct Ord3 {
    s32 w[3];
};
extern struct Ord3 D_001A9EA0;

void func_002AB378(f32 *arg0, f32 *arg1) {
    struct Ord3 ord = D_001A9EA0;
    f32 t[3][3];
    f32 tr;
    f32 s;
    s32 i;
    s32 j;
    s32 k;

    tr = arg1[0] + arg1[5] + arg1[10];
    if (tr > 0.0f) {
        s = square_root(tr + 1.0f);
        arg0[3] = s * 0.5f;
        s = 0.5f / s;
        arg0[0] = (arg1[9] - arg1[6]) * s;
        arg0[1] = (arg1[2] - arg1[8]) * s;
        arg0[2] = (arg1[4] - arg1[1]) * s;
    } else {
        t[0][1] = arg1[1];
        t[0][2] = arg1[2];
        t[1][0] = arg1[4];
        t[1][2] = arg1[6];
        t[2][0] = arg1[8];
        t[2][1] = arg1[9];
        t[0][0] = arg1[0];
        t[1][1] = arg1[5];
        t[2][2] = arg1[10];
        i = 0;
        if (arg1[0] < arg1[5]) {
            i = 1;
        }
        if (t[i][i] < arg1[10]) {
            i = 2;
        }
        j = ord.w[i];
        k = ord.w[j];
        s = square_root(t[i][i] - (t[j][j] + t[k][k]) + 1.0f);
        arg0[i] = s * 0.5f;
        if (s != 0.0f) {
            s = 0.5f / s;
        }
        arg0[3] = (t[k][j] - t[j][k]) * s;
        arg0[j] = (t[j][i] + t[i][j]) * s;
        arg0[k] = (t[k][i] + t[i][k]) * s;
    }
}
