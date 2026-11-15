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

typedef int TI __attribute__((mode(TI)));

typedef struct Sub {
    s8 *p00;
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10;
    f32 f14;
    s8 *p18;
    f32 f1C;
} Sub;

typedef struct Obj {
    s8 pad00[4];
    s32 w04;
    u8 b08;
    s8 pad09[3];
    f32 f0C;
    f32 vec[4];
    Sub sub;
} Obj;

typedef struct Fr {
    f32 c[4];
    f32 a[4];
    f32 b[4];
    TI m0;
    TI m1;
    TI m2;
    TI pad;
} Fr;

extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern void transform_vector(f32 *, f32 *, s8 *);
extern void FastVecSub(f32 *, f32 *, f32 *);
extern void moby_transform_joint_to_world(s8 *, s32, f32 *);
extern void vec_scale_to_length(f32 *, f32 *, f32);
extern void FastVecAdd(f32 *, f32 *, f32 *);
extern f32 FastAddRotations(f32, f32);
extern s32 FloatToInt(f32);
extern f32 mat_get_product_element(f32 *, s8 *, f32 *, s32);
extern s32 FastDecTimer(s8 *);
extern void part_kill(Obj *);

/* Updates a small drifting particle that hops off the ground and slowly fades out. It disappears when it has faded away or its timer runs out. */
void part_update_bouncing_fade(Obj *particle)
{
    Sub *state = &particle->sub;
    Fr work;

    if (state->f10 != 0.0f) {
        s8 *matrix = state->p00;
        f32 *vec = particle->vec;
        work.m0 = *(TI *)matrix;
        work.m1 = *(TI *)(matrix + 0x10);
        work.m2 = *(TI *)(matrix + 0x20);
        work.a[1] = math_fast_sin_or_cos_b(state->f14) * state->f10;
        work.a[2] = math_fast_sin_or_cos_a(state->f14) * state->f10;
        work.a[0] = 0.0f;
        work.a[3] = 0.0f;
        transform_vector(work.b, work.a, (s8 *)&work.m0);
        FastVecSub(vec, vec, work.b);
        state->f1C = state->f1C + 0.0600100006f;
        moby_transform_joint_to_world(state->p18, 0, work.c);
        FastVecSub(work.a, work.c, vec);
        vec_scale_to_length(work.a, work.a, state->f1C);
        FastVecAdd(vec, vec, work.a);
        state->f14 = FastAddRotations(state->f14, 0.5235988f);
        state->f10 = state->f10 * 0.9f;
        work.a[1] = math_fast_sin_or_cos_b(state->f14) * state->f10;
        work.a[2] = math_fast_sin_or_cos_a(state->f14) * state->f10;
        work.a[0] = 0.0f;
        work.a[3] = 0.0f;
        transform_vector(work.b, work.a, (s8 *)&work.m0);
        FastVecAdd(vec, vec, work.b);
        if (mat_get_product_element(work.c, state->p18 + 0xC0, vec, 1) > 0.0f) {
            part_kill(particle);
            return;
        }
    }

    state->f04 = state->f04 + state->f0C * 0.011f;
    if (state->f04 <= 0.0f) {
        part_kill(particle);
        return;
    }
    if (FastDecTimer((s8 *)particle + 0xA) != 0) {
        part_kill(particle);
        return;
    }
    if (1.0f <= state->f04) {
        state->f0C = -state->f0C;
        state->f04 = state->f04 + state->f0C * 0.011f;
    }
    particle->f0C = particle->f0C + (-2940.0f);
    particle->w04 = (particle->w04 & 0x00FFFFFF) | (FloatToInt(state->f04 * 255.0f) << 24);
    state->f08 = state->f08 + 0.006f;
    if (1.0f < state->f08) state->f08 = state->f08 - 1.0f;
    particle->b08 = (s32)(state->f08 * 255.0f);
}
