/* 5 November 2026, round 4c: draft below is the 2-row form. Unit: its own file, e.g. src/game/0029F840-nogcse.c, with the cflags.txt line `-O2 -G0 -ffunction-sections -fno-gcse`; remove the INCLUDE_ASM line from src/game/0029DE38.c. Tried without gain: rec += 0x10 or the call inside the second group (mul.s before addu again), k and rec swapped (sll before li.s), k and rec in separate groups or only rec grouped (same 2 rows), `s *= k` before the call (same), a next pointer `dst = rec + 0x10` (allocation changes, 77 rows). A loop-note barrier always lands on mul.s, so `rec += 0x10` issues after the call; retail probably needs a real label boundary. */
/* 5 November 2026, round 4b: in its own unit with -O2 -G0 -ffunction-sections -fno-gcse (precedent: L03_00424C40-g8.c, 002A9640-rc2.c), the goto-fail form plus three groups gets 288/288, 2 rows: `do { s = *(float *)(obj + 0x2C); } while (0);`, `do { k = 0.0009765625f; rec = (char *)tab + e * 16; } while (0);`, `do { n = *(short *)(rec + 6); } while (0);`. bne slot, l.s/li.s/sll/addu/mul.s order and s3/s4 are right. Left: the end of the second group makes mul.s a sched2 barrier, so `rec += 0x10` (prio 4) issues after the call (prio 9) and the jal slot takes `move a1,s1` instead of `addiu s1,s1,0x10`. With only the s group and the n group: 4 rows (mul.s before addu, because li.s is the barrier and sll and mul.s become ready together). Putting the multiply in the second group, k * s, or k before s: no change. */
/* 5 November 2026, round 4: a shared `fail:` label in the e-test return block (cnt == 0 does `goto fail`) wrapped in `do { fail: return 0; } while (0);` stops cse1 following into the body (LOOP_END before the label defeats follow-jumps, the label defeats skip-blocks), so `a0 = p` survives cse1; gcse cprop then rewrites it (COPY-PROP reg p -> m), still 12 rows. With -fno-gcse that form gives retail's `bne / move a0,s0`, but the body stays l.s, sll, li.s, addu, a1, mul.s. Retail matched functions with a delay-slot zero-copy (002E7B48, 00334160, 003506B0) are s-register loop counters, not this idiom. */
/* 5 November 2026 (w-c5): reuse the hdr variable as the first-call argument (`char *p = *(char **)(obj + 0x24); ... tab = (int)p + cnt * 16; ... e = ...; p = m; if (e == 0xFF) return 0;`): 288/288, 0/28, 7 rows, prologue and hdr in a0 now right. Left: a0 = m before bne. Dumps show cse1 (following the jump into the one-use body label) turns `a0 = p` back into `a0 = m`, and m stays canonical because it lives longer; groups, `char *a = m` at entry, and p = m before/inside the e or float group do not change that. A float-load group gives the sched2 barrier after l.s but swaps s3/s4. */
/* 5 November 2026: new, no gain: the three transform calls as a static inline helper (288/288, 0/28, rec in s2, setup order unchanged); the joint lookup as an inline returning NULL with a caller test (304 bytes, the NULL test stays). Remaining: a0 = m first in the bne slot needs the block boundary after l.s. */
/* 5 November 2026 (w-c4): `n = 0; if (e != 0xFF) { body }` inverts the cnt test (bnez/b), regresses the prologue; no new form found. Retail fills bne's slot from before the branch (a0 = m set before the e test), so the next lever is a real a0-before-test source shape. */
/* 4 November 2026 current-RAC1 source-method trial; retained, not linked.
 * Removed the synthetic always-zero e & 0x100 arm. Three actual scale/setup/first-transform
 * groups each give 288/288 bytes, 0/28 USA placements, first +0x10. The object/count registers
 * and first-call setup remain different. The retained C is the measured real first-transform
 * group; historical exact claims below concern the removed synthetic arm.
 */
