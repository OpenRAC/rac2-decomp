/* 1 November 2026 (closer a3): 93 words, 1944/1952 with a pointer local for the second table read (no madd). The
 * colours: `int r = 96;` as the only variable with literal g, b, a gives retail's first loop exactly (hoisted
 * 0x167F6000 and 0x7F6000, ori 0x60 in the body), 1932 bytes until the rest fits. Retail's second loop: 0x7F006000 and
 * 0x7F0000 rematerialised and or'd into spill slot 0xC4, then ori 0x60; 0x30 and 0x3F3000 hoisted (BurstColor's
 * grouping). fp = 0 before the first loop has no use in the output: reload_cse may have dropped it. height + half stays
 * in the loop in retail (threshold). Texture base stays in the loop too. Unsolved: the second colour's two parts. */
/* 1 November 2026: with compiler/block-move-quad, tmpl = D_L00_002A26A0 gives retail's lq/sq copy and the
 * prologue: 1944/1952, 105 aligned words (ld/sd and 386 words without that compiler). Left: a madd at the
 * second table read (retail: mult, addu of the low part, lbu 4), the TI zero's register (t1, a1 in retail),
 * the tail lq in t1 (retail's %hi is live in t0 there), the spill slots 0xC4/0xCC. Needs that compiler. */
