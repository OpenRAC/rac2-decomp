#include "include_asm.h"
#include "common.h"
extern float func_002A78D8(float, float);
/* Copy the xyz components and clear the fourth word. Adapted from RAC1. */
static __inline__ void particle_copy_xyz(float *dst, float *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    *(int *)&dst[3] = 0;
}
extern void func_002ACB48(void *, float);
extern float func_00282E80(void *, void *);
extern void func_002A8F70(void *, int, int, void *, void *, float);
extern int func_00277F48(float, void *, int, int, int);
extern char *func_002C2A88(void *, int, int, int, int, int, int, float, float);
extern char *func_002C56B0(void *, int, int, int, int, int, int, float, float);
extern unsigned char *D_001F2628;
extern char *D_001B1D90[] __attribute__((sda));
extern char D_00189EA0[];

typedef struct {
    char pad00[0x88];
    float height;
    char pad8C[0x2290 - 0x8C];
    void *owner;
} ParticleHero2C2C80;

typedef struct {
    char pad00[0x2290];
    void *owner;
} ParticleHero2C58A8;

extern char *func_002C3F88(int,void *,float,float,int,int,int,void *);
extern void func_00283410(void *,void *);
extern void func_002830C0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern int D_001B1688[] __attribute__((sda));
extern int func_00283D38(int,int,float);
extern float func_00282E48(void *,void *);
extern void func_002AE730(float *,int *);
extern void func_002AE838(void *,void *);
extern void func_00282D08(void *,void *,void *,float);
extern char D_00189F00[];

extern char *func_002C5B70(void *, void *, int, int);
typedef unsigned int U128 __attribute__((mode(TI)));
typedef union { U128 q; f32 f[4]; } SplitVector;
typedef struct {
    unsigned char b0, b1, b2, b3;
    int x4;
    unsigned char b8, b9;
    short hA;
    int xC;
    SplitVector v10, v20, v30;
} Particle6DD8;

