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
void entity_start_launch_to_target(s8 *moby, s8 *target, f32 apex_z, f32 range_a, f32 range_b) {
    f32 scaled_angle;
    f32 height_delta;
    f32 total_angle;
    f32 target_z;
    s8 *vars;
    s8 *aim_vector;

    vars = *(s8 **)(moby + 0x68);
    ref_L14_003C96E0_00(moby, 0x16, 7);
    height_delta = apex_z - *(f32 *)(moby + 0x18);
    height_delta = height_delta + height_delta; aim_vector = vars + 0x1B0; total_angle = ref_L14_003C96E0_01(height_delta / range_a);
    total_angle = total_angle + ref_L14_003C96E0_01((2.0f * (apex_z - *(f32 *)(target + 8))) / range_b);
    ref_L14_003C96E0_02(aim_vector, target, moby + 0x10);
    ref_L14_003C96E0_03(aim_vector, aim_vector, 1.0f / total_angle);
    scaled_angle = ref_L14_003C96E0_01(height_delta * range_a);
    *(f32 *)(vars + 0x394) = range_a;
    *(f32 *)(vars + 0x398) = range_b;
    *(f32 *)(vars + 0x1B8) = scaled_angle;
    target_z = *(f32 *)(target + 8) + 0.333f;
    *(s32 *)(vars + 0x14C) = -1;
    *(f32 *)(vars + 0x3A0) = target_z;
}