/* GPT-6.1 Sol high, v1294, USA v1.01, default game -O2 -G0 -ffunction-sections.
 * Reconstructed candidate: 1952 compiled bytes / 1952 retail bytes, 0/27 places.
 * Size equality only: check.py first reports instruction mismatch at +0x14.
 * All declarations needed to compile this standalone unit are included below.
 *
 * This replaces the old inspection-only note with the complete four-loop body.
 * The six alleged unsupported MMI words are ordinary por zero materializations;
 * neither they nor the aligned transfers establish handwritten-assembly evidence.
 *
 * Remaining constraints:
 * - Retail's 80-byte aggregate copy uses paired lq/sq with t0/t1. Plain aggregate
 *   assignment, including an explicitly aligned(16) type, used ld/sd instead.
 *   The retained explicit quadword loop recovers its operations and iteration
 *   count, but uses v0/v1, another end register, and a different store schedule.
 * - The incoming velocity and first counter occupy s6/s5 rather than s5/s6.
 *   Distinct loop scopes recover the other incoming normal/object registers;
 *   moving only the first counter to function scope leaves the output unchanged.
 * - Retail keeps height + 0.5 inside the 100-particle loop; a named half constant
 *   hoists the sum here. Literal 0.5 instead gave 1948 bytes, with fewer saved FPRs.
 * - Color-channel locals expose partial packing and loop invariants, but their
 *   shared subexpressions differ. Literal colors and inline packing folded too
 *   early; sharing halved channels across the two loops worsened size to 2008.
 * - -g was measured on the earlier explicit-copy candidate (1932 bytes); it did
 *   not resolve transfer scheduling and introduced zero-materialization nops.
 *
 * Next: recover the original template-copy lowering and color-local lifetimes;
 * retain truthful call interfaces. In particular, func_002A8A20's caller consumes
 * f0, although its currently matched wrapper elsewhere is declared void.
 * The 0x3E6EEEF0 random bound is 14 * (1.0f / 60), not 14.0f / 60.0f.
 * No linked build or match is claimed. The original INCLUDE_ASM is restored.
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
extern void func_00308600(void *, void *, int, int, int);
extern float func_002A90F8(char *, char *);
extern void func_002BF728(char *, char *, float, float);
extern void func_002E5DA0(int, int, void *, int);
extern float func_002A89A8(void *, int, float);
extern float func_002A8A20(void *);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void *func_L00_0033AA40(void *, void *, unsigned int, float, float, int, float, int, int);
extern int func_L00_0031C998(int, int, float);
extern void *func_002BCB00(float, void *, void *, int, int, int, int, int, int, int);
extern void *func_00312B70(void *, void *, int, void *);
extern void func_0029F338(void *);

static __inline__ int BurstColor(int r, int g, int b, int a)
{
    return r | (g << 8) | (b << 16) | (a << 24);
}

void func_L00_0038E880(char *object, BurstVector *velocity, BurstVector *normal)
{
    int *data = *(int **)(object + 0x68);
    BurstTemplate tmpl;
    BurstVector delta, projected, shard, random, drift, point;
    float scale, distance, height, ground;
    BurstWeapon *w;

    tmpl = D_L00_002A26A0;
    scale = 1.0f + func_00283CE0(D_L00_00262570[D_00139568[12]].enabled != 0);
    func_00282D30(velocity, velocity, scale);
    func_00282CF0(&delta, D_L00_001B8DC0, object + 0x10);
    distance = func_00282DF0(&delta);
    {
        int i;
        for (i = 9; i >= 0; --i) {
            random.q = 0;
            random.f[0] = func_002A7878(-1.0f, 1.0f);
            random.f[1] = func_002A7878(-1.0f, 1.0f);
            shard.q = random.q;
            func_00282F20(&projected, normal, func_00282DB0(&shard, normal));
            func_00282CF0(&shard, &shard, &projected);
            func_00282F20(&projected, normal, func_002A7878(0.0f, 1.0f));
            func_00282CC0(&shard, &shard, &projected);
            func_00282F20(&shard, &shard, scale * func_002A7878(3.5f, 6.5f) * (1.0f / 60.0f));
            func_00282CC0(&shard, &shard, velocity);
            w = &D_L00_00262570[D_00139568[12]];
            func_00308600(object + 0x10, &shard, func_002A7820(60, 120), 0,
            w->enabled != 0);
        }
    }
    *(float *)(object + 0x18) += 1.0f;
    height = func_002A90F8(object + 0x10, (char *)&shard);
    *(float *)(object + 0x18) -= 1.0f;
    {
        int i;
        for (i = 149; i >= 0; --i) {
            drift.q = 0;
            drift.f[0] = func_002A7878(-1.0f, 1.0f);
            drift.f[1] = func_002A7878(-1.0f, 1.0f);
            drift.f[2] = func_002A7878(-0.5f, 2.0f);
            random.q = drift.q;
            func_00282F20(&random, &random, scale * func_002A7878(4.0f / 60.0f, 8.0f / 60.0f));
            func_002BF728(object + 0x10, (char *)&random, func_002A7878(0.05f, 0.1f) * 210000.0f, height);
        }
    }
    data[0] = 0;
    object[0xBC] = 0;
    func_002E5DA0(22, 0, object, 0);
    random.q = *(BurstQuad *)(object + 0x10);
    random.f[2] += 3.5f;
    height = func_002A89A8(&random, 0, 0.5f);
    ground = func_002A8A20(&random);
    if (height != ground && height - ground < 1.2f) {
        int r = 96, g = 96, b = 127, a = 22;
        float half = 0.5f;
        {
            int i;
            for (i = 99; i >= 0; --i) {
                float radius, angle;
                point.q = 0;
                point.f[0] = func_002A7878(-0.012500001f, 0.012500001f);
                point.f[1] = func_002A7878(-0.012500001f, 0.012500001f);
                point.f[2] = func_002A7878(4.0f / 60.0f, 14.0f * (1.0f / 60.0f));
                drift.q = point.q;
                radius = func_002A7878(0.0f, 0.35f);
                angle = func_002A7940();
                point.f[0] = func_00283180(angle) * radius;
                point.f[1] = func_00283198(angle) * radius;
                point.f[2] = 0.0f;
                func_00282CC0(&point, &point, object + 0x10);
                radius *= 8.0f / 60.0f;
                point.f[2] = height + half;
                drift.f[2] -= radius;
                func_L00_0033AA40(&point, &drift, 0, func_002A7878(0.25f, 1.0f), height,
                (r | (g << 8) | (b << 16) | (a << 24)), 1.0f / 180.0f, (r | (g << 8) | (b << 16)), 1);
            }
        }
        {
            int i;
            for (i = 19; i >= 0; --i) {
                int color1, color2;
                float life;
                color1 = func_L00_0031C998(BurstColor(0, 0, 0, 127), (r | (g << 8) | (b << 16) | (127 << 24)), func_002A7878(0.25f, 1.0f));
                color2 = func_L00_0031C998(0, BurstColor(48, 48, 63, 0), func_002A7878(0.5f, 1.0f));
                point.f[0] = func_002A7878(-3.0f, 3.0f);
                point.f[1] = func_002A7878(-3.0f, 3.0f);
                point.f[2] = func_002A7878(4.0f / 60.0f, 14.0f * (1.0f / 60.0f));
                func_00282F20(&point, &point, func_002A7878(1.5f, 3.0f) * (1.0f / 60.0f));
                point.f[2] = func_002A7878(3.0f, 6.0f) * (1.0f / 60.0f);
                drift.q = *(BurstQuad *)(object + 0x10);
                drift.f[2] = height;
                life = func_002A7878(31500.001953125f, 52500.0f);
                func_002BCB00(life, &drift, &point, color1, color2, func_002A7820(90, 150),
                1, *D_L00_001FE940.texture, -1, 0);
            }
        }
    }
    if (distance < 20.0f)
    D_L00_001B8C80.shake = 0.4f - distance * 0.0175f;
    else
    D_L00_001B8C80.shake = 0.050000011920928955f;
    D_L00_001B8C80.duration = 25;
    D_L00_001B8C80.timer = 0;
    func_00312B70(&tmpl, object + 0x10, 0, 0);
    func_0029F338(object);
}
