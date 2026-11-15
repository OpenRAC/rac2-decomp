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
void FloatToInt(f32 a);
f32 FastAddRotations(f32 a, f32 b);
f32 math_fast_sin_or_cos_a(f32 a);
f32 math_fast_sin_or_cos_b(f32 a);
void part_spawn_spinning_spark(struct Vec4 *a, struct Vec4 *b, s32 c);
void moby_release_slot_by_id(struct Obj *a);
void moby_mark_spawned(struct Obj *a);

/* Per-frame update for an explosion effect: throws out a few sparks and pushed particles (fewer as the counter drops), counts the counter down and then runs the shared update. */
void explosion_effect_update(struct Obj *moby)
{
    struct Vec4 vecB;
    struct Vec4 vecA;
    struct Tab *camera;
    s32 i;
    s32 j;
    f32 randA;
    f32 randB;
    f32 randC;
    f32 randD;
    f32 randE;
    f32 randF;
    f32 randG;
    s32 randH;
    f32 angle;
    f32 spreadAngle;
    f32 offsetX;
    f32 offsetY;
    f32 offsetZ;
    f32 turn;
    f32 cosPart;
    f32 sinPart;
    f32 speed;

    i = 0;
    if (0x21 - D_001AFC6C > 0) {
        do {
            i++;
            randA = math_random_float_range(0.0f, 0.3700000047683716f);
            randB = math_random_angle();
            randC = math_random_angle();
            vec_build_spherical_offset(&vecA, randA, randB, randC);
            randD = math_random_float_range(0.3499999940395355f, 0.6000000238418579f);
            vecA.z = vecA.z + randD;
            FastVecAdd(&vecA, &vecA, &moby->pos);
            randE = math_random_float_range(0.0016666668234393f, 0.01666666753590107f);
            randF = math_random_angle();
            randG = math_random_angle();
            vec_build_spherical_offset(&vecB, randE, randF, randG);
            randH = math_random_int_range(0x1E, 0x39);
            part_spawn_growing_puff(&vecA, &vecB, 0x4F20507F, 0x102F, randH, 150000.0f);
        } while (i < 0x21 - D_001AFC6C);
    }
    j = 0;
    if (0x32 - D_001AFC6C > 0) {
        camera = (struct Tab *)g_active_camera;
        do {
            j++;
            angle = mat_fast_helper_a(camera->f140 - moby->pos.x, camera->f144 - moby->pos.y);
            FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
            offsetX = math_random_signed_float_range(0.0f, 0.15000000596046448f);
            vecB.x = moby->pos.x + offsetX;
            offsetY = math_random_signed_float_range(0.0f, 0.15000000596046448f);
            vecB.y = moby->pos.y + offsetY;
            offsetZ = math_random_signed_float_range(0.0f, 0.15000000596046448f);
            vecB.z = moby->pos.z + offsetZ;
            speed = D_001B0A80;
            turn = math_random_signed_float_range(0.0f, -1.5707964897155762f);
            spreadAngle = FastAddRotations(angle, turn);
            cosPart = math_fast_sin_or_cos_a(spreadAngle);
            vecA.x = cosPart * 0.01666666753590107f * speed;
            sinPart = math_fast_sin_or_cos_b(spreadAngle);
            vecA.y = sinPart * 0.01666666753590107f * speed;
            speed = D_001B0A84;
            vecA.z = speed * 0.01666666753590107f;
            part_spawn_spinning_spark(&vecB, &vecA, 0x12C);
        } while (j < 0x32 - D_001AFC6C);
    }
    g_001AFC6C = D_001AFC6C - 1;
    moby_release_slot_by_id(moby);
    moby_mark_spawned(moby);
}
