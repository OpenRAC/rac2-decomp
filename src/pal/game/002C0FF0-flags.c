#include "include_asm.h"

#include "common.h"
typedef unsigned int U128 __attribute__((mode(TI)));
typedef union { U128 q; f32 f[4]; } SplitVector;
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
extern char *func_PAL_002C0FF0(void *, void *, int, void *, int, int);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00283028(void *, void *, void *);
extern void func_00282C88(void *);
extern float D_001BAFC0[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern unsigned char *D_001F2570;
void func_002B9180(void *);
int func_00282978(short *);
extern float func_00283CE0(int v);
extern void func_00282D30(char *dst, char *table, float scale);
extern void func_00282CC0(char *, char *, char *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern void func_00282CC0(char *, char *, char *);
extern int func_00283CF0(float);
extern void func_00282CC0(char *, char *, char *);
extern float func_00283CE0(int v);
extern int func_00283CF0(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

/* func_002C01F8 is in 002BF6F0-c01f8-g8.c. */

/* func_PAL_002C0FF0 uses the quadword-copy profile in 002C02F0-qcopy.c. */

/* Adapted from RAC1 effect_particle_updates.c; measured against RAC2 retail. */
void func_PAL_002C11C0(SplitParticle *p) {
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
        sp = p->f0C / (func_00283CE0((u8)pv->pad19[0]) * 28125.0f);
        hi = 0.7f;
        sc = 0.2f;
        p->f0C = p->f0C * 0.8f;
        zero = 0.0f;
        f = func_002A7878(lo, hi);
        nsp = -sp;
        func_00282D30((char *)v0u.f, (char *)pv, f);
        v1u.f[0] = p->posv.f[0] + func_002A7878(nsp, sp);
        v1u.f[1] = p->posv.f[1] + func_002A7878(nsp, sp);
        v1u.f[2] = p->posv.f[2] + func_002A7878(nsp, sp);
        v0u.f[0] = v0u.f[0] + func_002A7878(-p->pv.x * sc, p->pv.x * sc);
        v0u.f[1] = v0u.f[1] + func_002A7878(-pv->y * sc, pv->y * sc);
        v0u.f[2] = v0u.f[2] + func_002A7878(-pv->z * sc, zero);
        r = (SplitParticle *)func_PAL_002C0FF0(v1u.f, v0u.f, (pv->f18 & 0x10) | 0x88, pv->f1C, (u8)pv->pad19[0], 128);
        if (r != 0) {
            r->h0A = 2;
            r->f0C = p->f0C;
        }
        func_00282D30((char *)pv, (char *)pv, func_002A7878(lo, hi));
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
    if (2 < k) {
        func_00282CF0(v1u.f, p->posv.f, pv);
    } else {
        v1u.q = p->posv.q;
    }
    func_00282D30((char *)&c, (char *)&c, 0.01f);
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
        func_00282D30((char *)pv, (char *)pv, 0.02f);
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
        n = p->f0C - (func_00283CE0((u8)pv->pad19[0]) * 8437.5f - func_00283CE0((u8)pv->pad19[0]) * 937.5f) * 0.10000001f;
        p->f0C = n;
        if (n <= 0.0f) {
        kill:
            func_002B9180(p);
            return;
        }
    } else {
        p->f0C = p->f0C + (func_00283CE0((u8)pv->pad19[0]) * 8437.5f - func_00283CE0((u8)pv->pad19[0]) * 937.5f) * 0.080000006f;
    }
    f = func_00283CE0(pv->f14);
    s = f * 0.0004266667f + 0.08f;
    if (s < 0.0f) s = 0.0f;
    if (0.08f < s) s = 0.08f;
    if (pv->f18 & 8) {
        s = s / ((f32)pv->f16 * 0.142857149243355f + 1.0f);
    }
    p->f04 = (p->f04 & 0xFFFFFF) | (func_00283CF0(s * 256.0f) << 24);
    pv->z = pv->z + 0.011520001f;
    t = pv->f14;
    if (21 < t || (pv->f18 & 8)) {
        pv->x = pv->x * 0.95f;
        pv->y = pv->y * 0.95f;
    }
    fm = pv->f18;
    g = -1.0f;
    if (fm & 1) g = 1.0f;
    if (fm & 8) {
        pv->z = pv->z + 0.011520001f;
        f = func_00283CE0(pv->f16);
        pv->t = pv->t + g * (-0.012f) / f;
    } else {
        pv->t = pv->t + g * (-0.012f);
    }
    if (1.0f < pv->t) pv->t = pv->t - 1.0f;
    if (pv->t < 0.0f) pv->t = pv->t + 1.0f;
    p->f08 = (s32)(pv->t * 256.0f);
}
