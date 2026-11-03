/* functional: high. Unchecked: no capture run calls it (level00, level03, level07 and level12 runs), so no gate verdict. Read against all 1449 retail instructions of level 00's copy (0x3FA858-0x3FBEF8): every call (168) with its arguments, every store (quad colours, UVs, the 0x70-0x88 GS words), every $gp/lui data address, every float constant (incl. 0x3F490FDC and 0x3FC90FDC, 1/8590 = 0x38F42386, 28492/37082/8590) and every float compare's sense and operand order (c.eq.s d; c.lt.s d<11; c.le.s d<=7; c.lt.s 1e-5<|ang|; c.le.s on the screen box; c.lt.s t<0.5; the 0.9/0 UV clamps) agree. x8 is retail's andi 0xFF of the saved sra (an unsigned byte). From the earlier file: the near-miss draft with level 00's 0x2EE238 named func_00282DF0 and the two pi constants fixed; now also func_00280B90 declared as the port's host routine defines it (unsigned int game address, int, int). The earlier file did not compile: a stray comment tail after its first line (removed). */
/* func_L00_003FA858 (shared, 27 places): draws a moby's glow sprites: eight camera-facing quads
 * (two sizes from pvars 0x1C/0x1E, rotations from pvars ang[0..5]), then a screen-edge flare set
 * (func_00282978 / func_00279BD8 gate), a pvars+0x34 quad and a pvars+0x40 quad with clamped UVs.
 * From the near-miss draft nonmatching/levels/func_L00_003FA858.c. */
#include "common.h"

typedef float V4[4] __attribute__((aligned(16)));

typedef struct {
    V4 corner[4];
    s32 rgba[4];
    float uv[4][2];
    s64 d70;
    s64 d78;
    s64 d80;
    s64 d88;
} Quad;

typedef struct {
    f32 ang[6];
    s32 pad18;
    s16 t1C;
    s16 t1E;
    f32 k20;
    f32 k24;
    s16 n28;
    s16 n2A;
    f32 k2C;
    f32 k30;
    s16 t34;
    s16 t36;
    f32 k38;
    f32 k3C;
    s32 t40;
    f32 k44;
} Pv;

extern f32 D_L00_001B0A98 __attribute__((sda));
extern f32 D_L00_001B0A9C __attribute__((sda));
extern s32 D_L00_001B0AA4 __attribute__((sda));
extern s32 D_L00_001B0AA8 __attribute__((sda));
extern s32 D_L00_001B0B54 __attribute__((sda));
extern f32 D_L00_001B0B58 __attribute__((sda));
extern f32 D_L00_001B0B5C __attribute__((sda));
extern f32 D_L00_001B0B70 __attribute__((sda));
extern s32 D_L00_001B0B74 __attribute__((sda));
extern f32 D_L00_001B0B7C __attribute__((sda));
extern f32 D_L00_001B0B80 __attribute__((sda));
extern s32 D_L00_001B0B84 __attribute__((sda));
extern s32 D_L00_001B0B88 __attribute__((sda));
extern f32 D_L00_001B0B8C __attribute__((sda));
extern f32 D_L00_001B0B90 __attribute__((sda));
extern f32 D_L00_001B0B94 __attribute__((sda));
extern s32 D_L00_001B0B98 __attribute__((sda));
extern s32 D_L00_001B0B9C __attribute__((sda));
extern f32 D_L00_001B0BA0 __attribute__((sda));
extern f32 D_L00_001B0BA4 __attribute__((sda));
extern f32 D_L00_001B0BA8 __attribute__((sda));
extern f32 D_L00_001B0BAC __attribute__((sda));
extern V4 D_L00_001AA310[];
extern char D_L00_001B8DC0[];

