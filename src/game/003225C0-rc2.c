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

struct R192V {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} __attribute__((aligned(16)));

extern f32 func_002A7878(f32, f32);
extern void func_0029FCC0(void *, s32, struct R192V *);
extern void func_002820D0(struct R192V *, s32, s32, f32, f32, f32);

/* Draws a small glowing flash of random size at one joint of the robot enemy. */
void func_003225C0(void *moby) {
    struct R192V position;
    f32 size;
    position.z += RandomFloatRange(0.1f, 0.4f);
    TransformMobyJointToWorld(moby, 4, &position);
    size = RandomFloatRange(0.5f, 0.75f);
    DrawBillboardQuadWithUv(&position, 0x40, 0, size, RandomFloatRange(0.025f, 0.05f), 0.08f);
}
