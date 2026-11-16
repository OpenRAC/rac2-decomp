#include "include_asm.h"

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

/* Updates a particle that bounces around a joint and fades in and out, dying when it passes behind the joint's plane (PAL: 50 Hz timings). */
void part_update_bouncing_fade_pal(Obj *o)
{
    Sub *s = &o->sub;
    Fr fr;

    if (s->f10 != 0.0f) {
        s8 *m = s->p00;
        f32 *vec = o->vec;
        fr.m0 = *(TI *)m;
        fr.m1 = *(TI *)(m + 0x10);
        fr.m2 = *(TI *)(m + 0x20);
        fr.a[1] = math_fast_sin_or_cos_b(s->f14) * s->f10;
        fr.a[2] = math_fast_sin_or_cos_a(s->f14) * s->f10;
        fr.a[0] = 0.0f;
        fr.a[3] = 0.0f;
        transform_vector(fr.b, fr.a, (s8 *)&fr.m0);
        FastVecSub(vec, vec, fr.b);
        s->f1C = s->f1C + 0.07201201f;
        moby_transform_joint_to_world(s->p18, 0, fr.c);
        FastVecSub(fr.a, fr.c, vec);
        vec_scale_to_length(fr.a, fr.a, s->f1C);
        FastVecAdd(vec, vec, fr.a);
        s->f14 = FastAddRotations(s->f14, 0.62831855f);
        s->f10 = s->f10 * 0.88f;
        fr.a[1] = math_fast_sin_or_cos_b(s->f14) * s->f10;
        fr.a[2] = math_fast_sin_or_cos_a(s->f14) * s->f10;
        fr.a[0] = 0.0f;
        fr.a[3] = 0.0f;
        transform_vector(fr.b, fr.a, (s8 *)&fr.m0);
        FastVecAdd(vec, vec, fr.b);
        if (mat_get_product_element(fr.c, s->p18 + 0xC0, vec, 1) > 0.0f) {
            part_kill(o);
            return;
        }
    }

    s->f04 = s->f04 + s->f0C * 0.013200001f;
    if (s->f04 <= 0.0f) {
        part_kill(o);
        return;
    }
    if (FastDecTimer((s8 *)o + 0xA) != 0) {
        part_kill(o);
        return;
    }
    if (1.0f <= s->f04) {
        s->f0C = -s->f0C;
        s->f04 = s->f04 + s->f0C * 0.013200001f;
    }
    o->f0C = o->f0C + (-3528.0002f);
    o->w04 = (o->w04 & 0x00FFFFFF) | (FloatToInt(s->f04 * 255.0f) << 24);
    s->f08 = s->f08 + 0.0072000003f;
    if (1.0f < s->f08) s->f08 = s->f08 - 1.0f;
    o->b08 = (s32)(s->f08 * 255.0f);
}
