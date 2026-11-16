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

struct Vec3 { f32 x; f32 y; f32 z; };
struct Vec4 { f32 x; f32 y; f32 z; f32 w; };

extern void *cam_moby_create(void *, s32, s16, s32, void *, void *, void *, s32, f32, f32);
extern void FastVecAdd(struct Vec3 *, struct Vec3 *, struct Vec4 *);
extern void vec_scale_to_length(struct Vec4 *, void *, f32);
extern void matrix_mul_vec3(struct Vec3 *, struct Vec3 *, void *);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_random_float_range(f32, f32);
extern f32 math_random_angle(void);
extern void part_update_fading_debris(void);
extern s32 g_ground_check_inhibit;

/* Throws out eight pieces of debris in random directions when the robot enemy is destroyed. */
void robot_spawn_death_debris(void *moby) {
    struct Vec4 direction;
    struct Vec3 velocity;
    void *vars;
    void *piece;
    f32 angle;
    f32 speed;
    f32 value;
    f32 spin_time;
    s32 i;

    vars = (*(void **)((s8 *)(moby) + (0x68)));
    vec_scale_to_length(&direction, (s8 *)vars + 0xE0, 0.05000000447034836f);
    for (i = 0; i < 0xF; i++) {
        if (!(((0x7F8 >> i) ^ 1) & 1)) {
            angle = math_random_angle();
            speed = math_random_float_range(3.0f, 5.0f) * 0.016666668f;
            velocity.x = math_fast_sin_or_cos_a(angle) * speed;
            value = math_fast_sin_or_cos_b(angle) * speed;
            velocity.z = 0.0f;
            velocity.y = value;
            velocity.z = math_random_float_range(3.0f, 5.0f) * 0.016666668f;
            if (g_ground_check_inhibit != 0) {
                matrix_mul_vec3(&velocity, &velocity, (s8 *)moby + 0xC0);
            }
            FastVecAdd(&velocity, &velocity, &direction);
            spin_time = math_random_float_range(90.0f, 270.0f);
            value = math_random_float_range(10.0f, 20.0f);
            piece = cam_moby_create(moby, 2, (*(s16 *)((s8 *)(moby) + (0xAA))), i, (s8 *)moby + 0x10, (s8 *)moby + 0xF0, &velocity, 0xFF, spin_time, value);
            if ((*(s32 *)((s8 *)(vars) + (0x2B4))) != 0 && piece != 0) {
                (*(s32 *)((s8 *)(piece) + (0x64))) = (s32)part_update_fading_debris;
            }
        }
    }
}
