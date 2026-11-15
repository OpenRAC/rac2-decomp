#include "names.h"

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

extern f32 square_root(f32);
extern f32 math_fabs(f32);

/* Solves a quadratic equation and returns how many real roots it has (0, 1 or 2), larger root first. */
s32 math_solve_quadratic(f32 *root_high, f32 *root_low, f32 a, f32 b, f32 c) {
    f32 sqrt_part;
    f32 low_root;
    f32 four_ac;
    f32 high_root;
    f32 discriminant;
    f32 neg_b;
    f32 two_a;
    s32 root_count;

    four_ac = a * (c * 4.0f);
    discriminant = (b * b) - four_ac;
    if (discriminant == 0.0f) {
        *root_high = -b / (2.0f * a);
        return 1;
    }
    sqrt_part = square_root(math_fabs(discriminant));
    neg_b = -b;
    two_a = 2.0f * a;
    low_root = (neg_b - sqrt_part) / two_a;
    *root_high = (neg_b + sqrt_part) / two_a;
    *root_low = low_root;
    high_root = *root_high;
    if (high_root < low_root) {
        *root_low = high_root;
        *root_high = low_root;
    }
    root_count = 0;
    if (discriminant > 0.0f) {
        root_count = 2;
    }
    return root_count;
}
