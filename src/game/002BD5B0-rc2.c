
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

extern f32 func_00283198(f32);
extern f32 func_00283180(f32);
extern void func_002830C0(f32 *, f32 *, s8 *);
extern void func_00282CF0(f32 *, f32 *, f32 *);
extern void func_0029FCC0(s8 *, s32, f32 *);
extern void func_00282F20(f32 *, f32 *, f32);
extern void func_00282CC0(f32 *, f32 *, f32 *);
extern f32 func_00283B98(f32, f32);
extern s32 func_00283CF0(f32);
extern f32 func_002AB0E8(f32 *, s8 *, f32 *, s32);
extern s32 func_00282978(s8 *);
extern void func_002B9180(Obj *);

void func_002BD5B0(Obj *o)
{
    Sub *s = &o->sub;
    Fr fr;

    if (s->f10 != 0.0f) {
        s8 *m = s->p00;
        f32 *vec = o->vec;
        fr.m0 = *(TI *)m;
        fr.m1 = *(TI *)(m + 0x10);
        fr.m2 = *(TI *)(m + 0x20);
        fr.a[1] = func_00283198(s->f14) * s->f10;
        fr.a[2] = func_00283180(s->f14) * s->f10;
        fr.a[0] = 0.0f;
        fr.a[3] = 0.0f;
        transform_vector(fr.b, fr.a, (s8 *)&fr.m0);
        FastVecSub(vec, vec, fr.b);
        s->f1C = s->f1C + 0.0600100006f;
        func_0029FCC0(s->p18, 0, fr.c);
        FastVecSub(fr.a, fr.c, vec);
        vec_scale_to_length(fr.a, fr.a, s->f1C);
        FastVecAdd(vec, vec, fr.a);
        s->f14 = FastAddRotations(s->f14, 0.5235988f);
        s->f10 = s->f10 * 0.9f;
        fr.a[1] = func_00283198(s->f14) * s->f10;
        fr.a[2] = func_00283180(s->f14) * s->f10;
        fr.a[0] = 0.0f;
        fr.a[3] = 0.0f;
        transform_vector(fr.b, fr.a, (s8 *)&fr.m0);
        FastVecAdd(vec, vec, fr.b);
        if (func_002AB0E8(fr.c, s->p18 + 0xC0, vec, 1) > 0.0f) {
            func_002B9180(o);
            return;
        }
    }

    s->f04 = s->f04 + s->f0C * 0.011f;
    if (s->f04 <= 0.0f) {
        func_002B9180(o);
        return;
    }
    if (FastDecTimer((s8 *)o + 0xA) != 0) {
        func_002B9180(o);
        return;
    }
    if (1.0f <= s->f04) {
        s->f0C = -s->f0C;
        s->f04 = s->f04 + s->f0C * 0.011f;
    }
    o->f0C = o->f0C + (-2940.0f);
    o->w04 = (o->w04 & 0x00FFFFFF) | (FloatToInt(s->f04 * 255.0f) << 24);
    s->f08 = s->f08 + 0.006f;
    if (1.0f < s->f08) s->f08 = s->f08 - 1.0f;
    o->b08 = (s32)(s->f08 * 255.0f);
}
