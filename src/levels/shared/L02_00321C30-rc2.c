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
    TI toTarget;
    TI movedPosition;
} Scratch;

extern void ref_L02_00321C30_00(void *, void *, void *);
extern void ref_L02_00321C30_01(void *, void *, void *);
extern f32 ref_L02_00321C30_02(void *);
extern void ref_L02_00321C30_03(void *, void *, f32);

/* Moves a position toward a target, but by no more than a given limit. Returns how much of the distance was left over. */
f32 vec_step_toward_target_limited(void *position, void *target, f32 maxStep) {
    Scratch scratch;
    f32 distance;
    f32 stepLength;
    f32 negMaxStep;

    ref_L02_00321C30_01(&scratch.toTarget, target, position);
    stepLength = ref_L02_00321C30_02(&scratch.toTarget);
    distance = stepLength;
    if (maxStep < stepLength) {
        stepLength = maxStep;
    } else {
        negMaxStep = -maxStep;
        if (stepLength < negMaxStep) {
            stepLength = negMaxStep;
        }
    }
    ref_L02_00321C30_03(&scratch.toTarget, &scratch.toTarget, stepLength);
    ref_L02_00321C30_00(&scratch.movedPosition, position, &scratch.toTarget);
    return distance - stepLength;
}
