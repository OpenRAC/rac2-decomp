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

void func_PAL_002BE258(Obj *o)
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
        func_002830C0(fr.b, fr.a, (s8 *)&fr.m0);
        func_00282CF0(vec, vec, fr.b);
        s->f1C = s->f1C + 0.07201201f;
        func_0029FCC0(s->p18, 0, fr.c);
        func_00282CF0(fr.a, fr.c, vec);
        func_00282F20(fr.a, fr.a, s->f1C);
        func_00282CC0(vec, vec, fr.a);
        s->f14 = func_00283B98(s->f14, 0.62831855f);
        s->f10 = s->f10 * 0.88f;
        fr.a[1] = func_00283198(s->f14) * s->f10;
        fr.a[2] = func_00283180(s->f14) * s->f10;
        fr.a[0] = 0.0f;
        fr.a[3] = 0.0f;
        func_002830C0(fr.b, fr.a, (s8 *)&fr.m0);
        func_00282CC0(vec, vec, fr.b);
        if (func_002AB0E8(fr.c, s->p18 + 0xC0, vec, 1) > 0.0f) {
            func_002B9180(o);
            return;
        }
    }

    s->f04 = s->f04 + s->f0C * 0.013200001f;
    if (s->f04 <= 0.0f) {
        func_002B9180(o);
        return;
    }
    if (func_00282978((s8 *)o + 0xA) != 0) {
        func_002B9180(o);
        return;
    }
    if (1.0f <= s->f04) {
        s->f0C = -s->f0C;
        s->f04 = s->f04 + s->f0C * 0.013200001f;
    }
    o->f0C = o->f0C + (-3528.0002f);
    o->w04 = (o->w04 & 0x00FFFFFF) | (func_00283CF0(s->f04 * 255.0f) << 24);
    s->f08 = s->f08 + 0.0072000003f;
    if (1.0f < s->f08) s->f08 = s->f08 - 1.0f;
    o->b08 = (s32)(s->f08 * 255.0f);
}
