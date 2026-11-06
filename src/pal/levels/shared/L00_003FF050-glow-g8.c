/* func_PAL_L00_003FF050, the PAL copy of func_L00_003FA858: the same C, where the pvar 0x40 limit is scaled to 50 Hz. */
#include "common.h"

typedef float V4[4] __attribute__((aligned(16)));
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    TI128 corner[4];
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
extern TI128 D_L00_001AA310[];
extern char D_L00_001B8DC0[];

extern void func_00279BD8(void *, void *);
extern void func_0027C768(void *, void *, void *);
extern u64 func_0027C878(int);
extern void func_00280B90(void *, int, int);
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

/* result, packed, x and y start at zero: flow deletes those stores, but gcse counts them. They take the unit to 1450
 * RTL insns and 725 hash buckets, the first size at which sp+0x54 takes a lower PRE register than sp+0x1B0 and the
 * spill slots from 0x1C0 on keep their order. The first of the two then gets $s4, as in retail. */
static __inline__ s32 to_int(f32 value)
{
    s32 result = 0;
    result = func_00283CF0(value);
    return result;
}

static __inline__ u32 pack_alpha(s32 value)
{
    u32 packed = 0;
    packed = (u32)value << 24;
    return packed;
}

/* Width of one flare edge. */
static __inline__ void set_edge(f32 *v, s32 i, f32 t, f32 half)
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    if (t < half) {
        y = 2.0f * t;
        v[i] = D_L00_001B0BA4 + (D_L00_001B0BA8 - D_L00_001B0BA4) * y;
    } else {
        x = 2.0f * (t - half);
        v[i] = D_L00_001B0BA8 + (D_L00_001B0BAC - D_L00_001B0BA8) * x;
    }
}

/* Draws a moby's glow: eight camera-facing quads, the screen-edge flare set, then the pvars 0x34 and 0x40 quads.
 * moby is a late copy of the argument, so it has a high pseudo: moby + 0xC0 hashes after the frame addresses and
 * takes the last spill slot. It has to stay the first assignment in the function, or cprop folds it back. */
