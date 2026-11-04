/* 5 November 2026: exact with a non-empty do-while(0) statement macro, not landed.
 * The body below now rounds into t and converts through
 *   #define F2I(i, f) do { (i) = (f); } while (0)
 * and tools/check.py gives 2 of 2 places match (levels 02 and 11). With the macro's do/while
 * replaced by a plain assignment, the same source gives 0 of 2 (the D_001A7B90 mode load is
 * hoisted across the conversions). Mechanism, from a scratch cc1 that makes fix:SI a sched2
 * barrier: retail has a scheduling barrier at each of these float-to-int conversions. Applied
 * to every function, that barrier breaks 95 of 228 matched functions that convert, so it comes
 * from how these HUD files wrote the conversion, not from the compiler. The loop notes of a
 * one-iteration loop are such a barrier. Per AGENTS.md and the open "non-empty do { } while (0)"
 * question in docs/MATCHING-BLOCKERS.md this waits for a maintainer ruling.
 */
/* 2 November 2026, bounded scheduling check on the pinned workspace compiler:
 * -fno-schedule-insns: 332/332 bytes, 0/2 USA places, same mode-load hoist
 * (checker first mismatch +0xE4). -fno-schedule-insns2: 332/332, 0/2, first
 * mismatch +0x4 and changed prologue/order. Neither scheduler-off profile
 * closes the load ordering; default -G8 retained. No alternate-release or
 * linked build was run for these failed trials.
 */
/* Retained nonmatching reconstruction, 27 October 2026.
 * Profile: -O2 -G8 -ffunction-sections. Candidate and retail: 332 bytes. USA v1.01, USA v2.00 and PAL each reject both carrying places. The lui/lw of D_001A7B90 is hoisted across four FP conversion operations; all other words and registers agree after relocation. The 64-bit packet value and colour ABI were checked against current definitions. Computing the real right edge before the bottom conversion repaired the remaining tail. Reopen with evidence for the mode-load scheduling; preserve NaN guards and conversion order.
 */
#include "common.h"
extern void func_002FC560(unsigned int, unsigned long long);
extern int func_00283CF0(float);
extern int func_L00_0031C998(int, int, float);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern int D_L02_001B1330 __attribute__((sda));
extern int D_L02_001B1338[] __attribute__((sda));
extern int D_L02_001B1334[] __attribute__((sda));
extern int D_L02_001B133C[] __attribute__((sda));
extern int D_L02_001B1340 __attribute__((sda));
extern int D_L02_001B1348 __attribute__((sda));
extern int D_L02_001B134C[] __attribute__((sda));
extern int D_L02_001B1350[] __attribute__((sda));
extern float D_L02_001B3E04[] __attribute__((sda));
extern int D_001A7B90[] __attribute__((sda));
#define F2I(i, f) do { (i) = (f); } while (0)

void func_L02_003FE768(float fraction)
{
    int width;
    int color;
    int top;
    int bottom;
    int left;
    int right;
    float t;
    func_002FC560(0x42, 0x8000000044ULL);
    if (fraction < 0.0f)
        fraction = 0.0f;
    width = func_00283CF0((float)(D_L02_001B1338[0] - D_L02_001B1330) * fraction);
    if (fraction > 0.5f)
        color = func_L00_0031C998(D_L02_001B134C[0], D_L02_001B1348, fraction + fraction - 1.0f);
    else
        color = func_L00_0031C998(D_L02_001B1350[0], D_L02_001B134C[0], fraction + fraction);
    t = (float)D_L02_001B1334[0] * D_L02_001B3E04[0] + 0.5f;
    F2I(top, t);
    if (D_001A7B90[0])
        top -= D_L02_001B1340;
    left = D_L02_001B1330;
    right = left + width;
    t = (float)D_L02_001B133C[0] * D_L02_001B3E04[0] + 0.5f;
    F2I(bottom, t);
    if (D_001A7B90[0])
        bottom -= D_L02_001B1340;
    func_0028FC48(left, top, right, bottom, color, 0);
}
