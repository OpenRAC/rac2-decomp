/* Claude Opus 5.5 xhigh, task v1671, 2026-10-30; USA v1.01, level 20 only.
 * Best check.py: 756/756 bytes, 0/1 places; six of 189 instructions differ.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier
 * -frac2-zero-ti-por, in a dedicated -g8.c unit. Not a linked match.
 * Frame, saves, every callee-saved register (s7 next index, fp the 38C8 table),
 * all three loops and all scheduling agree except:
 * 1. +0x158..+0x164, the W pointer: this C forms (i*0xA0 + (table+0xC)) + 0x10,
 *    retail (table + i*0xA0) + 0x1C. expand_mult_add yields retail's only for a
 *    giv addend with a trailing constant, and simplify_giv_expr's
 *    sge_plus_constant gives that only for (plus REG const): the sum must be one
 *    register the loop pass cannot look through. A row pointer set before the
 *    loop shares its multiply with the [i][0] store and costs that store's madd;
 *    set inside the loop it is looked through. Tried: .f[3], (t[i]+j)->f[3],
 *    a point variable, a float pointer walk, a local table pointer.
 * 2. +0x230..+0x238: the ori of 0x7F7F7F follows the 38C8 table load; retail has
 *    it between the 38B0 and 38C8 loads. Its RTL position comes from when the
 *    loop pass moves it (second pass here).
 * What the rest needed: natural count-up draw loop with its own counter (gives
 * retail's giv order); MACRO_ADDR on all three short tables; and the previous
 * point read through a second name of the history table, so cse does not
 * rewrite table-0x10 as (table reg - 0x10). That keeps the giv addend a plain
 * register and lowers the table pseudo's priority below the 38C8 table's. The
 * _1 and _2 names are aliases of D_L20_00235580 with no other evidence: judge
 * them before landing. Reopen with a source shape for item 1.
 * Declarations and approved helpers follow.
 */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282CF0(void *, const void *, const void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_L00_002EBE88(void *, int, int, int, unsigned int, unsigned int, float, float, float);
extern short D_L20_001B38B0[10] MACRO_ADDR;
extern short D_L20_001B38C8[10] MACRO_ADDR;
extern short D_L20_001B38E0[10] MACRO_ADDR;
extern float D_L20_001B3904[] MACRO_ADDR;
extern Vector D_L20_00235580[10][10];
extern Vector D_L20_00235580_1[10][10];
extern Vector D_L20_00235580_2[10][10];
extern float D_L20_001AED84 __attribute__((sda));
extern unsigned int D_L20_001AED18 __attribute__((sda));
extern unsigned int D_L20_001AED1C __attribute__((sda));

void func_L20_0039F268(unsigned char *object) {
    Vector offset;
    Vector origin;
    Vector differences[10];
    unsigned char *state = *(unsigned char **)(object + 0x68);
    int i, j, k, alphaValue;
    float numerator, denominator;
    unsigned int colour;
    offset.q = 0;
    offset.f[2] = 0.75f;
    func_00282CC0(&origin, object + 0x10, &offset);
    for (i = 0; i < 10; ++i) {
        if (D_L20_001B38B0[i]) {
            for (j = 1; j < 10; ++j)
                func_00282CF0(&differences[j], &D_L20_00235580[i][j], &D_L20_00235580_1[i][j - 1]);
            qcopy(&D_L20_00235580[i][0], &origin);
            D_L20_00235580[i][0].f[3] = 0.04f;
            for (j = 1; j < 10; ++j) {
                func_00282CC0(&D_L20_00235580[i][j], &D_L20_00235580_1[i][j - 1], &differences[j]);
                ((float *)&D_L20_00235580_2[i][j])[3] = 0.04f;
            }
            if (D_L20_001B38B0[i] > 0) {
                numerator = func_00283CE0(D_L20_001B38B0[i]);
                denominator = func_00283CE0(D_L20_001B38E0[i]);
                D_L20_001B38C8[i] = func_00283CF0(D_L20_001AED84 * *(float *)(state + 0x14) * (numerator / denominator));
            } else D_L20_001B38C8[i] = 0;
        }
    }
    for (k = 0; k < 10; ++k) {
        if (D_L20_001B38B0[k]) {
            alphaValue = func_00283CF0(func_00283CE0(D_L20_001B38C8[k]) * D_L20_001B3904[0]);
            colour = D_L20_001AED18;
            if (*(short *)(object + 0xAA) == 0x1192) colour = D_L20_001AED1C;
            func_L00_002EBE88(D_L20_00235580[k], 23, 14, 10,
                             ((unsigned int)alphaValue << 24) | 0x7F7F7F,
                             ((unsigned int)alphaValue << 24) | colour, 0.0f, 4.0f, 0.0f);
        }
    }
}
