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

extern f32 ref_L00_003E9930_00(s32);
extern f32 ref_L00_003E9930_01(f32, f32);
extern f32 ref_L00_003E9930_02(f32);
extern f32 ref_L00_003E9930_03(f32);
extern void ref_L00_003E9930_04(void *, void *, void *);
extern void ref_L00_003E9930_05(void *, void *, void *);
extern void ref_L00_003E9930_06(void *, void *, void *);
extern void ref_L00_003E9930_07(void *, void *, void *);
extern void ref_L00_003E9930_08(void *, void *, f32);

struct Ent {
    s32 x0;
    f32 x4;
    f32 x8;
    s32 xc;
};

struct Fr {
    struct Ent e[2];
    s8 pad20[0xB0];
    s8 b0[0x10];
    s8 b1[0x10];
};

/* Works out a sideways direction for the lightning arcs from two points on a small circle. */
void vec_compute_arc_side_direction(s8 *moby, s8 *center, s8 *out_direction, f32 radius) {
    struct Fr frame;
    s32 remaining;
    f32 angle;
    f32 angle_step;
    f32 side_value;
    f32 depth_value;
    struct Ent *entry;

    angle = 0.0f;
    angle_step = 6.283185482025146484375f / ref_L00_003E9930_00(11);
    remaining = 1;
    entry = &frame.e[0];
    do {
        angle = ref_L00_003E9930_01(angle, angle_step);
        entry->xc = 0;
        side_value = ref_L00_003E9930_02(angle) * radius;
        entry->x0 = 0;
        entry->x4 = side_value;
        depth_value = ref_L00_003E9930_03(angle);
        entry->x8 = -depth_value * radius;
        ref_L00_003E9930_04(entry, entry, moby + 0xC0);
        ref_L00_003E9930_05(entry, entry, center);
        entry += 1;
        remaining -= 1;
    } while (remaining >= 0);
    ref_L00_003E9930_06(frame.b0, &frame.e[0], center);
    ref_L00_003E9930_06(frame.b1, &frame.e[1], center);
    ref_L00_003E9930_07(out_direction, frame.b0, frame.b1);
    ref_L00_003E9930_08(out_direction, out_direction, 1.0f);
}
