
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

/* Solves a quadratic equation and returns how many real roots it has (0, 1 or 2), larger root first. */
s32 func_002A88A0(f32 *rootHigh, f32 *rootLow, f32 a, f32 b, f32 c) {
    f32 sqrtPart;
    f32 lowRoot;
    f32 fourAc;
    f32 highRoot;
    f32 discriminant;
    f32 negB;
    f32 twoA;
    s32 rootCount;

    fourAc = a * (c * 4.0f);
    discriminant = (b * b) - fourAc;
    if (discriminant == 0.0f) {
        *rootHigh = -b / (2.0f * a);
        return 1;
    }
    sqrtPart = square_root(FloatAbs(discriminant));
    negB = -b;
    twoA = 2.0f * a;
    lowRoot = (negB - sqrtPart) / twoA;
    *rootHigh = (negB + sqrtPart) / twoA;
    *rootLow = lowRoot;
    highRoot = *rootHigh;
    if (highRoot < lowRoot) {
        *rootLow = highRoot;
        *rootHigh = lowRoot;
    }
    rootCount = 0;
    if (discriminant > 0.0f) {
        rootCount = 2;
    }
    return rootCount;
}
