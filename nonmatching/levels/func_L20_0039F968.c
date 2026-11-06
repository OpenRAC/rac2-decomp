/* 6 November 2026, Codex follow-up: current compiler reproduces the incoming
 * retained body at 996/996 bytes, 0/1 USA v1.01 places, 14 real instruction
 * differences (not the historical nine). Removing the history table-pointer local
 * gives the body below: 996/996, 0/1, 13 real differences, all +0xAC..+0xF8;
 * check.py reports "20_yeedil: instruction at +0xb0 differs". Profile remains
 * -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * New probes: real pointer-update/one-pass boundaries before the copy loop,
 * mixed indexed/cursor loops, reuse of the count/head locals, and contiguous
 * groups of the actual count/clamp/last/speed/copy operations. None closes the
 * address-association/scheduling gap. Integer/byte-pointer source views either
 * canonicalize back or change the loop more widely. -fno-cse-follow-jumps and
 * -fno-cse-skip-blocks produce 1004/1012 bytes; disabling strength reduction,
 * gcse or either scheduling pass diverges more widely. -g, -fno-force-mem,
 * -fno-sched-spec, -fno-sched-interblock and -fno-thread-jumps are unchanged.
 * No forbidden qualifiers, artificial operations or compiler changes used.
 * Next: source evidence for the CSE boundary or a qualified compiler-pass
 * explanation; further equivalent arithmetic/group spellings are tied.
 * No linked build run (lead owns builds); other releases not checked.
 */
/* 6 November 2026, round 7: body unchanged (996/996, 0/1, 9 rows). Cause found: retail's
 * src base needs cse1 NOT to relate D-16 to the dst's D (then loop keeps (i*400 + reg[D-16]) and
 * cse2 later turns it into D - 16), while cse2 must. Only a LOOP_END between them does that
 * inside the body (cse.c stops there before loop), so every in-body group adds the exit-label
 * alignment nop. A dst base pseudo `tab = D` before the loop (`&tab[i][h]`, bare D for src) gives
 * retail's exact copy-loop registers and sum; with the `history` local removed too it is 9 rows,
 * but D's lui/addiu land before the blez (source order). Behind `if (last > 0)` loop pass 2
 * hoists tab out of the outer loop (same block as its uses), 980-988 bytes. Row = D[i] forms:
 * 17 rows (hoisted high(D) takes $s1). ~135 compiles; dead ends: outer-loop row (44), index
 * forms, src-first, `history` for either side, -fno-rerun-loop-opt, -fmove-all-movables.
 */
/* 6 November 2026, round 4 (second pass): best body below, 996/996, 0/1, 9 rows (was ~33).
 * Profile -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier (rerun-loop-opt ON).
 * The copy loop as `qcopy_nc(&D[i][h], &D[i][h - 1])` fixes the prologue s1/s2, keeps state in
 * fp, and the point-loop preheader now matches. Only the copy-loop setup is left (+0xAC..+0x10C).
 * This is the func_L00_003C4F78 problem: the start is (last*16 + i*400) + (D-16), but retail has
 * last*16 + (i*400 + (D-16)). That match's fix (two-step dst in a do/while(0) group in the loop)
 * gets the right shape here too, but the group's LOOP_BEG aligns the loop's exit label (0x0039FA74,
 * unaligned in retail): +1 nop, 1004 bytes. `&D[i][-1] + h` gets the shape (the 0xFFFFFFF0 offset
 * stops cse1 relating it), but then D-16 is its own lui/addiu (24 rows). Block locals row/prev
 * inside `if (h > 0)`: rerun moves the table address into fp (988); before the guard: 17 rows.
 * Group form + -malign-loops=2 (with or without -frac2-hazard-labels): 984-988 bytes, because
 * retail's nops at +0x6C and +0xEC are real loop-head alignment. Hill-climb over declaration and
 * last/speed order (40 tries): no change from 9 rows.
 */
/* 6 November 2026: retained source unchanged (996/996, 0/1). Copy-loop source as
 * `(&D_L20_00234880[0][-1] + i * 25)[h]` (or a cast to Vector (*)[25]) gives retail's grouping
 * last*16 + (i*400 + (base-16)), but base-16 is then its own lui/addiu and comes before base;
 * retail derives it from base (addiu a1,v0,-0x10), so base must be live first. Pointer-pair and
 * `prev = &D[i][-1]` forms are worse (68-192 rows).
 */
