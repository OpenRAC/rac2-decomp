/* Closer C, 1 November 2026: 1500/1500, 36 rows. D_001A7BB3 is D_001A7BB0[3] (sda, nonzero offset). Left: s2/s3 and the
 * normal path, where retail rebuilds the hero address and 0x1C after func_L00_003266D8.
 */
/*
 * Tier: GPT-6.1 Sol, high effort; task v1147, 29 October 2026.
 * USA v1.01, current game -O2 -G8 -ffunction-sections.
 * Best retained check.py: 1496 bytes, retail 1500; 0 of 27 places match.
 * Frame 0x30 and saves s0..s3 agree. The player-state high half gets s2
 * instead of s3, and the input high half gets s3 instead of s2. Normal-path
 * player-base and 0x1c reuse across a call differs from retail rematerialization.
 * D_001A7BB3 uses split load registers and fills a slot retail leaves empty.
 *
 * Improvements over the sol-low draft: scoped base construction restores the
 * persistent high half; incomplete MACRO_ADDR globals reproduce mixed absolute
 * and GP accesses without invented object extents or duplicate storage names.
 * Splitting boolean normalization from the OR reproduces its instruction order.
 * Scoped statistics pointers, left-associated flag ORs and the tick snapshot
 * reproduce both statistics update sequences (apart from branch-to-exit offsets).
 *
 * Corrected retail control flow: timestamps use unsigned '<'; the 0x70 maximum
 * update is outside the saturated-counter guard; level 26 bypasses the two state
 * exclusions but still calls the prompt; the final prompt's nonzero result runs
 * the ordinary update chain. The earlier sol-low reconstruction gets these wrong.
 *
 * A 1500-byte variant with conditional input initialization and a MACRO_ADDR
 * byte load was also 0/27, first instruction mismatch +0x94; its duplicate input
 * high-half construction and GP byte load are less faithful than this draft.
 * No-gcse loses saved bases; no-expensive-optimizations worsens size; G0 and
 * gcse-unsplit-edges do not close the remaining differences. Allocator diagnostic
 * and ordinary objects agree. No linked-build match is claimed.
 * Next: independently recover the input/player declaration and base lifetimes,
 * especially the normal-path join, before more allocation or scheduling trials.
 * Self-contained declarations below; compile as a separate -g8.c unit.
 */
