/* 8 November 2026 (Sonnet round, s26, lesson 49): profile -O2 -G8 -ffunction-sections re-measured, 6 words (entry a0/a1 swap, 0xC8/0xCC slot sw/lw, loop-2 s0 rematerialisation). Locals rewritten as expressions one at a time: delay (6, same), camera (50), w (49), c (177), c1/c2 (252), pr dropped (7) or used in loop 2 (70): none beats the base; slot order is unchanged by any. No gain. */
/* 8 November 2026 (Sonnet round, lesson 48 sweep): every single statement move of 1-6 places inside a run of simple statements, every top-level simple statement moved up to 6 top-level items, and pairs of the best singles: no variant beats the base (6 words); moves either tie or get worse. */
/* 8 November 2026 (Sonnet round, prototype audit, lesson 47): func_002A8A20 is declared float(void *) but src/game/002A7750.c:421 is void (a tail call to func_002A89A8, which returns float); three matched callers (002B1C20-motion.c:70, 002A7EA0.c:35,86) also use the float result, so the src definition is the wrong one. Note unchanged (6 words). func_002BCB00 argument order differs from src only by float/int slot order. */
/* 8 November 2026 (permuter, 32 min -j3, seeded from the C below; the permuter drops typedef attributes, so mode(TI) was */
/* 8 November 2026, region donors (v101/m8h): entry window +0x34..+0x3c matches only func_L01_003801B8 (direct call arguments, not spilled PRE addresses); the same-unit sibling func_L00_0038DE70 (L00_0037E898.c:770) spills other addresses (ints at 0xDC-0xE4, 0x50/0x60 vectors, ascending). Nothing to transcribe. */
/* 8 November 2026 (named-local round 2): the C below is that best form (6 words: entry $a0/$a1 swap and the loop-2 sp+0x90 rematerialisation; its slot order is retail's). The entry registers are reload registers for the two address sets, not incoming arguments, and pr's explicit set always comes before the PRE insertion of &shard: data/pr set order, pr set before or after the tmpl copy (after it folds pr back) do not change that. Loop 2: pr as either argument of func_00282F20 alone (7-8 words), as func_002BF728's argument (9-12), in both calls (hard register, 70+), a block-local copy (folded), pr set right before loop 2 or after loop 1 with or without loop uses (8-71), pr->q store (1960 bytes): none loads it from 0xC8. */
/* 8 November 2026 (named-local slot order, the func_00281A08 technique): `int c;` moved to the top and `BurstVector *pr = &random;` declared right after it, with pr used only in the two calls after loop 2, gives retail's slot order (data 0xC0, c 0xC4, &random 0xC8, &shard 0xCC). Two residues remain (6 words): pr's set comes first, so &random takes $a0 and &shard $a1 at entry (retail the reverse), and loop 2 rematerializes sp+0x90 into $s0 instead of loading it from 0xC8. Using pr in loop 2 (directly or via a block-local copy) gives pr a hard register (1940-1960 bytes); setting pr later (after the tmpl copy, after loop 1/2) folds it back into the PRE register; a named &shard pointer changes size. */
/* 8 November 2026 (gcse table size): the five EE cc1 builds here (ours, 991111a, 991111-01, 991111b-r4, SN 2.95.2 273a) give the same PRE table size on this source, so the sizing rule is shared. Forced sizes 11..401: 0 diffs at 17-119 (12 sizes), 161, 177, 253, 289, 295, 373, 383. Only the insn count right after RTL expand (507, before jump1) gives 253; it misses the other targets, and no metric (cuid, max uid, all/non-note insns, +notes, +labels, max_reg_num, counts after jump/cse) over 1-4 fits more than one target. */
/* 8 November 2026 (round 3): the RAC1 twin (~/rac1-decomp mine_bomb_and_debris.c, the gz/wz splash block) writes
 * the channels as int locals set at declaration plus "int delay = 0;" as the splash's third argument, and notes
 * that this local orders five cached-address stack slots through the GCSE table size. Transcribed here (short
 * channels, delay replaces the ca = 0 trick): opcodes still all match (full diff 13 words), cse1 insn count 457,
 * the two spill slots stay swapped. No float rounding or colour clamp here for the dead-test helper idiom. */
/* 8 November 2026 (round 2): max_cuid at gcse is the insn count after cse1 (465 here, so 233 buckets); a match
 * needs 504-507. Measured forms (cse1 insn count): named temps for nested call results, x = x + 1 vs +=,
 * nested if vs &&, scale split, data assigned late, loops counting up: all 465-466. A pos = object + 0x10
 * pointer: 460. Inline wrappers lower the count: weapon-row helper 449, func_00282F20 445, func_00282CC0 453,
 * func_002A7820 457, func_002A7878 345 (and that one changes the code). No plausible form found that adds insns. */