/* Claude Opus 5.5 (opus-1, xhigh) worker, task v2165, 2026-11-03.
 * USA v1.01: 996/996 bytes, 0/1 places; first difference +0xB0. About 36 of
 * 249 rows differ once relocations are ignored, all in two places:
 *  1. History copy loop setup (+0xAC..+0x108): retail forms the source cursor
 *     as last*16 + (i*400 + (base-16)) with (base-16) an invariant register;
 *     here loop.c folds the -16 into the giv constant, so it is emitted as
 *     (last*16 + i*400) + (base-16). Retail also schedules `sll a3,s4,4;
 *     lui t0` ahead of the speed load and uses a2/a1/a0 where this has a3/v1/a0.
 *     Tried (same bytes): `.q` ARRAY_REF, `(D[i] + (h - 1))->q`,
 *     `(&D[i][h - 1])->q`; `*&D[i][h] = *&D[i][h-1]` merges both cursors.
 *  2. `last` gets $s2 and the point-loop tail cursor $s0; retail has them the
 *     other way round. Global priorities: out 42/11, tail 33/10, last 96/31;
 *     retail needs last ahead of tail. Fixing (1) may change last's refs.
 * What fixed the rest (from the 992-byte draft):
 *  - `history`/`level` locals holding the table addresses: the pseudos get no
 *    hard register, so reload rematerialises them (lui+addiu) and the madd
 *    pattern takes its LO alternative (mtlo; madd) exactly as retail does.
 *    The copy loop must keep the bare symbol (retail's lui a0; addiu v0,a0).
 *  - Point loop indexed by j with a separate up-counter n for points[n]
 *    (out cursor initialised in the preheader, after blez).
 *  - Tip via `int top = counts[i] - 1` (no folded -16).
 *  - First particle: size computed into a local before the colour store;
 *    second particle: size statement first.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier
 *          -fno-rerun-loop-opt (own unit, e.g. L20_0039F968-g8.c).
 * All required declarations follow. No linked check of this near miss.
 */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern void func_00282D30(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern int func_L02_002F1658(void);
extern void func_002AB668(void *, int, float);
extern void func_002ACDE8(void *, const void *, const void *);
extern void func_002ACB48(float *, float);
extern float func_00282DF0(const void *);
extern unsigned char *func_002C36D0(void *, int, int, int);
extern void func_L00_003C5310(void *, int, int, int, unsigned int, unsigned int, unsigned int, unsigned int,
                             int, int, int, float, float, float);
extern Vector D_L20_00234880[][25];
extern Vector D_L20_00235500[];
extern int D_L20_001B3870[] __attribute__((sda));
extern float D_L20_001AED3C __attribute__((sda));
extern float D_L20_001AED40 __attribute__((sda));
extern float D_L20_001AED50 __attribute__((sda));
extern float D_L20_001AED58 __attribute__((sda));
extern unsigned int D_L20_001AED44 __attribute__((sda));
extern unsigned int D_L20_001AED48 __attribute__((sda));
extern unsigned int D_L20_001AED4C __attribute__((sda));
extern float D_L20_001AED54 __attribute__((sda));
extern unsigned char D_L20_001FFB40[];

void func_L20_0039F968(unsigned char *object) {
    Vector points[25];
    Vector origin, offset, rotation;
    int i = 0;
    int *counts = D_L20_001B3870;
    unsigned char *level = D_L20_001FFB40;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *particle;
    int j, last;
    float length, limit;
    func_00282D30(&offset, object + 0xE0, D_L20_001AED3C);
    func_00282CC0(&origin, object + 0x10, &offset);
    for (; i < 8; ++i) {
        if (func_L02_002F1658()) {
            Vector *head;
            int historyIndex;
            float speed;
            ++counts[i];
            if (counts[i] > 24) counts[i] = 25;
            last = counts[i] - 1;
            speed = D_L20_001AED58;
            for (historyIndex = last; historyIndex > 0; --historyIndex)
                qcopy_nc(&D_L20_00234880[i][historyIndex], &D_L20_00234880[i][historyIndex - 1]);
            head = D_L20_00234880[i];
            func_002AB668(&rotation, (int)&D_L20_00235500[i], speed * 0.017453294f);
            func_002ACDE8(head, head, &rotation);
            func_002ACB48(head->f, 0.125f);
            length = func_00282DF0(head);
            limit = D_L20_001AED40 * 1.1f;
            if (limit < length) func_00282D30(head, head, limit / length);
            else {
                limit = D_L20_001AED40 * 0.9f;
                if (length < limit) func_00282D30(head, head, limit / length);
            }
        }
        last = counts[i] - 1;
        if (last < 0) last = 0;
        {
            int n = 0;
            for (j = last; j > 0; --j) {
                func_00282CC0(&points[n], &origin, &D_L20_00234880[i][j]);
                points[n].f[3] = 0.5f;
                ++n;
            }
        }
        func_00282CC0(&points[last], &origin, D_L20_00234880[i]);
        points[last].f[3] = 0.05f;
        if (func_L02_002F1658()) {
            int top = counts[i] - 1;
            Vector *tip = &points[top];
            particle = func_002C36D0(tip, 10, 0, 1);
            if (particle) {
                float size = D_L20_001AED50 * 210000.0f;
                *(unsigned int *)(particle + 4) = D_L20_001AED44 | *(unsigned int *)(state + 4);
                *(float *)(particle + 0xC) = size;
                particle[2] = (*(unsigned char **)(level + 0xF8))[1];
            }
            particle = func_002C36D0(tip, 10, 0, 1);
            if (particle) {
                *(float *)(particle + 0xC) = D_L20_001AED50 * 63000.00390625f;
                *(unsigned int *)(particle + 4) = 0x407F7F7F;
            }
        }
        func_L00_003C5310(points, 25, 14, 14, D_L20_001AED48, D_L20_001AED48 & 0xFFFFFF,
                          D_L20_001AED4C | *(unsigned int *)(state + 4), D_L20_001AED4C,
                          0, counts[i] - 1, counts[i], 0.1f, 0.2f, D_L20_001AED54);
    }
}
