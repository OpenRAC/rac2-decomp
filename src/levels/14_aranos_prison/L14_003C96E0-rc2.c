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

extern void ref_L14_003C96E0_00(s8 *, s32, s32);
extern f32 ref_L14_003C96E0_01(f32);
extern void ref_L14_003C96E0_02(s8 *, s8 *, s8 *);
extern void ref_L14_003C96E0_03(s8 *, s8 *, f32);

/* Starts a launch toward a target: works out the aim direction and the speeds from the heights and ranges, and puts the object into state 0x16. */
void entity_start_launch_to_target(s8 *moby, s8 *target, f32 apexZ, f32 rangeA, f32 rangeB) {
    f32 scaledAngle;
    f32 heightDelta;
    f32 totalAngle;
    f32 targetZ;
    s8 *vars;
    s8 *aimVector;

    vars = *(s8 **)(moby + 0x68);
    ref_L14_003C96E0_00(moby, 0x16, 7);
    heightDelta = apexZ - *(f32 *)(moby + 0x18);
    heightDelta = heightDelta + heightDelta; aimVector = vars + 0x1B0; totalAngle = ref_L14_003C96E0_01(heightDelta / rangeA);
    totalAngle = totalAngle + ref_L14_003C96E0_01((2.0f * (apexZ - *(f32 *)(target + 8))) / rangeB);
    ref_L14_003C96E0_02(aimVector, target, moby + 0x10);
    ref_L14_003C96E0_03(aimVector, aimVector, 1.0f / totalAngle);
    scaledAngle = ref_L14_003C96E0_01(heightDelta * rangeA);
    *(f32 *)(vars + 0x394) = rangeA;
    *(f32 *)(vars + 0x398) = rangeB;
    *(f32 *)(vars + 0x1B8) = scaledAngle;
    targetZ = *(f32 *)(target + 8) + 0.333f;
    *(s32 *)(vars + 0x14C) = -1;
    *(f32 *)(vars + 0x3A0) = targetZ;
}
