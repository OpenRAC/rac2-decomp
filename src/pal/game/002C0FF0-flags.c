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
extern char *part_spawn_scaled_smoke_pal(void *, void *, int, void *, int, int);
extern int CollLine(void *, void *, int, void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_clear_128(void *);
extern float g_coll_hit_normal[];
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern unsigned char *g_part_tex_smoke_table;
void part_kill(void *);
int FastDecTimer(short *);
extern float IntToFloat(int v);
extern void FastVecScale(char *dst, char *table, float scale);
extern void FastVecAdd(char *, char *, char *);
extern int CollLine(void *, void *, int, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern void FastVecAdd(char *, char *, char *);
extern int FloatToInt(float);
extern void FastVecAdd(char *, char *, char *);
extern float IntToFloat(int v);
extern int FloatToInt(float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* func_002C01F8 is in 002BF6F0-c01f8-g8.c. */

/* func_PAL_002C0FF0 uses the quadword-copy profile in 002C02F0-qcopy.c. */

/* Adapted from RAC1 effect_particle_updates.c; measured against RAC2 retail. */
void part_update_splitting_spark_pal(SplitParticle *p) {
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
    if (p->h0A != 0 && FastDecTimer(&p->h0A) != 0) {
        f32 sp, lo, hi, sc, zero, nsp;
        pv->f18 |= 0x88;
        lo = 0.5f;
        sp = p->f0C / (IntToFloat((u8)pv->pad19[0]) * 28125.0f);
        hi = 0.7f;
        sc = 0.2f;
        p->f0C = p->f0C * 0.8f;
        zero = 0.0f;
        f = math_random_float_range(lo, hi);
        nsp = -sp;
        FastVecScale((char *)v0u.f, (char *)pv, f);
        v1u.f[0] = p->posv.f[0] + math_random_float_range(nsp, sp);
        v1u.f[1] = p->posv.f[1] + math_random_float_range(nsp, sp);
        v1u.f[2] = p->posv.f[2] + math_random_float_range(nsp, sp);
        v0u.f[0] = v0u.f[0] + math_random_float_range(-p->pv.x * sc, p->pv.x * sc);
        v0u.f[1] = v0u.f[1] + math_random_float_range(-pv->y * sc, pv->y * sc);
        v0u.f[2] = v0u.f[2] + math_random_float_range(-pv->z * sc, zero);
        r = (SplitParticle *)part_spawn_scaled_smoke_pal(v1u.f, v0u.f, (pv->f18 & 0x10) | 0x88, pv->f1C, (u8)pv->pad19[0], 128);
        if (r != 0) {
            r->h0A = 2;
            r->f0C = p->f0C;
        }
        FastVecScale((char *)pv, (char *)pv, math_random_float_range(lo, hi));
        p->pv.x = p->pv.x + math_random_float_range(-p->pv.x * sc, p->pv.x * sc);
        pv->y = pv->y + math_random_float_range(-pv->y * sc, pv->y * sc);
        pv->z = pv->z + math_random_float_range(-pv->z * sc, zero);
        p->posv.f[0] = p->posv.f[0] + math_random_float_range(nsp, sp);
        p->posv.f[1] = p->posv.f[1] + math_random_float_range(nsp, sp);
        p->posv.f[2] = p->posv.f[2] + math_random_float_range(nsp, sp);
    }
    tab = g_part_tex_smoke_table;
    { int index = p->b02 - tab[0];
    p->b02 = tab[(p->h0A + pv->f16 + index) & 7]; }
    FastVecAdd((char *)v0u.f, (char *)p->posv.f, (char *)pv);
    hit = 0;
    k = pv->f14;
    if (2 < k) {
        FastVecSub(v1u.f, p->posv.f, pv);
    } else {
        v1u.q = p->posv.q;
    }
    FastVecScale((char *)&c, (char *)&c, 0.01f);
    fl = pv->f18;
    if (fl & 8) {
        if ((p->f04 & 0xFF000000) == 0) goto kill;
        pv->f18 = fl | 8;
        if (!(pv->f18 & 0x10)) hit = CollLine(v1u.f, v0u.f, 4, pv->f1C, 0) != 0;
    } else {
        c.f10 = pv->f1C;
        c.f14 = 0x10001;
        c.f1C = 1.0f;
        c.v.q = *(U128 *)pv;
        if (fl & 0x40) vec_clear_128(&c);
        c.f20 = 1;
        if (!(pv->f18 & 0x10)) hit = CollLine(v1u.f, v0u.f, 0, pv->f1C, &c) != 0;
    }
    if (hit) {
        vec_scale_to_length(v2, g_coll_hit_normal, 1.0f);
        vec_fast_normalize(pv, pv, g_coll_hit_normal);
        FastVecScale((char *)pv, (char *)pv, 0.02f);
        vec_scale_to_length(v2, g_coll_hit_normal, 0.055f);
        FastVecAdd((char *)p->posv.f, (char *)(g_coll_hit_normal - 8), (char *)v2);
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
        n = p->f0C - (IntToFloat((u8)pv->pad19[0]) * 8437.5f - IntToFloat((u8)pv->pad19[0]) * 937.5f) * 0.10000001f;
        p->f0C = n;
        if (n <= 0.0f) {
        kill:
            part_kill(p);
            return;
        }
    } else {
        p->f0C = p->f0C + (IntToFloat((u8)pv->pad19[0]) * 8437.5f - IntToFloat((u8)pv->pad19[0]) * 937.5f) * 0.080000006f;
    }
    f = IntToFloat(pv->f14);
    s = f * 0.0004266667f + 0.08f;
    if (s < 0.0f) s = 0.0f;
    if (0.08f < s) s = 0.08f;
    if (pv->f18 & 8) {
        s = s / ((f32)pv->f16 * 0.142857149243355f + 1.0f);
    }
    p->f04 = (p->f04 & 0xFFFFFF) | (FloatToInt(s * 256.0f) << 24);
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
        f = IntToFloat(pv->f16);
        pv->t = pv->t + g * (-0.012f) / f;
    } else {
        pv->t = pv->t + g * (-0.012f);
    }
    if (1.0f < pv->t) pv->t = pv->t - 1.0f;
    if (pv->t < 0.0f) pv->t = pv->t + 1.0f;
    p->f08 = (s32)(pv->t * 256.0f);
}
