/* 4 November 2026: faithful retained C; no linked match.
 * Replace the per-function cvt.w.s/mfc1 inline assembly with an ordinary C cast.
 * us: 732/736 bytes, 0/2 places; us2: absent; pal: absent.
 * Profile: -O2 -G0 -ffunction-sections.
 * Reopen: Find an independently evidenced original rounding/control-flow boundary; do not restore instruction primitives or dummy branches.
 * Earlier measurements below are historical, including any diagnostic-only
 * constructs they describe; those constructs are no longer active C.
 */
/* func_L04_00417028 - 736 bytes, places 04:00417028 and 11:00406B28.
 * Tier opus-2 (v1823), 31 October 2026: C below retained, not admissible, recompiled here: 736/736
 * bytes, 0/2 places, 63 cdiff rows differ, link values included. The overseer's lead (a test that vanishes, as in func_002D3D88)
 * did not work; func_L04_00416E38's note has the arms and options tried:
 * - func_002D3D88's helper with mode = D_L04_001B2D40 (assumed, not evidenced): 780/736; retail has no
 *   such load after the sprintf.
 * - if (r != 0) return r + adjust; return r; with adjust 0: 732/736, 100 rows differ, the same as plain
 *   C with reused float temporaries.
 * - Float locals for 112.0/142.0/118.0 set before the scale load: 732/736, 99 rows differ. f22/f21
 *   become retail's, but the argument loads still hoist.
 *
 * Tier opus-2 (v1724), 31 October 2026. Best check.py: 736/736 bytes, 0/2 places, 47 of 184 words
 * differ apart from link values (USA v1.01), default -O2 -G0 -ffunction-sections.
 * NOT ADMISSIBLE: the C below rounds through a volatile output asm (ftoi), kept only because it
 * is the closest measured form and shows what the original's construct must do. The best plain C
 * is the same body with (int) casts in x/y locals: 732/736 bytes, 88 words differ (opus-1, sol).
 *
 * The evidence is in func_L04_00416E38's note: a real block boundary right after each fix, kept
 * through sched2, deleted by jump2. With ftoi the size, the serial rounding, the argument loads
 * and the second group's order are retail's. What still differs is what a real boundary changes:
 * - 112/142/0.5 are tied here (f20/f21 swapped, mul.s f20,f0,f20); retail keeps them untied in
 *   f22/f21/f20 with the temporary in f0 and the scale in f1 (global pseudos).
 * - second group: y in $v0 here; retail has y in $v1 and loads D_001A7340 into $v0 in the next
 *   block, in front of (float)y, with f14 and the -50 after it.
 * - last group: x4 in $s0 throughout here; retail has lw $v1 ... sra $s0,$v1,1, with 118.0 loaded
 *   before the scale.
 * - the else branch's `b` takes the scale load into its delay slot; retail has a nop and the
 *   first insn after the join is li.s 112.0, which cannot go there.
 *
 * Earlier notes (opus-1, plain C):
 *
 * What differs is the same blocker as func_L04_00416E38 (see its note): from 0x4171B4 on,
 * retail rounds each coordinate serially in $f0 with the scale in $f1 (112/142/0.5 kept in
 * $f22/$f21/$f20, loaded where first used), the argument loads (a2 = 50, a3 = D_001A7340 - 50,
 * t0 = 96, t1 = 0x60442D00; f14 = 50.0, f15 = (float)(D_001A7340 - 50)) are not hoisted above
 * the roundings, and the second group converts x to float before y's fix. Here sched1
 * interleaves the two chains and hoists those loads; the else branch's `b` also takes the
 * scale load ($gp form) into its delay slot where retail has a nop (retail's first insn after
 * the join is li.s 112.0, which cannot go there).
 * Measured: the do { } while (0) rounding macro of func_L04_00416E38 with one int per
 * coordinate makes the first group retail's but costs 740 bytes (beql for beqz at 0x417090,
 * delay-slot fill at the join, second-group conversions after the y macro); the colour here is
 * the genuine zero-extended 64-bit style word (ori/dsll/ori), unlike func_L04_00416E38's.
 * Next: the original construct that bounds each rounding (see func_0033A520, func_0033C028).
 */
#include "include_asm.h"

extern int D_L04_001A8FE4 __attribute__((sda));
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern int func_001157AC(char *);
extern void func_0027EB88(int, int, int, int, int, int);
extern void func_0029B658(float, float, float, float, int, int);
extern int func_0027FBD8(int, int, unsigned long long, char *, int);
extern int D_L04_001B0920_gp __asm__("D_L04_001B0920__gp") __attribute__((section(".sdata")));
extern char D_L04_001B0B20[];
extern char D_L04_001B0B38[];
extern float D_L04_001B2D44 __attribute__((sda));
extern int D_001A7340 __attribute__((sda));

static __inline__ int ftoi(float f) {
    return (int)f;
}

void func_L04_00417028(void) {
    char text[64], prefix[64];
    func_00115DA8(prefix, func_00288FB8(0x2F82), D_L04_001A8FE4);
    if (D_L04_001B0920_gp / 60 % 60 < 10)
        func_00115DA8(text, D_L04_001B0B20, prefix, func_00288FB8(0x2F83), D_L04_001B0920_gp / 216000, D_L04_001B0920_gp / 3600 % 60, D_L04_001B0920_gp / 60 % 60, D_L04_001B0920_gp / 6 % 10);
    else
        func_00115DA8(text, D_L04_001B0B38, prefix, func_00288FB8(0x2F83), D_L04_001B0920_gp / 216000, D_L04_001B0920_gp / 3600 % 60, D_L04_001B0920_gp / 60 % 60, D_L04_001B0920_gp / 6 % 10);
    func_0027EB88(ftoi(D_L04_001B2D44 * 112.0f + 0.5f), ftoi(D_L04_001B2D44 * 142.0f + 0.5f), 50, D_001A7340 - 50, 96, 0x60442D00);
    func_0029B658((float)ftoi(D_L04_001B2D44 * 112.0f + 0.5f), (float)ftoi(D_L04_001B2D44 * 142.0f + 0.5f), 50.0f, (float)(D_001A7340 - 50), 96, 0x55F0C070);
    {
        int x = D_001A7340 / 2;
        int y = ftoi(D_L04_001B2D44 * 118.0f + 0.5f);
        func_0027FBD8(x, y, 0x80F0F0F0ULL, text, func_001157AC(text));
    }
}
