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

extern void ref_L18_00428338_00(s8 *, s32, s8 *);
extern s32 ref_L18_00428338_01(s8 *, s8 *, s8 *, s32, s32, s32, s32, f32, f32);
extern f32 ref_L18_00428338_02 __attribute__((sda));

/* Lets the enemy aim at a target using two attachment points while in one state. Returns 0 in other states. */
s32 enemy_aim_at_target(s8 *moby) {
    s8 attach_point_a[0x10];
    s8 attach_point_b[0x10];
    s8 *vars;

    vars = *(s8 **)(moby + 0x68);
    if (*(u8 *)(moby + 0x42) == 0xA) {
        ref_L18_00428338_00(moby, 2, attach_point_a);
        ref_L18_00428338_00(moby, 3, attach_point_b);
        return ref_L18_00428338_01(moby, attach_point_a, attach_point_b, (*(u8 *)(moby + 0xBC) ^ 1) == 0 ? 0x4010000 : 0x4000001, 2, 3, 0, (f32) *(u8 *)(vars + 0x34), ref_L18_00428338_02);
    }
    return 0;
}
