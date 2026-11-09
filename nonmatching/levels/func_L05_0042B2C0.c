/* 9 November 2026 (o54): body now 531/532 insns, frame 0x150, 186 opcode-only rows (was 533, 190): `AE0[0].v[3] = 0` after D60[0][0] and the row-head `r[0]` store after the 00E0 pair (permuter, honest). Measured: the seam copy target as a pointer (`w = ECE0[out]`) gives retail's madd form but cse merges it with the AE0 reload pointer (one madd, 525 insns); wrapping the reload in `do { } while (0)` restores retail's 00E0[out][1] reload but cse still merges the two pointers (4 madds of 5, 529); `(float *)ECE0 + out * 3` folds to the same RTL; -fno-gcse / -fno-rerun-cse-after-loop do not split them (cse1 merges). A `VBC *rad = &radial` local drops the 0xB0 caller-save (frame 0x140). Retail's AE0[31] qcopy loads &AE0[0] first; `qcopy(&ring[31], ring)` gives that but 529 insns. Permuter 1500 s from this body: only these moves or fake temps. */
/* 9 November 2026 (o50): new body, same flags (-frac2-no-extra-increment-givs -fno-rerun-loop-opt): 533/532 insns, frame 0x150, 190 opcode-only diff rows (o47 body 248; 457 positional rows). Found: retail's reloads come from writing the store and the reload with different address forms (array-form store `D_L05_0026ECE0[out][k] = ...`, reload through a row pointer `w`/`t = D_L05_0026ECE0[out]`): this gives the row-head x/y/z reload and the inner-loop x+y reloads (inner second half now as retail: x via the ECE0 giv, y via the out*12 giv). A separate pointer `r` for the row-head first entry (p had 3 sets, so alias.c gave it no base and its stores blocked the AE0 loads) lets sched1 hoist the AE0[0] loads like retail. Scripted lesson-48 sweep (every legal single move, greedy): 00E0[out][1] before [0] (row head and inner), FBE0[out] before the 00E0 pair in the seam, CE0[0] before D60[0][1] in the ring init, base = 0 before remaining = 320. Left: seam has 2 madds where retail has 4 (retail copy target and AE0 reload are two separate madd pointers that cse did not merge, plus a reload of 00E0[out][1] for D60); row head lacks the 00E0[out][1] reload; &radial is in fp (retail: caller-saved a3 with sq/lq) and CE0's giv takes the sq/lq; tail still takes ECE0 from ECE0+4; first/k/v placement unchanged by any source position (sweep). Moving `AE0[0].v[3] = 0` after D60[0][0] gives 186 ops but 531 insns. Tried: float (*pos)[3] row-array pointer (permuter idea; 505 insns, 0x140), pointer copy target in the seam (523 insns), multi-set q for 00E0 (no change). Permuter 1500 s from the r-pointer body: best only with a fake copy of first, the pos pointer (0x140/0x160) or a store moved into the inner loop (changes behaviour). */
/* 9 November 2026 (o47): size fixed. Same flags as o46. The row loop is a real for loop again, with `first = out + 1;` near its top and `out = first;` (a register copy) after the first strip entry: `out` is then no biv of the row loop, so no per-row givs, and the row loop keeps retail's per-row mult/madd and rematerialised luis (o46's goto form lost 43 insns of them; `out = first + 1` folds to out+2 and brings the givs back). Pointer `p = D_L05_0026ECE0[out]` for the row-head first entry and both seam entries, `q = ...[first]` for the seam copy, give retail's madd forms; `ring = D_L05_00270AE0` after the delta call puts &AE0 early like retail; inner first half in retail store order (ECE0, FBE0, 00E0). This body: 533/532 insns, frame 0x150 (retail), row-loop bnel and inner/row/tail branch positions as retail, 450 differing rows / 248 opcode-only (o46 body: 462/272 at 489 insns). Left: sched1 hoists `first`, `k = 29` and `v` over calls where retail keeps them one call later; spill slots 0x8C-0xA0 permuted (retail: rot2 copy, first, first*4, rot2, inv2, row); tail loop gets ECE0 from an earlier ECE0+4 register. Tried: v = startV at the row top (delay slot as retail, but 529 insns), first placed after the rotation calls (no change), seam store orders, -fno-schedule-insns (worse). Permuter 1500 s seeded from this structure: best 541 insns (244 ops but 503 rows), nothing better. */
/* 9 November 2026 (o46): with -frac2-no-extra-increment-givs (cflags precedent 00284268.c) the inner loop keeps retail's two `out++` (no biv-to-giv conversion); adding -fno-rerun-loop-opt gives frame 0x150 on the old body. This body (flags -O2 -G8 -ffunction-sections -frac2-zero-ti-por -frac2-no-extra-increment-givs -fno-rerun-loop-opt) is closer in structure: first ring loop counted down (k = 29..0, bgez, body ops identical to retail); row loop as `goto row_top` (retail does not strength-reduce `out` per row: per-row mult/madd, rematerialised luis); tail `while (1) { ...; if (remaining > 0) {...} else break; }` gives retail's blez/b ending; nextV = startV + stepU before the row loop gives retail's f27; inner first half reading CE0 first and writing ECE0 through `p` gives retail's 66/67-insn inner loop with CE0 strength-reduced, the separate out*12 giv for the y store and the x reload. Now 489 insns (1956/2128 bytes), frame 0x140, 462 differing rows / 272 opcode-only (old body under the same scorer: 504 / 332). Left: loop counter i lands in a caller-saved reg (sq/lq) where retail puts &radial; y reload missing; row-head address/madd forms. Tried: rotation2/inverse2 pointer locals, literal 31 after the inner loop, store reorders in the second half, -fno-gcse/-fno-rerun-cse-after-loop. Permuter 1500 s: only semantic-changing candidates. */
/* 9 November 2026 (o41, fresh rewrite from retail asm): retail frame 0x150 = 8 quads 0x00-0x7F (unit, center, delta, radial, rotation, inverse, rotation2, inverse2), 9 word spills 0x80-0xA0, one caller-save quad 0xB0 (&radial), regs 0xC0; ours had 5 caller-save quads + 2 extra spill words. This body (for loops, chained z store in the inner loop) gives 2112/2128, frame 0x190 (was 0x1A0), 501 check rows (old body 518); the same without the chained z gives 2120 bytes, 481 rows, 0x1A0. Cause traced in loop.c: the inner loop's two out++ get "biv increment converted to giv" (first pass; second pass converts the reduced givs too) unless loop_has_volatile, a jump between, or a not-always-executed increment; retail has neither conversion. Volatile color read in the loop: no conversion, 0x160, but 495 insns (not landable). Single out+=2 with [out+1]: 0x160, 485 insns. Retail also rematerialises outer-loop invariant addresses (50 lui) and its tail loop ends blez/b (no form of for(;;)/while/do with break reproduced it). Permuter 1500 s: only a fake-temp/dead-store gain. */
/* 8 November 2026 (Sonnet round o28, lesson 49): re-measured 2112/2128, frame 0x1A0 vs 0x150 (520/529 differing rows, 322 opcode-only). Retail register roles read from the asm: first ring loop counts fp 29..0 with pointer givs s5/s1/s2 and &radial s4, &inverse s6; startU is kept in f22 and u in f21 (two values; here they merge into f21); the inner loop keeps &radial in a caller-saved reg (one 128-bit sq/lq caller-save), out in s7 only incremented, and ECE0/00E0/FBE0 pointer givs s2/s0/s4 plus an out*12 offset s5. Tried: &rotation2/&inverse2 as pointer locals set before the first loop (522 rows, no frame change). Permuter 1500 s: best candidates use volatile (not landable). */
/* 8 November 2026 re-measure (today's compiler: set-side sticky volatile default,
 * mtc1 hazard-nop fix): this C in its own -g8 unit with -frac2-zero-ti-por gives
 * 2112/2128 bytes, frame 0x1A0 vs 0x150; the gap is not 2 instructions but ~400
 * aligned-diff lines (retail 50 lui vs 37, 4 madd vs 1, 1 caller-save sq vs 9).
 * Cause found in the -dL dump: loop.c converts the inner loop's first `out++`
 * into a giv ("Increment of biv converted to giv"), so `out` steps by 2 and every
 * output address gets a second 24-byte-step giv kept in caller-saved registers
 * across both quaternion calls. Retail keeps two +1 increments of out (s7) and
 * single givs stepped by 12 after each, so retail had no conversion: per
 * loop.c that needs a jump between the two increments (out is live after the
 * loop). A test jump between them (if (i == 100) break; diagnostic only) gives
 * 2128 bytes but still frame 0x190. Retail also keeps &rotation2/&inverse2 in
 * pseudos spilled at 0x98/0x9C, set before the FIRST ring loop.
 * MACRO_ADDR on all six tables: 2392 bytes, 0x1F0; on one table only:
 * 00270AE0 2120, 0026ECE0 2304, 002700E0 2160, 00270D60 2152, 0026FBE0 2112,
 * 00270CE0 2088 bytes, none below 0x1A0. No RAC1/RAC4 donor (searched the
 * angle 0.2026834, 0x53001, 0xFF9000000260 and the 148-vertex batch loop).
 * Next: find source that puts a real branch between the two out++ (or out as
 * a non-biv with pointer bivs) and the early &rotation2/&inverse2 pseudos.
 */
