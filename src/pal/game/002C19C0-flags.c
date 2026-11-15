#include "include_asm.h"

#include "common.h"
typedef unsigned int U128 __attribute__((mode(TI)));
typedef union { U128 q; f32 f[4]; } SplitVector;
typedef struct { SplitVector v; f32 x10; s16 h14; s16 h16; u8 b18; u8 pad[3]; s32 x1C; } FadeSplitMotion;
typedef struct { u8 pad[2]; u8 b2; u8 pad3; u32 x4; u8 b8; u8 pad9; s16 hA; f32 fC; SplitVector pos; FadeSplitMotion e; } FadeSplitParticle;
typedef struct { SplitVector v; s32 x10; s32 x14; u8 pad[4]; f32 x1C; s32 x20; } FadeSplitCollision;
extern int CollLine(void *, void *, int, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern unsigned char *D_001F2570;
void part_kill(void *);
int FastDecTimer(short *);
extern float IntToFloat(int v);
extern void FastVecScale(char *dst, char *table, float scale);
extern int math_random_int_below(int);
extern void FastVecAdd(char *, char *, char *);
extern int CollLine(void *, void *, int, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern void FastVecAdd(char *, char *, char *);
extern int FloatToInt(float);
extern void FastVecAdd(char *, char *, char *);
extern float IntToFloat(int v);
extern int FloatToInt(float);
extern void FastVecSub(void *, void *, void *);

/* func_PAL_002C19C0 uses the quadword-copy profile in 002C0CC0-qcopy.c. */

/* Adapted from RAC1 effect_particle_updates.c; measured against RAC2 retail. */
void func_PAL_002C1B50(FadeSplitParticle *m) {
    SplitVector v, p;
    FadeSplitCollision c;
    FadeSplitMotion *e = &m->e;
    FadeSplitParticle *n;
    f32 r, nr, a, s;
    s32 hit;
    u8 fl;
    u8 *tab;

    if (m->hA != 0 && FastDecTimer(&m->hA)) {
        e->b18 |= 0x88;
        r = m->fC * 0.0000011111111462014378f;
        m->fC *= 0.8f;
        nr = -r;
        FastVecScale((char *)&v, (char *)e, math_random_float_range(0.5f, 0.7f));
        p.f[0] = m->pos.f[0] + math_random_float_range(nr, r);
        p.f[1] = m->pos.f[1] + math_random_float_range(nr, r);
        p.f[2] = m->pos.f[2] + math_random_float_range(nr, r);
        v.f[0] += math_random_float_range(-e->v.f[0] * 0.2f, e->v.f[0] * 0.2f);
        v.f[1] += math_random_float_range(-e->v.f[1] * 0.2f, e->v.f[1] * 0.2f);
        v.f[2] += math_random_float_range(-e->v.f[2] * 0.2f, 0.0f);
        n = (FadeSplitParticle *)func_PAL_002C19C0((char *)&p, (char *)&v, (e->b18 & 0x10) | 0x88, e->x1C);
        if (n) {
            n->hA = 2;
            n->fC = m->fC;
        }
        FastVecScale((char *)e, (char *)e, math_random_float_range(0.5f, 0.7f));
        e->v.f[0] += math_random_float_range(-e->v.f[0] * 0.2f, e->v.f[0] * 0.2f);
        e->v.f[1] += math_random_float_range(-e->v.f[1] * 0.2f, e->v.f[1] * 0.2f);
        e->v.f[2] += math_random_float_range(-e->v.f[2] * 0.2f, 0.0f);
        m->pos.f[0] += math_random_float_range(nr, r);
        m->pos.f[1] += math_random_float_range(nr, r);
        m->pos.f[2] += math_random_float_range(nr, r);
    }
    tab = D_001F2570;
    { int index = m->b2 - tab[0];
    m->b2 = tab[(m->hA + e->h16 + index) & 7]; }
    FastVecAdd((char *)&v, (char *)&m->pos, (char *)e);
    hit = 0;
    if (e->h14 > 2) {
        FastVecSub(&p, &m->pos, e);
    } else {
        p.q = m->pos.q;
    }
    FastVecScale((char *)&c, (char *)&c, 0.01f);
    fl = e->b18;
    if (fl & 8) {
        if (!(m->x4 & 0xFF000000)) goto kill;
        e->b18 = fl | 8;
        if (!math_random_int_below(3) && !(e->b18 & 0x10)) hit = CollLine(&p, &v, 0, (void *)e->x1C, 0) != 0;
    } else {
        c.x10 = e->x1C;
        c.x1C = 1.0f;
        c.v.q = e->v.q;
        c.x14 = 1;
        c.x20 = 1;
        if (!math_random_int_below(3) && !(e->b18 & 0x10)) hit = CollLine(&p, &v, 0, (void *)e->x1C, &c) != 0;
    }
    if (hit) e->b18 |= 8;
    else qcopy(&m->pos, &v);
    if (e->b18 & 8) {
        e->h16++;
        m->fC -= 26000.002f;
        if (m->fC <= 0.0f) {
        kill:
            part_kill(m);
            return;
        }
    } else {
        m->fC += 20800.002f;
    }
    s = IntToFloat(e->h14);
    a = s * 0.0004266667f + 0.08f;
    if (a < 0.0f) a = 0.0f;
    if (0.08f < a) a = 0.08f;
    if (e->b18 & 8) a /= (f32)e->h16 * 0.142857149243355f + 1.0f;
    m->x4 = (m->x4 & 0xFFFFFF) | (FloatToInt(a * 256.0f) << 24);
    e->v.f[2] += 0.011520001f;
    if (e->h14 > 21 || (e->b18 & 8)) {
        e->v.f[0] *= 0.95f;
        e->v.f[1] *= 0.95f;
    }
    { u8 f2 = e->b18;
    s = -1.0f;
    if (f2 & 1) s = 1.0f;
    if (f2 & 8) {
        e->v.f[2] += 0.011520001f;
        e->x10 += s * (-0.012f) / IntToFloat(e->h16);
    } else {
        e->x10 += s * (-0.012f);
    } }
    if (1.0f < e->x10) e->x10 -= 1.0f;
    if (e->x10 < 0.0f) e->x10 += 1.0f;
    m->b8 = (s32)(e->x10 * 256.0f);
}
