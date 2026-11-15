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

extern s32 D_001AFC6C;
extern s32 g_001AFC6C __attribute__((sda));
extern f32 D_001B0A80 __attribute__((sda));
extern f32 D_001B0A84 __attribute__((sda));
extern s8 g_active_camera[];

struct Vec4 { f32 x; f32 y; f32 z; f32 w; };
struct Obj { s8 pad[0x10]; struct Vec4 pos; };
struct Tab { s8 pad[0x140]; f32 f140; f32 f144; };

f32 math_random_float_range(f32 a, f32 b);
f32 math_random_angle(void);
void vec_build_spherical_offset(struct Vec4 *p, f32 x, f32 y, f32 z);
s32 math_random_int_range(s32 a, s32 b);
void part_spawn_growing_puff(struct Vec4 *a, struct Vec4 *b, u32 c, s32 d, s32 e, f32 f);
void FastVecAdd(struct Vec4 *a, struct Vec4 *b, struct Vec4 *c);
f32 mat_fast_helper_a(f32 a, f32 b);
f32 math_random_signed_float_range(f32 a, f32 b);
int FloatToInt(f32 a);
f32 FastAddRotations(f32 a, f32 b);
f32 math_fast_sin_or_cos_a(f32 a);
f32 math_fast_sin_or_cos_b(f32 a);
unsigned char *part_spawn_spinning_spark(struct Vec4 *a, struct Vec4 *b, s32 c);
void moby_release_slot_by_id(struct Obj *a);
void moby_mark_spawned(struct Obj *a);

/* Per-frame update for an explosion effect: throws out a few sparks and pushed particles (fewer as the counter drops), counts the counter down and then runs the shared update. */
void explosion_effect_update(struct Obj *moby)
{
    struct Vec4 vec_b;
    struct Vec4 vec_a;
    struct Tab *camera;
    s32 i;
    s32 j;
    f32 rand_a;
    f32 rand_b;
    f32 rand_c;
    f32 rand_d;
    f32 rand_e;
    f32 rand_f;
    f32 rand_g;
    s32 rand_h;
    f32 angle;
    f32 spread_angle;
    f32 offset_x;
    f32 offset_y;
    f32 offset_z;
    f32 turn;
    f32 cos_part;
    f32 sin_part;
    f32 speed;

    i = 0;
    if (0x21 - D_001AFC6C > 0) {
        do {
            i++;
            rand_a = math_random_float_range(0.0f, 0.3700000047683716f);
            rand_b = math_random_angle();
            rand_c = math_random_angle();
            vec_build_spherical_offset(&vec_a, rand_a, rand_b, rand_c);
            rand_d = math_random_float_range(0.3499999940395355f, 0.6000000238418579f);
            vec_a.z = vec_a.z + rand_d;
            FastVecAdd(&vec_a, &vec_a, &moby->pos);
            rand_e = math_random_float_range(0.0016666668234393f, 0.01666666753590107f);
            rand_f = math_random_angle();
            rand_g = math_random_angle();
            vec_build_spherical_offset(&vec_b, rand_e, rand_f, rand_g);
            rand_h = math_random_int_range(0x1E, 0x39);
            part_spawn_growing_puff(&vec_a, &vec_b, 0x4F20507F, 0x102F, rand_h, 150000.0f);
        } while (i < 0x21 - D_001AFC6C);
    }
    j = 0;
    if (0x32 - D_001AFC6C > 0) {
        camera = (struct Tab *)g_active_camera;
        do {
            j++;
            angle = mat_fast_helper_a(camera->f140 - moby->pos.x, camera->f144 - moby->pos.y);
            FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
            offset_x = math_random_signed_float_range(0.0f, 0.15000000596046448f);
            vec_b.x = moby->pos.x + offset_x;
            offset_y = math_random_signed_float_range(0.0f, 0.15000000596046448f);
            vec_b.y = moby->pos.y + offset_y;
            offset_z = math_random_signed_float_range(0.0f, 0.15000000596046448f);
            vec_b.z = moby->pos.z + offset_z;
            speed = D_001B0A80;
            turn = math_random_signed_float_range(0.0f, -1.5707964897155762f);
            spread_angle = FastAddRotations(angle, turn);
            cos_part = math_fast_sin_or_cos_a(spread_angle);
            vec_a.x = cos_part * 0.01666666753590107f * speed;
            sin_part = math_fast_sin_or_cos_b(spread_angle);
            vec_a.y = sin_part * 0.01666666753590107f * speed;
            speed = D_001B0A84;
            vec_a.z = speed * 0.01666666753590107f;
            part_spawn_spinning_spark(&vec_b, &vec_a, 0x12C);
        } while (j < 0x32 - D_001AFC6C);
    }
    g_001AFC6C = D_001AFC6C - 1;
    moby_release_slot_by_id(moby);
    moby_mark_spawned(moby);
}
