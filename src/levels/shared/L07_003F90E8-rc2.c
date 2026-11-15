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

extern s32 ref_L07_003F90E8_00 __attribute__((sda));
extern f32 ref_L07_003F90E8_01(s32);

/* Blends smoothly between two values depending on where a global value sits between two limits. */
f32 math_interpolate_between_limits(s32 low_limit, s32 high_limit, f32 low_value, f32 high_value) {
    f32 high_term;
    f32 current_term;
    f32 low_term;

    if (low_limit >= ref_L07_003F90E8_00) {
        return low_value;
    }
    if (ref_L07_003F90E8_00 >= high_limit) {
        return high_value;
    }
    current_term = ref_L07_003F90E8_01(ref_L07_003F90E8_00);
    low_term = ref_L07_003F90E8_01(low_limit);
    high_term = ref_L07_003F90E8_01(high_limit);
    {
        f32 den = high_term - ref_L07_003F90E8_01(low_limit);
        f32 num = current_term - low_term;
        f32 dif = high_value - low_value;
        num = num / den;
        return low_value + (dif * num);
    }
}
