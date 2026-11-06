/* 7 November 2026 (USA v1.01, -O2 -G8 -ffunction-sections as L05_00421B98-g8.c): 1848/1852
 * bytes, 0/1, not a match. This body replaces the M25/M34 one below. New in it: the y coordinate
 * goes through the same inline helper as the merged func_L11_004456A0 / func_L02_003FF6E8, with
 * per-block `half` and `one` locals and a single-test dead mode compare (`if (mode == active)`).
 * That reproduces retail's whole prologue: frame 0xF0, the four saved FPRs and the unused saved
 * $s2 (it is `one`, allocated across the calls; its only use, the dead compare, goes at flow2).
 * Constants and 0x8710 stay CSE'd within each block, as in retail.
 * Measured and rejected (each one compile):
 *   - L02's `result != 0 && mode == active`: the two branches end cse's path, so -1/1/0, 0.5 and
 *     0x8710 are rematerialised at every draw (1836 bytes); block-local float variables for them
 *     are constant-propagated the same way. `mode == active && result != 0`: 1932-1948 bytes.
 *   - y in its own statement before the draw: same allocation, worse schedule.
 *   - mode loaded before the func_00336D50 call (passed to the helper): 1860 bytes.
 *   - -fno-schedule-insns2 gives 1852 bytes but leaves the prologue unscheduled (retail's is
 *     scheduled), so it is not the profile. -fno-schedule-insns: 1804; -g: 1848, no better.
 * Left, and why (cc1 -dl -dg on this body): retail converts each y with `mfc1 $a0` and keeps the
 * sprite in $v0 until after the chain (`daddu $a0,$v0` late). Here the dead mode load is a
 * block-local pseudo (load and branch in the chunk after the call), so local-alloc gives it $v0
 * before global-alloc sees the sprite pseudo; the sprite then takes $a0, the fix result $v1, and
 * sched2 fills the y chain with the constant loads. Retail's roles need the mode load kept out of
 * $v0 (sprite allocated first, or $v0 still live at the load), which no wording here reached.
 * The else arm also still swaps 0x8710 and the constant 1 ($s0/$s1).
 *
 * Earlier notes:
 * func_L05_00421B98 (1852 B): draw two HUD icon pairs, the countdown icon and its box.
 * M25 2026-10-26 near miss. Profile -O2 -G8 -ffunction-sections (a -g8.c unit): 1848/1852 bytes.
 * Byte-identical modulo addresses to func_L10_00424CD0, func_L15_00431590 and func_L25_0040DE40
 * (family F35): one match ports to all four.
 * Measured declarations: x halves are sda scalars (), y halves the plain sized scalar
 * after them (lui $at per access); D_L05_001A904C, D_L05_001B2D80/2D84 plain sized
 * (lui/load in flow, $gp in delay slots). The colors initializer must sit in an inner
 * block after the two draws (retail copies it just before func_0028E588).
 * Left: retail saves an unused $s2 (frame 0xF0, mine 0xE0); 0x8710 lives in $s1 and the
 * state pointer in $s0 (mine swapped); retail loads the float constants after the y
 * conversion and uses $a0 as the mfc1/mtc1 temporary (arg 0 set last); the countdown
 * box computes x-0x33 before the D_L05_001B2D80 test (args precomputed).
 * M34 2026-10-26 (about 60 min, no match): what the four retail copies show and what moved.
 *   - The countdown box y is `y = (float)(Y - 13) * scale + 0.5f; if (D_L05_001B2D80 == 1)
 *     y += 1.0f;` with `x = D_L05_001B1430 - 0x33` in a local before the if and the
 *     func_0028E588 call in its own statement first: that gives retail's bne with add.s 0.5
 *     in the slot and the lone add.s 1.0 (the ?: form adds 0.0 on the other arm). Retail keeps
 *     the constant 1 for that compare in $s0, set at the head of the arm (unexplained), and
 *     recomputes &colors (addiu $t1,$sp,0x80) where this cc1 keeps it in a saved register.
 *   - Every draw: retail issues the y chain (flt Y, S, flt X, mul, add, fix, flt) with no
 *     filler and only then the -1/1/0 constants and a0 = v0, so the fix temporary is $a0. Here
 *     sched1/sched2 fill the chain's latency slots with the constants and the a0 move (RTL dumps:
 *     the CSE'd constant pseudos cross calls, so they carry no dependence on the call). Neither
 *     -fno-schedule-insns, -fno-schedule-insns2, -g, -ffast-math nor a static inline draw helper
 *     reproduces it (all worse or unchanged); the helper loads x/y before the call.
 *   - The unused saved $s2 is still unexplained (no spill slot in retail's frame).
 */

#include "common.h"

