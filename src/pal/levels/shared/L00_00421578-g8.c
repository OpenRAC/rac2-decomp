#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 pad5[0x4B];
    f32 f50;
    u8 pad54[0x1C];
    f32 f70;
    u8 pad74[0x6C];
} LevelClass;
typedef struct {
    u8 pad0[0x18];
    char *moby;
    s32 count;
    f32 pos[4];
    u8 pad30[0x10];
    f32 normal[4];
} CollResult;
typedef struct {
    f32 v[4];
    char *moby;
    s32 mask;
    s8 b18;
    s8 b19;
    u16 h1A;
    f32 f1C;
    s32 i20;
} CollQuery;
extern char D_00189E20[];
extern u8 D_00139568[];
extern u8 D_00188660[];
extern LevelClass D_L00_00262570[];
extern void *D_0018C0B0 __attribute__((nosda));
extern CollResult D_L00_001BF200 __attribute__((aligned(16)));
extern char D_L00_001B8DC0[];
extern f32 D_L00_001B1470 __attribute__((sda));
extern int func_L00_0032A088(int id, int index);
extern int *func_L00_0032A0B8(int id, int index);
extern void func_002AFFD8(void *, void *, int);
extern void func_00300190(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_002AB668(void *, void *, float);
extern void func_00283028(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern int func_00282978(void *);
extern int func_00282948(void *);
extern float func_00282C48(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002AA150(float, float, float);
extern float *func_002AB1F0(char *);
extern char *func_002AF580(void *, void *, int *, float, float, int, int, int,
                           float, float, float, int, int);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_PAL_L00_00423418(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_0032F0B8(char *, int, int);
extern char *func_PAL_L00_00421578(int, void *, int, int, int, int);
extern float func_L00_0041DEF0(char *, void *, void *);
extern void func_002FEE70(int, void *, int);
extern void func_002FEE50(int);
extern void func_0029F338(void *);
extern void func_L00_00322EC8(void *);
extern void func_L00_00322BE0(void *, int);
extern void func_002E59F8(int);
extern int func_002E59B0(void *, int);
extern void func_PAL_002AD288(void *, void *, int, float, float);
extern void ref_L00_0041CB80_00(void *, void *);
extern void func_PAL_L00_00423778(void *);
extern int func_00283D38(int, int, float);
extern void func_00283658(void *, void *);
extern void func_002AB6D8(void *, void *);

void func_PAL_L00_00421E28(char *m)
{
    f32 old[4] __attribute__((aligned(16)));
    f32 fwd[4] __attribute__((aligned(16)));
    f32 rel[4] __attribute__((aligned(16)));
    f32 npos[4] __attribute__((aligned(16)));
    f32 a[4] __attribute__((aligned(16)));
    f32 b[4] __attribute__((aligned(16)));
    CollQuery q __attribute__((aligned(16)));
    f32 c90[4] __attribute__((aligned(16)));
    f32 cA0[4] __attribute__((aligned(16)));
    f32 mat[16] __attribute__((aligned(16)));
    int found;
    char *pv;
    char *base;
    int *offs;
    char *segs;
    char *slots;
    char *flags;
    char *t;
    char *o;
    char *opv;
    float *r;
    float *tr;
    float *r1;
    float range;
    LevelClass *cls;
    int lim;
    u64 st;
    u64 st2;
    float dist;
    float ang;
    float roll;
    float spd;
    float sc;
    float glow;
    float rnd;
    int ok;
    int bad;
    int b8;
    int j1, j2, j3, j5, j6, n;
    char *se1, *se2, *e1, *e2, *p1, *p2, *hp;
    int c0;
    int c1;
    int fl;
    void *cq;

    pv = *(char **)(m + 0x68);
    base = (char *)func_L00_0032A088(*(int *)(pv + 0x50), *(int *)(pv + 0x3C));
    if (base == 0) {
        func_002FEE50(*(int *)(pv + 0x6C));
        func_0029F338(m);
        return;
    }
    offs = func_L00_0032A0B8(*(int *)(pv + 0x50), *(int *)(pv + 0x3C));
    slots = base + offs[0];
    flags = base + offs[1];
    segs = base + offs[2];
    qcopy(old, m + 0x10);
    func_002AFFD8(m + 0x10, fwd, 1);
    func_00300190(m + 0x10, m + 0x10);
    func_00300190(pv + 0x40, pv + 0x40);
    func_00282CF0(rel, pv + 0x40, &((Hero *)D_00189E20)->b[0x80]);
    func_002ACEC0(rel, rel, &((Hero *)D_00189E20)->b[0x2C0], -((Hero *)D_00189E20)->f[0x15C / 4]);
    func_00282CC0(pv + 0x40, rel, &((Hero *)D_00189E20)->b[0x80]);
    qcopy(npos, m + 0x10);
    switch (*(u8 *)(m + 0x20)) {
    case 0:
        if (func_00282978(pv + 0x10) != 0) {
            *(u8 *)(m + 0x20) = 1;
        }
        func_00282978(pv + 0x18);
        if (*(s16 *)(pv + 0x34) != 0) {
            *(s16 *)(pv + 0x34) = 0;
            r = ((Hero *)D_00189E20)->ptr[0x1450 / 4];
            if (r != 0 && *(u8 *)((char *)r + 0x20) != 0xFE && *(u8 *)((char *)r + 0x20) != 0xFD) {
                *(float **)(pv + 0x14) = r;
            } else {
                *(char **)(pv + 0x14) = func_002AF580(m + 0x10, pv, &found, 3.14159298f, 3.14159298f, 0, 0, 0,
                                                     12.0f, 3.14159298f, 3.14159298f, 1, 0);
            }
            if (*(char **)(pv + 0x14) != 0) {
                *(s16 *)(pv + 0x1A) = 0;
                *(s16 *)(pv + 0x12) = 10;
                *(s16 *)(pv + 0x18) = 0;
            }
        }
        dist = 0.0f;
        bad = 0;
        t = *(char **)(pv + 0x14);
        if (t == 0 || *(u8 *)(t + 0x20) == 0xFE || *(u8 *)(t + 0x20) == 0xFD
            || *(s16 *)(t + 0x32) == 0 || !(*(u16 *)(t + 0x34) & 0x1000)
            || ((tr = func_002AB1F0(t)) != 0 && *tr <= dist)) {
            bad = 1;
        }
        if (*(char **)(pv + 0x14) != 0 && bad == 0) {
            if (*(s16 *)(pv + 0x18) == 0) {
                r1 = func_002AB1F0(*(char **)(pv + 0x14));
                if (r1 != 0) {
                    func_00282D30(b, fwd, r1[4]);
                    func_00282CC0(a, *(char **)(pv + 0x14) + 0x10, b);
                } else {
                    qcopy(a, *(char **)(pv + 0x14) + 0x10);
                }
                dist = func_L00_0041DEF0(m, a, fwd);
            }
        } else {
            *(char **)(pv + 0x14) = 0;
            if (*(s16 *)(pv + 0x36) != 0) {
                dist = func_L00_0041DEF0(m, pv + 0x40, fwd);
                func_00282CC0(a, m + 0x10, pv);
                func_00282CF0(b, pv + 0x40, a);
                if (func_00282DB0(b, pv) < 0.0f) {
                    *(s16 *)(pv + 0x36) = 0;
                }
            }
        }
        func_002FEE70(*(int *)(pv + 0x6C), pv, 0);
        q.mask = 0x10000;
        q.moby = m;
        q.i20 = 1;
        q.f1C = (&D_L00_00262570[D_00139568[0x16]])->f70;
        qcopy(q.v, pv);
        func_00282F20(q.v, q.v, 1.0f);
        q.b18 = 1;
        q.v[3] = 5627.9248f;
        q.b19 = 1;
        q.h1A = *(u16 *)(m + 0xAA);
        func_00282CC0(m + 0x10, m + 0x10, pv);
        if (*(f32 *)(m + 0x10) < 2.0f || *(f32 *)(m + 0x10) > 1021.0f
            || *(f32 *)(m + 0x14) < 2.0f || *(f32 *)(m + 0x14) > 1021.0f
            || *(f32 *)(m + 0x18) < 2.0f || *(f32 *)(m + 0x18) > 1021.0f) {
            if (*(int *)(pv + 0x30) >= 0) {
                ((int *)flags)[*(int *)(pv + 0x30)] = 0;
                func_L00_00322EC8(slots + *(int *)(pv + 0x30) * 0x150);
                *(int *)(pv + 0x30) = -1;
            }
            if (*(int *)(pv + 0x38) != -1) {
                se1 = (char *)D_00188660 + *(int *)(pv + 0x38) * 0x70;
                if (*(char **)(se1 + 0x88) == m && *(u8 *)(se1 + 0x74) != 0) {
                    func_002E59F8(*(int *)(pv + 0x38));
                }
            }
            *(int *)(pv + 0x38) = -1;
            func_002FEE50(*(int *)(pv + 0x6C));
            func_0029F338(m);
            return;
        }
        if (*(s16 *)(pv + 0x18) != 0) {
            fl = 2;
            cq = 0;
        } else {
            cq = &q;
            fl = 0;
        }
        if (func_002761F8(npos, m + 0x10, fl | 0x10, D_0018C0B0, cq) != 0) {
            qcopy(m + 0x10, D_L00_001BF200.pos);
            func_PAL_L00_00423418(D_L00_001BF200.pos, 10, *(char **)(pv + 0x68) == 0);
            *(s16 *)(pv + 0x36) = 0;
            ok = 0;
            if (D_L00_001BF200.moby != 0) {
                ok = D_L00_001BF200.count < 1;
            }
            if (ok != 0) {
                r = func_002AB1F0(D_L00_001BF200.moby);
                if (r != 0) {
                    if (*(u8 *)((char *)r + 9) == 1) {
                        func_002E5CF8(3, 0, m);
                    } else {
                        func_002E5CF8(4, 0, m);
                    }
                } else {
                    func_002E5CF8(2, 0, m);
                }
                if (D_L00_001BF200.moby == *(char **)(pv + 0x14)) {
                    cls = &D_L00_00262570[D_00139568[0x16]];
                    range = cls->f70;
                    if (r != 0 && r[0] <= range) {
                        *(char **)(pv + 0x14) = 0;
                        *(s16 *)(pv + 0x34) = 1;
                    }
                }
                *(s16 *)(pv + 0x2C) += 1;
                lim = D_L00_00262570[D_00139568[0x16]].b4 ? 2 : 3;
                if (*(s16 *)(pv + 0x2C) >= lim) {
                    *(u8 *)(m + 0x20) = 1;
                }
                if (D_L00_00262570[D_00139568[0x16]].b4 != 0) {
                    func_PAL_0032F0B8(D_L00_001BF200.moby, 0x41, *(int *)(m + 0xB8));
                } else {
                    func_PAL_0032F0B8(D_L00_001BF200.moby, 0x16, *(int *)(m + 0xB8));
                }
            } else {
                func_002E5CF8(2, 0, m);
            }
            if (*(f32 *)(pv + 0x1C) == 1.0f && ok != 0) {
                func_00282DD8(a, pv, m + 0xE0);
                func_002ACEC0(pv, pv, a, -func_002A7878(0.17453295f, 0.610865295f));
                *(f32 *)(pv + 0x1C) = 2.0f;
            } else {
                if (ok != 0) {
                    qcopy(a, D_L00_001BF200.moby + 0xE0);
                } else {
                    func_00282D30(a, D_L00_001BF200.normal, 0.0009765625f);
                    func_00282F20(a, a, 1.0f);
                }
                func_00283028(pv, pv, a);
                func_00282D30(b, a, 0.2f);
                func_00282CC0(m + 0x10, m + 0x10, b);
                if (*(char **)(pv + 0x14) == 0) {
                    *(s16 *)(pv + 0x34) = 1;
                }
                *(f32 *)(pv + 0x1C) = 2.0f;
            }
            if (ok != 0) {
                *(s16 *)(pv + 0x18) = 8;
                *(s16 *)(pv + 0x1A) = 1;
                *(s16 *)(pv + 0x12) = 0;
                if (D_L00_00262570[D_00139568[0x16]].b4 != 0 && *(char **)(pv + 0x68) != 0) {
                    *(char **)(pv + 0x68) = 0;
                    func_002AFFD8(m + 0x10, a, 1);
                    ang = func_002A78D8(0.785398245f, 1.3962636f);
                    func_002AB668(b, a, ang);
                    func_002ACDE8(pv, pv, b);
                    o = func_PAL_L00_00421578(*(int *)(m + 0xB8), m + 0x10, 0, *(int *)(pv + 0x3C), 0, 0);
                    if (o != 0) {
                        opv = *(char **)(o + 0x68);
                        *(f32 *)(m + 0x2C) = *(f32 *)(m + 0x2C) * 0.5f;
                        *(f32 *)(o + 0x2C) = *(f32 *)(o + 0x2C) * 0.5f;
                        if (*(int *)(pv + 0x30) >= 0) {
                            e1 = slots + *(int *)(pv + 0x30) * 0x150;
                            for (j1 = 0; j1 < *(int *)(e1 + 0x148); j1++) {
                                p1 = ((char **)(e1 + 0x120))[j1];
                                if (p1 != 0) {
                                    *(f32 *)(p1 + 0x2C) = *(f32 *)(p1 + 0x2C) * 0.5f;
                                }
                            }
                        }
                        if (*(int *)(opv + 0x30) >= 0) {
                            e2 = slots + *(int *)(opv + 0x30) * 0x150;
                            for (j2 = 0; j2 < *(int *)(e2 + 0x148); j2++) {
                                p2 = ((char **)(e2 + 0x120))[j2];
                                if (p2 != 0) {
                                    *(f32 *)(p2 + 0x2C) = *(f32 *)(p2 + 0x2C) * 0.5f;
                                }
                            }
                        }
                        qcopy(o + 0x10, m + 0x10);
                        b8 = *(int *)(m + 0xB8);
                        for (j3 = 0; j3 < 3; j3++) {
                            qcopy(o + 0xC0 + j3 * 16, m + 0xC0 + j3 * 16);
                        }
                        qcopy(o + 0xF0, m + 0xF0);
                        qcopy(opv, pv);
                        *(int *)(o + 0xB8) = b8;
                        func_002AB668(b, a, -ang);
                        func_002ACDE8(opv, opv, b);
                    }
                }
            }
        }
        st = *(u32 *)(pv + 0x18);
        if (st == 0x10000) {
            if (*(char **)(pv + 0x14) == 0) {
                *(s16 *)(pv + 0x1A) = 0;
            } else {
                func_00282CF0(a, *(char **)(pv + 0x14) + 0x10, m + 0x10);
                if (func_00282DB0(pv, a) >= 0.0f) {
                    *(s16 *)(pv + 0x1A) = 0;
                }
            }
        }
        if (*(char **)(pv + 0x14) != 0 && (st2 = *(u32 *)(pv + 0x18)) == 0) {
            func_00282CF0(a, *(char **)(pv + 0x14) + 0x10, m + 0x10);
            if (func_00282DB0(pv, a) < 0.0f) {
                *(s16 *)(pv + 0x1A) = 1;
                *(s16 *)(pv + 0x18) = 8;
            }
        }
        func_00282F20(m + 0xC0, pv, 1.0f);
        func_00282DD8(m + 0xD0, m + 0xC0, fwd);
        func_00282F20(m + 0xD0, m + 0xD0, 1.0f);
        func_00282DD8(m + 0xE0, m + 0xD0, m + 0xC0);
        roll = -dist * 1.0471977f;
        if (roll == 0.0f) {
            roll = -0.069813177f;
            if (*(f32 *)(pv + 0x58) > 0.0f) {
                roll = 0.069813177f;
            }
        }
        *(f32 *)(pv + 0x58) = func_002AA150(*(f32 *)(pv + 0x58), roll, 0.05f);
        if (func_00282C48(*(f32 *)(pv + 0x58)) > 1e-05f) {
            func_002AB668(a, m + 0xC0, *(f32 *)(pv + 0x58));
            func_002ACDE8(m + 0xD0, m + 0xD0, a);
            func_002ACDE8(m + 0xE0, m + 0xE0, a);
        }
        *(f32 *)(pv + 0x28) = func_00283B98(*(f32 *)(pv + 0x28), 0.418879062f);
        if (func_00282C48(*(f32 *)(pv + 0x28)) > 1e-05f) {
            func_002AB668(a, m + 0xE0, *(f32 *)(pv + 0x28));
            func_002ACDE8(m + 0xC0, m + 0xC0, a);
            func_002ACDE8(m + 0xD0, m + 0xD0, a);
        }
        *(f32 *)(m + 0xCC) = *(f32 *)(m + 0xDC) = *(f32 *)(m + 0xEC) = 0.0f;
        spd = (&D_L00_00262570[D_00139568[0x16]])->f50 * 0.020000001f;
        func_00282F20(pv, pv, spd + (0.3f - spd) * dist);
        if (*(int *)(pv + 0x30) >= 0) {
            for (n = *(int *)(pv + 0x54) - 1; n > 0; n--) {
                hp = (char *)(n * 16 + ((int *)base)[*(int *)(pv + 0x30)]);
                qcopy(hp, hp - 16);
                func_00300190(hp, hp);
            }
            qcopy(((char **)base)[*(int *)(pv + 0x30)], npos);
            if (*(int *)(pv + 0x54) < 40) {
                *(int *)(pv + 0x54) += 1;
            }
            if (func_00282948(pv + 0x60) != 0) {
                sc = 0.5f;
                if (*(char **)(pv + 0x68) == 0) {
                    sc = 0.25f;
                }
                func_00282CF0(a, m + 0x10, D_L00_001B8DC0);
                func_00282DD8(b, a, m + 0xE0);
                func_00282F20(b, b, sc);
                func_00282CF0(((char **)segs)[*(int *)(pv + 0x30)], m + 0x10, b);
                rnd = func_002A78D8(0.0f, 0.1f);
                func_00282D30(c90, m + 0xE0, rnd);
                func_00282CC0(((char **)segs)[*(int *)(pv + 0x30)], ((char **)segs)[*(int *)(pv + 0x30)], c90);
                func_00282CC0(((char **)segs)[*(int *)(pv + 0x30)] + 0x60, m + 0x10, b);
                func_00282D30(c90, m + 0xE0, rnd);
                func_00282CC0(((char **)segs)[*(int *)(pv + 0x30)] + 0x60, ((char **)segs)[*(int *)(pv + 0x30)] + 0x60, c90);
                func_00282D30(cA0, b, 0.666f);
                func_00282CF0(((char **)segs)[*(int *)(pv + 0x30)] + 0x10, m + 0x10, cA0);
                rnd = rnd + func_002A78D8(0.0f, 0.1f);
                func_00282D30(c90, m + 0xE0, rnd);
                func_00282CC0(((char **)segs)[*(int *)(pv + 0x30)] + 0x10, ((char **)segs)[*(int *)(pv + 0x30)] + 0x10, c90);
                func_00282D30(cA0, b, 0.666f);
                func_00282CC0(((char **)segs)[*(int *)(pv + 0x30)] + 0x50, m + 0x10, cA0);
                func_00282D30(c90, m + 0xE0, rnd);
                func_00282CC0(((char **)segs)[*(int *)(pv + 0x30)] + 0x50, ((char **)segs)[*(int *)(pv + 0x30)] + 0x50, c90);
                func_00282D30(cA0, b, 0.333f);
                func_00282CF0(((char **)segs)[*(int *)(pv + 0x30)] + 0x20, m + 0x10, cA0);
                rnd = rnd + func_002A78D8(0.0f, 0.1f);
                func_00282D30(c90, m + 0xE0, rnd);
                func_00282CC0(((char **)segs)[*(int *)(pv + 0x30)] + 0x20, ((char **)segs)[*(int *)(pv + 0x30)] + 0x20, c90);
                func_00282D30(cA0, b, 0.333f);
                func_00282CC0(((char **)segs)[*(int *)(pv + 0x30)] + 0x40, m + 0x10, cA0);
                func_00282D30(c90, m + 0xE0, rnd);
                func_00282CC0(((char **)segs)[*(int *)(pv + 0x30)] + 0x40, ((char **)segs)[*(int *)(pv + 0x30)] + 0x40, c90);
                qcopy(((char **)segs)[*(int *)(pv + 0x30)] + 0x30, m + 0x10);
                func_00282D30(c90, m + 0xE0, rnd + func_002A78D8(0.0f, 0.1f));
                func_00282CC0(((char **)segs)[*(int *)(pv + 0x30)] + 0x30, ((char **)segs)[*(int *)(pv + 0x30)] + 0x30, c90);
                for (j5 = 0; j5 < 7; j5++) {
                    *(f32 *)(((char **)segs)[*(int *)(pv + 0x30)] + j5 * 16 + 0xC) = 0.15f;
                }
                *(int *)(pv + 0x60) = 3;
            } else {
                for (j6 = 0; j6 < 7; j6++) {
                    func_00282CF0(c90, old, ((char **)segs)[*(int *)(pv + 0x30)] + j6 * 16);
                    func_00282CC0(((char **)segs)[*(int *)(pv + 0x30)] + j6 * 16, c90, m + 0x10);
                    *(f32 *)(((char **)segs)[*(int *)(pv + 0x30)] + j6 * 16 + 0xC) = 0.15f;
                }
            }
            ref_L00_0041CB80_00(func_PAL_L00_00423778, m);
        }
        *(f32 *)(pv + 0x64) = func_00283B98(*(f32 *)(pv + 0x64), D_L00_001B1470 * 0.0003490659f);
        glow = func_00283198(*(f32 *)(pv + 0x64)) * 0.5f + 0.5f;
        if (D_L00_00262570[D_00139568[0x16]].b4 != 0) {
            if (*(char **)(pv + 0x68) != 0) {
                c0 = 0xFF0A0A;
                c1 = 0xFF7F7F;
            } else {
                c0 = 0xFF7FFF;
                c1 = 0xFF7FFF;
            }
        } else {
            c0 = 0x0A0AFF;
            c1 = 0x7F7FFF;
        }
        *(u32 *)(m + 0x78) = func_00283D38(c0, c1, glow) | 0xFF000000;
        if (*(int *)(pv + 0x30) >= 0) {
            func_00283658(mat, m + 0xC0);
            func_002AB6D8(mat, m + 0xF0);
            func_L00_00322BE0(slots + *(int *)(pv + 0x30) * 0x150, 0);
        }
        if (func_002E59B0(m, *(int *)(pv + 0x38)) == 0) {
            *(int *)(pv + 0x38) = func_002E5CF8(1, 4, m);
        }
        break;
    case 1:
        if (*(int *)(pv + 0x30) >= 0) {
            ((int *)flags)[*(int *)(pv + 0x30)] = 0;
            func_L00_00322EC8(slots + *(int *)(pv + 0x30) * 0x150);
            *(int *)(pv + 0x30) = -1;
        }
        if (*(int *)(pv + 0x38) != -1) {
            se2 = (char *)D_00188660 + *(int *)(pv + 0x38) * 0x70;
            if (*(char **)(se2 + 0x88) == m && *(u8 *)(se2 + 0x74) != 0) {
                func_002E59F8(*(int *)(pv + 0x38));
            }
        }
        *(int *)(pv + 0x38) = -1;
        func_PAL_002AD288(m, m + 0x10, -1, 0.5f, 5.0f);
        func_002FEE50(*(int *)(pv + 0x6C));
        func_0029F338(m);
        break;
    }
}
