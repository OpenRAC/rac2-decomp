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

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

extern f32 ref_L18_00437BA8_00(f32);
extern f32 ref_L18_00437BA8_01(f32);
extern f32 ref_L18_00437BA8_02(f32, f32);
extern f32 ref_L18_00437BA8_03(s32);
extern s32 ref_L18_00437BA8_04(s32);
extern s32 ref_L18_00437BA8_05(s32, s32);
extern f32 ref_L18_00437BA8_06(f32, f32);
extern void ref_L18_00437BA8_07(void *, Vec3 *, void *, s32, s32);
extern f32 ref_L18_00437BA8_08 __attribute__((sda));
extern f32 ref_L18_00437BA8_09 __attribute__((sda));
extern f32 ref_L18_00437BA8_10 __attribute__((sda));
extern f32 ref_L18_00437BA8_11 __attribute__((sda));
extern s32 ref_L18_00437BA8_12 __attribute__((sda));

/* Spawns a ring of small sparks around a point, each flying outward at its own random speed. */
void part_l18_spawn_ring_of_sparks(void *position, s32 count) {
    f32 radial_speed;
    f32 angle_step;
    f32 angle;
    s32 random_bit;
    s32 remaining;
    s32 random_offset;
    Vec3 velocity;

    angle_step = 6.2831855f / ref_L18_00437BA8_03(count);
    angle = ref_L18_00437BA8_06(-3.1415927f, 3.1415927f);
    if (count > 0) {
        remaining = count;
        do {
            remaining -= 1;
            radial_speed = ref_L18_00437BA8_06(ref_L18_00437BA8_08, ref_L18_00437BA8_09) * 0.016666668f;
            velocity.x = radial_speed * ref_L18_00437BA8_00(angle);
            velocity.y = radial_speed * ref_L18_00437BA8_01(angle);
            velocity.z = ref_L18_00437BA8_06(ref_L18_00437BA8_10, ref_L18_00437BA8_11) * 0.016666668f;
            random_bit = ref_L18_00437BA8_04(2);
            random_offset = ref_L18_00437BA8_05(-2, 2);
            ref_L18_00437BA8_07(position, &velocity, &ref_L18_00437BA8_12, random_bit, random_offset);
            angle = ref_L18_00437BA8_02(angle, angle_step);
        } while (remaining != 0);
    }
}
