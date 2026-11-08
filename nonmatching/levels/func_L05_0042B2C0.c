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
    VBC unit, center, delta, radial, rotation, inverse, rotation2, inverse2;
    float u = startU, nextU, v;
    int i, row, out = 0, remaining, base, first;
    unit.q = 0;
    unit.v[3] = unit.v[2] = 1.0f;
    qcopy(&center, origin);
    ref_L05_0042B2C0_00(&delta, axis, advance);
    ref_L05_0042B2C0_00(&radial, &unit, radius);
    radial.v[3] = 0;
    ref_L05_0042B2C0_01(&rotation, axis, 0.202683404f);
    ref_L05_0042B2C0_00(&inverse, &rotation, -1.0f);
    inverse.v[3] = rotation.v[3];
    ref_L05_0042B2C0_02(&D_L05_00270AE0[0], &center, &radial);
    D_L05_00270D60[0][0] = u;
    D_L05_00270D60[0][1] = startV;
    D_L05_00270CE0[0] = color;
    v = startV + stepU;
    for (i = 1; i < 31; i++) {
        ref_L05_0042B2C0_03(&radial, &rotation, &radial);
        ref_L05_0042B2C0_03(&radial, &radial, &inverse);
        ref_L05_0042B2C0_02(&D_L05_00270AE0[i], &center, &radial);
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
    row = 1;
    do {
        ref_L05_0042B2C0_00(&radial, &unit, radius);
        v = startV;
        ref_L05_0042B2C0_01(&rotation2, axis, 0.202683404f);
        radial.v[3] = 0;
        ref_L05_0042B2C0_00(&inverse2, &rotation2, -1.0f);
        inverse2.v[3] = rotation2.v[3];
        if (row == 5) color &= 0xFFFFFF;
        i = 0;
        D_L05_0026ECE0[out][0] = D_L05_00270AE0[i].v[0];
        D_L05_0026ECE0[out][1] = D_L05_00270AE0[i].v[1];
        D_L05_0026ECE0[out][2] = D_L05_00270AE0[i].v[2];
        D_L05_002700E0[out][0] = D_L05_00270D60[i][0];
        D_L05_002700E0[out][1] = D_L05_00270D60[i][1];
        D_L05_0026FBE0[out] = D_L05_00270CE0[i];
        out++;
        first = out;
        D_L05_0026ECE0[out][0] = center.v[0] + radial.v[0];
        D_L05_0026ECE0[out][1] = center.v[1] + radial.v[1];
        D_L05_0026ECE0[out][2] = center.v[2] + radial.v[2];
        D_L05_002700E0[out][0] = u;
        D_L05_002700E0[out][1] = v;
        D_L05_0026FBE0[out] = color;
        D_L05_00270AE0[i].v[0] = D_L05_0026ECE0[out][0];
        D_L05_00270AE0[i].v[1] = D_L05_0026ECE0[out][1];
        D_L05_00270AE0[i].v[2] = D_L05_0026ECE0[out][2];
        D_L05_00270AE0[i].v[3] = 0;
        D_L05_00270D60[i][0] = u;
        D_L05_00270D60[i][1] = D_L05_002700E0[out][1];
        D_L05_00270CE0[i] = color;
        out++;
        nextU = u + stepV;
        v += stepU;
        i = 1;
        do {
            D_L05_0026ECE0[out][0] = D_L05_00270AE0[i].v[0];
            D_L05_0026ECE0[out][1] = D_L05_00270AE0[i].v[1];
            D_L05_0026ECE0[out][2] = D_L05_00270AE0[i].v[2];
            D_L05_002700E0[out][0] = D_L05_00270D60[i][0];
            D_L05_002700E0[out][1] = D_L05_00270D60[i][1];
            D_L05_0026FBE0[out] = D_L05_00270CE0[i];
            out++;
            ref_L05_0042B2C0_03(&radial, &rotation2, &radial);
            ref_L05_0042B2C0_03(&radial, &radial, &inverse2);
            D_L05_0026ECE0[out][0] = center.v[0] + radial.v[0];
            D_L05_0026ECE0[out][1] = center.v[1] + radial.v[1];
            D_L05_002700E0[out][1] = v;
            v += stepU;
            D_L05_00270D60[i][1] = D_L05_002700E0[out][1];
            D_L05_00270AE0[i].v[0] = D_L05_0026ECE0[out][0];
            D_L05_00270AE0[i].v[1] = D_L05_0026ECE0[out][1];
            D_L05_00270AE0[i].v[2] = D_L05_0026ECE0[out][2] = center.v[2] + radial.v[2];
            D_L05_0026FBE0[out] = color;
            D_L05_002700E0[out][0] = u;
            D_L05_00270AE0[i].v[3] = 0;
            D_L05_00270CE0[i] = color;
            D_L05_00270D60[i][0] = u;
            out++;
        } while (++i < 31);
        D_L05_0026ECE0[out][0] = D_L05_00270AE0[i].v[0];
        D_L05_0026ECE0[out][1] = D_L05_00270AE0[i].v[1];
        D_L05_0026ECE0[out][2] = D_L05_00270AE0[i].v[2];
        D_L05_002700E0[out][0] = D_L05_00270D60[i][0];
        D_L05_002700E0[out][1] = D_L05_00270D60[i][1];
        D_L05_0026FBE0[out] = D_L05_00270CE0[i];
        out++;
        D_L05_0026ECE0[out][0] = D_L05_0026ECE0[first][0];
        D_L05_0026ECE0[out][1] = D_L05_0026ECE0[first][1];
        D_L05_0026ECE0[out][2] = D_L05_0026ECE0[first][2];
        D_L05_002700E0[out][1] = v;
        D_L05_002700E0[out][0] = u;
        D_L05_0026FBE0[out] = D_L05_0026FBE0[first];
        D_L05_00270D60[i][0] = u;
        D_L05_00270D60[i][1] = D_L05_002700E0[out][1];
        D_L05_00270CE0[i] = D_L05_0026FBE0[first];
        D_L05_00270AE0[i].v[0] = D_L05_0026ECE0[out][0];
        D_L05_00270AE0[i].v[1] = D_L05_0026ECE0[out][1];
        D_L05_00270AE0[i].v[2] = D_L05_0026ECE0[out][2];
        D_L05_00270AE0[i].v[3] = 0;
        out++;
        u = nextU;
        ref_L05_0042B2C0_02(&center, &center, &delta);
    } while (++row < 6);
    ref_L05_0042B2C0_05(6, ref_L05_0042B2C0_04(texture));
    ref_L05_0042B2C0_05(0x42, 0x8000000040ULL | ((long long)D_L05_001B1724 << 2));
    ref_L05_0042B2C0_05(8, 0);
    ref_L05_0042B2C0_05(0x14, 0xFF9000000260ULL);
    ref_L05_0042B2C0_05(0x47, 0x53001);
    ref_L05_0042B2C0_05(0x4A, 0);
    ref_L05_0042B2C0_06();
    remaining = 320; base = 0;
    while (remaining > 0) {
        int n = remaining < 149 ? remaining : 148;
        ref_L05_0042B2C0_07(n, D_L05_0026ECE0[base], &D_L05_0026FBE0[base], D_L05_002700E0[base], 1);
        remaining -= n;
        if (remaining > 0) { remaining += 2; base += n - 2; }
    }
}
