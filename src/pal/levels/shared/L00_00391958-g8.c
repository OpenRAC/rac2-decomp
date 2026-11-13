/* func_PAL_L00_00391958: the PAL copy of func_L00_0038E880 (L00_0038E880-g8.c), the impact
 * burst (shards, splash, ring and sparks), with its frame counts and per-frame rates for 50 Hz.
 * The v1.01 notes:
 * Spill slots follow gcse's PRE hash-bucket order, S = (insns at gcse / 2) | 1;
 * retail's order of the &random/&shard reaching registers (0xC8/0xCC) needs
 * S = 253. The set-once constant locals and per-site copies of object, data,
 * normal, velocity, scale, height and the colour channels each add one insn at
 * gcse and leave the final code unchanged (cprop folds them).
 */
#include "common.h"
typedef int BurstQuad __attribute__((mode(TI)));
typedef union { BurstQuad q; float f[4]; } BurstVector;
typedef struct { BurstQuad q[5]; } BurstTemplate __attribute__((aligned(16)));
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xDB]; } BurstWeapon;
typedef struct { char pad[0x160]; float shake; int unused; int duration, timer; } BurstCamera;
typedef struct { char pad[0x2C]; unsigned char *texture; } BurstParticles;

extern BurstTemplate D_L00_002A26A0;
extern unsigned char D_00139568[];
extern BurstWeapon D_L00_00262570[];
extern char D_L00_001B8DC0[];
extern BurstCamera D_L00_001B8C80;
extern BurstParticles D_L00_001FE940;
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void *func_00308600(void *, void *, int, int, int);
extern float func_002A90F8(char *, char *);
extern void *func_002BF728(char *, char *, float, float);
extern int func_002E5DA0(int, int, void *, int);
extern float func_002A89A8(void *, int, float);
extern float func_002A8A20(void *);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void *func_L00_0033AA40(void *, void *, unsigned int, float, float, int, float, int, int);
extern int func_L00_0031C998(int, int, float);
extern void *func_002BCB00(void *, void *, int, int, float, int, int, int, int, int);
extern void *func_00312B70(void *, void *, int, void *);
extern void func_0029F338(void *);