typedef struct SplitMotion {
    f32 x, y, z, w;
    f32 t;
    s16 f14;
    s16 f16;
    u8 f18;
    char pad19[3];
    void *f1C;
} SplitMotion;
typedef struct SplitParticle {
    u8 b00;
    char pad01;
    u8 b02;
    char pad03;
    u32 f04;
    u8 f08;
    char pad09;
    s16 h0A;
    f32 f0C;
    SplitVector posv;
    SplitMotion pv;
} SplitParticle;
typedef struct { SplitVector v; void *f10; s32 f14; s32 f18; f32 f1C; s32 f20; char pad[0xC]; } SplitCollision;
typedef struct { SplitVector v; f32 x10; s16 h14; s16 h16; u8 b18; u8 pad[3]; s32 x1C; } FadeSplitMotion;
typedef struct { u8 pad[2]; u8 b2; u8 pad3; u32 x4; u8 b8; u8 pad9; s16 hA; f32 fC; SplitVector pos; FadeSplitMotion e; } FadeSplitParticle;
typedef struct { SplitVector v; s32 x10; s32 x14; u8 pad[4]; f32 x1C; s32 x20; } FadeSplitCollision;
extern char *func_002C02F0(void *, void *, int, void *, int, int);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00283028(void *, void *, void *);
extern void func_00282C88(void *);
extern float D_001BAFC0[];
extern unsigned char *D_001F25F4, *D_001F26A8;
extern int func_002A9568(int, int, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern float func_002A7940(void);
extern int func_002AAE98(float, float, float, float);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_001163B0(void);
extern unsigned char *D_001F2570;
extern unsigned char *D_001F2688;
extern int func_002A8860(void *, int);
extern void func_0029FCC0(void *, int, void *);

/* Qwen draft (branch qwen/autonomy, c8b09022), checked by tools/check.py */
void func_002B9180(void *);

int func_00282978(short *);

extern int func_00282978_9(char *p);

extern void func_002B9180_13(char *self);

extern float func_00283CE0_2(int v);

extern int func_00283CF0_6(float f);

extern void func_00282CC0_17(char *dst, char *src, char *vec);

extern void func_00300190_4(char *dst, char *src);

extern void func_00282D30_12(char *dst, char *table, float scale);

extern char D_0018A0E0_1[];

extern void Fa2a84657_FUN_00282D48(float *tmp, char *v, float k);

extern void Fa2a84657_FUN_00282CD8(float *tmp, char *a, char *v);

extern int Fa2a84657_FUN_00282978(char *field);

extern void Fa2a84657_FUN_002B9180(unsigned char *p);

typedef struct { unsigned int f0, f4, f8, f12, f16, f20; } T;

extern int func_00282978_12(short *);

extern void func_002B9180_19(char *);

extern float func_00283CE0_5(int);

extern int func_00283D38_6(int, int, float);

struct T {
    float a;
    float b;
    int c;
    int d;
    float e;
};

extern void F15a8b7f0_FUN_00282D30(char *first, char *second, float blend);

extern void F15a8b7f0_FUN_00282CC0(char *first, char *second, char *third);

extern void F15a8b7f0_FUN_002B9180(char *object);


extern void func_00282CC0_19(void *out, void *in, void *src);

extern int func_00282978_11(void *p);

extern void func_002B9180_15(void *self);

extern float func_00283CE0_4(int n);

extern int func_00283D38_3(int handle, int previous, float ratio);

extern char D_00189E20_18[];

extern void Fccb147a4_FUN_002B9180(char *a, char *b);

extern void Fccb147a4_FUN_00300190(char *a, char *b);

extern void Fa03721e9_FUN_00282CC0(char *a, char *b, char *c);

extern void Fa03721e9_FUN_002B9180(char *p);


#ifndef RAC2_T_S16_F570CFB4B
#define RAC2_T_S16_F570CFB4B
typedef short s16_F570cfb4b;
#endif

extern void func_002B9180_7(u8 *);


extern int F7cacd225_FUN_00282978(short *p);

extern void F7cacd225_FUN_002B9180(char *o);

extern float F7cacd225_FUN_00283CE0(int n);

extern int F7cacd225_FUN_00283D38(int a, int b, float q);

#ifndef RAC2_T_OBJ_F7CACD225
#define RAC2_T_OBJ_F7CACD225
typedef struct {
    int pad0;
    int f4;
    short pad8;
    short s10;
    float f12;
    float f16;
    float f20;
    float f24;
    int pad28;
    int f32;
} Obj_F7cacd225;
#endif

extern int func_00282978_6(char *);

extern void func_002B9180_10(char *);

extern void func_00282CC0_21(char *, char *, char *);

extern void func_00300190_2(char *, char *);

#ifndef RAC2_T_VEC16_F9A4B4D8B
#define RAC2_T_VEC16_F9A4B4D8B
typedef struct {
    float f[4];
} Vec16_F9a4b4d8b;
#endif

#ifndef RAC2_T_V4_FC3CB9262
#define RAC2_T_V4_FC3CB9262
typedef int V4_Fc3cb9262 __attribute__((mode(TI)));
#endif

extern void Fc3cb9262_FUN_00282CC0(char *a, char *b, char *c);

extern int Fc3cb9262_FUN_00283CF0(float f);

extern int Fc3cb9262_FUN_00282978(char *a);

extern void Fc3cb9262_FUN_002B9180(char *a);

void func_002BF6F0(void *param_1)
{
  int lVar1;

  lVar1 = func_00282978((short *)((char *)param_1 + 10));
  if (lVar1 != 0) {
    func_002B9180(param_1);
  }
  return;
}

/* func_002BF728 uses the quadword-copy profile in 002BF728-qcopy.c. */

extern int func_002A77E0(int);
extern void func_00282CC0(char *, char *, char *);
extern float func_00282E20(void *);
extern void func_00282F70(char *, char *, float);
extern void func_002AA2E8(float *, float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float D_001B5358;

/* Advances one object: the halfword at offset 10 is capped at 12 and, when the
   sub-object's float at 0x30 is below the object's float at 0x18, the word at
   offset 4 is cleared; the packed byte in that word is then rescaled by the
   halfword, the float at offset 12 grows by 840.0f and is limited by the
   sub-object's float at 0x3C, the object's vector is moved by the sub-object's
   motion triple and the last pair of floats is written back from the angle
   kept in the sub-object. */
void func_002BF8F0(char *self)
{
    char *s1 = self + 0x20;
    float vec[3];
    float f0;
    float f1;
    float f2;
    float f3;
    float g;
    unsigned int a;

    if (func_00282978((short *)(self + 0xA)) != 0) {
        func_002B9180(self);
        return;
    }
    f1 = *(float *)(self + 0x18);
    if (*(float *)(s1 + 0x10) < f1) {
        *(int *)(s1 + 8) = 0;
        if (*(short *)(self + 0xA) >= 13) {
            *(short *)(self + 0xA) = 12;
        }
    }
    if (*(float *)(s1 + 0x10) < *(float *)(self + 0x18) + 8.6666667461395263671875e-01f) {
        if (func_002A77E0(20) == 0) {
            if (*(short *)(self + 0xA) >= 13) {
                *(short *)(self + 0xA) = 12;
            }
        }
    }
    if (*(short *)(self + 0xA) < 14) {
        a = *(unsigned int *)(self + 4);
        *(unsigned int *)(self + 4) = (((int)(a >> 24) * (int)*(short *)(self + 0xA) / 14) << 24) | (a & 0xFFFFFF);
    }
    f0 = *(float *)(self + 0xC);
    f0 = f0 + 8.4000006103515625000000e+02f;
    *(float *)(self + 0xC) = f0;
    f1 = *(float *)(s1 + 0xC);
    if (f1 < f0) {
        *(float *)(self + 0xC) = f1;
    }
    vec[0] = *(float *)(s1 + 0);
    vec[1] = *(float *)(s1 + 4);
    vec[2] = *(float *)(s1 + 8);
    f0 = func_00282E20((void *)vec);
    func_00282F70((char *)vec, (char *)vec, f0 * 9.7000002861022949218750e-01f);
    func_00282CC0(self + 0x10, self + 0x10, (char *)vec);
    func_002AA2E8(&vec[2], 2.1666666492819786071777e-02f, 1.3888889225199818611145e-03f);
    *(float *)(s1 + 4) = vec[1];
    *(float *)(s1 + 0) = vec[0];
    *(float *)(s1 + 8) = vec[2];
    f0 = func_00283B98(*(float *)(s1 + 0x14), *(float *)(s1 + 0x18));
    *(float *)(s1 + 0x14) = f0;
    g = func_00283B98(D_001B5358, 1.5707964897155761718750e+00f);
    f3 = func_00283198(*(float *)(s1 + 0x14));
    f2 = f3 * *(float *)(s1 + 0x1C);
    f0 = func_00283180(g);
    vec[0] = f0 * f2;
    vec[1] = func_00283198(g) * f2;
    vec[2] = 0.0f;
    func_00282CC0(self + 0x10, self + 0x10, (char *)vec);
}


extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern void *func_002C19D8(void *, float, void *, float, int);
extern void func_002C3D80(void *, int, float, float);
typedef union { unsigned char b[0x2600]; int i[0x980]; float f[0x980]; } L_BFC50Hero;
extern char D_00189E20[];
extern void *D_001A9E74 __attribute__((section(".sdata")));
extern float D_001BAF80[];
extern char D_001BAFA0[];

void func_002BFC50(char *self)
{
    char *s1 = self + 0x20;
    float vec[4] __attribute__((aligned(16)));
    int state = *(int *)(s1 + 0x10);

    if (state == 0) {
        func_00282CC0(self + 0x10, self + 0x10, s1);
    } else if (state == 1) {
        func_00282CC0((char *)vec, self + 0x10, s1);
        if (func_002761F8(self + 0x10, vec, 2, 0, 0) == 0) {
            goto copy;
        }
        if (func_00278E78() == 0) {
            func_002C19D8(D_001BAFA0, 0.2f, D_001A9E74, 5250.0f, -1);
        }
        func_002B9180(self);
        return;
    } else if (state == 3) {
        func_00282CC0(self + 0x10, self + 0x10, s1);
        if (*(float *)(self + 0x18) < ((L_BFC50Hero *)D_00189E20)->f[0x330 / 4]) {
            void *t = D_001A9E74;

            *(float *)(self + 0x18) = ((L_BFC50Hero *)D_00189E20)->f[0x330 / 4];
            func_002C19D8(self + 0x10, 0.2f, t, 5250.0f, -1);
            func_002B9180(self);
            return;
        }
    } else {
        func_00282CC0((char *)vec, self + 0x10, s1);
        if (func_002761F8(self + 0x10, vec, 2, 0, 0) == 0) {
            goto copy;
        }
        if (func_00278E78() != 0) {
            D_001BAF80[10] = D_001BAF80[10] + 0.05f;
            func_002C3D80(&D_001BAF80[8], -1, 0.25f, 3150.0f);
        }
        func_002B9180(self);
        return;
copy:
        qcopy(self + 0x10, vec);
    }
    *(float *)(s1 + 8) = *(float *)(s1 + 8) - *(float *)(s1 + 0x1C);
    self[8] = self[8] + 2;
    if (--*(int *)(s1 + 0x14) <= 0 || *(float *)(self + 0x18) < *(float *)(s1 + 0x18)) {
        *(int *)(self + 4) = *(int *)(self + 4) - 0x10000000;
        if (*(int *)(self + 4) < 0) {
            func_002B9180(self);
        }
    }
}

/* func_002BFE80 is defined in 002BFE80-dbg.c. */

extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern int func_L00_0031C998(int, int, float);
extern float D_001B5340[];
extern int abs(int);

void func_002BFFE8(char *self)
{
    char *s1 = self + 0x20;
    float vec[4];
    int d;
    float f;

    if (func_00282978((short *)(self + 0xA)) != 0) {
        func_002B9180(self);
        return;
    }
    func_00282CF0(vec, D_001B5340, s1);
    if (func_00282DF0(vec) > 5.0f) {
        func_00282F20(vec, vec, 1.25f);
    } else {
        func_00282D30((char *)vec, (char *)vec, 0.25f);
    }
    func_00282CC0((char *)(self + 0x10), s1, (char *)vec);
    d = abs(*(short *)(self + 0xA) - *(int *)(s1 + 0x14));
    f = (float)(*(int *)(s1 + 0x14) - d) / (float)*(int *)(s1 + 0x14);
    *(int *)(self + 4) = func_L00_0031C998(0, *(int *)(s1 + 0x10), f);
}


/* func_002C01F8 is in 002BF6F0-c01f8-g8.c. */

/* func_002C02F0 uses the quadword-copy profile in 002C02F0-qcopy.c. */

/* Adapted from RAC1 effect_particle_updates.c; measured against RAC2 retail. */
void func_002C04C0(SplitParticle *p) {
    SplitVector v0u;
    SplitVector v1u;
    SplitCollision c;
    f32 v2[4];
    SplitMotion *pv;
    SplitParticle *r;
    u8 *tab;
    u8 fl;
    s32 fm;
    s64 hit;
    s32 k, t;
    f32 f, g, s;

    pv = &p->pv;
    if (p->h0A != 0 && func_00282978(&p->h0A) != 0) {
        f32 sp, lo, hi, sc, zero, nsp;
        pv->f18 |= 0x88;
        lo = 0.5f;
        sp = p->f0C / (func_00283CE0_2((u8)pv->pad19[0]) * 28125.0f);
        hi = 0.7f;
        sc = 0.2f;
        p->f0C = p->f0C * 0.8f;
        zero = 0.0f;
        f = func_002A7878(lo, hi);
        nsp = -sp;
        func_00282D30_12((char *)v0u.f, (char *)pv, f);
        v1u.f[0] = p->posv.f[0] + func_002A7878(nsp, sp);
        v1u.f[1] = p->posv.f[1] + func_002A7878(nsp, sp);
        v1u.f[2] = p->posv.f[2] + func_002A7878(nsp, sp);
        v0u.f[0] = v0u.f[0] + func_002A7878(-p->pv.x * sc, p->pv.x * sc);
        v0u.f[1] = v0u.f[1] + func_002A7878(-pv->y * sc, pv->y * sc);
        v0u.f[2] = v0u.f[2] + func_002A7878(-pv->z * sc, zero);
        r = (SplitParticle *)func_002C02F0(v1u.f, v0u.f, (pv->f18 & 0x10) | 0x88, pv->f1C, (u8)pv->pad19[0], 128);
        if (r != 0) {
            r->h0A = 2;
            r->f0C = p->f0C;
        }
        func_00282D30_12((char *)pv, (char *)pv, func_002A7878(lo, hi));
        p->pv.x = p->pv.x + func_002A7878(-p->pv.x * sc, p->pv.x * sc);
        pv->y = pv->y + func_002A7878(-pv->y * sc, pv->y * sc);
        pv->z = pv->z + func_002A7878(-pv->z * sc, zero);
        p->posv.f[0] = p->posv.f[0] + func_002A7878(nsp, sp);
        p->posv.f[1] = p->posv.f[1] + func_002A7878(nsp, sp);
        p->posv.f[2] = p->posv.f[2] + func_002A7878(nsp, sp);
    }
    tab = D_001F2570;
    { int index = p->b02 - tab[0];
    p->b02 = tab[(p->h0A + pv->f16 + index) & 7]; }
    func_00282CC0((char *)v0u.f, (char *)p->posv.f, (char *)pv);
    hit = 0;
    k = pv->f14;
    if (3 < k) {
        func_00282CF0(v1u.f, p->posv.f, pv);
    } else {
        v1u.q = p->posv.q;
    }
    func_00282D30_12((char *)&c, (char *)&c, 0.01f);
    fl = pv->f18;
    if (fl & 8) {
        if ((p->f04 & 0xFF000000) == 0) goto kill;
        pv->f18 = fl | 8;
        if (!(pv->f18 & 0x10)) hit = func_002761F8(v1u.f, v0u.f, 4, pv->f1C, 0) != 0;
    } else {
        c.f10 = pv->f1C;
        c.f14 = 0x10001;
        c.f1C = 1.0f;
        c.v.q = *(U128 *)pv;
        if (fl & 0x40) func_00282C88(&c);
        c.f20 = 1;
        if (!(pv->f18 & 0x10)) hit = func_002761F8(v1u.f, v0u.f, 0, pv->f1C, &c) != 0;
    }
    if (hit) {
        func_00282F20(v2, D_001BAFC0, 1.0f);
        func_00283028(pv, pv, D_001BAFC0);
        func_00282D30_12((char *)pv, (char *)pv, 0.02f);
        func_00282F20(v2, D_001BAFC0, 0.055f);
        func_00282CC0((char *)p->posv.f, (char *)(D_001BAFC0 - 8), (char *)v2);
        if (p->f0C < 200000.0f && (pv->f18 & 8) == 0) {
            p->f0C = p->f0C + p->f0C;
        }
        pv->f18 |= 8;
    } else {
        qcopy(p->posv.f, v0u.f);
    }
    if (pv->f18 & 8) {
        f32 n;
        pv->f16++;
        n = p->f0C - (func_00283CE0_2((u8)pv->pad19[0]) * 8437.5f - func_00283CE0_2((u8)pv->pad19[0]) * 937.5f) * 0.0694444477558136f;
        p->f0C = n;
        if (n <= 0.0f) {
        kill:
            func_002B9180(p);
            return;
        }
    } else {
        p->f0C = p->f0C + (func_00283CE0_2((u8)pv->pad19[0]) * 8437.5f - func_00283CE0_2((u8)pv->pad19[0]) * 937.5f) * 0.0555555559694767f;
    }
    f = func_00283CE0_2(pv->f14);
    s = f * 0.000246913579758257f + 0.08f;
    if (s < 0.0f) s = 0.0f;
    if (0.08f < s) s = 0.08f;
    if (pv->f18 & 8) {
        s = s / ((f32)pv->f16 * 0.142857149243355f + 1.0f);
    }
    p->f04 = (p->f04 & 0xFFFFFF) | (func_00283CF0(s * 256.0f) << 24);
    pv->z = pv->z + 0.008f;
    t = pv->f14;
    if (25 < t || (pv->f18 & 8)) {
        pv->x = pv->x * 0.95f;
        pv->y = pv->y * 0.95f;
    }
    fm = pv->f18;
    g = -1.0f;
    if (fm & 1) g = 1.0f;
    if (fm & 8) {
        pv->z = pv->z + 0.008f;
        f = func_00283CE0_2(pv->f16);
        pv->t = pv->t + g * (-0.01f) / f;
    } else {
        pv->t = pv->t + g * (-0.01f);
    }
    if (1.0f < pv->t) pv->t = pv->t - 1.0f;
    if (pv->t < 0.0f) pv->t = pv->t + 1.0f;
    p->f08 = (s32)(pv->t * 256.0f);
}



/* func_002C0CC0 uses the quadword-copy profile in 002C0CC0-qcopy.c. */

/* Adapted from RAC1 effect_particle_updates.c; measured against RAC2 retail. */
void func_002C0E50(FadeSplitParticle *m) {
    SplitVector v, p;
    FadeSplitCollision c;
    FadeSplitMotion *e = &m->e;
    FadeSplitParticle *n;
    f32 r, nr, a, s;
    s32 hit;
    u8 fl;
    u8 *tab;

    if (m->hA != 0 && func_00282978(&m->hA)) {
        e->b18 |= 0x88;
        r = m->fC * 0.0000011111111462014378f;
        m->fC *= 0.8f;
        nr = -r;
        func_00282D30_12((char *)&v, (char *)e, func_002A7878(0.5f, 0.7f));
        p.f[0] = m->pos.f[0] + func_002A7878(nr, r);
        p.f[1] = m->pos.f[1] + func_002A7878(nr, r);
        p.f[2] = m->pos.f[2] + func_002A7878(nr, r);
        v.f[0] += func_002A7878(-e->v.f[0] * 0.2f, e->v.f[0] * 0.2f);
        v.f[1] += func_002A7878(-e->v.f[1] * 0.2f, e->v.f[1] * 0.2f);
        v.f[2] += func_002A7878(-e->v.f[2] * 0.2f, 0.0f);
        n = (FadeSplitParticle *)func_002C0CC0((char *)&p, (char *)&v, (e->b18 & 0x10) | 0x88, e->x1C);
        if (n) {
            n->hA = 2;
            n->fC = m->fC;
        }
        func_00282D30_12((char *)e, (char *)e, func_002A7878(0.5f, 0.7f));
        e->v.f[0] += func_002A7878(-e->v.f[0] * 0.2f, e->v.f[0] * 0.2f);
        e->v.f[1] += func_002A7878(-e->v.f[1] * 0.2f, e->v.f[1] * 0.2f);
        e->v.f[2] += func_002A7878(-e->v.f[2] * 0.2f, 0.0f);
        m->pos.f[0] += func_002A7878(nr, r);
        m->pos.f[1] += func_002A7878(nr, r);
        m->pos.f[2] += func_002A7878(nr, r);
    }
    tab = D_001F2570;
    { int index = m->b2 - tab[0];
    m->b2 = tab[(m->hA + e->h16 + index) & 7]; }
    func_00282CC0((char *)&v, (char *)&m->pos, (char *)e);
    hit = 0;
    if (e->h14 > 3) {
        func_00282CF0(&p, &m->pos, e);
    } else {
        p.q = m->pos.q;
    }
    func_00282D30_12((char *)&c, (char *)&c, 0.01f);
    fl = e->b18;
    if (fl & 8) {
        if (!(m->x4 & 0xFF000000)) goto kill;
        e->b18 = fl | 8;
        if (!func_002A77E0(3) && !(e->b18 & 0x10)) hit = func_002761F8(&p, &v, 0, (void *)e->x1C, 0) != 0;
    } else {
        c.x10 = e->x1C;
        c.x1C = 1.0f;
        c.v.q = e->v.q;
        c.x14 = 1;
        c.x20 = 1;
        if (!func_002A77E0(3) && !(e->b18 & 0x10)) hit = func_002761F8(&p, &v, 0, (void *)e->x1C, &c) != 0;
    }
    if (hit) e->b18 |= 8;
    else qcopy(&m->pos, &v);
    if (e->b18 & 8) {
        e->h16++;
        m->fC -= 18055.5546875f;
        if (m->fC <= 0.0f) {
        kill:
            func_002B9180(m);
            return;
        }
    } else {
        m->fC += 14444.4443359375f;
    }
    s = func_00283CE0_2(e->h14);
    a = s * 0.000246913579758257f + 0.08f;
    if (a < 0.0f) a = 0.0f;
    if (0.08f < a) a = 0.08f;
    if (e->b18 & 8) a /= (f32)e->h16 * 0.142857149243355f + 1.0f;
    m->x4 = (m->x4 & 0xFFFFFF) | (func_00283CF0(a * 256.0f) << 24);
    e->v.f[2] += 0.008f;
    if (e->h14 > 25 || (e->b18 & 8)) {
        e->v.f[0] *= 0.95f;
        e->v.f[1] *= 0.95f;
    }
    { u8 f2 = e->b18;
    s = -1.0f;
    if (f2 & 1) s = 1.0f;
    if (f2 & 8) {
        e->v.f[2] += 0.008f;
        e->x10 += s * (-0.01f) / func_00283CE0_2(e->h16);
    } else {
        e->x10 += s * (-0.01f);
    } }
    if (1.0f < e->x10) e->x10 -= 1.0f;
    if (e->x10 < 0.0f) e->x10 += 1.0f;
    m->b8 = (s32)(e->x10 * 256.0f);
}

/* Updates one byte-addressed object by packing a converted short-ratio value with three bytes, applying the bound helper sequence to three stored floats, and accumulating one byte and one float. */
void func_002C1840(char *self)
{
    float vec[4];
    float tmp[4];
    char *s1;
    char *p;
    float f20;
    float t;
    unsigned int v;

    if (func_00282978_9(self + 10)) {
        func_002B9180_13(self);
        return;
    }
    s1 = self + 32;
    f20 = func_00283CE0_2(*(short *)(s1 + 30));
    t = func_00283CE0_2(*(short *)(s1 + 28));
    v = func_00283CF0_6(f20 * ((float)*(short *)(self + 10) / t));
    v = v << 24;
    v = v | (*(unsigned char *)(s1 + 19) << 16);
    v = v | (*(unsigned char *)(s1 + 18) << 8);
    v = v | *(unsigned char *)(s1 + 17);
    *(unsigned int *)(self + 4) = v;
    vec[3] = 0.0f;
    vec[0] = *(float *)(self + 32);
    vec[1] = *(float *)(s1 + 4);
    vec[2] = *(float *)(s1 + 8);
    func_00282CC0_17((char *)self + 16, (char *)self + 16, (char *)vec);
    if (*(float *)(self + 28) != 0.0f) {
        if (*(float *)(self + 28) == 2.0f)
            func_00300190_4((char *)self + 16, (char *)self + 16);
        *(float *)(self + 28) = 2.0f;
    }
    p = (char *)tmp;
    func_00282D30_12(p, D_0018A0E0_1, *(float *)(s1 + 12));
    func_00282CC0_17((char *)vec, (char *)vec, p);
    func_00282D30_12((char *)vec, (char *)vec, *(float *)(s1 + 24));
    *(float *)s1 = vec[0];
    *(float *)(s1 + 4) = vec[1];
    *(float *)(s1 + 8) = vec[2];
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(s1 + 16);
    *(float *)(self + 12) = *(float *)(self + 12) + *(float *)(s1 + 20);
}

typedef struct {
    float vx;
    float vy;
    int f8;
    int fC;
    float spin;
    void *owner;
} L_C19D8Payload;
typedef struct {
    unsigned char b0, b1, b2, b3;
    int color;
    unsigned char seed, alpha;
    unsigned short size;
    float life;
    float position[4];
    L_C19D8Payload payload;
} L_C19D8Particle;
extern void *func_002B9030(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern int func_001163B0(void);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern unsigned char *D_001F25F4;

void *func_002C19D8(void *position, float size, void *owner, float spin, int color)
{
    L_C19D8Particle *p = (L_C19D8Particle *)func_002B9030(0x2D);
    L_C19D8Payload *out;
    float angle;
    float speed;
    int c;

    if (p) {
        qcopy(p->position, position);
        if (color == -1) {
            c = ((func_002A77E0(6) + 0x14) << 24) | 0x808080;
        } else {
            c = color;
        }
        out = &p->payload;
        p->color = c;
        p->alpha = func_00283CF0(1.0f) + 32;
        p->b3 = 0x48;
        p->b1 = 1;
        p->b2 = *D_001F25F4;
        p->seed = func_001163B0();
        p->size = 4;
        p->life = size * 210000.0f;
        angle = func_002A7940();
        speed = func_002A7878(0.0015f, 0.0025f);
        p->payload.vx = func_00283180(angle) * speed;
        out->vy = func_00283198(angle) * speed;
        out->owner = owner;
        out->spin = spin;
        out->f8 = 0;
    }
    return p;
}

/* func_002C1B38 is in the -G8 sibling. */

extern float func_00282C48(float);

void func_002C1C88(char *self)
{
    char *motion = self + 0x20;
    func_00282CC0_17(self + 0x10, self + 0x10, motion);
    *(float *)(self + 0x0C) += 5880.0f;
    *(float *)(motion + 0x14) *= 0.98f;
    *(float *)(motion + 0x10) += *(float *)(motion + 0x14);
    *(unsigned char *)(self + 8) = func_00283CF0_6(*(float *)(motion + 0x10));
    if (*(float **)(motion + 0x18)) {
        if (func_00282C48(*(float *)(self + 0x18) - **(float **)(motion + 0x18)) < 0.2f)
            *(float *)(self + 0x18) = **(float **)(motion + 0x18) + 0.02f;
    }
    if (--*(short *)(self + 0xA) == 0) {
        *(int *)(self + 4) -= 0x01000000;
        *(short *)(self + 0xA) = 1;
    }
    if ((*(unsigned int *)(self + 4) & 0xFF000000) == 0)
        func_002B9180(self);
}

extern void func_00282D30_fa(void *, void *, float);

void func_002C1DB0(char *a0)
{
    char *p = a0;
    char *q = p + 32;
    int v;

    func_00282D30_fa(q, q, 0.975f);
    func_00282CC0(p + 16, p + 16, q);
    *(float *)(p + 12) = *(float *)(p + 12) + 14700.0f;
    *(u8 *)(p + 8) = *(u8 *)(p + 8) + *(u8 *)(q + 16);
    v = *(int *)(p + 4) + 0xFE000000;
    *(int *)(p + 4) = v;
    if (v < 0) {
        func_002B9180(p);
    }
}

extern void func_00282CC0(char *, char *, char *);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern int func_00283D38(int, int, float);

void func_002C1E50(char *obj) {
    char *tail = obj + 0x20;
    obj[8] += tail[0x1C];
    func_00282CC0(obj + 0x10, obj + 0x10, tail);
    *(int *)(obj + 4) = func_00283D38(*(int *)(tail + 0x18), *(int *)(tail + 0x14),
        func_00282C48(func_00283CE0(*(short *)(obj + 0x0A)) * *(float *)(tail + 0x10) - 1.0f));
    if (func_00282978((short *)(obj + 0x0A)) != 0) {
        func_002B9180(obj);
    }
}


/* func_002C1FC0 is defined in 002BF6F0-g8.c. */

void func_002C2080(unsigned char *p)
{
    float tmp[4];
    char *v;
    int n;

    v = (char *)p + 32;
    Fa2a84657_FUN_00282D48(tmp, v, 9.4999998807907104492188e-01f);
    *(float *)(v + 8) = *(float *)(v + 8) + 1.3888889225199818611145e-03f;
    Fa2a84657_FUN_00282CD8(tmp, (char *)p + 16, v);

    n = *(int *)(p + 4) + (int)0xFE000000;
    *(int *)(p + 4) = n;
    if (((unsigned)(n & 0xFF000000) - 1) > 0x5EFFFFFFu || Fa2a84657_FUN_00282978((char *)p + 10) != 0) {
        Fa2a84657_FUN_002B9180(p);
    } else {
        float f0;
        float f1;

        f1 = *(float *)(p + 12);
        f0 = 2.1000000000000000000000e+05f - f1;
        f0 = f0 * 7.0000000298023223876953e-02f;
        f1 = f1 + f0;
        *(float *)(p + 12) = f1;
        p[8] = p[8] + 1;
    }
}

/* Tests the halfword at offset 10 through a helper; on zero it stores a scaled int at offset 4 and a 210000.0f-scaled interpolation of two floats at offset 12, otherwise calls a second helper. */
void func_002C2170(char *p)
{
    if (func_00282978_12((short *)(p + 10)) != 0) {
        func_002B9180_19(p);
    } else {
        struct T *t = (struct T *)(p + 32);
        float k = func_00283CE0_5(*(short *)(p + 10)) * t->e;

        *(int *)(p + 4) = func_00283D38_6(t->d, t->c, k);
        *(float *)(p + 12) = ((t->a - t->b) * k + t->b) * 210000.0f;
    }
}

/* Move a particle while tweening its size and alpha, then apply gravity. */
void func_002C23B8(char *p)
{
    char *q = p + 32;
    Vec16_F9a4b4d8b v;
    float t;
    int alpha;

    p[8] += (unsigned char)q[10];
    if (*(short *)(q + 8) - *(short *)(p + 10) < 6) {
        t = (float)(*(short *)(q + 8) - *(short *)(p + 10)) * 0.2f;
        *(float *)(p + 12) = *(float *)(q + 4) +
            ((*(float *)q + *(float *)(q + 4)) * 0.5f - *(float *)(q + 4)) * t;
        {
            int c2 = (unsigned char)q[11] >> 1;
            int c = (unsigned char)q[11];
            alpha = func_00283CF0((float)c + (float)(c2 - c) * t);
        }
    } else {
        t = func_00283CE0_2(*(short *)(q + 8) - 6);
        t = (float)*(short *)(p + 10) / t;
        *(float *)(p + 12) = *(float *)q +
            ((*(float *)q + *(float *)(q + 4)) * 0.5f - *(float *)q) * t;
        alpha = func_00283CF0((float)((unsigned char)q[11] >> 1) * t);
    }
    *(int *)(p + 4) = (alpha << 24) | (*(int *)(p + 4) & 0xffffff);
    particle_copy_xyz(v.f, (float *)(q + 12));
    func_00282CC0(p + 16, p + 16, (char *)&v);
    *(float *)(q + 20) -= *(float *)(q + 24);
    if (*(float *)(p + 28) != 0) {
        if (*(float *)(p + 28) == 2.0f)
            func_00300190_2(p + 16, p + 16);
        *(float *)(p + 28) = 2.0f;
    }
    if (*(float *)(p + 16) < 2 || *(float *)(p + 16) > 1021 ||
        *(float *)(p + 20) < 2 || *(float *)(p + 20) > 1021 ||
        *(float *)(p + 24) < 2 || *(float *)(p + 24) > 1021) {
        func_002B9180(p);
        return;
    }
    if (func_00282978((short *)(p + 10)))
        func_002B9180(p);
}

extern void func_002C96F8(float, float, void *, int *, float *, void *);

extern int func_00277F48(float, void *, int, int, int);

extern float func_00283CE0(int);

extern int func_002AAE98(float, float, float, float);

#ifndef RAC2_T_VEC16_F5621621C
#define RAC2_T_VEC16_F5621621C
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_F5621621c;
#endif

extern void func_002A9850(void *a0, Vec16_F5621621c *src, int *p, int n, int t0, int t1, int t2, int t3, float f1, float f2, float f3);

extern int D_001BF000[];

/* Updates one object: it copies its vector into a local, adds the two motion
   floats and hands the result with the motion's third float to a helper, then
   bails out through the second helper when the halfword at offset 10 is
   taken. Otherwise it packs a colour from the halfword and pushes the object
   through a vector helper with the table at D_001BF000. The two words the
   first helper writes (n and f) are the retail's scratch out-parameters: it
   never reads them back. The words at offsets 0x20 and 0x34 are 32-bit in the
   object and the helpers take them as pointers, so they are cast on the way
   out. */
void func_002C2658(char *obj)
{
    char *motion = obj + 0x20;
    char *vec = obj + 0x10;
    V4_Fc3cb9262 local[2];
    int n;
    float f;
    int count;

    local[0] = *(V4_Fc3cb9262 *)(obj + 0x10);
    *(float *)(motion + 4) = *(float *)(motion + 4) + *(float *)(motion + 8);
    func_002C96F8(*(float *)(motion + 4), *(float *)(motion + 0xC),
                  (void *)*(int *)(obj + 0x20), &n, &f, vec);

    if (func_00282978((short *)(obj + 0xA)) != 0) {
        func_002B9180(obj);
        return;
    }

    {
        int index = *(short *)(obj + 0xA);

        if ((float)index < 7.5f)
            *(int *)(obj + 4) = func_002AAE98(0.7f, 0.7f, 0.7f,
                                             func_00283CE0(index) * 0.0106666666f);
    }

    count = func_00277F48(0.15f, vec, 16, *(int *)(motion + 0x14), 0);
    local[1] = *(V4_Fc3cb9262 *)(obj + 0x10);
    func_002A9850((void *)*(int *)(motion + 0x14), (Vec16_F5621621c *)&local[1],
                   D_001BF000, count, 0, 0x810001, 2, 1, 2.0f, 1.0f, 1.0f);
}


void func_002C28F8(char *object)
{
    int count;
    int low;
    int high;

    F15a8b7f0_FUN_00282D30(object + 32, object + 32, 0.975f);
    F15a8b7f0_FUN_00282CC0(object + 16, object + 16, object + 32);
    *(float *)(object + 12) += 6300.0f;
    count = *(unsigned char *)(object + 4) - 4;
    if (count <= 0)
        F15a8b7f0_FUN_002B9180(object);
    else {
        low = (count << 8) | 0x60000000;
        high = (count << 16) | low;
        *(int *)(object + 4) = high | count;
    }
}

extern int func_00283CF0(float);

/* A drifting spark: moves by its velocity, spins, slows its fall and fades over its last
   64 frames; it frees itself when the count runs out. */
void func_002C29A0(char *p)
{
    char *vel = p + 0x20;

    func_00282CC0(p + 0x10, p + 0x10, vel);
    *(float *)(p + 0xC) += 5880.0f;
    *(float *)(vel + 0x14) *= 0.98f;
    *(float *)(vel + 0x10) += *(float *)(vel + 0x14);
    p[8] = func_00283CF0(*(float *)(vel + 0x10));
    if (--*(short *)(p + 0xA) <= 0)
        func_002B9180(p);
    if (*(short *)(p + 0xA) > 0x40)
        *(int *)(p + 4) = ((0x80 - *(short *)(p + 0xA)) << 24) | 0x808080;
    else
        *(int *)(p + 4) = (*(short *)(p + 0xA) << 24) | 0x808080;
}

/* func_002C2A88 uses the quadword-copy profile in 002C2A88-qcopy.c. */

void func_002C2C80(char *p) {
 char *q=p+32; SplitVector v; int i; float f, a, speed;
 switch(*(unsigned char *)(q+20)) {
 case 0: {
  float duration=func_00283CE0_2(*(unsigned char *)(q+17));
  *(int *)(p+4)=func_00283D38(0xff4080ff,0,(duration-func_00283CE0_2(*(short *)(p+10)))/duration);
  if(func_00282978((short *)(p+10))) {
   if(*(unsigned char *)(q+16)==1)func_002B9180(p);
   else {*(unsigned char *)(q+20)=1;*(short *)(p+10)=*(unsigned char *)(q+18);}
  }
  break; }
 case 1:
  for(i=0;i<*(unsigned char *)(q+19);i++) {
   qcopy(&v,p+16);
   func_002ACB48(&v,0.05f);
   speed=1.0f;
   if(*(short *)(p+10)<10)speed=func_00283CE0_2(*(short *)(p+10))*0.1f;
   func_002C2A88(&v,2,*(unsigned char *)(q+17),*(unsigned char *)(q+18),*(unsigned char *)(q+19),*(unsigned char *)(q+21),*(int *)(q+24),*(float *)(q+28),speed);
  }
  if(func_00282978((short *)(p+10)))func_002B9180(p);
  { char *pos=D_00189EA0; ParticleHero2C2C80 *hero;
  if(func_00282E80(p+16,pos)<0.3f) {
   hero=(ParticleHero2C2C80 *)(pos-128);
   if(hero->height<*(float *)(p+24)+1.2f) {
   func_00282CF0(&v,pos,p+16);
   func_00282F20(&v,&v,1.0f);v.f[2]=1.0f;
   func_002A8F70(hero->owner,*(int *)(q+24),1,p+16,&v,*(float *)(q+28));
  }}
  }
  break;
 case 2:
  func_00282CC0(p+16,p+16,q);
  a=func_00283CE0_2(*(unsigned char *)(q+21));
  f=(a-func_00283CE0_2(*(short *)(p+10)))/a;
  *(int *)(p+4)=func_00283D38((*(unsigned char *)(q+22)<<24)|0x4060,0x8fafff,f);
  if(f<0.6f)*(float *)(p+12)+=9030.0f;else *(float *)(p+12)-=16800.0f;
  p[2]=D_001F2628[func_001163B0()&7];
  if((((p-D_001B1D90[0])>>6)&1))p[8]++;else p[8]--;
  if(func_00282978((short *)(p+10)))func_002B9180(p);
  break;
 }
}




extern unsigned char *r1_func_00218928(int);
extern int r1_func_001FA898(float);
extern void r1_func_001F9BF0(void *, void *, void *);
extern char D_00189EA0[];
extern unsigned char *r1_D_L00_001B2400[];


/* rac1-decomp src/overlays/shared/alpha_fade_particle_updates.c: func_002C2FD8 */
/* spawns particle type 0x3B from a position, colour index and flags */
unsigned char *func_002C2FD8(float f, void *pos, int a1, unsigned char a2, int idx, int flag, int s, int mode) {
    unsigned char *r = r1_func_00218928(0x3B);
    if (r != 0) {
        char *v = (char *)r + 0x20;
        *(int *)(v + 0x10) = mode;
        if (mode == 1) {
            r1_func_001F9BF0(v, pos, D_00189EA0);
        }
        qcopy(r + 0x10, pos);
        *(int *)(r + 4) = a1;
        r[9] = r1_func_001FA898(1.0f) + 0x20;
        if (flag != 0) {
            r[3] = 0x44;
        } else {
            r[3] = 0x48;
        }
        r[8] = a2;
        r[1] = 0;
        *(float *)(r + 0xC) = f * 210000.0f;
        r[2] = *r1_D_L00_001B2400[idx];
        *(short *)(r + 0xA) = s;
    }
    return r;
}

extern void func_00282CC0(char *, char *, char *);

void func_002C30F8(char *self)
{
    char *part = self + 0x20;
    if (*(int *)(part + 0x10) == 1)
        func_00282CC0(self + 0x10, D_00189EA0, part);
    if (func_00282978((short *)(self + 0xA)) != 0)
        func_002B9180(self);
}

/* Creates a particle at POS moving by VEL; in mode 1 it also keeps its offset from the
   resident view origin. */
/* func_002C3150 uses the quadword-copy profile in 002C3150-qcopy.c. */

/* advances three floats of a sub-object by a resident offset triple, calls a three-pointer update, subtracts the offsets back out, rejects the result when any coordinate leaves the 2.0..1021.0 band, and otherwise rescales a 24-bit handle by the ratio of two helper lookups over a signed halfword index */
void func_002C3280(u8 *self)
{
    char *s2 = (char *)self + 32;
    int n;
    float a;

    if (*(int *)(s2 + 28) == 1) {
        char *base = D_00189E20_18;
        *(float *)(self + 16) = *(float *)(base + 128) + *(float *)(s2 + 16);
        *(float *)(self + 20) = *(float *)(base + 132) + *(float *)(s2 + 20);
        *(float *)(self + 24) = *(float *)(base + 136) + *(float *)(s2 + 24);
        func_00282CC0_19(self + 16, self + 16, s2);
        *(float *)(s2 + 16) = *(float *)(self + 16) - *(float *)(base + 128);
        *(float *)(s2 + 20) = *(float *)(self + 20) - *(float *)(base + 132);
        *(float *)(s2 + 24) = *(float *)(self + 24) - *(float *)(base + 136);
    } else {
        func_00282CC0_19(self + 16, self + 16, s2);
    }

    if (*(float *)(self + 16) < 2.0f || *(float *)(self + 16) > 1021.0f
        || *(float *)(self + 20) < 2.0f || *(float *)(self + 20) > 1021.0f
        || *(float *)(self + 24) < 2.0f || *(float *)(self + 24) > 1021.0f) {
        func_002B9180_15(self);
        return;
    }

    if (func_00282978_11((char *)self + 10) != 0) {
        func_002B9180_15(self);
        return;
    }

    n = *(int *)(self + 4) & 0xFFFFFF;
    a = func_00283CE0_4(*(short *)(self + 10) - 1);
    /* One statement: retail has no line label between the second call and the
       division, so no division padding (docs/COMPILER-NOTES.md). */
    *(int *)(self + 4) = func_00283D38_3(n, *(int *)(self + 4), a / func_00283CE0_4(*(short *)(self + 10)));
}

/* func_002C3430 uses the hazard-label profile in 002C3430-fade.c. */


void func_002C37E0(char *obj)
{
    char *sub = obj + 32;
    int w;
    int n;

    switch (*(unsigned char *)(sub + 2)) {
    case 2:
        *(float *)(obj + 16) = *(float *)(*(char **)(sub + 4) + 16) + *(float *)(sub + 16);
        *(float *)(obj + 20) = *(float *)(*(char **)(sub + 4) + 20) + *(float *)(sub + 20);
        *(float *)(obj + 24) = *(float *)(*(char **)(sub + 4) + 24) + *(float *)(sub + 24);
        break;
    case 1:
        goto tail;
    }
    w = *(int *)(obj + 4);
    n = (w >> 24);
    n = n - *(short *)(obj + 32);
    if (n <= 0) {
        Fccb147a4_FUN_002B9180(obj, sub);
        return;
    }
    *(int *)(obj + 4) = (w & 0xffffff) | (n << 24);
tail:
    if (*(unsigned char *)(sub + 3) != 0) {
        obj += 16;
        Fccb147a4_FUN_00300190(obj, obj);
    }
}


/* func_002C38E0 is in the -G8 sibling. */

/* Advances a spark, stops it on collision, and decays its RGBA channels. */
void func_002C3B08(char *p) {
 float v[4];char *q;
 if(!p)return;
 q=p+32;*(float *)(p+12)+=-100.0f;
 func_00282CC0((char *)v,p+16,q);
 if(*(float *)q!=0 || *(float *)(q+4)!=0 || *(float *)(q+8)!=0){
 if(func_002761F8(p+16,v,2,p,0)){*(U128 *)(p+16)=*(U128 *)D_001BAFA0;func_00282C88(q);*(float *)(p+12)+=*(float *)(p+12);}
 else {*(U128 *)(p+16)=*(U128 *)v;if(*(float *)(q+12)!=0)*(float *)(q+8)+=*(float *)(q+12);else *(float *)(q+8)+=-0.0063f;}}
 if(*(float *)(q+28)<=0 || func_00282978((short *)(p+10)) || *(float *)(p+12)<0 || v[0]<0.01f || v[1]<0.01f || v[2]<0.01f){func_002B9180(p);return;}
 *(float *)(q+16)+=-0.01f;if(*(float *)(q+16)<0)*(float *)(q+16)=0;
 *(float *)(q+20)+=-0.03001f;if(*(float *)(q+20)<0)*(float *)(q+20)=0;
 *(float *)(q+24)+=-0.05f;if(*(float *)(q+24)<0)*(float *)(q+24)=0;
 if(*(float *)(q+28)<0)*(float *)(q+28)=0;
 *(int *)(p+4)=func_002AAE98(*(float *)(q+16),*(float *)(q+20),*(float *)(q+24),*(float *)(q+28));p[8]--;
}

/* func_002C3D80 uses the quadword-copy profile in 002C3D80-qcopy.c. */

void func_002C3EE8(char *p)
{
    char *q = p + 32;

    Fa03721e9_FUN_00282CC0(p + 16, p + 16, q);
    *(float *)(p + 12) = *(float *)(p + 12) + *(float *)(q + 16);
    *(unsigned char *)(p + 8) = *(unsigned char *)(p + 8) + 1;
    if (--*(short *)(p + 10) == 0) {
        *(unsigned int *)(p + 4) = *(unsigned int *)(p + 4) + 0xff000000;
        *(short *)(p + 10) = 2;
    }
    if ((*(unsigned int *)(p + 4) & 0xff000000) == 0)
        Fa03721e9_FUN_002B9180(p);
}

/* func_002C3F88 uses the quadword-copy profile in 002C3F88-qcopy.c. */

/* Updates an attached spark and emits children; mode 1 orbits its owner.
 * The interleaved prototype preserves each EE argument register bank. */
void func_002C4100(char *p) {
 char *q=p+32; float v[4], w[4], rot[4], mat[16]; char *child;
 if(*(short *)(q+28)==0) {
  if(func_002A8860(p+4,*(short *)(q+26))) {func_002B9180(p);return;}
  if(*(char **)(q+12)) {
   v[0]=*(float *)(p+32);v[1]=*(float *)(q+4);v[2]=*(float *)(q+8);
   func_00282D30(v,v,func_00283CE0_2(*(short *)(q+24)));
   func_00282CC0(p+16,*(char **)(q+12)+16,(char *)v);
  }
  return;
 }
 if(func_00282978((short *)(p+10)) || (*(short *)(p+10)<10 && func_002A8860(p+4,16))) {func_002B9180(p);return;}
 if(*(short *)(q+28)==1)func_002C3F88(0,p+16,0,0,10,0,*(signed char *)(p+7),0);
 else {
  v[0]=*(float *)(q);v[1]=*(float *)(q+4);v[2]=*(float *)(q+8);
  child=func_002C3F88(*(int *)(q+12),p+16,0,0,10,0,*(signed char *)(p+7),v);
  if(child) *(short *)(child+56)=*(short *)(q+24);
 }
 if(*(short *)(q+28)==1) {
  qcopy(p+16,*(char **)(q+12)+16);
  v[0]=func_00283180(*(float *)(q+16))*2.25f;
  v[1]=func_00283198(*(float *)(q+16))*2.25f;
  v[2]=v[0]; v[0]=0;
  w[0]=func_00283180(*(float *)(q+20))*0.28f;
  w[1]=func_00283198(*(float *)(q+20))*0.28f;
  w[2]=w[0]; w[0]=0;
  func_00282C88(rot);rot[1]=*(float *)(q+16);
  func_00283410(mat,rot);func_002830C0(w,w,mat);
  func_00282CC0((char *)v,(char *)v,(char *)w);
  func_00283098(v,v,*(char **)(q+12)+192);
  func_00282CC0(p+16,p+16,(char *)v);
  *(float *)(q+16)=func_00283B98(*(float *)(q+16),0.015998853370547295f);
  *(float *)(q+20)=func_00283B98(*(float *)(q+20),0.07272206246852875f);
 }
}



/* Follows a selected attachment, randomizes its rotation, and fades by lifetime. */
extern float func_002A78D8(float, float);
extern float func_00283CE0(int);

void func_002C4500(char *object)
{
    char *motion = object + 0x20;
    int angle;
    float alpha;
    if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
        *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
        *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f)
        goto destroy;
    if (*(short *)(motion + 0x16) == 1) {
        qcopy(object + 0x10, *(char **)(*(char **)(motion + 0x1C) + 0x68) + 0xC0);
    } else if (*(short *)(motion + 0x16) == 3) {
        qcopy(object + 0x10, *(char **)(*(char **)(motion + 0x1C) + 0x68) + 0xD0);
    } else if (*(short *)(motion + 0x16) == 2) {
        qcopy(object + 0x10, *(char **)(*(char **)(motion + 0x1C) + 0x68) + 0x1E0);
    } else if (*(short *)(motion + 0x16) == 4) {
        float z = *(float *)(object + 0x18);
        qcopy(object + 0x10, *(char **)(motion + 0x1C) + 0x10);
        *(float *)(object + 0x18) = z + 0.2f;
    } else {
        func_00282CC0(object + 0x10, object + 0x10, motion);
    }
    if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
        *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
        *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f)
        goto destroy;
    angle = *(unsigned char *)(object + 8);
    angle += func_00283CF0(func_002A78D8(0.0f, 64.0f));
    if (angle > 255) angle -= 255;
    *(unsigned char *)(object + 8) = angle;
    if (func_00282978(object + 0xA)) {
destroy:
        func_002B9180(object);
        return;
    }
    alpha = func_00283CE0(*(short *)(object + 0xA));
    {
        float scale = func_00283CE0(*(short *)(motion + 0x14));
        alpha = alpha * *(float *)(motion + 0x10) * scale;
    }
    *(int *)(object + 4) = (func_00283CF0(alpha) << 24) | *(int *)(motion + 0x18);
}

/* decrements a signed short counter and, at zero, rotates a 24-bit identifier beside it and reloads the counter; calls a helper when the identifier's top byte is clear */
void func_002C4788(u8 *a0) {
    s16_F570cfb4b *p = (s16_F570cfb4b *)(a0 + 10);
    if (--*p == 0) {
        *(s32 *)(a0 + 4) += 0xff000000;
        *p = 2;
    }
    if ((*(s32 *)(a0 + 4) & 0xff000000) == 0) {
        func_002B9180_7(a0);
    }
}

/* Pulls toward a target, blends colour by distance, then advances through
 * three timed movement/fade phases. */
void func_002C47E8(char *p) {
 char *q=p+32; float v[4],a[4],b[4];float f;
 if(D_001B1688[0]&1)p[8]++;
 f=func_00282E48(p+16,D_00189F00);
 if(f<5.0f && *(float *)(*(char **)(q+24)+8)>0.0f) {
  func_00282CF0(a,*(void **)(q+24),p+16);
  if(func_00282DF0(a)>0.5f) {func_00282F20(a,a,0.1f/f);func_00282CC0(p+16,p+16,(char *)a);}
  else {func_00282F20(a,a,0.005f);func_002AE730(a,(int *)(p+36));}
 }
 f=(2.5f-(f-0.5f))*0.4f;
 if(f>1.0f)f=1.0f;else if(f<0.0f)f=0.0f;
 *(int *)(p+4)=func_00283D38(*(int *)(q+8),*(int *)(q+12),f);
 if(*(short *)(q+16)) {
  /* Retail writes zero to the hardware register at 0x10000000. */
  *(volatile int *)0x10000000=0;
  func_002AE838(v,q);func_00282CC0(p+16,p+16,(char *)v);
  f=func_00283CE0_2(*(short *)(p+10))/func_00283CE0_2(*(short *)(q+16));
  *(int *)(p+4)=func_00283D38(*(int *)(p+4)&0xffffff,*(int *)(p+4),1.0f-f);
  if(func_00282978((short *)(p+10))){*(short *)(q+16)=0;*(short *)(p+10)=*(short *)(q+18);}
 } else if(*(short *)(q+18)) {
  func_002AE838(a,q);func_002AE838(b,q+4);
  func_00282D08(v,b,a,func_00283CE0_2(*(short *)(p+10))/func_00283CE0_2(*(short *)(q+18)));
  func_00282CC0(p+16,p+16,(char *)v);
  if(func_00282978((short *)(p+10))){*(short *)(q+18)=0;*(short *)(p+10)=*(short *)(q+20);}
 } else {
  int color;
  func_002AE838(v,q+4);func_00282CC0(p+16,p+16,(char *)v);
  color=*(int *)(p+4)&0xffffff;
  *(int *)(p+4)=func_00283D38(color,*(int *)(p+4),func_00283CE0_2(*(short *)(p+10))/func_00283CE0_2(*(short *)(q+20)));
  if(func_00282978((short *)(p+10)))func_002B9180(p);
 }
}


void func_002C4B10(u8 *a0)
{
    f32 value = *(f32 *)(a0 + 0x0C);
    *(u8 *)(a0 + 0x08) = *(u8 *)(a0 + 0x08) + *(u8 *)(a0 + 0x38);
    if (value <= 0.0f) {
        *(f32 *)(a0 + 0x0C) = 0.0f;
        func_002B9180(a0);
    }
}

/* func_002C4B50 is in 002BF6F0-c4b50.c. */

/* func_002C4D18 is in 002BF6F0-c4b50.c. */

void func_002C4F08(char *self)
{
    char *motion = self + 0x20;
    float len;
    float f;

    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(motion + 0x12);
    func_00282CC0_17(self + 0x10, self + 0x10, motion);
    *(float *)(motion + 8) = *(float *)(motion + 8) - 3.0000000260770320892334e-03f;
    len = func_00282E20(motion);
    /* Preserve both retail operations: floating-point rounding means subtracting
       and adding 1.0f cannot generally be simplified away. */
    f = len * 9.7000002861022949218750e-01f - 1.0f + 1.0f;
    f = f / len;
    *(float *)(self + 0x20) = *(float *)(self + 0x20) * f;
    *(float *)(motion + 4) = *(float *)(motion + 4) * f;
    if (func_00282978((short *)(self + 0xA)) == 0) {
        f = *(float *)(self + 0xC) + *(float *)(motion + 0x14) * 2.0f;
        *(float *)(self + 0xC) = f;
        if (f < 15000.0f)
            *(float *)(self + 0xC) = 15000.0f;
    } else {
        if (func_002A8860(self + 4, *(int *)(motion + 0x1C)) != 0) {
            *(int *)(self + 0xC) = 0;
            func_002B9180(self);
        }
    }
}


extern float func_00283CE0_2(int v);
extern int func_00283CF0_6(float f);
extern void func_00282CC0_17(char *dst, char *src, char *vec);
extern int func_00282978_9(char *p);
extern void func_002B9180_13(char *self);


/* The particle update: the quad at 0x20 is copied to the stack, the value of
   the helper at 0xA is divided by the copy's fourth float, the two scaled
   results are packed into the word at 4 and the byte at 8. */
void func_002C5068(char *self)
{
    V4_Fc3cb9262 vec;
    float f3;
    float f21;
    int v;

    vec = *(V4_Fc3cb9262 *)(self + 0x20);
    f3 = ((float *)&vec)[3];
    ((float *)&vec)[3] = 0.0f;
    f21 = func_00283CE0_2(*(short *)(self + 0xA)) / f3;
    v = func_00283CF0_6(f21 * 38.0f);
    *(int *)(self + 4) = (v << 24) | 0x808080;
    v = func_00283CF0_6(f21 * 33.0f);
    *(char *)(self + 8) = (char)v;
    func_00282CC0_17(self + 0x10, self + 0x10, (char *)&vec);
    if (func_00282978_9(self + 0xA) != 0) {
        func_002B9180_13(self);
    }
}

/* func_002C5120 is in 002BF6F0-c5120-g8.c. */


void func_002C5550(Obj_F7cacd225 *o)
{
    int v;

    if (o->f16 < 2.0f || o->f16 > 1021.0f ||
        o->f20 < 2.0f || o->f20 > 1021.0f ||
        o->f24 < 2.0f || o->f24 > 1021.0f ||
        F7cacd225_FUN_00282978(&o->s10) != 0) {
        F7cacd225_FUN_002B9180((char *)o);
        return;
    }
    v = o->f32;
    if (v != 0) {
        o->f12 = o->f12 * 0.99f;
        o->f4 = F7cacd225_FUN_00283D38(0x30FFFFFF, o->f4, F7cacd225_FUN_00283CE0(o->s10 - 1) / F7cacd225_FUN_00283CE0(o->s10));
    } else {
        o->f12 = o->f12 * 0.95f;
        o->f4 = F7cacd225_FUN_00283D38(0x603F1008, o->f4, F7cacd225_FUN_00283CE0(o->s10 - 1) / F7cacd225_FUN_00283CE0(o->s10));
    }
}

/* func_002C56B0 uses the quadword-copy profile in 002C56B0-qcopy.c. */

void func_002C58A8(char *p) {
 char *q=p+32; SplitVector v; struct { float v[4]; void *owner; int flags; unsigned char mode, enabled; short mask; float scale; int last; } c; int i; float f,a,speed;
 switch(*(unsigned char *)(q+20)) {
 case 0:
  for(i=0;i<*(unsigned char *)(q+19);i++) {
   qcopy(&v,p+16);
   func_002ACB48(&v,0.05f);
   speed=1.0f;
   if(*(short *)(p+10)<10)speed=func_00283CE0_2(*(short *)(p+10))*0.1f;
   func_002C56B0(&v,0,1,*(short *)(q+16),*(unsigned char *)(q+19),*(unsigned char *)(q+21),*(int *)(q+24),*(float *)(q+28),speed);
  }
  if(func_00282978((short *)(p+10)))func_002B9180(p);
  func_00282C88(&c);
  { ParticleHero2C58A8 *hero=(ParticleHero2C58A8 *)D_00189E20;
  c.owner=hero->owner;c.flags=0x10000;c.mode=2;c.mask=0x820;c.enabled=1;c.scale=1.0f;c.last=0; }
  if((D_001B1688[0]+*(unsigned char *)(q+23))%10==0)
   func_00277F48(0.2f,p+16,16,(int)c.owner,(int)&c);
  break;
 case 1:
  func_00282CC0(p+16,p+16,q);
  a=func_00283CE0_2(*(unsigned char *)(q+21));
  f=(a-func_00283CE0_2(*(short *)(p+10)))/a;
  *(int *)(p+4)=func_00283D38((*(unsigned char *)(q+22)<<24)|0x4060,0x8fafff,f);
  if(f<0.6f)*(float *)(p+12)+=9030.0f;else *(float *)(p+12)-=16800.0f;
  p[2]=D_001F2628[func_001163B0()&7];
  if((((p-D_001B1D90[0])>>6)&1))p[8]++;else p[8]--;
  if(func_00282978((short *)(p+10)))func_002B9180(p);
  break;
 }
}


/* func_002C5B70 uses the quadword-copy profile in 002C5B70-qcopy.c. */

/* Adapted from RAC1 effect_particle_updates.c; measured against RAC2 retail. */
void func_002C5D00(FadeSplitParticle *m) {
    SplitVector v, p;
    FadeSplitCollision c;
    FadeSplitMotion *e = &m->e;
    FadeSplitParticle *n;
    f32 r, nr, a, s;
    s32 hit;
    u8 fl;
    u8 *tab;

    if (m->hA != 0 && func_00282978(&m->hA)) {
        e->b18 |= 0x88;
        r = m->fC * 0.0000011111111462014378f;
        m->fC *= 0.8f;
        nr = -r;
        func_00282D30_12((char *)&v, (char *)e, func_002A7878(0.5f, 0.7f));
        p.f[0] = m->pos.f[0] + func_002A7878(nr, r);
        p.f[1] = m->pos.f[1] + func_002A7878(nr, r);
        p.f[2] = m->pos.f[2] + func_002A7878(nr, r);
        v.f[0] += func_002A7878(-e->v.f[0] * 0.2f, e->v.f[0] * 0.2f);
        v.f[1] += func_002A7878(-e->v.f[1] * 0.2f, e->v.f[1] * 0.2f);
        v.f[2] += func_002A7878(-e->v.f[2] * 0.2f, 0.0f);
        n = (FadeSplitParticle *)func_002C5B70((char *)&p, (char *)&v, 0x88, e->x1C);
        if (n) {
            n->hA = 2;
            n->fC = m->fC;
        }
        func_00282D30_12((char *)e, (char *)e, func_002A7878(0.5f, 0.7f));
        e->v.f[0] += func_002A7878(-e->v.f[0] * 0.2f, e->v.f[0] * 0.2f);
        e->v.f[1] += func_002A7878(-e->v.f[1] * 0.2f, e->v.f[1] * 0.2f);
        e->v.f[2] += func_002A7878(-e->v.f[2] * 0.2f, 0.0f);
        m->pos.f[0] += func_002A7878(nr, r);
        m->pos.f[1] += func_002A7878(nr, r);
        m->pos.f[2] += func_002A7878(nr, r);
    }
    tab = D_001F2688;
    { int index = m->b2 - tab[0];
    m->b2 = tab[(m->hA + e->h16 + index) & 7]; }
    func_00282CC0((char *)&v, (char *)&m->pos, (char *)e);
    hit = 0;
    if (e->h14 > 3) {
        func_00282CF0(&p, &m->pos, e);
    } else {
        p.q = m->pos.q;
    }
    func_00282D30_12((char *)&c, (char *)&c, 0.01f);
    fl = e->b18;
    if (fl & 8) {
        if (!(m->x4 & 0xFF000000)) goto kill;
        e->b18 = fl | 8;
        if (!func_002A77E0(3)) hit = func_002761F8(&p, &v, 0, (void *)e->x1C, 0) != 0;
    } else {
        c.x10 = e->x1C;
        c.x1C = 1.0f;
        c.v.q = e->v.q;
        c.x14 = 1;
        c.x20 = 1;
        if (!func_002A77E0(3)) hit = func_002761F8(&p, &v, 0, (void *)e->x1C, &c) != 0;
    }
    if (hit) e->b18 |= 8;
    else qcopy(&m->pos, &v);
    if (e->b18 & 8) {
        e->h16++;
        m->fC -= 18055.5546875f;
        if (m->fC <= 0.0f) {
        kill:
            func_002B9180(m);
            return;
        }
    } else {
        m->fC += 14444.4443359375f;
    }
    s = func_00283CE0_2(e->h14);
    a = s * 0.000246913579758257f + 0.08f;
    if (a < 0.0f) a = 0.0f;
    if (0.08f < a) a = 0.08f;
    if (e->b18 & 8) a /= (f32)e->h16 * 0.142857149243355f + 1.0f;
    m->x4 = (m->x4 & 0xFFFFFF) | (func_00283CF0(a * 256.0f) << 24);
    e->v.f[2] += 0.0002f;
    if (e->h14 > 25 || (e->b18 & 8)) {
        e->v.f[0] *= 0.95f;
        e->v.f[1] *= 0.95f;
    }
    { u8 f2 = e->b18;
    s = -1.0f;
    if (f2 & 1) s = 1.0f;
    if (f2 & 8) {
        e->v.f[2] += 0.0002f;
        e->x10 += s * (-0.01f) / func_00283CE0_2(e->h16);
    } else {
        e->x10 += s * (-0.01f);
    } }
    if (1.0f < e->x10) e->x10 -= 1.0f;
    if (e->x10 < 0.0f) e->x10 += 1.0f;
    m->b8 = (s32)(e->x10 * 256.0f);
}

/* func_002C6360 is in the -G8 sibling (its two globals are read through $gp). */

extern float func_00283198(float);
extern int func_00283CF0(float);

void func_002C64D8(char *s1)
{
    float f20;
    float t;
    char *s0;

    if (s1 == 0)
        return;
    s0 = s1 + 0x20;
    if (func_00282978((short *)(s1 + 0x24)) != 0) {
        func_002B9180(s1);
        return;
    }
    f20 = func_00283CE0(*(short *)(s0 + 4)) / func_00283CE0(*(short *)(s0 + 6));
    t = func_00283198(f20 * 6.283186f);
    *(int *)(s1 + 4) = (*(int *)(s1 + 4) & 0x00FFFFFF)
                       + (func_00283CF0(func_00282C48(func_00283CE0(*(int *)(s0 + 0xC)) * t)) << 24);
}

/* func_002C65A0 is in 002BF6F0-c65a0.c. */

/* If a probe call on a sub-object returns zero, folds a byte counter into the top byte of a packed word, rebuilds a 16-byte vector from two sub-records for a helper, then clamps a running float against a limit and accumulates two sub-record fields into the object. */
void func_002C6748(char *obj)
{
    Vec16_F9a4b4d8b local;
    char *s1;
    char *s2;
    int a;
    int v1;

    if (func_00282978_6(obj + 10) != 0) {
        func_002B9180_10(obj);
        return;
    }

    a = *(int *)(obj + 4);
    s1 = obj + 32;
    *(int *)(obj + 4) = (a & 0x00ffffff) | (((a >> 24) + *(unsigned char *)(s1 + 20)) << 24);

    s2 = obj + 16;
    local.f[0] = *(float *)(obj + 32);
    local.f[1] = *(float *)(s1 + 4);
    local.f[2] = *(float *)(s1 + 8);
    local.f[3] = 0.0f;
    func_00282CC0_21(s2, s2, (char *)&local);

    *(float *)(s1 + 8) = *(float *)(s1 + 8) - *(float *)(s1 + 12);

    if (*(float *)(obj + 28) != 0.0f) {
        if (*(float *)(obj + 28) == 2.0f)
            func_00300190_2(s2, s2);
        *(float *)(obj + 28) = 2.0f;
    }
    v1 = *(unsigned char *)(s1 + 21);

    *(unsigned char *)(obj + 8) = *(unsigned char *)(obj + 8) + v1;
    *(float *)(obj + 12) += *(float *)(s1 + 16);
}

typedef struct {
    int *colors;
    short *sizes;
    short *times;
    short last_index;
    short reserved0E;
    short lifetime;
    short reserved12;
    float scale;
} ParticleKeyframes;
extern int func_002A9568(int, int, float);

void func_002C6868(char *self)
{
    char *motion = self + 0x20;
    ParticleKeyframes *control = *(ParticleKeyframes **)(motion + 0x10);
    short elapsed;
    float duration, factor;
    func_00282D30_12(motion, motion, (control->scale - 1.0f) + 1.0f);
    func_00282CC0_17(self + 0x10, self + 0x10, motion);
    *(unsigned char *)(self + 8) += *(unsigned char *)(motion + 0x18);
    elapsed = control->lifetime - *(short *)(self + 0xA);
    if (control->times[*(short *)(motion + 0x14) + 1] < elapsed &&
        *(short *)(motion + 0x14) < control->last_index)
        ++*(short *)(motion + 0x14);
    duration = func_00283CE0_2(control->times[*(short *)(motion + 0x14) + 1] -
        control->times[*(short *)(motion + 0x14)]);
    factor = (float)(elapsed -
        control->times[*(short *)(motion + 0x14)]) / duration;
    *(int *)(self + 4) = func_002A9568(
        control->colors[*(short *)(motion + 0x14)],
        control->colors[*(short *)(motion + 0x14) + 1], factor);
    *(float *)(self + 0xC) =
        ((float)control->sizes[*(short *)(motion + 0x14)] +
         factor * (float)(control->sizes[*(short *)(motion + 0x14) + 1] - control->sizes[*(short *)(motion + 0x14)])) * 1000.0f;
    if (func_00282978((short *)(self + 0xA)))
        func_002B9180(self);
}

/* Follows a sound emitter's moby: fades its volume byte (the top byte of +4) up by 4
   toward the target while the moby is visible and active, else down by 4 to zero,
   then places the emitter at the moby (or at its joint, pulled 0.4 of the way toward
   the camera). A dead or dying moby (state 0xFE/0xFD) or none lets the emitter finish
   and frees it. */
typedef int TI128_2C6A08 __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x10];
    float pos[4];
    unsigned char state;
    unsigned char pad21[0x10];
    unsigned char visible;
    unsigned char pad32[2];
    unsigned short flags;
} EmitterMoby2C6A08;
typedef struct {
    EmitterMoby2C6A08 *moby;
    unsigned char pad4[2];
    short joint;
    unsigned char pad8[3];
    signed char target;
} EmitterRef2C6A08;
typedef struct {
    unsigned char pad0[4];
    int packed;
    unsigned char ticks;
    unsigned char pad9[7];
    float pos[4];
    EmitterRef2C6A08 ref;
} Emitter2C6A08;
extern float D_001B5340[];
extern int func_002A8860(void *, int);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

