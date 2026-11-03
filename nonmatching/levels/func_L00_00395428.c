/* Reconstructed on 2026-10-23, revised 2026-11-03 (v2138); default -O2 -G8 -ffunction-sections.
 * US: 1412/1428 bytes, 0/27 placements (previous draft 1360/1428).
 * The 2026-11-03 revision recovers these retail forms:
 * - NOT_SDA on D_L00_0025C64C: split lui in the beq delay slot.
 * - MACRO_ADDR on the four short arrays: per-access lui/addiu pairs.
 * - A separate scan index k: the scan loop gets caller-saved registers.
 * - Count-up indexed j-loops: loop.c recomputes i*80 per preheader, and the
 *   D[i][0] store uses retail's mtlo/madd.
 * Remaining difference: the giv start of &D[i][j-1].
 * - Retail computes (i*80 + la(D-16)) + 16 for every j-1 pointer and
 *   (la(D) + i*80) + 16 for every j pointer, with separate D and D-16 loads.
 * - Here, &D[i][j - 1] keeps the D-16 load, but cse use_related_value
 *   rewrites whichever of D / D-16 comes second as reg +/- 16.
 * - The pointer forms (&D[i][j] - 1, D[i] + j - 1 and (&D[i][j])[-1]) all give
 *   la(D) + (i*80 - 16): +52 bytes over the canonical form, still wrong.
 * - MACRO_ADDR on the table hoists la(D) into a saved register and spills
 *   (1364-1384 bytes).
 * Other remaining differences:
 * - object stays in $s6 rather than $fp.
 * - The beqz delay slot is copied from case 0 rather than stolen.
 * - bnez rather than bnel at the else arm.
 * - The !emitting path branches straight to the loop end; retail branches
 *   to a `b; addiu s6,s4,1` stub. A nested if gives identical code.
 * Reopen with a spelling that keeps both D and D-16 table loads, unrelated by cse.
 * The older comments below are preserved as historical provenance, not conclusions.
 */
/* MMI (SPECIAL2) instruction: no C spelling. 1428 bytes, level
   00_aranos_tutorial. Retail at 0x00395428 carries the SPECIAL2 words
   0x72821800, 0x72821800 (+0x030C, +0x049C) - opcode 0x1C, which rabbitizer
   prints as `INVALID`; it is the MMI family (pcpyld and its relatives) the
   sixth wave recorded and that no C spelling reaches. This cc1 emits
   `lq`/`sq` for a `mode(TI)` local and `ldl`/`ldr`/`sdl`/`sdr` for a struct
   assignment, never the packed copy. ASM_FUNC candidate, as for the rest of
   the family. */

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { char pad[0x2290]; char *object; int mode; } WorldState;
extern WorldState D_00189E20;
extern float D_L00_0025C64C NOT_SDA;
extern short D_L00_001B2778[] MACRO_ADDR, D_L00_001B2790[] MACRO_ADDR, D_L00_001B27A8[] MACRO_ADDR, D_L00_001B27C0[] MACRO_ADDR;
extern int D_L00_001AF278 __attribute__((sda));
extern int D_L00_001AF27C __attribute__((sda));
extern float D_L00_001AF274 __attribute__((sda));
extern float D_L00_001B27DC __attribute__((sda));
extern int D_L00_001B27D4, D_L00_001B27D8;
extern Vector D_L00_00239EF0[][5];
extern Vector D_L00_001B8DC0;
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_0029F530(void *);
extern int func_00282948(int *);
extern float func_00283CE0(int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7988(void *, float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_L00_003959C0(void);
extern void func_L00_002E6EF8(void *, void *);

void func_L00_00395428(char *object)
{
    Vector origin, random, difference, offsets[5];
    int emitting = 0;
    int i, j, k, active;
    float distance;
    if (*(unsigned char *)(D_00189E20.object + 0x43) != 0x7B)
        D_L00_0025C64C = 0.1f;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned char *)(object + 0x20) = 2;
        {
            short *a = D_L00_001B2778, *b = D_L00_001B27A8, *c = D_L00_001B27C0;
            for (i = 9; i >= 0; i--) {
                *a++ = 0;
                *b++ = 2;
                *c++ = 1;
            }
        }
        D_L00_001B27D4 = D_L00_001AF278;
        D_L00_001B27D8 = D_L00_001AF27C;
        break;
    case 2:
        if (D_00189E20.mode == 31) {
            distance = func_0029F530(object);
            if (distance >= 6.0f) {
                emitting = 1;
                if (!func_00282948(&D_L00_001B27D4)) {
                    float elapsed = func_00283CE0(D_L00_001B27D4);
                    elapsed /= func_00283CE0(D_L00_001AF278);
                    D_L00_001B27DC = 1.0f - elapsed;
                } else if (distance >= 12.0f) {
                    if (!func_00282948(&D_L00_001B27D8)) {
                        float elapsed = func_00283CE0(D_L00_001B27D8);
                        elapsed /= func_00283CE0(D_L00_001AF27C);
                        D_L00_001B27DC = elapsed;
                    } else {
                        D_L00_001B27DC = 0.0f;
                    }
                } else {
                    D_L00_001B27DC = 1.0f;
                }
            }
        } else {
            D_L00_001B27D4 = D_L00_001AF278;
            D_L00_001B27D8 = D_L00_001AF27C;
            func_002A7470(object, 1, 0, 12);
        }
        break;
    }
    func_00282D30(&origin, object + 0xD0, -0.5f);
    func_00282CC0(&origin, &origin, object + 0x10);
    active = 0;
    for (k = 0; k < 10; k++) {
        if (D_L00_001B2778[k]) {
            active = 1;
            break;
        }
    }
    if (!emitting && !active)
        return;
    for (i = 0; i < 10; i++) {
        if (--D_L00_001B2778[i] < 0)
            D_L00_001B2778[i] = 0;
        if (!D_L00_001B2778[i]) {
            if (!emitting)
                continue;
            D_L00_001B2778[i] = 2;
            D_L00_001B2790[i] = 64;
            func_002A7988(&random, D_L00_001AF274, D_L00_001AF274);
            D_L00_00239EF0[i][0].q = origin.q;
            {
                float sign = 1.0f;
                for (j = 1; j < 5; j++) {
                    func_00282CF0(&difference, (&D_L00_00239EF0[i][j] - 1), &D_L00_001B8DC0);
                    func_002ACEC0(&random, &random, &difference,
                                 func_002A7878(0.174532949924469f, 0.7853982448577881f) * sign);
                    sign = -sign;
                    func_00282CC0(&D_L00_00239EF0[i][j], (&D_L00_00239EF0[i][j] - 1), &random);
                }
            }
        } else {
            for (j = 1; j < 5; j++) {
                func_00282CF0(&offsets[j], &D_L00_00239EF0[i][j], (&D_L00_00239EF0[i][j] - 1));
                offsets[j].f[0] += func_002A78D8(0.0f, 0.1f);
                offsets[j].f[1] += func_002A78D8(0.0f, 0.1f);
                offsets[j].f[2] += func_002A78D8(0.0f, 0.1f);
            }
            D_L00_00239EF0[i][0].q = origin.q;
            for (j = 1; j < 5; j++)
                func_00282CC0(&D_L00_00239EF0[i][j], (&D_L00_00239EF0[i][j] - 1), &offsets[j]);
            if (D_L00_001B2778[i] > 0)
                D_L00_001B2790[i] = 32;
            else
                D_L00_001B2790[i] = 0;
        }
    }
    func_L00_002E6EF8(func_L00_003959C0, object);
}