/* 8 November 2026: 1952/1952 bytes, 0/27 US placements; every opcode now matches. The only difference left is
 * two spill slots that trade places: the &shard and &random address pseudos get 0xC8 and 0xCC, and retail has
 * 0xCC and 0xC8 (8 sw/lw words). reload hands out slots in pseudo-number order, and both pseudos come from gcse
 * PRE (expressions 23 and 38), numbered in hash-bucket order. (plus vfp 128) hashes to 14158 and (plus vfp 144)
 * to 14174, so the order only flips when the table has 253, 289 or 295 buckets (max_cuid 504-507, 576-579 or
 * 588-591); this source gives 233. What closed the opcodes (the matched sibling func_L00_003AE900 in
 * L00_003AE900-g8.c supplied the idioms):
 * cr/cg/cb channel variables with c1/c2/c partial products and (cb / 2) halving; half = 0.5f inside the loop;
 * a camera pointer local for the shake store (as in func_L00_0037E898); the weapon read written as
 * idx * 224 + base; func_002BCB00 declared (void *, void *, int, int, float, ...), an equivalent EE-ABI form
 * that donor uses; short channels (orders the loop-2 constants); ca = 0 set inside loop 1 and used second in the
 * halved colour, which gives retail's dead fp = 0 (combine's USE keeps the shortest-lived channel). Tried and
 * dropped: a pointer local for &random (54 diffs), an inline func_002A7878 wrapper (217 buckets, 1976 bytes),
 * -fno-gcse / -fno-rerun-cse-after-loop / -fno-strength-reduce (slots unchanged or worse). No complete match. */
/* Earlier notes (1-2 November 2026, 1944/1952): lq/sq template copy, ignored returns of func_00308600 and
 * func_002BF728, the integer return of func_002E5DA0, and 14 * (1.0f / 60) for the random bound. */
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

void func_L00_0038E880(char *object, BurstVector *velocity, BurstVector *normal)
{
    int *data = *(int **)(object + 0x68);
    BurstTemplate tmpl;
    BurstVector delta, projected, shard, random, drift, point;
    float scale, distance, height, ground;
    int c;
    BurstVector *pr = &random;
    BurstWeapon *w;

    tmpl = D_L00_002A26A0;
    scale = 1.0f + func_00283CE0(((BurstWeapon *)(D_00139568[12] * 224 + (int)D_L00_00262570))->enabled != 0);
    func_00282D30(velocity, velocity, scale);
    func_00282CF0(&delta, D_L00_001B8DC0, object + 0x10);
    distance = func_00282DF0(&delta);
    {
        int i;
        for (i = 9; i >= 0; --i) {
            int lifetime;
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
            lifetime = func_002A7820(60, 120);
            w = &D_L00_00262570[D_00139568[12]];
            func_00308600(object + 0x10, &shard, lifetime, 0,
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
    {
    short cr = 0x60;
    short cg = 0x60;
    short cb = 0x7F;
    int delay = 0;

    random.q = *(BurstQuad *)(object + 0x10);
    random.f[2] += 3.5f;
    height = func_002A89A8(pr, 0, 0.5f);
    ground = func_002A8A20(pr);
    if (height != ground && height - ground < 1.2f) {
        {
            int i;
            for (i = 0; i < 100; i++) {
                float radius, angle, half;
                int c1, c2;
                point.q = 0;
                point.f[0] = func_002A7878(-0.012500001f, 0.012500001f);
                point.f[1] = func_002A7878(-0.012500001f, 0.012500001f);
                point.f[2] = func_002A7878(4.0f / 60.0f, 14.0f * (1.0f / 60.0f));
                drift.q = point.q;
                radius = func_002A7878(0.0f, 0.35f);
                half = 0.5f;
                angle = func_002A7940();
                point.f[0] = func_00283180(angle) * radius;
                point.f[1] = func_00283198(angle) * radius;
                point.f[2] = 0.0f;
                func_00282CC0(&point, &point, object + 0x10);
                radius *= 8.0f / 60.0f;
                point.f[2] = height + half;
                drift.f[2] -= radius;
                c1 = (0x16 << 24) | (cb << 16) | (cg << 8);
                c2 = (cb << 16) | (cg << 8);
                func_L00_0033AA40(&point, &drift, delay, func_002A7878(0.25f, 1.0f), height,
                c1 | cr, 1.0f / 180.0f, c2 | cr, 1);
            }
        }
        c = (0x7F << 24) | (cb << 16) | (cg << 8);
        {
            int i;
            for (i = 0; i < 20; i++) {
                int color1, color2;
                float life;
                color1 = func_L00_0031C998(0x7F000000, c | cr, func_002A7878(0.25f, 1.0f));
                color2 = func_L00_0031C998(0, ((cb / 2) << 16) | ((cg / 2) << 8) | (cr / 2), func_002A7878(0.5f, 1.0f));
                point.f[0] = func_002A7878(-3.0f, 3.0f);
                point.f[1] = func_002A7878(-3.0f, 3.0f);
                point.f[2] = func_002A7878(4.0f / 60.0f, 14.0f * (1.0f / 60.0f));
                func_00282F20(&point, &point, func_002A7878(1.5f, 3.0f) * (1.0f / 60.0f));
                point.f[2] = func_002A7878(3.0f, 6.0f) * (1.0f / 60.0f);
                drift.q = *(BurstQuad *)(object + 0x10);
                drift.f[2] = height;
                life = func_002A7878(31500.001953125f, 52500.0f);
                func_002BCB00(&drift, &point, color1, color2, life, func_002A7820(90, 150),
                1, *D_L00_001FE940.texture, -1, 0);
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
    D_L00_001B8C80.duration = 25;
    D_L00_001B8C80.timer = 0;
    func_00312B70(&tmpl, object + 0x10, 0, 0);
    func_0029F338(object);
}
