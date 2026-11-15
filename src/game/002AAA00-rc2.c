
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
extern f32 func_00283B98(f32, f32);
extern void func_002AA2E8(f32 *, f32, f32);
extern f32 func_002AA738(s32, f32, f32);
extern void func_002AA800(f32 *, s32, f32, f32);

f32 func_002AAA00(f32 *p, f32 *q, s32 mode, f32 fa, f32 fb, f32 fc, f32 fd)
{
    s32 a0;
    f32 r1;
    f32 t23;
    f32 s4;
    f32 s2;
    f32 r;

    a0 = mode;
    if (mode != 2) {
        goto abc;
    }
    if (fa > 0.0f && *p < 0.0f) {
        goto aa0;
    }
    a0 = 0;
    if (fa < 0.0f && *p > 0.0f) {
        goto aa0;
    }
    goto abc;
aa0:
    a0 = 1;
    if (fa < 0.0f) {
        a0 = -1;
    }
abc:
    r1 = func_002AA738(a0, fa, *p);
    if (*q == 0.0f && r1 == 0.0f) {
        return 0.0f;
    }
    {
        f32 qv = *q;
        f32 qn;

        if (0.0f <= qv * r1) {
            t23 = ((qv * qv) / fc) * 0.5f;
            if (func_00282C48(r1) < t23) {
                s2 = func_00282C48(r1);
                if (t23 < s2 + func_00282C48(*q)) {
                    ApproachValue(q, 0.0f, fc);
                } else {
                    ApproachValue(q, 0.0f, fc * 1.1f);
                }
            } else {
                r = square_root((fc + fc) * r1);
                if (fd < r) {
                    r = fd;
                }
                if (r1 < 0.0f) {
                    StepAngleTowardTarget(q, 0, -r, fb);
                } else {
                    StepAngleTowardTarget(q, 0, r, fb);
                }
            }
            s4 = func_00282C48(r1);
            if (func_00282C48(*q) < s4) {
                qn = *q;
            } else {
                *p = fa;
                return r1;
            }
        } else {
            if (0.0f <= qv) {
                qn = qv - fc;
            } else {
                qn = qv + fc;
            }
            *q = qn;
        }
        *p = FastAddRotations(qn, *p);
        return *q;
    }
}
