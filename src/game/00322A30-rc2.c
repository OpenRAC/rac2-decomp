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

extern void *func_00273730(void *, s32, s16, s32, void *, void *, void *, s32, f32, f32);
extern void func_00282CC0(struct Vec3 *, struct Vec3 *, struct Vec4 *);
extern void func_00282F20(struct Vec4 *, void *, f32);
extern void func_00283098(struct Vec3 *, struct Vec3 *, void *);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern f32 func_002A7878(f32, f32);
extern f32 func_002A7940(void);
extern void func_00322C10(void);
extern s32 D_001A8CA0;

/* Throws out eight pieces of debris in random directions when the robot enemy is destroyed. */
void func_00322A30(void *moby) {
    struct Vec4 direction;
    struct Vec3 velocity;
    void *vars;
    void *piece;
    f32 angle;
    f32 speed;
    f32 value;
    f32 spinTime;
    s32 i;

    vars = (*(void **)((s8 *)(moby) + (0x68)));
    vec_scale_to_length(&direction, (s8 *)vars + 0xE0, 0.05000000447034836f);
    for (i = 0; i < 0xF; i++) {
        if (!(((0x7F8 >> i) ^ 1) & 1)) {
            angle = RandomAngle();
            speed = RandomFloatRange(3.0f, 5.0f) * 0.016666668f;
            velocity.x = FastSinOrCosA(angle) * speed;
            value = FastSinOrCosB(angle) * speed;
            velocity.z = 0.0f;
            velocity.y = value;
            velocity.z = RandomFloatRange(3.0f, 5.0f) * 0.016666668f;
            if (D_001A8CA0 != 0) {
                matrix_mul_vec3(&velocity, &velocity, (s8 *)moby + 0xC0);
            }
            FastVecAdd(&velocity, &velocity, &direction);
            spinTime = RandomFloatRange(90.0f, 270.0f);
            value = RandomFloatRange(10.0f, 20.0f);
            piece = CreateCameraMoby(moby, 2, (*(s16 *)((s8 *)(moby) + (0xAA))), i, (s8 *)moby + 0x10, (s8 *)moby + 0xF0, &velocity, 0xFF, spinTime, value);
            if ((*(s32 *)((s8 *)(vars) + (0x2B4))) != 0 && piece != 0) {
                (*(s32 *)((s8 *)(piece) + (0x64))) = (s32)UpdateFadingDebrisPiece;
            }
        }
    }
}
