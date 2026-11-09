/* 9 November 2026 (o40 cross-block max_cuid search): insns that survive cse1 but die later do exist, but only one per site: dead initial values in another block (`long tex = 0`, `flags = 0`, `int n/j/k/c = 0`, loop-body `float v = 0.0f`, `int col = 0`) give +1 each with the same final code (342, 171 buckets, same 12 diff lines); single-use named constant locals (`int last = 30` for `i < 30`, also k < 2, n < 2, c >= 0x1F, k & 1, t < 4, 0x8000L << 24) give +1 each and keep the code, 0.1f gives -1; all together 347 (173 buckets, 14 lines). Re-reading locals at each use (col, v, c, the `n == 0` copy, qcopy placement) moves -4..+3 and mostly changes code; a dead counter is removed before gcse. No natural form gets near 360-363 or 292-295 (S=181 would fit our reg numbers d=85 n=88 j=89 i=158). */
/* 9 November 2026 (o39 toolchain probe): gcse.c alloc_gcse_mem counts only class-i insns (NOTEs, so -g/line notes, get no cuid), once per pass before cprop; MAX_PASSES 1; table size max_cuid/2|1, same text in all five gcse.c trees. No option moves it: -g0/-g1/-g3/-ggdb3/-gstabs, -fno-cse-follow-jumps, -f(no-)cse-skip-blocks, -fno-thread-jumps, -f(no-)force-mem, -fforce-addr, -f(no-)inline-functions, -O3, -fno-edge-lcm, every -frac2-* switch, -G0/-G4 and 20 -m/-f target flags all give 167 buckets (max_cuid 332-335); loop-time flags (-fno-strength-reduce, -fno-rerun-*) change only later code. Other cc1s (SDK 991111-01, 991111a, RAC1 game cc1 prebuilt and rebuilt): 167. */
/* 9 November 2026 (o37 max_cuid sweep): no honest spelling moves max_cuid (334) near 292-295 or 360-363. cse1 + delete_trivially_dead_insns reduce 486 expand insns to 334, so local spellings are canonical: 27 spelling swaps (i % 4, pointer/array forms, test forms), 256 qcopy/TImode-copy mixes and 5115 `Pkt *p` site/assignment mixes all give 334-336. Only inline forwarding wrappers move it, by one insn per call site (an fp-address argument goes straight into $a0-$a3, so its PRE pseudo goes): draw/scale wrappers -1 each, the func_0027C878 wrapper +1, all with the same 12 diff lines; reach 330-335 only. Helpers for the corner, bend or whole k-loop block change the code (134-239 lines). `((float (*)[2])P)[k + 10][0]` takes uv out of PRE (no longer hashed) but loop.c then keeps it out of the spill (frame 0x310, 64 lines). */
/* 9 November 2026 (o33 slot research): spill slots follow pseudo number (reload alter_reg, upward); the spilled values are gcse PRE regs, numbered in hash-bucket order, bucket = (14029 + regno + offset) % S, S = (max_cuid/2)|1 = 167. With uv = fp+80 no reg numbering gives retail's order at S=167 (needs S 147/181, max_cuid 292-295/360-363; max_cuid stayed 167 buckets over ~30 flag/spelling variants). `Pkt *p = P;` declared before d with the uv store as `p[0].uv[k][0]` makes every spill slot match retail (hash 166, last), but p stays live in $s3 / the uv copy moves late: 41 lines vs 12. */
/* 9 November 2026 (Sonnet round s39): base still 13 words (all spill-slot order). No gain: loop tests != (17-30), unsigned j/k (14/17), while+continue j loop (167), swapped if/else arms (64-232), swapped k arms (18-23), joined/reordered c tests (16+), duplicated k-loop tails per if/else arm (1600/1632 bytes: jump2 does not merge them). Permuter (-j2, 1500 s) found 11 words: declare `long new_var;` between t and j and write `new_var = P[1].zero = P[2].zero = 0; P[0].zero = new_var;` (a fake temp for the zero store, so kept out of the body; the declaration order alone and plain chain reorderings stay 13). Slots still differ (uv 0x29C vs retail 0x2B0). */
/* 8 November 2026 (Sonnet round, lesson 49 + declaration sweep): re-measured 1376/1376, 15 differing words excluding relocations (note said 14). Locals checked against retail: d (one reg $s7), tex/flags, c, i/j/n/k all real, nothing to inline. Greedy sweep of every scalar/array declaration position (about 190 compiles): `int n; int j; int k;` declared right after `flags` (body below now) gives 13 words; a permuter run (-j2, 1500 s) only found the same `int n` move (60 vs 70). Spill-slot order still differs. */
/* 8 November 2026 (Sonnet round, lesson 48 sweep): every single statement move of 1-6 places inside a run of simple statements, every top-level simple statement moved up to 6 top-level items, and pairs of the best singles: no variant beats the base (14 words); moves either tie or get worse. */
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
    int n;
    int j;
    int k;
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