extern void func_00279BD8(void *, void *);
extern void func_0027C768(void *, void *, void *);
extern unsigned long func_0027C878(int);
extern void func_00280B90(unsigned int, int, int); /* as the port's host routine (host/render.c) defines it: a game address */
extern void func_00281DE8(void *, s32, s32, s32);
extern int func_00282978(void *);
extern float func_00282C48(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_002A7AA8(float, float, float, float, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern float func_00282DF0(void *);
extern void func_002FC560(unsigned int, unsigned long long);

void func_L00_003FA858(u8 *moby)
{
    Quad q;
    V4 m[4];
    V4 dir;
    V4 rot;
    V4 vF0;
    V4 v100;
    V4 v110;
    V4 v120;
    V4 v130;
    V4 v140;
    V4 v150;
    V4 v160;
    V4 v170;
    V4 v180;
    V4 v190;
    V4 v1A0;
    V4 v1B0;
    Pv *pv;
    f32 d;
    f32 fade;
    f32 dot;
    f32 size;
    f32 a;
    f32 k;
    s32 alpha;
    s32 x;
    s32 c;
    s32 t2;
    s32 t3;
    s32 i1;
    s32 i2;
    s32 i3;
    s32 i4;
    s32 i5;
    s32 i6;
    s32 i7;
    s32 i8;
    s32 i9;
    s32 i10;
    s32 i11;
    f32 *pos;
    void *p36;
    u8 x8;
    f32 *pF0;
    f32 *p100;
    f32 *p110;
    f32 *p120;
    f32 *p130;

    pv = *(Pv **)(moby + 0x68);
    func_00282CF0(dir, moby + 0x10, D_L00_001B8DC0);
    d = func_00282DF0(dir);
    if (d != 0.0f) {
        func_00282D30(dir, dir, 1.0f / d);
    }
    fade = 1.0f;
    if (d < 11.0f) {
        if (d <= 7.0f) {
            fade = 0.0f;
        } else {
            fade = (d - 7.0f) * 0.25f;
        }
    }
    dot = func_00282DB0(dir, (f32 *)(moby + 0xC0));
    size = D_L00_001B0A9C + (D_L00_001B0A98 - D_L00_001B0A9C) * (func_00283CE0(pv->t1C) * pv->k20);
    if (pv->t1C < pv->n28) {
        k = func_00283CE0(pv->t1C) * pv->k2C;
        a = func_00283CE0(D_L00_001B0AA8) * k;
    } else {
        a = func_00283CE0(D_L00_001B0AA8);
    }
    alpha = ((u32)(func_00283CF0(a * dot * dot)) << 24);

    if (func_00282C48(pv->ang[0]) > 0.00001f) {
        func_002AB668(rot, (f32 *)(moby + 0xC0), pv->ang[0]);
        func_002ACDE8(m[1], (f32 *)(moby + 0xD0), rot);
        func_002ACDE8(m[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(m[1], (f32 *)(moby + 0xD0));
        qcopy(m[2], (f32 *)(moby + 0xE0));
    }
    pos = (f32 *)(moby + 0x10);
    qcopy(m[3], pos);
    p36 = &pv->t36;
    func_00282D30(m[0], (f32 *)(moby + 0xC0), size);
    func_00282D30(m[1], m[1], size);
    func_00282D30(m[2], m[2], size);
    m[2][3] = m[1][3] = m[0][3] = 0.0f;
    m[3][3] = 1.0f;
    func_00281DE8(&q, 0x38, 1, 0x80);
    p130 = v130;
    p120 = v120;
    pF0 = vF0;
    p100 = v100;
    p110 = v110;
    c = alpha | D_L00_001B0AA4;
    q.rgba[0] = c;
    q.rgba[1] = c;
    q.rgba[2] = c;
    q.rgba[3] = c;
    q.uv[0][0] = 0.0f;
    q.uv[0][1] = 0.0f;
    q.uv[1][0] = 0.0f;
    q.uv[1][1] = 1.0f;
    q.uv[2][0] = 1.0f;
    q.uv[2][1] = 0.0f;
    q.uv[3][0] = 1.0f;
    q.uv[3][1] = 1.0f;
    for (i1 = 0; i1 < 4; i1++) {
        func_002830C0(&q.corner[i1], &D_L00_001AA310[i1], m);
    }
    func_00280B90((unsigned int)&q, 0, 0);

    if (func_00282C48(pv->ang[0]) > 0.00001f) {
        func_002AB668(rot, (f32 *)(moby + 0xC0), -pv->ang[0]);
        func_002ACDE8(m[1], (f32 *)(moby + 0xD0), rot);
        func_002ACDE8(m[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(m[1], (f32 *)(moby + 0xD0));
        qcopy(m[2], (f32 *)(moby + 0xE0));
    }
    qcopy(m[3], pos);
    func_00282D30(m[0], (f32 *)(moby + 0xC0), size);
    func_00282D30(m[1], m[1], size);
    func_00282D30(m[2], m[2], size);
    m[2][3] = m[1][3] = m[0][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i2 = 0; i2 < 4; i2++) {
        func_002830C0(&q.corner[i2], &D_L00_001AA310[i2], m);
    }
    func_00280B90((unsigned int)&q, 0, 0);

    size = D_L00_001B0B5C + (D_L00_001B0B58 - D_L00_001B0B5C) * (func_00283CE0(pv->t1E) * pv->k24);
    if (pv->t1E < pv->n2A) {
        k = func_002A7AA8(1.0f, 0.0f, 1.0f, 2.0f, func_00283CE0(pv->t1E) * pv->k30);
    } else {
        k = 1.0f;
    }
    x = func_00283CF0(func_00283CE0(D_L00_001B0B54) * k * fade);
    a = func_00283CE0(x) * 0.2f;
    x = ((u32)(x) << 24);
    c = ((u32)(func_00283CF0(a)) << 24) | 0xFFFFFF;
    q.rgba[0] = c;
    q.rgba[3] = c;
    q.rgba[2] = c;
    q.rgba[1] = c;
    if (func_00282C48(pv->ang[1]) > 0.00001f) {
        func_002AB668(rot, (f32 *)(moby + 0xC0), pv->ang[1]);
        func_002ACDE8(m[1], (f32 *)(moby + 0xD0), rot);
        func_002ACDE8(m[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(m[1], (f32 *)(moby + 0xD0));
        qcopy(m[2], (f32 *)(moby + 0xE0));
    }
    x8 = x >> 24;
    func_00282D30(m[0], (f32 *)(moby + 0xC0), size * 1.5f);
    func_00282D30(m[1], m[1], size * 1.5f);
    func_00282D30(m[2], m[2], size * 1.5f);
    m[2][3] = m[1][3] = m[0][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i3 = 0; i3 < 4; i3++) {
        func_002830C0(&q.corner[i3], &D_L00_001AA310[i3], m);
    }
    func_00280B90((unsigned int)&q, 0, 0);

    {
        s32 b = func_00283CF0(func_00283CE0(D_L00_001B0B54) * k * fade * 1.5f);
        if (b >= 0x100) {
            b = 0xFF;
        }
        func_00281DE8(&q, 0x39, 1, 0x80);
        c = ((u32)(b) << 24) | 0xFFFFFF;
    }
    q.rgba[0] = c;
    q.rgba[1] = c;
    q.rgba[2] = c;
    q.rgba[3] = c;
    q.uv[0][0] = 0.0f;
    q.uv[0][1] = 0.0f;
    q.uv[1][0] = 0.0f;
    q.uv[1][1] = 1.0f;
    q.uv[2][0] = 1.0f;
    q.uv[2][1] = 0.0f;
    q.uv[3][0] = 1.0f;
    q.uv[3][1] = 1.0f;
    qcopy(p120, pos);
    if (func_00282C48(pv->ang[2]) > 0.00001f) {
        func_002AB668(rot, (f32 *)(moby + 0xC0), pv->ang[2]);
        func_002ACDE8(m[1], (f32 *)(moby + 0xD0), rot);
        func_002ACDE8(m[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(m[1], (f32 *)(moby + 0xD0));
        qcopy(m[2], (f32 *)(moby + 0xE0));
    }
    func_00282D30(m[0], (f32 *)(moby + 0xC0), size * 1.25f);
    func_00282D30(m[1], m[1], size * 1.25f);
    func_00282D30(m[2], m[2], size * 1.25f);
    m[2][3] = m[1][3] = m[0][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i4 = 0; i4 < 4; i4++) {
        func_002830C0(&q.corner[i4], &D_L00_001AA310[i4], m);
    }
    func_00280B90((unsigned int)&q, 0, 0);

    if (func_00282C48(pv->ang[3]) > 0.00001f) {
        func_002AB668(rot, (f32 *)(moby + 0xC0), pv->ang[3]);
        func_002ACDE8(m[1], (f32 *)(moby + 0xD0), rot);
        func_002ACDE8(m[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(m[1], (f32 *)(moby + 0xD0));
        qcopy(m[2], (f32 *)(moby + 0xE0));
    }
    qcopy(m[3], pos);
    func_00282D30(m[0], (f32 *)(moby + 0xC0), size);
    func_00282D30(m[1], m[1], size);
    func_00282D30(m[2], m[2], size);
    m[2][3] = m[1][3] = m[0][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i5 = 0; i5 < 4; i5++) {
        func_002830C0(&q.corner[i5], &D_L00_001AA310[i5], m);
    }
    func_00280B90((unsigned int)&q, 0, 0);

    c = x | 0xFFFFFF;
    q.rgba[0] = c;
    q.rgba[3] = c;
    q.rgba[2] = c;
    q.rgba[1] = c;
    func_00282CF0(rot, D_L00_001B8DC0, pos);
    func_00282F20(rot, rot, 0.25f);
    func_00282CC0(m[3], pos, rot);
    func_002AFFD8(p120, p130, 1);
    func_00282CF0(pF0, D_L00_001B8DC0, m[3]);
    func_00282F20(pF0, pF0, 1.0f);
    func_00282DD8(p100, pF0, p130);
    func_00282F20(p100, p100, 1.0f);
    func_00282DD8(p110, p100, pF0);

    if (func_00282C48(pv->ang[4]) > 0.00001f) {
        func_002AB668(v140, pF0, pv->ang[4]);
        func_002ACDE8(m[1], p100, v140);
        func_002ACDE8(m[2], p110, v140);
    } else {
        qcopy(m[1], p100);
        qcopy(m[2], p110);
    }
    func_00282D30(m[0], pF0, size);
    func_00282D30(m[1], m[1], size);
    func_00282D30(m[2], m[2], size);
    m[2][3] = m[1][3] = m[0][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i6 = 0; i6 < 4; i6++) {
        func_002830C0(&q.corner[i6], &D_L00_001AA310[i6], m);
    }
    func_00280B90((unsigned int)&q, 0, 0);

    if (func_00282C48(pv->ang[5]) > 0.00001f) {
        func_002AB668(v140, pF0, pv->ang[5]);
        func_002ACDE8(m[1], p100, v140);
        func_002ACDE8(m[2], p110, v140);
    } else {
        qcopy(m[1], p100);
        qcopy(m[2], p110);
    }
    func_00282D30(m[0], pF0, size * 0.75f);
    func_00282D30(m[1], m[1], size * 0.75f);
    func_00282D30(m[2], m[2], size * 0.75f);
    m[2][3] = m[1][3] = m[0][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i7 = 0; i7 < 4; i7++) {
        func_002830C0(&q.corner[i7], &D_L00_001AA310[i7], m);
    }
    func_00280B90((unsigned int)&q, 0, 0);

    t2 = ((u32)(func_00283CF0(func_00283CE0(x8) * 0.2f)) << 24);
    func_00281DE8(&q, 0x38, 1, 0x80);
    c = t2 | 0xFFFFFF;
    q.rgba[0] = c;
    q.rgba[3] = c;
    q.rgba[2] = c;
    q.rgba[1] = c;
    if (func_00282C48(pv->ang[1]) > 0.00001f) {
        func_002AB668(v140, pF0, pv->ang[1]);
        func_002ACDE8(m[1], p100, v140);
        func_002ACDE8(m[2], p110, v140);
    } else {
        qcopy(m[1], p100);
        qcopy(m[2], p110);
    }
    func_00282D30(m[0], pF0, size * 1.5f);
    func_00282D30(m[1], m[1], size * 1.5f);
    func_00282D30(m[2], m[2], size * 1.5f);
    m[2][3] = m[1][3] = m[0][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i8 = 0; i8 < 4; i8++) {
        func_002830C0(&q.corner[i8], &D_L00_001AA310[i8], m);
    }
    func_00280B90((unsigned int)&q, 0, 0);

    if (func_00282978(p36) == 0) {
        func_00279BD8(v140, pos);
        if (v140[0] >= 28492.0f && v140[0] <= 37082.0f && v140[1] >= 28492.0f && v140[1] <= 37082.0f) {
            f32 t;
            f32 r;
            f32 *s;
            f32 inv;
            f32 one;
            f32 span;
            f32 nx;
            f32 ny;
            inv = 0.000116414434f;
            one = 1.0f;
            v140[1] -= 28492.0f;
            v140[0] -= 28492.0f;
            span = 8590.0f;
            t3 = ((u32)(func_00283CF0(D_L00_001B0BA0 * ((f32)pv->t36 * pv->k38))) << 24);
            func_002ACEC0(v150, p130, dir, 0.7853982448577881f);
            func_00281DE8(&q, D_L00_001B0B88, 1, 0x80);
            t = (v140[1] < v140[0] ? v140[1] : v140[0]) * inv;
            c = t3 | D_L00_001B0B98;
            q.d70 = 5;
            r = D_L00_001B0B94 / D_L00_001B0B90;
            q.uv[3][0] = one;
            q.rgba[0] = D_L00_001B0B9C;
            q.rgba[2] = c;
            q.uv[0][0] = 0.0f;
            q.uv[0][1] = one;
            q.uv[1][0] = one;
            q.uv[1][1] = one;
            q.uv[2][0] = 0.0f;
            q.uv[2][1] = 0.0f;
            q.uv[3][1] = 0.0f;
            q.rgba[1] = D_L00_001B0B9C;
            q.rgba[3] = c;
            if (t < 0.5f) {
                v160[3] = D_L00_001B0BA4 + (D_L00_001B0BA8 - D_L00_001B0BA4) * (2.0f * t);
            } else {
                v160[3] = D_L00_001B0BA8 + (D_L00_001B0BAC - D_L00_001B0BA8) * (2.0f * (t - 0.5f));
            }
            ny = span - v140[1];
            t = (ny < v140[0] ? ny : v140[0]) * inv;
            if (t < 0.5f) {
                v160[2] = D_L00_001B0BA4 + (D_L00_001B0BA8 - D_L00_001B0BA4) * (2.0f * t);
            } else {
                v160[2] = D_L00_001B0BA8 + (D_L00_001B0BAC - D_L00_001B0BA8) * (2.0f * (t - 0.5f));
            }
            nx = span - v140[0];
            t = (ny < nx ? ny : nx) * inv;
            if (t < 0.5f) {
                v160[1] = D_L00_001B0BA4 + (D_L00_001B0BA8 - D_L00_001B0BA4) * (2.0f * t);
            } else {
                v160[1] = D_L00_001B0BA8 + (D_L00_001B0BAC - D_L00_001B0BA8) * (2.0f * (t - 0.5f));
            }
            t = (v140[1] < nx ? v140[1] : nx) * inv;
            if (t < 0.5f) {
                v160[0] = D_L00_001B0BA4 + (D_L00_001B0BA8 - D_L00_001B0BA4) * (2.0f * t);
            } else {
                v160[0] = D_L00_001B0BA8 + (D_L00_001B0BAC - D_L00_001B0BA8) * (2.0f * (t - 0.5f));
            }
            func_00282F20(v170, dir, D_L00_001B0B8C);
            s = v160;
            for (i9 = 0; i9 < 4; i9++) {
                func_00282F20(v150, v150, *s);
                func_00282DD8(v180, dir, v150);
                func_00282F20(v180, v180, D_L00_001B0B90);
                func_00282CC0(v190, D_L00_001B8DC0, v170);
                func_00282CF0(v1A0, v190, pos);
                func_00282CC0(&q.corner[0], v190, v180);
                func_00282CF0(&q.corner[1], v190, v180);
                func_00282CC0(v190, pos, v150);
                func_00282CC0(v190, v1A0, v190);
                func_00282D30(v180, v180, r);
                func_00282CC0(&q.corner[2], v190, v180);
                func_00282CF0(&q.corner[3], v190, v180);
                func_00280B90((unsigned int)&q, 0, 0);
                if (i9 < 3) {
                    func_002ACEC0(v150, v150, dir, 1.5707964897155762f);
                }
                s++;
            }
        }
    }

    if (pv->t34 != 0) {
        k = func_00283CE0(pv->t34) * pv->k3C;
        func_00281DE8(&q, 0xB, 4, 0x80);
        c = ((u32)(func_00283CF0(k * 255.0f)) << 24) | 0x808080;
        q.rgba[0] = c;
        q.rgba[1] = c;
        q.rgba[2] = c;
        q.rgba[3] = c;
        q.uv[0][0] = 0.0f;
        q.uv[0][1] = 0.0f;
        q.uv[1][0] = 0.0f;
        q.uv[1][1] = 1.0f;
        q.uv[2][0] = 1.0f;
        q.uv[2][1] = 0.0f;
        q.uv[3][0] = 1.0f;
        q.uv[3][1] = 1.0f;
        func_00282CF0(v140, pos, D_L00_001B8DC0);
        func_00282F20(v150, v140, 0.1f);
        func_00282CC0(v160, D_L00_001B8DC0, v150);
        func_00282DD8(v170, v140, p130);
        func_00282F20(v170, v170, D_L00_001B0B70);
        func_00282DD8(v180, v170, v140);
        func_00282F20(v180, v180, D_L00_001B0B70);
        func_00282CC0(v190, v160, v180);
        func_00282CC0(&q.corner[0], v190, v170);
        func_00282CF0(&q.corner[1], v190, v170);
        func_00282CF0(v190, v160, v180);
        func_00282CC0(&q.corner[2], v190, v170);
        func_00282CF0(&q.corner[3], v190, v170);
        func_00280B90((unsigned int)&q, 0, 0);
    }

    if (pv->t40 != 0 && pv->t40 <= D_L00_001B0B74) {
        f32 sz;
        k = func_00283CE0(pv->t40) * pv->k44;
        sz = D_L00_001B0B80 + (D_L00_001B0B7C - D_L00_001B0B80) * k;
        func_00282CF0(v140, pos, D_L00_001B8DC0);
        func_00282F20(v140, v140, 0.3f);
        func_00282CC0(v150, D_L00_001B8DC0, v140);
        func_00281DE8(&q, D_L00_001B0B84, 1, 0x80);
        q.d88 = (0x8000LL << 24) | 0x4A;
        c = ((u32)(func_00283CF0(k * 255.0f)) << 24) | 0x808080;
        q.rgba[0] = c;
        q.rgba[1] = c;
        q.rgba[2] = c;
        q.rgba[3] = c;
        q.uv[0][0] = 0.0f;
        q.uv[0][1] = 0.0f;
        q.uv[1][0] = 0.0f;
        q.uv[1][1] = 1.0f;
        q.uv[2][0] = 1.0f;
        q.uv[2][1] = 0.0f;
        q.uv[3][0] = 1.0f;
        q.uv[3][1] = 1.0f;
        qcopy(v160, p130);
        func_00282DD8(v170, v140, v160);
        func_00282F20(v170, v170, sz);
        func_00282DD8(v180, v170, v140);
        func_00282F20(v180, v180, sz);
        func_00282CC0(v190, v150, v180);
        func_00282CC0(&q.corner[0], v190, v170);
        func_00282CF0(&q.corner[1], v190, v170);
        func_00282CF0(v190, v150, v180);
        func_00282CC0(&q.corner[2], v190, v170);
        func_00282CF0(&q.corner[3], v190, v170);
        func_002FC560(0x47, 0x31001);
        func_00280B90((unsigned int)&q, 0, 0);
        func_002FC560(0x47, 0x33001);
        qzero(v1A0);
        for (i10 = 0; i10 < 4; i10++) {
            func_00282CC0(v1A0, v1A0, &q.corner[i10]);
        }
        func_00282D30(v1A0, v1A0, 0.25f);
        for (i11 = 0; i11 < 4; i11++) {
            func_00282CF0(v1B0, &q.corner[i11], v1A0);
            func_00282D30(v1B0, v1B0, 0.8f);
            func_00282CC0(v1B0, v1A0, v1B0);
            func_0027C768(&q.corner[i11], &q.uv[i11][0], &q.uv[i11][1]);
            if (q.uv[i11][0] > 0.9f) {
                q.uv[i11][0] = 0.9f;
            } else if (q.uv[i11][0] < 0.0f) {
                q.uv[i11][0] = 0.0f;
            }
            if (q.uv[i11][1] > 0.9f) {
                q.uv[i11][1] = 0.9f;
            } else if (q.uv[i11][1] < 0.0f) {
                q.uv[i11][1] = 0.0f;
            }
        }
        q.d78 = func_0027C878(-7);
        q.d88 = (0x8000LL << 24) | 0x54;
        q.d80 = (0xFF90LL << 32) | 0x260;
        q.d70 = 0;
        func_00280B90((unsigned int)&q, 0, 0);
    }
}