/* Follows the particle's target (or one of its joints): the alpha fades towards the limit
   while the target is shown and out otherwise; a missing or dying target fades the particle
   out and frees it. The second read of the colour word is the retail copy kept by GCSE. */
void func_002C6A08(Emitter2C6A08 *emitter)
{
    float joint[4];
    float toward[4];
    EmitterMoby2C6A08 *moby;
    int level;
    int target;
    EmitterRef2C6A08 *ref;

    if (emitter == 0)
        return;
    emitter->ticks++;
    ref = &emitter->ref;
    moby = ref->moby;
    if (moby == 0 || moby->state == 0xFE || moby->state == 0xFD) {
        if (func_002A8860(&emitter->packed, 4) != 0)
            func_002B9180(emitter);
        return;
    }
    level = emitter->packed >> 24;
    target = ref->target;
    if (moby->visible != 0 && !(moby->flags & 2)) {
        if (level < target) {
            level += 4;
            if (target < level)
                level = target;
        }
    } else {
        level -= 4;
        if (level < 0)
            level = 0;
    }
    emitter->packed = (emitter->packed & 0xFFFFFF) | (level << 24);
    if (ref->joint == -1) {
        qcopy(emitter->pos, ref->moby->pos);
        return;
    }
    func_0029FCC0(ref->moby, ref->joint, joint);
    func_00282CF0(toward, D_001B5340, joint);
    func_00282F20(toward, toward, 0.4f);
    func_00282CC0((char *)emitter->pos, (char *)joint, (char *)toward);
}