/* GPT-6.1 Sol (high), worker v1347, USA v1.01.
 * Profile: -O2 -G8 -ffunction-sections -frac2-zero-ti-por.
 * Best size: 2120/2128 bytes, 0/4 places. Not a verified behavioral match.
 * All required declarations are below; use a dedicated -g8.c unit to retry.
 *
 * Reconstructed the output-to-cache UV reads and the final seam's position and
 * color copies from the first NEW vertex of each strip. The GP object is a
 * signed 32-bit word widened before the 64-bit GS-state shift (retail uses lw).
 * Keep i from the middle loop for the seam rather than assigning literal 31.
 *
 * Remaining: retail frame 0x150 versus 0x1A0 here, output/source pointer
 * lifetimes, initial FP-value coalescing, and draw-loop branch scheduling.
 * Middle-loop strength reduction creates extra addresses live across both
 * quaternion calls; retail increments one output pointer twice by 12 bytes.
 * Signed/unsigned out, array/record views, and for/do loops tie at 2120 bytes.
 * Flat output arrays: 2080 bytes, 0x190 frame; explicit advancing pointers:
 * 1968-2056 bytes, 0x160-0x170 frame. Disabling strength reduction gives
 * 2168-2216 bytes; disabling GCSE gives 2084 bytes without fixing the frame.
 * Stopped after 15 exploratory checks and one regalloc dump; final recheck ties.
 * Next: recover the original middle-loop induction/address expressions;
 * equal size would still need instruction and all-placement qualification.
 */
