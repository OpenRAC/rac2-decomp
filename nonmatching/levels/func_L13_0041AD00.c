/* 8 November 2026 (Sonnet round, measured): uv store as a row pointer, a float pointer, a value local or split product: still 14 words; the uv store per arm in one loop or both: 142-263 words. Permuter (-j2, 1500 s, 200 base): best 190, no spill-slot change. */
/* 8 November 2026 (named-local slot order, the func_00281A08 technique): retail's spill slots 0x29C..0x2B0 hold j+1, n+1, j*16, &cnt, i+1, uv; ours have uv first, then the same five. Named jn/nn/in/cnt locals (loop step = next form) keep registers and schedule but take the lowest slots (0x280..), ahead of the loop-invariant stack-address temps, so the order gets worse (46 words); a named uv = P[0].uv is folded back into the PRE register (no change); named v270/v260 pointers change size (1360). Named locals only move a value earlier; retail needs uv moved last. */
/* 8 November 2026 (max_cuid search): RAC1's exact forms (one flags expression, twelve separate setup stores), while/do loops, i % 4, joined or reordered tests, temps and ~200 random combos of 23 such rewrites all keep max_cuid 334-335 (167 buckets). Only code-changing forms move it: row/corner pointers 314 (157), the uv store per arm 378 (189). No equivalent form reaches 274, 294 or 362. */
/* 8 November 2026 (gcse table size): the five EE cc1 builds here (ours, 991111a, 991111-01, 991111b-r4, SN 2.95.2 273a) give the same PRE table size on this source, so the sizing rule is shared. Forced sizes 11..401 give 0 diffs only at 49, 103, 137, 147, 181 (ours 167, 15 diffs); the expand-time count gives 235 (15). No metric over 1-4 fits this and func_L00_0038E880 together. */
/* 8 November 2026, round 14: 1376/1376 bytes, 0/2, 14 differing words excluding
 * relocation fields (was 79). Profile: -O2 -G8 -ffunction-sections -frac2-qcopy
 * -frac2-qcopy-barrier -fno-sched-spec -Wa,--r5900-la-addend=sn
 * (-fno-sched-interblock gives the same output). New base: a transcription of RAC1's
 * matched draw_electric_beam (~/rac1-decomp src/overlays/shared/vendor_beam.c, built
 * there with -fno-sched-spec): Beam struct (pts at 0x20, seg[4][4] at 0x420, cnt at 0x18),
 * qcopy for the copies, per-loop locals in the uv/colour setup loop. Only the flags
 * expression and the four chained setup stores keep the older form. The uv table now
 * uses one SDATA view with the la-addend option (the [t][1] loads become lui/addiu,
 * the [k][0] base stays $gp), so the two-name alias is gone; same output as before.
 * All registers and the whole schedule now match. Only the spill-slot order differs:
 * retail puts the uv pointer (&P[0].uv, gcse PRE pseudo 387) in the highest slot
 * (0x2B0) and the j/n/i counters, j*16 and &cnt one slot lower each; here the uv
 * pointer is lowest (0x29C). Slots follow pseudo number (alter_reg); PRE numbers its
 * reaching regs in expression hash-bucket order, and no table size fits that order
 * with these reg numbers. 9-variable declaration orders (700 cc1 runs), -g,
 * -fno-gcse (1420 bytes), sticky-volatile, a Pkt pointer, a cnt idx pointer, i % 4
 * and joined/moved cnt tests all tie or lose. */
/* 7 November 2026, round 13: no gain (79 words). In retail the row copy is allocated before */
/* 7 November 2026, round 13: no gain (79 words). In retail the row copy is allocated before
 * the original in both loops (k loop: copy $s5, original $s6; i loop: copy $s0, original
 * $s5) and the uv pointer before the D pointer. The original always has more weighted refs
 * (k loop 16 vs 13), so no spelling flips it: 240 row forms (association, which pointer is
 * the copy, increment order), 80 single-level groups around the row statements, a per-branch
 * offset variable (107), rows hoisted as loop invariants (no copy, 153), add operand swap,
 * goto loops (96 local, not admissible) and -flive-range (346) all tie or lose. */
/* 6 November 2026, round 12: 1376/1376 bytes, 0/2, 79 differing words excluding relocation
 * fields (was 101). Changes: index test `index>-1` gives retail's slti/beqz/slti/bnel;
 * branch row b = branch*16 + (k*64 + s) with no group gives retail's operand order and
 * drops the two extra nops; one do-while group around the setup n-loop body keeps s in
 * $s7 (without it s and &previous swap: 82 words). -g has no effect; the j-loop region is
 * 8 blocks / ~40 insns, under the 10/100 limits, so no block split explains
 * -fno-sched-interblock (without it: 202). Remaining: branch row b (16 refs) outranks k
 * and side, so k is $s4 not $s3 and side $s5 not $s4; i-loop copy gets $s4 not $s0;
 * spill-slot order; the setup n-loop increments move after the group barrier. */
