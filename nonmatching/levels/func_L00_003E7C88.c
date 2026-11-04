/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 436/436 bytes, 0/27 placements; first difference 0xc.
 * Profile: -O2 -G64 -Wa,-G64 -ffunction-sections -fno-strength-reduce -fno-rerun-loop-opt.
 * Current source reproduces 436 bytes in USA v1.01 and v2.00; PAL has no canonical row. The old
 * 412-byte index entry is superseded. Index/fade saved-register roles and the D-1 base remain
 * different.
 * Earlier measurements below are historical where superseded by this note.
 */
/*
 * Retained manual C reconstruction; not linked or counted.
 * Tier opus-1 (Claude Opus 5.5, xhigh), task v2202, 3 November 2026.
 * Profile: -O2 -G64 -Wa,-G64 -ffunction-sections -fno-strength-reduce -fno-rerun-loop-opt,
 * as its own unit src/levels/shared/L00_003E3258-fade.c (one appended cflags line; replace
 * the INCLUDE_ASM marker in L00_003E3258.c with a comment). func_L00_003E80A8 stays in
 * L00_003E3258.c and func_L00_003E7E40 in L00_003E7E40-trails.c.
 * Retail: 436 bytes; compiled: 436 bytes. Coverage: us 0/27 (tools/check.py: first
 * difference at +0xc). cdiff: 33 of 109 rows differ, and most of those are relocation-only.
 *
 * Fades the 32-byte records of the table at D_L00_0024EFC0: a fading record advances and is
 * drawn; a finished one runs its callback (or frees its object) and is replaced by the
 * last record.
 *
 * Every instruction, the frame (0x60, $s0-$s7, $ra, $f20) and the loop.c hoisting
 * (0.0 and sym-32 hoisted; 1/60, 0x80 and base+16 not hoisted) match retail. Only two
 * register choices differ:
 *  1. i is in $s4 and fade in $s3 (retail: i $s3, fade $s4). Global priority is
 *     floor_log2(refs)*refs/live: fade has 11 refs over 106 insns, i has 9 refs over 122.
 *     Moving `i = 0` into the if does not change the order. Retail must give i at least
 *     13 refs, or give fade 7 refs or fewer, with the same code.
 *  2. The hoisted D-1 is rebuilt by cse2 as $s2(p)-32 (retail: $s6(base)-32). cse
 *     make_regs_eqv makes p the canonical register for the symbol because p lives longer
 *     than base.
 * Findings that got here (the earlier drafts gave 412/432 bytes):
 *  - base = D; offset = 0; p = base; fade = &p->fade, in this order. A copy that
 *    directly follows its source's set is swapped by cse (the lo_sum then goes to p).
 *  - The end record must use the symbol form (D - 1) + cnt*32. TREE_CONSTANT arg0 stops
 *    fold reassociating, and expand_binop swaps the CONST so that `addu v1,v1,s7` results.
 *  - The callback address needs base+16 first and offset as the first addu operand.
 *    Single-expression forms are reassociated by fold into base+(offset+16). The symbol
 *    form keeps the operand order, but loop.c hoists its high/lo_sum pair (savings 2).
 *    A separate int temp gives `addiu v0,base,16; addu s1,offset,v0` (life 1, not hoisted).
 */
#include "common.h"

typedef struct {
    char *object;
    unsigned char rgb[4];
    int unused;
    float fade;
    void (*callback)(char *);
    int rest[3];
} FadeEntry;

extern FadeEntry D_L00_0024EFC0[];
extern int D_L00_001B2B60[] __attribute__((sda));
extern float D_L00_001B065C __attribute__((sda));
extern int D_L00_001B0648[3] __attribute__((sda));
extern char *D_L00_001B0650[] __attribute__((sda));
extern void ref_L00_003E7C88_00(float *, float, float);
extern void func_L00_003E7E40(char *, void *, float);
extern void func_L00_003E80A8(int, char *);
extern void func_002A0488(char *, int, int, int);
extern void func_0029F338(char *);

void func_L00_003E7C88(void) {
    int i;
    i = 0;
    if (D_L00_001B2B60[0] > 0) {
        FadeEntry *base = D_L00_0024EFC0;
        int offset = 0;
        FadeEntry *p = base;
        float *fade = &p->fade;
        do {
            char *o = p->object;
            if (*fade != 0.0f) {
                ref_L00_003E7C88_00(fade, 0.0f, D_L00_001B065C * 0.01666666753590107f);
                func_L00_003E7E40(o, D_L00_001B0648, *fade);
                func_L00_003E80A8(i, D_L00_001B0650[0]);
            } else {
                int callbacks = (int)&base->callback;
                void (**callback)(char *) = (void (**)(char *))(offset + callbacks);
                if (*callback) {
                    func_002A0488(o, p->rgb[0], p->rgb[1], p->rgb[2]);
                    *(unsigned char *)(o + 35) = 128;
                    *(unsigned short *)(o + 52) &= ~2;
                    (*callback)(o);
                } else func_0029F338(o);
                {
                    FadeEntry *end = (FadeEntry *)((char *)(D_L00_0024EFC0 - 1) + D_L00_001B2B60[0] * 32);
                    D_L00_001B2B60[0]--;
                    *p = *end;
                }
            }
            i++;
            p++;
            fade += 8;
            offset += 32;
        } while (i < D_L00_001B2B60[0]);
    }
}
