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

extern f32 ref_L07_003F68F0_00 __attribute__((sda));
extern f32 ref_L07_003F68F0_01(f32);
extern f32 ref_L07_003F68F0_02(f32, f32);

/* Swings the object's yaw back and forth: adds the step to a swing angle and sets the yaw around its rest yaw. */
void swing_update_yaw(s8 *moby, f32 turnStep) {
    s8 *vars;
    f32 swingAngle;
    f32 yaw;

    vars = *(s8 **)(moby + 0x68);
    swingAngle = ref_L07_003F68F0_02(*(f32 *)(vars + 0x54), turnStep);
    *(f32 *)(vars + 0x54) = swingAngle;
    yaw = ref_L07_003F68F0_00 * (ref_L07_003F68F0_01(swingAngle) * 0.017453294f);
    *(f32 *)(moby + 0xF8) = yaw;
    *(f32 *)(moby + 0xF8) = ref_L07_003F68F0_02(yaw, *(f32 *)(vars + 0x60));
}