/* 6 November 2026, round 10b: no gain (101 words, ~45 runs). Branch row b keeps 16-17 refs and outranks side; the i-loop copy takes $s0 only inside a group, which splits row and quotient; six index-test spellings and five flags give no slti/bnel; spill slots follow pseudo number and the uv base comes first here. */
/* 6 November 2026, round 10: 1376/1376 bytes, 0/2, 101 differing words excluding
 * relocation fields (was 279), first +0xa0. Profile adds -fno-sched-interblock
 * (stops arg moves above the j&1 test; v now lands in a0). Changes: branch-loop args
 * as ((ADVector (*)[4])(s+0x420))[k]+branch (keeps s in $s7, frame 0x320);
 * vertex v = (ADVector *)(j*16 + (int)q); setup chains q[0]=q[1]=q[2] and a forward
 * n loop (setup now matches); i-loop rows b = i*16 + s; a = b; b += 0x30;
 * a += 0x20 with no group (copy kept, quotient spilled, one subu tail); branch
 * rows the same with a do { b = ... } while (0) group (gives s one more weighted
 * ref so s beats &previous for $s7). Remaining: branch row b (17 refs) outranks
 * the uv giv and side, so side lands in $s5 not $s4 and k in $s4 not $s3; i-loop
 * copy gets $s5 not $s0; index tests give beql/bltz, retail beqz/slti/bnel;
 * spill-slot order differs. */
/* 6 November 2026, round 9: the func_L13_0041AB30 idiom (p = s + i*16; r = p;
 * do { r += 0x20; } while (0); p += 0x30; same for the 0x420/0x460 branch rows)
 * stays at 1420/1376 bytes, 0/2, 281 rows (279 before); -g and
 * -frac2-sticky-volatile-refs tie. The blocker is still allocation: the state pointer
 * spills to 0x280 and (i/4)*4 holds $fp, while retail keeps s in $s7, &previous in
 * $fp and spills the quotient (so one subu, not one per tail). Original C retained. */
/* Nonmatching C reconstruction (opus-1, v2196, USA v1.01, 2026-11-03).
 * Tier: far. Profile: -O2 -G8 -ffunction-sections -frac2-qcopy
 * -frac2-qcopy-barrier. Best cdiff: 1420 compiled bytes / 1376 retail,
 * 0 of 2 places.
 * Semantics fix over the earlier 1380-byte draft: retail's j=1 corner calls
 * func_00282CC0(v, v, &previous) (a2 = fp), not &side. Each corner is row0
 * -/+ previous (j=0,1) or row1 -/+ side (j=2,3), with the j&1 test inside
 * each arm. That gives retail's control flow: the sll is shared before the
 * j<2 branch (PRE), per-arm vertex address, CC0 tails cross-jumped.
 * The earlier draft's size was closer only because its j=1 call was wrong.
 * Testing j&1 once after the if/else (with a dir variable) gave 1364 bytes
 * and fewer copies, but lost the per-arm tests retail has.
 * The idx pointer in the branch loop reproduces retail's s+0x18 spill before
 * the i loop; nested index<31 / index>=0 tests keep retail's two slti tests.
 * Remaining: v lands in v1 (extra a0 copies) instead of a0; the state
 * pointer spills where retail keeps it in s7 (retail spills the quotient
 * and next index instead); retail copies the row (X = i*16 + s; Y = X;
 * Y += 0x20; X += 0x30), the same copy pattern as func_L13_0041AB30;
 * frame 0x310 versus 0x320.
 * All declarations are below.
 */
#include "common.h"

typedef struct Pkt {
    float corner[4][4];
    unsigned int color[4];
    float uv[4][2];
    long zero;
    long tex;
    long state;
    long flags;
} Pkt;

typedef struct {
    int idx;
    char pad4[0x10];
    int color;
    unsigned char cnt[4];
    char pad1c[4];
    float pts[64][4];
    float seg[4][4][4];
} Beam;

extern void func_00283410(void *, void *);
extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern long func_0027C878(int);
extern void func_00280B90(void *, void *, int);
extern char D_L13_001B98C0[];
extern int D_L13_001B163C __attribute__((sda));
extern int D_L13_001B1640 __attribute__((sda));
extern int D_L13_001B1644 __attribute__((sda));
extern int D_L13_001B1648 __attribute__((sda));
extern int D_L13_001B164C __attribute__((sda));
extern float D_L13_001B1660[4][2] SDATA(D_L13_001B1660);