void func_PAL_L00_00391958(char *object, BurstVector *velocity, BurstVector *normal)
{
    int *data = *(int **)(object + 0x68);
    BurstTemplate tmpl;
    BurstVector delta, projected, shard, random, drift, point;
    float scale, distance, height, ground;
    int c;
    BurstWeapon *w;
    char *pa, *pb, *pc, *pd, *pe, *pf;
    int *pg;
    int kind, z1, z2;

    tmpl = D_L00_002A26A0;
    scale = 1.0f + func_00283CE0(((BurstWeapon *)(D_00139568[12] * 224 + (int)D_L00_00262570))->enabled != 0);
    func_00282D30(velocity, velocity, scale);
    func_00282CF0(&delta, D_L00_001B8DC0, object + 0x10);
    distance = func_00282DF0(&delta);
    pa = object;
    pb = object;
    pc = object;
    {
        int i;
        int lo = 50, hi = 100, none = 0;
        BurstVector *n1 = normal, *n2 = normal, *n3 = normal, *v1 = velocity;
        char *o1 = object;
        float s1 = scale;
        for (i = 9; i >= 0; --i) {
            int lifetime;
            random.q = 0;
            random.f[0] = func_002A7878(-1.0f, 1.0f);
            random.f[1] = func_002A7878(-1.0f, 1.0f);
            shard.q = random.q;
            func_00282F20(&projected, n1, func_00282DB0(&shard, n2));
            func_00282CF0(&shard, &shard, &projected);
            func_00282F20(&projected, n3, func_002A7878(0.0f, 1.0f));
            func_00282CC0(&shard, &shard, &projected);
            func_00282F20(&shard, &shard, s1 * func_002A7878(3.5f, 6.5f) * 0.020000001f);
            func_00282CC0(&shard, &shard, v1);
            lifetime = func_002A7820(lo, hi);
            w = &D_L00_00262570[D_00139568[12]];
            func_00308600(o1 + 0x10, &shard, lifetime, none,
            w->enabled != 0);
        }
    }
    *(float *)(pa + 0x18) += 1.0f;
    height = func_002A90F8(pc + 0x10, (char *)&shard);
    *(float *)(pb + 0x18) -= 1.0f;
    pd = object;
    pe = object;
    pf = object;
    pg = data;
    kind = 22;
    z1 = 0;
    z2 = 0;
    {
        int i;
        char *o2 = object;
        float h2 = height, s2 = scale;
        for (i = 149; i >= 0; --i) {
            drift.q = 0;
            drift.f[0] = func_002A7878(-1.0f, 1.0f);
            drift.f[1] = func_002A7878(-1.0f, 1.0f);
            drift.f[2] = func_002A7878(-0.5f, 2.0f);
            random.q = drift.q;
            func_00282F20(&random, &random, s2 * func_002A7878(0.080000006f, 0.16000001f));
            func_002BF728(o2 + 0x10, (char *)&random, func_002A7878(0.05f, 0.1f) * 210000.0f, h2);
        }
    }
    pg[0] = 0;
    pd[0xBC] = 0;
    func_002E5DA0(kind, z1, pe, z2);
    {
    short cr = 0x60;
    short cg = 0x60;
    short cb = 0x7F;
    int delay = 0;

    random.q = *(BurstQuad *)(pf + 0x10);
    random.f[2] += 3.5f;
    height = func_002A89A8(&random, 0, 0.5f);
    ground = func_002A8A20(&random);
    if (height != ground && height - ground < 1.2f) {
        {
            int i;
            int count = 100, alpha = 0x16, on = 1;
            char *o3 = object;
            float h3 = height, h4 = height;
            short b1 = cb, b2 = cb, g1 = cg, g2 = cg, r1 = cr, r2 = cr;
            for (i = 0; i < count; i++) {
                float radius, angle, half;
                int c1, c2;
                point.q = 0;
                point.f[0] = func_002A7878(-0.015000001f, 0.015000001f);
                point.f[1] = func_002A7878(-0.015000001f, 0.015000001f);
                point.f[2] = func_002A7878(0.080000006f, 0.28000003f);
                drift.q = point.q;
                radius = func_002A7878(0.0f, 0.35f);
                half = 0.5f;
                angle = func_002A7940();
                point.f[0] = func_00283180(angle) * radius;
                point.f[1] = func_00283198(angle) * radius;
                point.f[2] = 0.0f;
                func_00282CC0(&point, &point, o3 + 0x10);
                radius *= 0.16000001f;
                point.f[2] = h3 + half;
                drift.f[2] -= radius;
                c1 = (alpha << 24) | (b1 << 16) | (g1 << 8);
                c2 = (b2 << 16) | (g2 << 8);
                func_L00_0033AA40(&point, &drift, delay, func_002A7878(0.25f, 1.0f), h4,
                c1 | r1, 0.008f, c2 | r2, on);
            }
        }
        c = (0x7F << 24) | (cb << 16) | (cg << 8);
        {
            int i;
            int count = 20, full = 0x7F000000, black = 0, lmin = 75, lmax = 125, one = 1, ntex = -1, zero = 0;
            char *o4 = object;
            int c4 = c;
            short r3 = cr;
            float h5 = height;
            for (i = 0; i < count; i++) {
                int color1, color2;
                float life;
                color1 = func_L00_0031C998(full, c4 | r3, func_002A7878(0.25f, 1.0f));
                color2 = func_L00_0031C998(black, ((cb / 2) << 16) | ((cg / 2) << 8) | (cr / 2), func_002A7878(0.5f, 1.0f));
                point.f[0] = func_002A7878(-3.0f, 3.0f);
                point.f[1] = func_002A7878(-3.0f, 3.0f);
                point.f[2] = func_002A7878(0.080000006f, 0.28000003f);
                func_00282F20(&point, &point, func_002A7878(1.5f, 3.0f) * 0.020000001f);
                point.f[2] = func_002A7878(3.0f, 6.0f) * 0.020000001f;
                drift.q = *(BurstQuad *)(o4 + 0x10);
                drift.f[2] = h5;
                life = func_002A7878(31500.001953125f, 52500.0f);
                func_002BCB00(&drift, &point, color1, color2, life, func_002A7820(lmin, lmax),
                one, *D_L00_001FE940.texture, ntex, zero);
            }
        }
    }
    }
    {
        BurstCamera *camera = &D_L00_001B8C80;
        if (distance < 20.0f)
            camera->shake = 0.4f - distance * 0.0175f;
        else
            camera->shake = 0.050000011920928955f;
    }
    D_L00_001B8C80.duration = 21;
    D_L00_001B8C80.timer = 0;
    func_00312B70(&tmpl, object + 0x10, 0, 0);
    func_0029F338(object);
}