void func_PAL_L00_003FF050(u8 *self)
{
    Quad q;
    V4 m[4];
    V4 dir;
    V4 rot;
    V4 basis[5];
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
    f32 scale;
    f32 k;
    s32 c;
    s32 t2;
    s32 b;
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
    f32 t;
    f32 least;
    f32 *s;
    f32 inv;
    f32 one;
    f32 span;
    f32 nx;
    f32 ny;
    s32 alpha;
    u8 *moby = self;

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
    a = func_00283CE0(pv->t1C) * pv->k20;
    size = D_L00_001B0A9C + (D_L00_001B0A98 - D_L00_001B0A9C) * a;
    if (pv->t1C < pv->n28) {
        k = func_00283CE0(pv->t1C) * pv->k2C;
        a = func_00283CE0(D_L00_001B0AA8) * k;
    } else {
        a = func_00283CE0(D_L00_001B0AA8);
    }
    a *= dot;
    /* A scheduling barrier: the shift stays ahead of the next call's argument load. */
    do {
        alpha = to_int(a * dot) << 24;
    } while (0);

    if (func_00282C48(pv->ang[0]) > 0.00001f) {
        func_002AB668(rot, (f32 *)(moby + 0xC0), pv->ang[0]);
        func_002ACDE8(m[1], (f32 *)(moby + 0xD0), rot);
        func_002ACDE8(m[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(m[1], (f32 *)(moby + 0xD0));
        qcopy(m[2], (f32 *)(moby + 0xE0));
    }
    qcopy(m[3], (f32 *)(moby + 0x10));
    func_00282D30(m[0], (f32 *)(moby + 0xC0), size);
    func_00282D30(m[1], m[1], size);
    func_00282D30(m[2], m[2], size);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    func_00281DE8(&q, 0x38, 1, 0x80);
    c = alpha | D_L00_001B0AA4;
    q.rgba[0] = q.rgba[1] = q.rgba[2] = q.rgba[3] = c;
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
    func_00280B90(&q, 0, 0);

    if (func_00282C48(pv->ang[0]) > 0.00001f) {
        func_002AB668(rot, (f32 *)(moby + 0xC0), -pv->ang[0]);
        func_002ACDE8(m[1], (f32 *)(moby + 0xD0), rot);
        func_002ACDE8(m[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(m[1], (f32 *)(moby + 0xD0));
        qcopy(m[2], (f32 *)(moby + 0xE0));
    }
    qcopy(m[3], (f32 *)(moby + 0x10));
    func_00282D30(m[0], (f32 *)(moby + 0xC0), size);
    func_00282D30(m[1], m[1], size);
    func_00282D30(m[2], m[2], size);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i2 = 0; i2 < 4; i2++) {
        func_002830C0(&q.corner[i2], &D_L00_001AA310[i2], m);
    }
    func_00280B90(&q, 0, 0);

    a = func_00283CE0(pv->t1E) * pv->k24;
    size = D_L00_001B0B5C + (D_L00_001B0B58 - D_L00_001B0B5C) * a;
    if (pv->t1E < pv->n2A) {
        a = func_00283CE0(pv->t1E) * pv->k30;
        k = func_002A7AA8(1.0f, 0.0f, 1.0f, 2.0f, a);
    } else {
        k = 1.0f;
    }
    alpha = to_int(func_00283CE0(D_L00_001B0B54) * k * fade);
    a = func_00283CE0(alpha) * 0.2f;
    alpha = pack_alpha(alpha);
    b = pack_alpha(to_int(a));
    q.rgba[0] = q.rgba[1] = q.rgba[2] = q.rgba[3] = b | 0xFFFFFF;
    if (func_00282C48(pv->ang[1]) > 0.00001f) {
        func_002AB668(rot, (f32 *)(moby + 0xC0), pv->ang[1]);
        func_002ACDE8(m[1], (f32 *)(moby + 0xD0), rot);
        func_002ACDE8(m[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(m[1], (f32 *)(moby + 0xD0));
        qcopy(m[2], (f32 *)(moby + 0xE0));
    }
    scale = size * 1.5f;
    func_00282D30(m[0], (f32 *)(moby + 0xC0), scale);
    func_00282D30(m[1], m[1], scale);
    func_00282D30(m[2], m[2], scale);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i3 = 0; i3 < 4; i3++) {
        func_002830C0(&q.corner[i3], &D_L00_001AA310[i3], m);
    }
    func_00280B90(&q, 0, 0);

    {
        b = func_00283CF0(func_00283CE0(D_L00_001B0B54) * k * fade * 1.5f);
        if (b >= 0x100) {
            b = 0xFF;
        }
        func_00281DE8(&q, 0x39, 1, 0x80);
        q.rgba[0] = q.rgba[1] = q.rgba[2] = q.rgba[3] = pack_alpha(b) | 0xFFFFFF;
    }
    q.uv[0][0] = 0.0f;
    q.uv[0][1] = 0.0f;
    q.uv[1][0] = 0.0f;
    q.uv[1][1] = 1.0f;
    q.uv[2][0] = 1.0f;
    q.uv[2][1] = 0.0f;
    q.uv[3][0] = 1.0f;
    q.uv[3][1] = 1.0f;
    qcopy(basis[3], (f32 *)(moby + 0x10));
    if (func_00282C48(pv->ang[2]) > 0.00001f) {
        func_002AB668(rot, (f32 *)(moby + 0xC0), pv->ang[2]);
        func_002ACDE8(m[1], (f32 *)(moby + 0xD0), rot);
        func_002ACDE8(m[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(m[1], (f32 *)(moby + 0xD0));
        qcopy(m[2], (f32 *)(moby + 0xE0));
    }
    scale = size * 1.25f;
    func_00282D30(m[0], (f32 *)(moby + 0xC0), scale);
    func_00282D30(m[1], m[1], scale);
    func_00282D30(m[2], m[2], scale);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i4 = 0; i4 < 4; i4++) {
        func_002830C0(&q.corner[i4], &D_L00_001AA310[i4], m);
    }
    func_00280B90(&q, 0, 0);

    if (func_00282C48(pv->ang[3]) > 0.00001f) {
        func_002AB668(rot, (f32 *)(moby + 0xC0), pv->ang[3]);
        func_002ACDE8(m[1], (f32 *)(moby + 0xD0), rot);
        func_002ACDE8(m[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(m[1], (f32 *)(moby + 0xD0));
        qcopy(m[2], (f32 *)(moby + 0xE0));
    }
    qcopy(m[3], (f32 *)(moby + 0x10));
    func_00282D30(m[0], (f32 *)(moby + 0xC0), size);
    func_00282D30(m[1], m[1], size);
    func_00282D30(m[2], m[2], size);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i5 = 0; i5 < 4; i5++) {
        func_002830C0(&q.corner[i5], &D_L00_001AA310[i5], m);
    }
    func_00280B90(&q, 0, 0);

    c = alpha | 0xFFFFFF;
    q.rgba[0] = q.rgba[1] = q.rgba[2] = q.rgba[3] = c;
    func_00282CF0(rot, D_L00_001B8DC0, (f32 *)(moby + 0x10));
    func_00282F20(rot, rot, 0.25f);
    func_00282CC0(m[3], (f32 *)(moby + 0x10), rot);
    func_002AFFD8(basis[3], basis[4], 1);
    func_00282CF0(basis[0], D_L00_001B8DC0, m[3]);
    func_00282F20(basis[0], basis[0], 1.0f);
    func_00282DD8(basis[1], basis[0], basis[4]);
    func_00282F20(basis[1], basis[1], 1.0f);
    func_00282DD8(basis[2], basis[1], basis[0]);

    if (func_00282C48(pv->ang[4]) > 0.00001f) {
        func_002AB668(v140, basis[0], pv->ang[4]);
        func_002ACDE8(m[1], basis[1], v140);
        func_002ACDE8(m[2], basis[2], v140);
    } else {
        qcopy(m[1], basis[1]);
        qcopy(m[2], basis[2]);
    }
    func_00282D30(m[0], basis[0], size);
    func_00282D30(m[1], m[1], size);
    func_00282D30(m[2], m[2], size);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i6 = 0; i6 < 4; i6++) {
        func_002830C0(&q.corner[i6], &D_L00_001AA310[i6], m);
    }
    func_00280B90(&q, 0, 0);

    if (func_00282C48(pv->ang[5]) > 0.00001f) {
        func_002AB668(v140, basis[0], pv->ang[5]);
        func_002ACDE8(m[1], basis[1], v140);
        func_002ACDE8(m[2], basis[2], v140);
    } else {
        qcopy(m[1], basis[1]);
        qcopy(m[2], basis[2]);
    }
    scale = size * 0.75f;
    func_00282D30(m[0], basis[0], scale);
    func_00282D30(m[1], m[1], scale);
    func_00282D30(m[2], m[2], scale);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i7 = 0; i7 < 4; i7++) {
        func_002830C0(&q.corner[i7], &D_L00_001AA310[i7], m);
    }
    func_00280B90(&q, 0, 0);

    t2 = pack_alpha(to_int(func_00283CE0((u8)(alpha >> 24)) * 0.2f));
    func_00281DE8(&q, 0x38, 1, 0x80);
    c = t2 | 0xFFFFFF;
    q.rgba[0] = q.rgba[1] = q.rgba[2] = q.rgba[3] = c;
    if (func_00282C48(pv->ang[1]) > 0.00001f) {
        func_002AB668(v140, basis[0], pv->ang[1]);
        func_002ACDE8(m[1], basis[1], v140);
        func_002ACDE8(m[2], basis[2], v140);
    } else {
        qcopy(m[1], basis[1]);
        qcopy(m[2], basis[2]);
    }
    scale = size * 1.5f;
    func_00282D30(m[0], basis[0], scale);
    func_00282D30(m[1], m[1], scale);
    func_00282D30(m[2], m[2], scale);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    for (i8 = 0; i8 < 4; i8++) {
        func_002830C0(&q.corner[i8], &D_L00_001AA310[i8], m);
    }
    func_00280B90(&q, 0, 0);

    if (func_00282978(&pv->t36) == 0) {
        func_00279BD8(v140, (f32 *)(moby + 0x10));
        if (v140[0] >= 28492.0f && v140[0] <= 37082.0f && v140[1] >= 28492.0f && v140[1] <= 37082.0f) {
            f32 h;
            inv = 0.000116414434f;
            one = 1.0f;
            v140[0] -= 28492.0f;
            v140[1] -= 28492.0f;
            span = 8590.0f;
            k = (f32)pv->t36 * pv->k38;
            alpha = pack_alpha(to_int(D_L00_001B0BA0 * k));
            func_002ACEC0(v150, basis[4], dir, 0.78539824f);
            func_00281DE8(&q, D_L00_001B0B88, 1, 0x80);
            least = v140[1] <= v140[0] ? v140[1] : v140[0];
            t = least * inv;
            c = alpha | D_L00_001B0B98;
            q.d70 = 5;
            k = D_L00_001B0B94 / D_L00_001B0B90;
            q.uv[0][0] = 0.0f;
            q.uv[0][1] = one;
            q.uv[1][0] = one;
            q.uv[1][1] = one;
            q.uv[2][0] = 0.0f;
            q.uv[2][1] = 0.0f;
            q.uv[3][0] = one;
            q.uv[3][1] = 0.0f;
            q.rgba[0] = q.rgba[1] = D_L00_001B0B9C;
            q.rgba[2] = q.rgba[3] = c;
            h = 0.5f;
            set_edge(v160, 3, t, h);
            ny = span - v140[1];
            least = ny <= v140[0] ? ny : v140[0];
            t = least * inv;
            h = 0.5f;
            set_edge(v160, 2, t, h);
            nx = span - v140[0];
            least = ny <= nx ? ny : nx;
            t = least * inv;
            set_edge(v160, 1, t, 0.5f);
            least = v140[1] <= nx ? v140[1] : nx;
            t = least * inv;
            set_edge(v160, 0, t, 0.5f);
            func_00282F20(v170, dir, D_L00_001B0B8C);
            s = v160;
            for (i9 = 0; i9 < 4; i9++) {
                func_00282F20(v150, v150, *s);
                func_00282DD8(v180, dir, v150);
                func_00282F20(v180, v180, D_L00_001B0B90);
                func_00282CC0(v190, D_L00_001B8DC0, v170);
                func_00282CF0(v1A0, v190, (f32 *)(moby + 0x10));
                func_00282CC0(&q.corner[0], v190, v180);
                func_00282CF0(&q.corner[1], v190, v180);
                func_00282CC0(v190, (f32 *)(moby + 0x10), v150);
                func_00282CC0(v190, v1A0, v190);
                func_00282D30(v180, v180, k);
                func_00282CC0(&q.corner[2], v190, v180);
                func_00282CF0(&q.corner[3], v190, v180);
                func_00280B90(&q, 0, 0);
                if (i9 < 3) {
                    func_002ACEC0(v150, v150, dir, 1.5707965f);
                }
                s++;
            }
        }
    }

    if (pv->t34 != 0) {
        k = func_00283CE0(pv->t34) * pv->k3C;
        func_00281DE8(&q, 0xB, 4, 0x80);
        c = pack_alpha(to_int(k * 255.0f)) | 0x808080;
        q.rgba[0] = q.rgba[1] = q.rgba[2] = q.rgba[3] = c;
        q.uv[0][0] = 0.0f;
        q.uv[0][1] = 0.0f;
        q.uv[1][0] = 0.0f;
        q.uv[1][1] = 1.0f;
        q.uv[2][0] = 1.0f;
        q.uv[2][1] = 0.0f;
        q.uv[3][0] = 1.0f;
        q.uv[3][1] = 1.0f;
        func_00282CF0(v140, (f32 *)(moby + 0x10), D_L00_001B8DC0);
        func_00282F20(v150, v140, 0.1f);
        func_00282CC0(v160, D_L00_001B8DC0, v150);
        func_00282DD8(v170, v140, basis[4]);
        func_00282F20(v170, v170, D_L00_001B0B70);
        func_00282DD8(v180, v170, v140);
        func_00282F20(v180, v180, D_L00_001B0B70);
        func_00282CC0(v190, v160, v180);
        func_00282CC0(&q.corner[0], v190, v170);
        func_00282CF0(&q.corner[1], v190, v170);
        func_00282CF0(v190, v160, v180);
        func_00282CC0(&q.corner[2], v190, v170);
        func_00282CF0(&q.corner[3], v190, v170);
        func_00280B90(&q, 0, 0);
    }

    if (pv->t40 != 0 && pv->t40 <= (((int)(D_L00_001B0B74) * 5 + 2) / 6)) {
        f32 sz;
        k = func_00283CE0(pv->t40) * pv->k44;
        sz = D_L00_001B0B80 + (D_L00_001B0B7C - D_L00_001B0B80) * k;
        func_00282CF0(v140, (f32 *)(moby + 0x10), D_L00_001B8DC0);
        func_00282F20(v140, v140, 0.3f);
        func_00282CC0(v150, D_L00_001B8DC0, v140);
        func_00281DE8(&q, D_L00_001B0B84, 1, 0x80);
        q.d88 = (0x8000LL << 24) | 0x4A;
        c = pack_alpha(to_int(k * 255.0f)) | 0x808080;
        q.rgba[0] = q.rgba[1] = q.rgba[2] = q.rgba[3] = c;
        q.uv[0][0] = 0.0f;
        q.uv[0][1] = 0.0f;
        q.uv[1][0] = 0.0f;
        q.uv[1][1] = 1.0f;
        q.uv[2][0] = 1.0f;
        q.uv[2][1] = 0.0f;
        q.uv[3][0] = 1.0f;
        q.uv[3][1] = 1.0f;
        qcopy(v160, basis[4]);
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
        func_00280B90(&q, 0, 0);
        func_002FC560(0x47, 0x33001);
        qzero_nc(v1A0);
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
        q.d80 = (0xFF90LL << 32) | 0x260;
        q.d88 = (0x8000LL << 24) | 0x54;
        q.d70 = 0;
        func_00280B90(&q, 0, 0);
    }
}