void func_L13_0041AD00(char *m) {
    Beam *d = *(Beam **)(m + 0x68);
    Pkt P[3];
    float M1[16] __attribute__((aligned(16)));
    float M2[16] __attribute__((aligned(16)));
    float v230[4] __attribute__((aligned(16)));
    float v240[4] __attribute__((aligned(16)));
    float v250[4] __attribute__((aligned(16)));
    float v260[4] __attribute__((aligned(16)));
    float v270[4] __attribute__((aligned(16)));
    long tex;
    long flags;
    int j, n, k;
    int c;
    int t;

    func_00283410(M1, (char *)d + 0x650);
    func_00283698(M2, M1);
    qcopy_nc(&M1[12], m + 0x10);
    func_00282CF0(v230, D_L13_001B98C0, m + 0x10);
    func_00283098(v230, v230, M2);
    tex = func_0027C878(D_L13_001B163C);
    flags = (long)D_L13_001B1640;
    flags |= (long)D_L13_001B1644 << 2;
    flags |= (long)D_L13_001B1648 << 4;
    flags |= (long)D_L13_001B164C << 6;
    flags |= 0x8000L << 24;
    P[0].state = P[1].state = P[2].state = 0xFF9000000260L;
    P[0].tex = P[1].tex = P[2].tex = tex;
    P[0].zero = P[1].zero = P[2].zero = 0;
    P[0].flags = P[1].flags = P[2].flags = flags;
    for (t = 0; t < 4; t++) {
        float v = D_L13_001B1660[t][1];
        int col;
        P[2].uv[t][1] = v;
        P[1].uv[t][1] = v;
        P[0].uv[t][1] = v;
        col = d->color;
        P[2].color[t] = col;
        P[1].color[t] = col;
        P[0].color[t] = col;
    }
    func_00282C88(v250);
    {
        int i;
        for (i = 0; i < 31; i++) {
            qcopy(v240, v250);
            if (i < 30) {
                func_00282CF0(v270, d->pts[i], d->pts[i + 2]);
                func_00282CF0(v260, d->pts[i + 1], v230);
                func_00282DD8(v250, v260, v270);
                func_00282F20(v250, v250, 0.1f);
            } else {
                func_00282C88(v250);
            }
            for (k = 0; k < 4; k++) {
                if (k < 2) {
                    qcopy(P[0].corner[k], d->pts[i]);
                    if (k & 1)
                        func_00282CC0(P[0].corner[k], P[0].corner[k], v240);
                    else
                        func_00282CF0(P[0].corner[k], P[0].corner[k], v240);
                } else {
                    qcopy(P[0].corner[k], d->pts[i + 1]);
                    if (k & 1)
                        func_00282CC0(P[0].corner[k], P[0].corner[k], v250);
                    else
                        func_00282CF0(P[0].corner[k], P[0].corner[k], v250);
                }
                P[0].uv[k][0] = D_L13_001B1660[k][0] + func_00283CE0(i - i / 4 * 4) * 0.25f;
            }
            func_00280B90(&P[0], M1, 0);
        }
    }
    for (j = 0; j < 4; j++) {
        func_00282C88(v250);
        c = d->cnt[j];
        if (c >= 0x1F)
            continue;
        if (c <= -1)
            continue;
        for (n = 0; n < 3; n++) {
            qcopy(v240, v250);
            if (n < 2) {
                func_00282CF0(v270, d->seg[n][j], d->seg[n + 2][j]);
                func_00282CF0(v260, d->seg[n + 1][j], v230);
                func_00282DD8(v250, v260, v270);
                func_00282F20(v250, v250, 0.1f);
            } else {
                func_00282C88(v250);
            }
            if (n == 0)
                qcopy(v240, v250);
            for (k = 0; k < 4; k++) {
                if (k < 2) {
                    qcopy(P[0].corner[k], d->seg[n][j]);
                    if (k & 1)
                        func_00282CC0(P[0].corner[k], P[0].corner[k], v240);
                    else
                        func_00282CF0(P[0].corner[k], P[0].corner[k], v240);
                } else {
                    qcopy(P[0].corner[k], d->seg[n + 1][j]);
                    if (k & 1)
                        func_00282CC0(P[0].corner[k], P[0].corner[k], v250);
                    else
                        func_00282CF0(P[0].corner[k], P[0].corner[k], v250);
                }
                P[0].uv[k][0] = D_L13_001B1660[k][0] + func_00283CE0(n - n / 4 * 4) * 0.25f;
            }
            func_00280B90(&P[0], M1, 0);
        }
    }
}
