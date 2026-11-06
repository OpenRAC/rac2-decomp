/* 6 November 2026, round 10: retained best C, USA v1.01 656/656 bytes, 0/1
 * places; -O2 -G0 -ffunction-sections. 43 differing instruction positions after
 * masking relocation fields (was 49). Two inline helpers, as in matched
 * func_002CE5D0 (menu_screen_y): menu_round for the title row and
 * menu_screen_y(value, offset) with `if (flag == 1) return (int)(y + offset);`
 * for the loop. The loop body now matches, including the increments after
 * cvt.s.w and $f2 for the adjustment. Left: in both text calls the title move
 * (daddu a0,v0) and the int->float row conversion are placed differently and
 * zero is set too early (12 + 11 positions); the key copy uses a0/a1/a3 instead
 * of v1/a0/a2 and the .y pointer is base+4 instead of its own lui/addiu (20).
 * Measured, no better: calls written as arguments (lesson 28; 668 bytes
 * without the outer group, 54-60 with it); inline title-draw helper (73);
 * groups of title+row only (46), title outside the group (54); float-returning
 * round helper; int-offset helper (672 bytes); `int i = 0` before keys (48,
 * fixes i in the delay slot but swaps s3/s4); [][2] and pointer y views;
 * -fno-sched-interblock (tie), -fno-schedule-insns, -mno-split-addresses
 * (648 bytes); 40-step hill-climb over the group statement order (tie).
 */
/* Superseded 6 November 2026, Codex follow-up: retained best C, USA v1.01 656/656 bytes,
 * 0/1 places; -O2 -G0 -ffunction-sections. check.py: "03_endako: instruction at
 * +0x58 differs". There are 49 differing instruction positions after masking
 * only relocation fields, versus 60 for the previous retained C (the earlier
 * 92/102 line counts included unresolved relocation display differences).
 * Grouping the real title lookup and argument reads restores half in $f20 and
 * zero in $f21. An outer group around the second draw prevents part of the
 * loop preheader from crossing that draw. Remaining: zero is materialized too
 * early, title/coordinate argument moves and loads interleave differently,
 * key-array initialization and coordinate-pointer setup differ, and loop
 * increments occur between mfc1 and mtc1 rather than after cvt.s.w.
 * New measured controls: all 21 integer/FP-bank interleavings preserve the
 * physical call contract but tie or worsen; explicit rounded-int/float locals,
 * groups around lookup/conversion/argument-read intervals and nested groups
 * bottom out at this form. Adjacent independent x/c/d/zero assignment swaps
 * tie. Moving the actual loop increment between rounding/helper/draw steps
 * ties; grouping that increment adds four bytes. An explicit four-key memcpy
 * ties; initializing i before it gives 53 differences. A direct y-array view
 * fixes the base+4 expression but worsens scheduling by one position.
 * With this source, -frac2-sticky-volatile-refs, -fno-regmove and -g tie;
 * -fno-schedule-insns, -fno-schedule-insns2, -fno-gcse,
 * -fno-rerun-cse-after-loop and -fno-rerun-loop-opt worsen size or instructions.
 * No donor found by key/color constants in local RAC1/RAC4 sources. Next useful
 * evidence is the original text-argument conversion/call grouping or a compiler
 * scheduling witness; do not repeat the tied order/flag probes. No linked build.
 */
/* Superseded 6 November 2026, round 2: default -G0 profile, 656/656 bytes, 0/1 USA,
 * 92 diff lines (the previous form gave 102). Plain call arguments with literal 0.5f/0.0f
 * put half in $f20 before the first call as retail does; a group around the second text
 * call keeps the loop set-up (i, the constant 1, the coordinate pointers) after that call;
 * an unconditional (float)shift fixes the loop registers (i s3, shift s1, keys s2, buffer s4).
 * Left: half/zero swapped ($f21/$f20) once the group is in; in both text calls retail does
 * the whole row conversion before loading any other argument, here sched interleaves them;
 * retail's .y pointer is %hi/%lo(D_001B0164) where this forms base+4; loop increments sit
 * between mfc1 and mtc1. Measured, none closer: group around both calls or the first only
 * (668 bytes, extra $f22), group around the loop's row block (660), a `half` variable,
 * -ffast-math, -fno-schedule-insns, -fno-schedule-insns2 (652).
 */
