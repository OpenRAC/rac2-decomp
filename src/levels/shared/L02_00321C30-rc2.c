#include "names.h"
/* SPDX-License-Identifier: MIT
 * MIT License
 *
 * Copyright (c) 2026 RC2 decomp contributions
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

typedef int TI __attribute__((mode(TI)));
typedef struct {
    TI to_target;
    TI moved_position;
} Scratch;

extern void ref_L02_00321C30_00(void *, void *, void *);
extern void ref_L02_00321C30_01(void *, void *, void *);
extern f32 ref_L02_00321C30_02(void *);
extern void ref_L02_00321C30_03(void *, void *, f32);

/* Moves a position toward a target, but by no more than a given limit. Returns how much of the distance was left over. */
f32 vec_step_toward_target_limited(void *position, void *target, f32 max_step) {
    Scratch scratch;
    f32 distance;
    f32 step_length;
    f32 neg_max_step;

    ref_L02_00321C30_01(&scratch.to_target, target, position);
    step_length = ref_L02_00321C30_02(&scratch.to_target);
    distance = step_length;
    if (max_step < step_length) {
        step_length = max_step;
    } else {
        neg_max_step = -max_step;
        if (step_length < neg_max_step) {
            step_length = neg_max_step;
        }
    }
    ref_L02_00321C30_03(&scratch.to_target, &scratch.to_target, step_length);
    ref_L02_00321C30_00(&scratch.moved_position, position, &scratch.to_target);
    return distance - step_length;
}