#include "common.h"
extern char D_00189E20[], D_00138180[], D_0018C750[];
extern int D_L00_001A8F00[] MACRO_ADDR, D_L00_001A8FB8[] MACRO_ADDR, D_L00_001A8FF0[] MACRO_ADDR, D_001A7428[] MACRO_ADDR, D_L00_001B19C4[] MACRO_ADDR, D_001A79F0[] MACRO_ADDR, D_001A7390[] MACRO_ADDR, D_L00_001B1AE0[] MACRO_ADDR;
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern int D_001A7424 __attribute__((sda));
extern int D_L00_001A8FB4 __attribute__((sda));
extern int D_L00_001A8FF4 __attribute__((sda));
extern float D_L00_001B18E0 __attribute__((sda));
extern int func_L00_002A3B80();
extern int func_L00_002A6DD0();
extern int func_L00_002CB218();
extern int func_L00_002D6728();
extern int func_L00_002D6768();
extern int func_L00_002D67A8();
extern int func_L00_002D6880();
extern int func_00272368();
extern int func_L00_002ED808();
extern int func_L00_002F43F8();
extern int func_00289178();
extern int func_0028E138();
extern int func_00290730();
extern int func_00290748();
extern int func_L00_002FC058();
extern int func_002914B8();
extern int func_L00_0030C710();
extern int func_L00_0030C7F8();
extern int func_0029BCD8();
extern int func_L00_00310048();
extern int func_0029FFB8();
extern int func_L00_003266D8();
extern int func_L00_0032B270();
extern int func_L00_0032B2A8();
extern int func_002B49E0();
extern int func_002B6658();
extern int func_L00_0032EF10();
extern int func_002B9390();
extern int func_002E4AC8();
extern int func_002E5E58();
extern int func_002E5F60();
extern int func_002F5220();
extern int func_002F52B8();
extern int func_L00_0036F480();
extern int func_L00_0037E5C0();
#define I(p,o) (*(int *)((p)+(o)))
#define U(p,o) (*(unsigned int *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
void func_L00_0036F488(void)
{
    int blocked;
    if (func_L00_002F43F8() && !func_002B49E0(4, 1, 1, 0, 0)) return;
    if (!D_L00_001A8F00[0] && (D_001A7424 & 1) && !func_002B49E0(4, 1, 1, 0, 0)) return;
    if (func_L00_0036F480()) return;
    {
        char *p = D_00189E20;
        int special = 0;
        char *obj;
        blocked = I(p, 0x2294) != 0x31;
        obj = *(char **)(p + 0x1830);
        if (obj) {
            int id = *(short *)(obj + 0xaa);
            if (id == 0x905 || id == 0x85c || id == 0xeef || id == 0x10ee) special = 1;
        }
        blocked |= special;
    }
    blocked = (blocked != 0);
    blocked |= func_L00_002D6728() != 0;
    blocked |= func_L00_002D67A8(3) != 0;
    blocked |= func_L00_002D6880() != 0;
    func_L00_002FC058();
    {
        if (func_L00_0032EF10(16, D_L00_001A8FB8[0], 0) && D_L00_001B19C4[0] >= 8) {
            char *p = D_00189E20;
            if (I(p, 0x2294) != 0x6f && B(p, 0x123c) != 2 && I(p, 0x2294) != 0x31 && blocked && I(p, 0x2294) != 0x1c && !D_L00_001A8F00[0] && D_L00_001B18E0 < 0.2f && B(p, 0x22b4) < 2 && !D_L00_001A8FB4 && D_001A7BB0[3]) {
                func_00290730();
                if (func_00290748()) {
                    if (B(p, 0x22b4) != 1) func_L00_002CB218();
                    if (!func_002B49E0(4, 1, 7, 0, 0)) return;
                }
            }
        }
    }
    {
        int active = func_L00_0032B270();
        char *input = D_00138180;
        if (!active) {
            if ((I(input, 0x1a4) & 0x800) || D_001A7428[0]) {
                if (D_L00_001B19C4[0] < 8) goto normal;
                {
                    char *p = D_00189E20;
                    if (I(p, 0x2294) != 0x6f && (B(p, 0x123c) != 2 || I(p, 0x1248) == 10)) {
                        if (!blocked || D_L00_001A8F00[0]) goto second;
                        if (!func_002B49E0(3, 1, 1, 0, 0)) {
                            func_L00_0032B2A8(func_L00_002A3B80() != 0);
                            func_002E5E58(18, 0, 0);
                            return;
                        }
                    }
                }
            }
        }
    }
second:
    {
        if (D_L00_001B19C4[0] >= 8) {
            char *input = D_00138180;
            if (I(input, 0x1a4) & 0x500) {
                char *p = D_00189E20;
                if (I(p, 0x229c) != 22 && I(p, 0x2294) != 0x6f && blocked && I(p, 0x2294) != 0x1c && !D_L00_001A8F00[0]) {
                    if (func_L00_002D6728()) {
                        if (func_L00_002D6768()) goto normal;
                    }
                    if (D_L00_001A8FF0[0] && !D_L00_001A8FF4) {
                        if ((D_001A79F0[0] == 26 || (I(p, 0x2294) != 0x5b && I(p, 0x2294) != 0x58)) && func_002B49E0(4, 1, 6, 0, 0)) {
                            char *stats = D_0018C750;
                            if (H(stats, 0x1a4) < 0xffff) H(stats, 0x1a4)++;
                        }
                        {
                            char *stats = D_0018C750;
                            if (U(stats, 0x1a8) < D_001A7390[0]) U(stats, 0x1a8) = D_001A7390[0];
                            U(stats, 0x1ac) = (U(stats, 0x1ac) | (1 << D_001A79F0[0])) | 0x80000000;
                            return;
                        }
                    }
                    if (!func_002B49E0(3, 1, 2, 0, 0)) {
                        func_L00_0032B2A8(func_L00_002A3B80() != 0);
                        {
                            char *stats = D_0018C750;
                            if (H(stats, 0x6c) < 0xffff) {
                                H(stats, 0x6c)++;
                            }
                            {
                                unsigned int tick = D_001A7390[0];
                                if (U(stats, 0x70) < tick) U(stats, 0x70) = tick;
                            }
                            U(stats, 0x74) = (U(stats, 0x74) | (1 << D_001A79F0[0])) | 0x80000000;
                        }
                    }
                    return;
                }
            }
        }
    }
normal:
    {
        char *p = D_00189E20;
        if (I(p, 0x2294) != 0x1c) func_L00_003266D8();
    }
    {
        char *input = D_00138180;
        if (I(input, 0x1a4) & 0x200) {
            char *p = D_00189E20;
            if (I(p, 0x2294) != 0x1c && I(p, 0x2294) != 0x31) {
                func_L00_0030C7F8(360);
                func_L00_0030C710(180);
            }
        }
    }
    if (D_L00_001B1AE0[0] && !func_002B49E0(6, 1, 0, 0, 0)) {
        func_L00_0032B2A8(func_L00_002A3B80() != 0);
        D_L00_001B1AE0[0] = 0;
    } else {
        func_002F5220(); func_L00_0037E5C0(); func_L00_00310048(); func_002B6658(); func_002E5F60(); func_L00_002A6DD0(); func_002B9390(); func_L00_002ED808(); func_00272368(); func_002E4AC8(); func_002914B8(); func_0029FFB8(); func_0028E138(1); func_0029BCD8(); func_00289178(); func_002F52B8();
    }
}