/* Retained bounded near miss, 2026-10-28: default profile656/656 bytes.
 * Five forms: named half constant removes duplicated FPR and restores0xf0
 * frame; explicit row/zero/adjustment lifetimes and -fno-regmove tie the
 * remaining scheduling. -fno-schedule-insns and -fno-gcse reach652 bytes and
 * are not retained. First difference+0x4c is swapped persistenthalf/zero FPRs,
 * followed by independent argument setup hoisted across coordinate conversion.
 * Reopen with a measured genuine constant lifetime/scheduling witness.
 * Getter keeps its actual integer stored-address return; text drawing takes
 * an explicit pointer cast. Printer returnsint and is variadic. Font renderer
 * style is64-bit unsignedlong, and both ending wrappers returnint.
 * The actual local formatting capacity is128 bytes; its initialized text is
 * terminated by the verified sprintf-style helper before font consumption.
 * Four key words16 bytes and four coordinate pairs32 bytes are complete.
 */
#include "common.h"

struct MenuCoordinate { float x, y; };
extern unsigned char *D_L03_001A904C __attribute__((sda));
extern float D_L03_001B014C SDATA(D_L03_001B014C);
extern float D_L03_001B0150 SDATA(D_L03_001B0150);
extern float D_L03_001B0154 SDATA(D_L03_001B0154);
extern float D_L03_001B0158 SDATA(D_L03_001B0158);
extern struct MenuCoordinate D_L03_001B0160[];
extern struct MenuCoordinate D_L03_001B0160_gp[] SDATA(D_L03_001B0160);
extern int D_L03_001B0140 SDATA(D_L03_001B0140);
extern int D_L03_001B3280 __attribute__((sda));
extern float D_L03_001B3284 __attribute__((sda));
extern char D_L03_001B0190[], D_L03_001B0198[];
extern unsigned char D_001A7A7C[] __attribute__((sda));
extern int func_00336D50(unsigned char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern unsigned char *func_00288FB8(int);
extern int func_00115DA8(char *, char *, ...);
extern int func_00283CF0(float);
extern int func_0027FB40(int, int, unsigned long, unsigned char *, int);
extern int func_L00_00443DF8(char *);
extern int func_L00_00443E18(char *);

static __inline__ int menu_round(float value)
{
    return (int)(value * D_L03_001B3284 + 0.5f);
}

static __inline__ int menu_screen_y(float value, float offset)
{
    float y = value * D_L03_001B3284 + 0.5f;
    if (D_L03_001B3280 == 1)
        return (int)(y + offset);
    return (int)y;
}

int func_L03_003C7018(void)
{
    if (D_L03_001A904C) {
        {
            char *title;
            float row, x, c, d, z;

            do {
                title = (char *)func_00336D50(D_L03_001A904C + 0x8710, 0xc6);
                row = (float)menu_round(D_L03_001B0150);
                x = D_L03_001B014C;
                c = D_L03_001B0154;
                d = D_L03_001B0158;
                z = 0.0f;
            } while (0);
            func_00300A00(title, 0x60442d00, x, row, c, d, z);
        }
        do {
            char *title;
            float row, x, c, d, z;

            do {
                title = (char *)func_00336D50(D_L03_001A904C + 0x8710, 0xc7);
                row = (float)menu_round(D_L03_001B0150);
                x = D_L03_001B014C;
                c = D_L03_001B0154;
                d = D_L03_001B0158;
                z = 0.0f;
            } while (0);
            func_00300A00(title, 0x55f0c070, x, row, c, d, z);
        } while (0);
        {
            int keys[4] = {11599,12116,12769,12770};
            unsigned char buffer[128];
            int i;
            for (i = 0; i < 4; i++) {
                int shift = 5;
                int x;
                unsigned char *label = func_00288FB8(keys[i]);
                if (i == 1) {
                    func_00115DA8((char *)buffer, D_L03_001B0190, label, D_L03_001B0140 + 1);
                    shift = -4;
                } else {
                    func_00115DA8((char *)buffer, D_L03_001B0198, label);
                }
                x = func_00283CF0(D_L03_001B0160_gp[i].x);
                func_0027FB40(x, func_00283CF0((float)menu_screen_y(D_L03_001B0160[i].y, (float)shift)), 0x80808080UL, buffer, 0x80);
            }
        }
        if (D_001A7A7C[0]) {
            func_L00_00443DF8((char *)D_L03_001A904C + 0x36f28);
            func_L00_00443E18((char *)D_L03_001A904C + 0x36f28);
        }
    }
    return 1;
}