char *func_002C6DD8(void *a0, void *a1, int a2, float f1)
{
    V4_Fc3cb9262 vec;
    Particle6DD8 *s0;
    int v;
    SplitVector *pos;

    s0 = func_002B9030(0x5A);
    if (s0 != 0) {
        s0->x4 = 0x7FFFFFFF;
        s0->xC = 0x7FFFFFFF;
        v = func_00283CF0_6(2.0f);
        s0->b9 = (char)(v + 0x20);
        s0->b3 = 0x48;
        s0->b1 = 3;
        s0->b2 = *D_001F26A8;
        pos = &s0->v30;
        qcopy_nc(pos, a1);
        pos->f[3] = f1;
        qcopy_nc(&s0->v10, a0);
        func_00282F20(&vec, pos, 0.9f);
        func_00282CF0(&s0->v20, a0, &vec);
        s0->hA = a2;
        s0->v10.f[3] = 0.05f;
        s0->b8 = (char)(*(unsigned char *)&s0->hA - 0xF);
        s0->v20.f[3] = 2.0f;
    }
    return (char *)s0;
}


/* func_002C7050 is defined in 002BF6F0-trail-g8.c. */

extern int func_00282948(short *);
/* Delay movement and the size/alpha tween until the secondary timer fires. */
void func_002C72A0(char *p)
{
    char *q = p + 32;
    Vec16_F9a4b4d8b v;
    float t;
    int elapsed, alpha;

    p[8] += (unsigned char)q[10];
    if (func_00282948((short *)(q + 24))) {
        elapsed = *(short *)(q + 8) - *(short *)(p + 10);
        if (elapsed < *(short *)(q + 30)) {
            t = (float)elapsed * 0.2f;
            *(float *)(p + 12) = *(float *)(q + 4) +
                ((*(float *)q + *(float *)(q + 4)) * 0.5f - *(float *)(q + 4)) * t;
            {
                int c2 = (unsigned char)q[11] >> 1;
                int c = (unsigned char)q[11];
                alpha = func_00283CF0((float)c + (float)(c2 - c) * t);
            }
        } else {
            t = func_00283CE0_2(*(short *)(q + 8) - 6);
            t = (float)*(short *)(p + 10) / t;
            *(float *)(p + 12) = *(float *)q +
                ((*(float *)q + *(float *)(q + 4)) * 0.5f - *(float *)q) * t;
            alpha = func_00283CF0((float)((unsigned char)q[11] >> 1) * t);
        }
        *(int *)(p + 4) = (alpha << 24) | (*(int *)(p + 4) & 0xffffff);
        particle_copy_xyz(v.f, (float *)(q + 12));
        func_00282CC0(p + 16, p + 16, (char *)&v);
        if (*(float *)(p + 16) < 2 || *(float *)(p + 16) > 1021 ||
            *(float *)(p + 20) < 2 || *(float *)(p + 20) > 1021 ||
            *(float *)(p + 24) < 2 || *(float *)(p + 24) > 1021) {
            func_002B9180(p);
            return;
        }
        if (func_00282978((short *)(p + 10))) {
            func_002B9180(p);
            return;
        }
    }
    if (*(float *)(p + 28) != 0) {
        if (*(float *)(p + 28) == 2.0f)
            func_00300190_2(p + 16, p + 16);
        *(float *)(p + 28) = 2.0f;
    }
}

void func_002C7538(char *a0)
{
    V4_Fc3cb9262 buf;
    char *s0 = a0 + 32;
    float f0;
    float f1;
    float f2;

    f1 = *(float *)(s0 + 16) + 1.0000000474974513053894e-03f;
    f2 = *(float *)(s0 + 8) - 3.0000000260770320892334e-03f;
    *(float *)(s0 + 16) = f1;
    *(float *)(s0 + 8) = f2;
    f0 = *(float *)(s0 + 20) * f1 * 2.1000000000000000000000e+05f;
    buf = *(V4_Fc3cb9262 *)s0;
    *(float *)(a0 + 12) = f0;
    Fc3cb9262_FUN_00282CC0(a0 + 16, a0 + 16, (char *)&buf);
    *(int *)(a0 + 4) = (Fc3cb9262_FUN_00283CF0((float)*(short *)(a0 + 10)) << 24) | 0x00FFD2D2;
    *(unsigned char *)(a0 + 8) = *(unsigned char *)(a0 + 8) + *(unsigned char *)(s0 + 24);
    if (Fc3cb9262_FUN_00282978(a0 + 10) != 0)
        Fc3cb9262_FUN_002B9180(a0);
}