#include "common.h"
typedef unsigned int QBC __attribute__((mode(TI)));
typedef union { QBC q; float v[4]; } VBC;
extern VBC D_L05_00270AE0[32];
extern float D_L05_0026ECE0[][3], D_L05_002700E0[][2], D_L05_00270D60[][2];
extern unsigned D_L05_0026FBE0[], D_L05_00270CE0[];
extern int D_L05_001B1724 __attribute__((sda));
extern void ref_L05_0042B2C0_00(void *, void *, float);
extern void ref_L05_0042B2C0_01(void *, void *, float);
extern void ref_L05_0042B2C0_02(void *, void *, void *);
extern void ref_L05_0042B2C0_03(void *, void *, void *);
extern unsigned long long ref_L05_0042B2C0_04(int);
extern void ref_L05_0042B2C0_05(int, unsigned long long);
extern void ref_L05_0042B2C0_06(void);
extern void ref_L05_0042B2C0_07(int, void *, void *, void *, int);
void func_L05_0042B2C0(VBC *origin, VBC *axis, int texture, unsigned color,
 float advance, float radius, float stepU, float stepV, float startV, float startU)
{
    float *p, *q, *r, *w, *t;
    VBC *ring;
    VBC unit, center, delta, radial, rotation, inverse, rotation2, inverse2;
    float u, v, nextU, nextV;
    int k, i, row, out, first, remaining, base, n;

    unit.q = 0;
    unit.v[3] = unit.v[2] = 1.0f;
    out = 0;
    u = startU;
    qcopy(&center, origin);
    ref_L05_0042B2C0_00(&delta, axis, advance);
    ring = D_L05_00270AE0;
    ref_L05_0042B2C0_00(&radial, &unit, radius);
    radial.v[3] = 0;
    ref_L05_0042B2C0_01(&rotation, axis, 0.202683404f);
    ref_L05_0042B2C0_00(&inverse, &rotation, -1.0f);
    inverse.v[3] = rotation.v[3];

    ref_L05_0042B2C0_02(&ring[0], &center, &radial);
    D_L05_00270D60[0][0] = u;
    D_L05_00270CE0[0] = color;
    D_L05_00270D60[0][1] = startV;
    v = startV + stepU;
    for (i = 1, k = 29; k >= 0; k--, i++) {
        ref_L05_0042B2C0_03(&radial, &rotation, &radial);
        ref_L05_0042B2C0_03(&radial, &radial, &inverse);
        ref_L05_0042B2C0_02(&ring[i], &center, &radial);
        D_L05_00270D60[i][1] = v;
        v += stepU;
        D_L05_00270CE0[i] = color;
        D_L05_00270D60[i][0] = startU;
    }
    qcopy(&D_L05_00270AE0[31], &D_L05_00270AE0[0]);
    D_L05_00270CE0[31] = D_L05_00270CE0[0];
    D_L05_00270D60[31][1] = v;
    D_L05_00270D60[31][0] = startU;
    ref_L05_0042B2C0_02(&center, &center, &delta);
    u += stepV;

    nextV = startV + stepU;
    for (row = 1; row < 6; row++) {
        ref_L05_0042B2C0_00(&radial, &unit, radius);
        first = out + 1;
        radial.v[3] = 0;
        ref_L05_0042B2C0_01(&rotation2, axis, 0.202683404f);
        ref_L05_0042B2C0_00(&inverse2, &rotation2, -1.0f);
        inverse2.v[3] = rotation2.v[3];
        if (row == 5)
            color &= 0xFFFFFF;
        v = startV;

        r = D_L05_0026ECE0[out];
        r[1] = D_L05_00270AE0[0].v[1];
        r[2] = D_L05_00270AE0[0].v[2];
        D_L05_002700E0[out][0] = D_L05_00270D60[0][0];
        D_L05_002700E0[out][1] = D_L05_00270D60[0][1];
        r[0] = D_L05_00270AE0[0].v[0];
        D_L05_0026FBE0[out] = D_L05_00270CE0[0];
        out = first;
        D_L05_0026ECE0[out][0] = center.v[0] + radial.v[0];
        D_L05_0026ECE0[out][1] = center.v[1] + radial.v[1];
        D_L05_0026ECE0[out][2] = center.v[2] + radial.v[2];
        D_L05_002700E0[out][1] = v;
        D_L05_002700E0[out][0] = u;
        D_L05_0026FBE0[out] = color;
        w = D_L05_0026ECE0[out];
        D_L05_00270AE0[0].v[0] = w[0];
        D_L05_00270AE0[0].v[1] = w[1];
        D_L05_00270AE0[0].v[2] = w[2];
        D_L05_00270D60[0][0] = u;
        D_L05_00270AE0[0].v[3] = 0;
        D_L05_00270D60[0][1] = D_L05_002700E0[out][1];
        D_L05_00270CE0[0] = color;
        out++;
        nextU = u + stepV;
        v = nextV;

        for (i = 1; i < 31; i++) {
            p = D_L05_0026ECE0[out];
            p[0] = D_L05_00270AE0[i].v[0];
            p[1] = D_L05_00270AE0[i].v[1];
            p[2] = D_L05_00270AE0[i].v[2];
            D_L05_0026FBE0[out] = D_L05_00270CE0[i];
            D_L05_002700E0[out][0] = D_L05_00270D60[i][0];
            D_L05_002700E0[out][1] = D_L05_00270D60[i][1];
            out++;
            ref_L05_0042B2C0_03(&radial, &rotation2, &radial);
            ref_L05_0042B2C0_03(&radial, &radial, &inverse2);
            D_L05_0026ECE0[out][0] = center.v[0] + radial.v[0];
            D_L05_0026ECE0[out][1] = center.v[1] + radial.v[1];
            D_L05_002700E0[out][1] = v;
            D_L05_002700E0[out][0] = u;
            D_L05_0026FBE0[out] = color;
            t = D_L05_0026ECE0[out];
            D_L05_00270AE0[i].v[0] = t[0];
            D_L05_00270AE0[i].v[1] = t[1];
            D_L05_00270AE0[i].v[2] = D_L05_0026ECE0[out][2] = center.v[2] + radial.v[2];
            D_L05_00270AE0[i].v[3] = 0;
            D_L05_00270D60[i][0] = u;
            D_L05_00270D60[i][1] = D_L05_002700E0[out][1];
            D_L05_00270CE0[i] = color;
            out++;
            v += stepU;
        }

        p = D_L05_0026ECE0[out];
        p[0] = D_L05_00270AE0[i].v[0];
        p[1] = D_L05_00270AE0[i].v[1];
        p[2] = D_L05_00270AE0[i].v[2];
        D_L05_0026FBE0[out] = D_L05_00270CE0[i];
        D_L05_002700E0[out][0] = D_L05_00270D60[i][0];
        D_L05_002700E0[out][1] = D_L05_00270D60[i][1];
        out++;
        D_L05_002700E0[out][0] = u;
        D_L05_002700E0[out][1] = v;
        q = D_L05_0026ECE0[first];
        D_L05_0026ECE0[out][0] = q[0];
        D_L05_0026ECE0[out][1] = q[1];
        D_L05_0026ECE0[out][2] = q[2];
        D_L05_0026FBE0[out] = D_L05_0026FBE0[first];
        D_L05_00270D60[i][0] = u;
        D_L05_00270D60[i][1] = D_L05_002700E0[out][1];
        D_L05_00270CE0[i] = D_L05_0026FBE0[first];
        t = D_L05_0026ECE0[out];
        D_L05_00270AE0[i].v[0] = t[0];
        D_L05_00270AE0[i].v[1] = t[1];
        D_L05_00270AE0[i].v[2] = t[2];
        D_L05_00270AE0[i].v[3] = 0;
        out++;
        u = nextU;
        ref_L05_0042B2C0_02(&center, &center, &delta);
    }

    ref_L05_0042B2C0_05(6, ref_L05_0042B2C0_04(texture));
    ref_L05_0042B2C0_05(0x42, 0x8000000040ULL | ((long long)D_L05_001B1724 << 2));
    ref_L05_0042B2C0_05(8, 0);
    ref_L05_0042B2C0_05(0x14, 0xFF9000000260ULL);
    ref_L05_0042B2C0_05(0x47, 0x53001);
    ref_L05_0042B2C0_05(0x4A, 0);
    ref_L05_0042B2C0_06();
    base = 0;
    remaining = 320;
    while (1) {
        n = remaining < 149 ? remaining : 148;
        ref_L05_0042B2C0_07(n, D_L05_0026ECE0[base], &D_L05_0026FBE0[base], D_L05_002700E0[base], 1);
        remaining -= n;
        if (remaining > 0) {
            remaining += 2;
            base += n - 2;
        } else
            break;
    }
}