extern char *D_L05_001B13B0 __attribute__((sda));
extern int D_L05_001B354C __attribute__((sda));
extern int D_L05_001B3548 __attribute__((sda));
extern int D_L05_001B1428 __attribute__((sda));
extern int D_L05_001B142C;
extern int D_L05_001B1430 __attribute__((sda));
extern int D_L05_001B1434;
extern int D_L05_001B1438 __attribute__((sda));
extern int D_L05_001B143C;
extern int D_L05_001B1440 __attribute__((sda));
extern int D_L05_001B1444;
extern int D_L05_001A904C;
extern int D_L05_001B2D80;
extern float D_L05_001B2D84;
extern int D_001A79FC;
extern int func_00336D50(int, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern int func_0028E588(int, int);
extern int func_0028EA58(int, int, int, int, int, unsigned int *);
extern int func_00115DA8(char *, const char *, ...);
extern void func_0027F5B8(int, int, unsigned long long, unsigned char *, int);

/* A coordinate scaled for the display and rounded to a whole pixel. The display-mode test has no
   effect on the result, but it is real: its load and compare go at flow2, after allocation
   (as in func_L11_004456A0 and func_L02_003FF6E8). */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_L05_001B2D80;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (mode == active)
        scaled = 1.0f;
    return result;
}

#define ICON(id, color, x, y, a, b, c)                                                       \
    func_00300A00(func_00336D50(D_L05_001A904C + 0x8710, id), color, (float)(x),            \
                  (float)scaled_coord(y, D_L05_001B2D84, half, one), a, b, c)

void func_L05_00421B98(int first, int second, int third, int fourth)
{
    char text[0x80];
    char *state = *(char **)(D_L05_001B13B0 + 0x68);
    float scale;
    int time;

    if (D_L05_001B354C == 0) {
        D_L05_001B354C = 1;
        D_L05_001B3548 = D_001A79FC;
    }
    if (D_L05_001A904C == 0)
        return;
    if (first) {
        float half = 0.5f;
        int one = 1;

        ICON(0xBD, 0x60442D00, D_L05_001B1428, D_L05_001B142C, -1.0f, 1.0f, 0.0f);
        ICON(0xBE, 0x55F0C070, D_L05_001B1428, D_L05_001B142C, -1.0f, 1.0f, 0.0f);
    }
    if (second && D_L05_001B3548 < D_001A79FC) {
        if (func_00282948(state + 0x50) == 0) {
            time = *(int *)(state + 0x50);
            if (time >= 0x123) {
                float half = 0.5f;
                int one = 1;

                scale = func_00283CE0(300 - time) * 0.1f;
                if (scale > 1.0f)
                    scale = 1.0f;
                else if (scale < 0.0f)
                    scale = 0.0f;
                ICON(0xBF, 0x60442D00, D_L05_001B1430, D_L05_001B1434, scale, scale, 0.0f);
                ICON(0xC0, 0x55F0C070, D_L05_001B1430, D_L05_001B1434, scale, scale, 0.0f);
            } else if (time < 10) {
                float half = 0.5f;
                int one = 1;

                scale = func_00283CE0(time) * 0.1f;
                if (scale > 1.0f)
                    scale = 1.0f;
                else if (scale < 0.0f)
                    scale = 0.0f;
                ICON(0xBF, 0x60442D00, D_L05_001B1430, D_L05_001B1434, scale, scale, 0.0f);
                ICON(0xC0, 0x55F0C070, D_L05_001B1430, D_L05_001B1434, scale, scale, 0.0f);
            } else {
                float half = 0.5f;
                int one = 1;

                ICON(0xBF, 0x60442D00, D_L05_001B1430, D_L05_001B1434, 1.0f, 1.0f, 0.0f);
                ICON(0xC0, 0x55F0C070, D_L05_001B1430, D_L05_001B1434, 1.0f, 1.0f, 0.0f);
                {
                    unsigned int colors[4] = { 0x8080F0F0, 0x8080F0F0, 0x8080F0F0, 0x8080F0F0 };
                    {
                        int id = func_0028E588(0xEAA2, 3);
                        int x = D_L05_001B1430 - 0x33;
                        float y = (float)(D_L05_001B1434 - 13) * D_L05_001B2D84 + half;
                        if (D_L05_001B2D80 == one)
                            y += 1.0f;
                        func_0028EA58(id, x, (int)y, 0x1C, 0x1C, colors);
                    }
                    func_00115DA8(text, "%d", D_001A79FC);
                    func_0027F5B8(D_L05_001B1430 + 5, (int)((float)(D_L05_001B1434 + 2) * D_L05_001B2D84 + 0.5f),
                                  0x80808080ULL, (unsigned char *)text, 0x80);
                }
            }
        } else {
            D_L05_001B3548 = D_001A79FC;
            *(int *)(state + 0x50) = 300;
        }
    }
    if (third) {
        float half = 0.5f;
        int one = 1;

        ICON(0xC1, 0x60442D00, D_L05_001B1438, D_L05_001B143C, 1.1f, 1.0f, 0.0f);
        ICON(0xC2, 0x55F0C070, D_L05_001B1438, D_L05_001B143C, 1.1f, 1.0f, 0.0f);
    }
    if (fourth) {
        float half = 0.5f;
        int one = 1;

        ICON(0xC1, 0x60442D00, D_L05_001B1440, D_L05_001B1444, 1.1f, 1.0f, 0.0f);
        ICON(0xC2, 0x55F0C070, D_L05_001B1440, D_L05_001B1444, 1.1f, 1.0f, 0.0f);
    }
}