/* func_0029F840 - 288 bytes, 28 places (the boot and every level). Tier: Opus 5.5 xhigh, 1 Nov 2026.
   Best check.py result: the C below gives 28 of 28 places in USA v1.01, PAL and v2.00. tools/build.py was not
   run. No match is claimed and the marker stays in src/: the exact bytes need the `if (out != 0)` arm, whose
   `e & 0x100` is always 0 because e is a byte. That is a fake dependency with value-identical arms, whose only
   effect is on scheduling and allocation (AGENTS.md "Rules"; WORKER2.md reports such a form as FAILED).
   Needs a maintainer's ruling, or the original construct. It has the "real test that vanished" shape of
   func_002D3D88, except that its adjustment is an invented always-zero term, not a parameter passed 0.

   Without that arm (the call taking m and the field load directly): 288/288 bytes, 0/28 places, 12 of 72 cdiff
   rows differ, all in the first call's setup.
   Retail:  bne v0,v1 / [move a0,s0]; b / [v0=0]; l.s f12; li.s f20; sll; addu s1; mul.s; move a1,s1; jal
   Clean C: bnel v0,v1 / [l.s f12];   b / [v0=0]; sll; li.s f20; addu s1; move a1,s1; move a0,s0; mul.s; jal

   What retail's order requires, measured with cc1 -dS -dR -fsched-verbose-6:
   - sched2 sees a block boundary right after l.s. l.s and li.s share the one memory unit, so in one block sll
     pairs with l.s; a block starting at li.s gives retail's li.s, sll, addu, mul.s, a1.
   - a0 is set before that boundary through a pseudo p. With p = m in both arms of a test, gcse's cprop rewrites
     a0 = p to a0 = m and a0 stays late, so p's second set must not be a plain copy until after cprop.
   - The test must stay live up to sched2. With a test combine folds (`if (e & 0x100)`, arm p = out; s = 1.0f),
     greg has a0 = s0; l.s; jump, but the label is gone by sched2 and the result is the clean C's 12 rows.
   How the form below gets there, from the dumps: cse2 still has p = m + t; combine reduces it to p = m; greg
   gives a0 = s0 in both places; sched2 keeps the test and the arm, so the boundary holds; jump2 removes the
   arm's redundant move and the test, leaving no word.

   Next: a construct with a real reason to be there that collapses after cse2, probably from a macro or inline
   helper in the original. Measured, not retail: `int adj = 0; ... m + adj * 16` in the arm (the clean C's 12
   rows); `if (e < 0) p = out;` (movn, 304 bytes); `if (e < 0) { p = out; s = 1.0f; }` (304 bytes, the setup in
   retail's order but the test and arm stay); both arms p = m; s = field on `index != 0` (boundary right, a0
   late, s3 and s4 exchanged).
   Needs only the externs below. */
#include "common.h"

extern void func_00282D60(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283130(void *, unsigned long long);
extern void func_00282D30(void *, void *, float);
int func_0029F840(char *obj, char *m, char *out, int index) {
    char *p = *(char **)(obj + 0x24);
    int cnt = *(short *)(p + 0x2E);
    int tab;
    char *rec;
    int n;
    int i;
    int e;
    char *dst;
    float k;
    float s;

    if (cnt == 0) {
        goto fail;
    }
    tab = (int)p + cnt * 16;
    index += tab;
    e = ((unsigned char *)index)[1];
    p = m;
    if (e == 0xFF) {
        do {
fail:
            return 0;
        } while (0);
    }
    do {
        s = *(float *)(obj + 0x2C);
    } while (0);
    do {
        k = 0.0009765625f;
        rec = (char *)tab + e * 16;
    } while (0);
    func_00282D60(p, rec, s * k);
    rec += 0x10;
    func_00283098(m, m, obj + 0xC0);
    func_00282CC0(m, m, obj + 0x10);
    do {
        n = *(short *)(rec + 6);
    } while (0);
    if (out != 0 && n > 0) {
        dst = out;
        for (i = n; i != 0;) {
            i--;
            func_00283130(dst, *(unsigned long long *)rec);
            rec += 8;
            func_00282D30(dst, dst, *(float *)(obj + 0x2C) * k);
            *(float *)(dst + 0xC) = 1.0f;
            dst += 0x10;
        }
    }
    return n;
}
