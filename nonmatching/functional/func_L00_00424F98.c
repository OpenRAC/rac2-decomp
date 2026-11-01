/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* func_L00_00424F98 (380 bytes) - near miss. Claude Opus 5.5 (opus-1), v1647, 30 October 2026.
 * Profile: standalone unit, "-O2 -G8 -ffunction-sections -g" (e.g. L00_00424F98-g8-dbg.c).
 * Best check.py: 376 of 380 bytes, 0/27 places; every instruction matches except one
 * missing nop before the final div.s (and the bc1f offset that follows from it).
 * Control flow is now retail's: the forced-zero y path (flags & 2) jumps straight to the
 * throttle division (retail +0x120 `b` -> +0x160), and the non-zero y test returns to the
 * epilogue. Writing it as `if (*y != 0.0f) return;` inside the else and the division
 * after the if/else gives that join, and the join label also keeps the bc1f delay slot
 * empty as in retail (the earlier drafts tested *y after the if/else: no jump threading,
 * divisor load stolen into the bc1f slot; the sol-high nested form returned on flags & 2,
 * which is not retail's behaviour).
 * Remaining word: retail is `L: lwc1 f0,0x24(t0) ; lwc1 f1,gp ; nop ; div.s`. The -g line
 * label of the division statement sits before `lwc1 f1` (one slot), so the SDK division
 * floor wants one nop, but this gas counts the gp load macro's relaxation alternatives
 * (gp-relative + lui/lwc1 in a variant frag) toward the fallback distance, saturating it at
 * two: no nop. A non-macro load (`lwc1 $f1,0($9)`) after the same label does get the nop.
 * Needs: pad_div_erratum_nops.py to count only the emitted alternative of a relaxable load
 * (assembler change, not C). The SDATA view and the plain sda scalar tie.
 * Declarations: all below.
 */
#include "include_asm.h"
#include "common.h"

/* The resident challenge counter: runs, best time and a bit per level. */
typedef struct {
    char pad[0x60];
    unsigned short count;
    unsigned short pad62;
    unsigned int best;
    unsigned int flags;
} L00_00424F98_Counter;

/* The vehicle's input block, at +0x1C0 of its motion record. */
typedef struct {
    char pad0[0x10];
    int flags;
    float steer_out;
    char pad18[4];
    float steer;
    char pad20[4];
    float throttle;
} L00_00424F98_Input;

extern float D_00138280[];
extern float D_00138284[];
extern s32 D_001A7BA8 MACRO_ADDR;
extern s32 D_001A7BA4 MACRO_ADDR;
extern s32 D_001A79F0 MACRO_ADDR;
extern unsigned int D_001A7390 MACRO_ADDR;
extern L00_00424F98_Counter D_0018C750;
extern s32 ref_L00_00424F98_00 __attribute__((sda));
extern s32 ref_L00_00424F98_01 __attribute__((sda));
extern float ref_L00_00424F98_02 __attribute__((sda));
extern float ref_L00_00424F98_03 SDATA(ref_L00_00424F98_03);

/* The vehicle's steering and throttle inputs, with the stunt counter: holding the
   stick centred for a second counts one run and records the best time. */
void func_L00_00424F98(char *obj, float *x, float *y)
{
    L00_00424F98_Input *t = (L00_00424F98_Input *)(*(char **)(obj + 0x70) + 0x1C0);
    L00_00424F98_Counter *c;
    unsigned int n;
    float v;

    if (t->flags & 1) {
        *x = 0.0f;
    } else {
        *x = D_00138280[0];
        if (D_001A7BA8 == 0)
            *x = -*x;
    }
    if (*x == 0.0f) {
        ref_L00_00424F98_00 = 0;
        ref_L00_00424F98_01 = 0;
        if (t->steer != 0.0f)
            *x = t->steer;
    } else {
        t->steer_out = ref_L00_00424F98_02;
        c = &D_0018C750;
        n = c->count;
        if ((unsigned short)n < 3U) {
            ref_L00_00424F98_00++;
            if (ref_L00_00424F98_01 == 0 && ref_L00_00424F98_00 > 0x3C) {
                if ((unsigned short)n < 0xFFFF)
                    c->count = n + 1;
                if (D_001A7390 > c->best)
                    c->best = D_001A7390;
                ref_L00_00424F98_01 = 1;
                c->flags = (c->flags | (1 << D_001A79F0)) | 0x80000000;
            }
        }
    }
    if (t->flags & 2) {
        *y = 0.0f;
    } else {
        v = D_00138284[0];
        *y = -v;
        if (D_001A7BA4 == 0)
            *y = v;
        if (*y != 0.0f)
            return;
    }
    {
        float throttle = t->throttle;
        *y = throttle / ref_L00_00424F98_03;
    }
}
