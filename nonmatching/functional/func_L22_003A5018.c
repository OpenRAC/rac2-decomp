/* functional: high. SAME on 4 level-22 calls. From the 3008-byte matching draft: its 45 ref_ names are named by the gp address retail forms for each use (gp 0x1AEFF0: D_L22_001AF304..001AF4D0, plus D_L22_001B2AD0 for the store in func_00282948's delay slot and D_L22_001B2984 for the box width's scale), checked use by use against retail; and func_L00_0030CF60 is called on every path, as retail does (the draft called it only when D_L22_001AF304 is set). Unrun blocks read against retail: the D_L22_001B2980 == 1 arms (+3.0 for the six HUD frame sprites, +1.0 for the six icon/label sprites), and the whole D_L22_001B2AC8 message switch (0: func_L00_0030DD70(text 0x2FA3, -1); 1: func_0029CC50(0x1240, D_L22_001B2ACC, -1); 2: func_0029CC50(0x1241, ctl+0x32C halfword, -1); then the D_L22_001B2AD0 countdown sets it to -1). */
/* func_L22_003A5018: draws level 22's two-team arena HUD: six frame sprites, two labels, two gauges (D_0018B694 over ctl+0x324, ctl+0x20 over D_L22_001B2AA8), the two counters and up to two icons a side, the timed message (D_L22_001B2AC8) and the D_L22_001AF304 box; returns 1. */
/* Claude Opus 5.5 xhigh tier, task v1817, 31 October 2026.
 * Retained complete behavioural draft: USA v1.01, 3008/3008 bytes, 0/2 places
 * (levels 22 and 23); 129 of 752 rows still differ beyond relocated values, none
 * before 0x3A5400 (the prologue and sprites 1-5 are exact).
 * No linked build, no PAL/us2 check (no match).
 * Compile in an isolated -g8.c unit with -O2 -G8 -ffunction-sections -g. Without
 * -g the pre-div.s nop pairs go (2992 bytes); -fno-schedule-insns is far worse.
 *
 * What this draft recovered, each measured:
 * - Y1/Y3 return int from an if/else with (int) in both arms. Retail's sprite 9
 *   looks like a single `if (...) sy += 1.0f` but is the same Y1 as sprite 10:
 *   jump2 (after sched2) cross-jumps its identical cvt/mfc1 tails. Its real join
 *   is what stops cse, so sprite 10 reloads 0.5, 1.0 and 1 into locals. This
 *   took the size from 2968 to 3008. A plain `if` lets cse-skip-blocks carry them.
 * - (float)Y3(sy) must convert after the join. A (float) on a ternary is folded
 *   into its arms, which moved mtc1/cvt.s.w before the label and broke sched2's
 *   first clock of each block (lwc1 f12/lui a1/mtc1 f16/ori a1).
 * - The saved constants 1 (retail s3, s4) are two locals assigned 1 and passed as
 *   func_0028E588's variant: cse keeps a1=1 literal and canonicalises the later
 *   `D_L22_001B2980 == 1` register to the local, so it lives across the calls.
 * - Icon 2/4: compute x before sy. func_0027FB40 takes u64 and returns int.
 *
 * Remaining blocker: retail has a scheduling barrier directly after five roundings
 * (sprites 7, 8, both counter values, the box width), all (int)(... + 0.5f). No
 * later instruction goes above the mfc1, even in free slots (sprite 7: `lwc1 f1;
 * daddu a0,v0; mul; add; cvt; mfc1 a2; lw a1; addiu t1; lw a3; jal; lw t0`), and
 * s1/f20 stay below sprite 8's barrier while s3/f21 rise above sprite 6's call.
 * cse must cross it (f21, f22, s3 reach sprite 9). The (int)(ratio * x) gauge
 * conversions have no barrier. Most other differences follow from it: colour's
 * lifetime sets s0/s1/s4/s5/s6, so value/colour/format/high-copy get other saved
 * registers, and the box and label swap s0/s1.
 *
 * Tried without the barrier: plain and full-expression inlines, statement
 * expressions, nesting func_0028E588 in the call, reordering gauge statements,
 * alternate integer/FP argument interleavings (same bytes). Diagnostics only, not
 * retained or landable: `do { } while (0)` after or around the rounding gives a
 * barrier but ends cse1 at LOOP_END (losing the saved 1) and puts sprite in v0,
 * so daddu a0,v0 lands after add.s, 3012-3016 bytes: not an exact-bytes form.
 * `if (iy) y = iy;` with a dead arm left the differing rows unchanged, so it gave
 * no barrier (its RTL was not inspected).
 * Next: a construct leaving a block boundary or barrier in sched1 and sched2,
 * crossable by cse (perhaps a branch that survives until jump2), then recheck the
 * remaining gauge and sprite 10 argument order, which may follow from it.
 *
 * Bounded investigation: 23 check.py compiles plus RTL dumps (-ds -dt -dG -dS -dR).
 * Retail GP offsets of refs: 00=0324; 01=0414; 02=0418; 03=0420;
 * 04=0430; 05=3AE0; 06=3994; 07..30=0440..049C (four-byte steps);
 * 31=0314; 32..41=04A4..04C8 (four-byte steps); 42=04D0;
 * 43=04E0; 44=04CC. Required declarations follow.
 */
#include "common.h"

extern u8 * D_L22_001A904C_base[] __asm__("D_L22_001A904C") __attribute__((sda));
#define D_L22_001A904C D_L22_001A904C_base[0]
extern int D_L22_001B2980_base[] __asm__("D_L22_001B2980") __attribute__((sda));
#define D_L22_001B2980 D_L22_001B2980_base[0]
extern float D_L22_001B2984_base[] __asm__("D_L22_001B2984") __attribute__((sda));
#define D_L22_001B2984 D_L22_001B2984_base[0]
extern int D_0018B694 NOT_SDA;
extern int D_L22_001B2AA8_base[] __asm__("D_L22_001B2AA8") __attribute__((sda));
#define D_L22_001B2AA8 D_L22_001B2AA8_base[0]
extern int D_001A7340_base[] __asm__("D_001A7340") __attribute__((sda));
#define D_001A7340 D_001A7340_base[0]
typedef struct HudCounters {
    int unknown[2];
    int rightCount;
    int rightIcons;
    int unknown10[2];
    int leftCount;
    int leftIcons;
} HudCounters;
extern HudCounters D_L22_001B1910 NOT_SDA;
extern char D_L22_001AF4D8[] NOT_SDA;
extern int D_L22_001B2AC8 MACRO_ADDR;
extern int D_L22_001B2ACC_base[] __asm__("D_L22_001B2ACC") __attribute__((sda));
#define D_L22_001B2ACC D_L22_001B2ACC_base[0]
extern int D_L22_001B2AD0_base[] __asm__("D_L22_001B2AD0") __attribute__((sda));
#define D_L22_001B2AD0 D_L22_001B2AD0_base[0]
extern u64 D_L22_001AF418_base[] __asm__("D_L22_001AF418") __attribute__((sda));
#define D_L22_001AF418 D_L22_001AF418_base[0]
extern u64 D_L22_001AF428_base[] __asm__("D_L22_001AF428") __attribute__((sda));
#define D_L22_001AF428 D_L22_001AF428_base[0]
extern u8 *D_L22_001AF314 __attribute__((sda));
extern float D_L22_001AF404 __attribute__((sda)), D_L22_001AF408 __attribute__((sda));
extern u64 D_L22_001AF410 __attribute__((sda)), D_L22_001AF420 __attribute__((sda));
extern int D_L22_001AF430 __attribute__((sda));
extern int D_L22_001AF434 __attribute__((sda));
extern int D_L22_001AF438 __attribute__((sda));
extern int D_L22_001AF43C __attribute__((sda));
extern int D_L22_001AF440 __attribute__((sda));
extern int D_L22_001AF444 __attribute__((sda));
extern int D_L22_001AF448 __attribute__((sda));
extern int D_L22_001AF44C __attribute__((sda));
extern int D_L22_001AF450 __attribute__((sda));
extern int D_L22_001AF454 __attribute__((sda));
extern int D_L22_001AF458 __attribute__((sda));
extern int D_L22_001AF45C __attribute__((sda));
extern int D_L22_001AF460 __attribute__((sda));
extern int D_L22_001AF464 __attribute__((sda));
extern int D_L22_001AF468 __attribute__((sda));
extern int D_L22_001AF46C __attribute__((sda));
extern int D_L22_001AF470 __attribute__((sda));
extern int D_L22_001AF474 __attribute__((sda));
extern int D_L22_001AF478 __attribute__((sda));
extern int D_L22_001AF47C __attribute__((sda));
extern int D_L22_001AF480 __attribute__((sda));
extern int D_L22_001AF484 __attribute__((sda));
extern int D_L22_001AF488 __attribute__((sda));
extern int D_L22_001AF48C __attribute__((sda));
extern int D_L22_001AF304 __attribute__((sda));
extern int D_L22_001AF494 __attribute__((sda));
extern int D_L22_001AF498 __attribute__((sda));
extern int D_L22_001AF49C __attribute__((sda));
extern int D_L22_001AF4A0 __attribute__((sda));
extern int D_L22_001AF4A4 __attribute__((sda));
extern int D_L22_001AF4A8 __attribute__((sda));
extern int D_L22_001AF4AC __attribute__((sda));
extern int D_L22_001AF4B0 __attribute__((sda));
extern int D_L22_001AF4B4 __attribute__((sda));
extern int D_L22_001AF4B8 __attribute__((sda));
extern u8 D_L22_001AF4C0[] SDATA(D_L22_001AF4C0);
extern int D_L22_001AF4D0 __attribute__((sda));
extern int D_L22_001AF4BC __attribute__((sda));

extern void *func_00336D50(void *, int);
extern void func_00300A00(void *, unsigned int, float, float, float, float, float);
extern void *func_0028E588(int, int);
extern int func_0028EA58(void *, int, int, int, int, void *);
extern void func_0027EAE8(int, int, int, int, int, void *);
extern int func_00115DA8(char *, char *, ...);
extern int func_001157AC(char *);
extern int func_0027FB40(int, int, u64, char *, int);
extern char *func_00288FB8(int);
extern void func_L00_0030DD70(char *, int);
extern void func_0029CC50(int, int, int);
extern int func_00282948(void *);
extern void func_002802E0(void *, int, int, int, int, int, int, int, int);
extern void func_0029B888(void *, unsigned int, char *, int, int, int, int, char *, int, int);
extern void func_L00_0030CF60(void);

/* Screen-space coordinates use the active video mode's vertical scale. */
static __inline__ int Y3(float y) {
    if (D_L22_001B2980 == 1)
        return (int)(y + 3.0f);
    return (int)y;
}
static __inline__ int Y1(float y) {
    if (D_L22_001B2980 == 1)
        return (int)(y + 1.0f);
    return (int)y;
}
#define Y0(y) ((int)((float)(y) * D_L22_001B2984 + 0.5f))

int func_L22_003A5018(void) {
    char textBuffer[64];
    char *text;
    union { u64 d[2]; u32 w[4]; } colours;
    u8 box[32];
    u8 *obj = D_L22_001AF314;
    u8 *ctl = *(u8 **)(obj + 0x68);
    int y;
    int one, one2;
    char *label, *hint;

    {
        void *sprite = func_00336D50(D_L22_001A904C + 0x8710, 0xC3);
        float sy = D_L22_001AF408 * D_L22_001B2984 + 0.5f;
        sy = (float)Y3(sy);
        func_00300A00(sprite, 0x60442D00, D_L22_001AF404, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = func_00336D50(D_L22_001A904C + 0x8710, 0xC4);
        float sy = D_L22_001AF408 * D_L22_001B2984 + 0.5f;
        sy = (float)Y3(sy);
        func_00300A00(sprite, 0x60241700, D_L22_001AF404, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = func_00336D50(D_L22_001A904C + 0x8710, 0xC5);
        float sy = D_L22_001AF408 * D_L22_001B2984 + 0.5f;
        sy = (float)Y3(sy);
        func_00300A00(sprite, 0x55F0C070, D_L22_001AF404, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = func_00336D50(D_L22_001A904C + 0x8710, 0xC3);
        float sy = D_L22_001AF408 * D_L22_001B2984 + 0.5f;
        sy = (float)Y3(sy);
        func_00300A00(sprite, 0x60442D00, D_L22_001AF404, sy, -1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = func_00336D50(D_L22_001A904C + 0x8710, 0xC4);
        float sy = D_L22_001AF408 * D_L22_001B2984 + 0.5f;
        sy = (float)Y3(sy);
        func_00300A00(sprite, 0x60241700, D_L22_001AF404, sy, -1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = func_00336D50(D_L22_001A904C + 0x8710, 0xC5);
        float sy = D_L22_001AF408 * D_L22_001B2984 + 0.5f;
        sy = (float)Y3(sy);
        func_00300A00(sprite, 0x55F0C070, D_L22_001AF404, sy, -1.0f, 1.0f, 0.0f);
    }
    one = 1;
    func_0028EA58(func_0028E588(0xEAA4, one), D_L22_001AF44C, Y0(D_L22_001AF450), D_L22_001AF454, D_L22_001AF458, D_L22_001AF4C0);
    func_0028EA58(func_0028E588(0xEAA4, 0), D_L22_001AF45C, Y0(D_L22_001AF460), D_L22_001AF464, D_L22_001AF468, D_L22_001AF4C0);

    {
        float ratio = (float)D_0018B694 / (float)*(short *)(ctl + 0x324);
        int x, width;
        colours.d[0] = D_L22_001AF410;
        width = D_L22_001AF444;
        x = D_L22_001AF438 + D_L22_001AF430 + D_L22_001AF448;
        y = D_L22_001AF43C + D_L22_001AF434 / 2 - D_L22_001AF440 / 2;
        D_L22_001AF4D0++;
        colours.d[1] = D_L22_001AF418;
        colours.w[1] = (colours.w[1] & 0xFFFF00FF) | ((int)(ratio * 255.0f) << 8);
        func_0027EAE8(x, y, x + (int)(ratio * (float)width), y + D_L22_001AF440, 0xFFFFF1, &colours);
    }
    {
        float ratio = *(float *)(ctl + 0x20) / (float)D_L22_001B2AA8;
        int right, width;
        colours.d[0] = D_L22_001AF420;
        width = D_L22_001AF444;
        right = D_001A7340 - D_L22_001AF438 - D_L22_001AF430 - 4;
        colours.w[0] = (colours.w[1] & 0xFFFF00FF) | ((int)(ratio * 255.0f) << 8);
        colours.d[1] = D_L22_001AF428;
        func_0027EAE8(right - (int)(ratio * (float)width), y, right, y + D_L22_001AF440, 0xFFFFF1, &colours);
    }

    {
        void *sprite = func_0028E588(0xEAA5, 0);
        float sy = (float)D_L22_001AF470 * D_L22_001B2984 + 0.5f;
        func_0028EA58(sprite, D_L22_001AF46C, Y1(sy), D_L22_001AF474, D_L22_001AF478, D_L22_001AF4C0);
    }
    {
        void *sprite = func_0028E588(0xEAA5, 0);
        float sy = (float)D_L22_001AF480 * D_L22_001B2984 + 0.5f;
        func_0028EA58(sprite, D_L22_001AF47C, Y1(sy), D_L22_001AF484, D_L22_001AF488, D_L22_001AF4C0);
    }
    one2 = 1;
    func_00115DA8(textBuffer, D_L22_001AF4D8, D_L22_001B1910.leftCount);
    text = textBuffer;
    {
    int value = Y0(D_L22_001AF498);
    int colour = D_L22_001AF48C;
    func_0027FB40(D_L22_001AF494, value, colour, text, func_001157AC(text));
    }
    func_00115DA8(text, D_L22_001AF4D8, D_L22_001B1910.rightCount);
    {
    int value = Y0(D_L22_001AF4A0);
    int colour = D_L22_001AF48C;
    func_0027FB40(D_L22_001AF49C, value, colour, text, func_001157AC(text));
    }
    if (D_L22_001B1910.leftIcons) {
        void *sprite = func_0028E588(0xEAA5, one2);
        float sy = (float)D_L22_001AF4A8 * D_L22_001B2984 + 0.5f;
        func_0028EA58(sprite, D_L22_001AF4A4, Y1(sy), D_L22_001AF4B4, D_L22_001AF4B8, D_L22_001AF4C0);
    }
    if (D_L22_001B1910.leftIcons >= 2) {
        void *sprite = func_0028E588(0xEAA5, 1);
        int x = D_L22_001AF4A4 + D_L22_001AF4BC;
        float sy = (float)D_L22_001AF4A8 * D_L22_001B2984 + 0.5f;
        func_0028EA58(sprite, x, Y1(sy), D_L22_001AF4B4, D_L22_001AF4B8, D_L22_001AF4C0);
    }
    if (D_L22_001B1910.rightIcons) {
        void *sprite = func_0028E588(0xEAA5, 1);
        float sy = (float)D_L22_001AF4B0 * D_L22_001B2984 + 0.5f;
        func_0028EA58(sprite, D_L22_001AF4AC, Y1(sy), D_L22_001AF4B4, D_L22_001AF4B8, D_L22_001AF4C0);
    }
    if (D_L22_001B1910.rightIcons >= 2) {
        void *sprite = func_0028E588(0xEAA5, 1);
        int x = D_L22_001AF4AC - D_L22_001AF4BC;
        float sy = (float)D_L22_001AF4B0 * D_L22_001B2984 + 0.5f;
        func_0028EA58(sprite, x, Y1(sy), D_L22_001AF4B4, D_L22_001AF4B8, D_L22_001AF4C0);
    }
    if (D_L22_001B2AC8 != -1 && obj[0x95] != 10) {
        switch (D_L22_001B2AC8) {
        case 0: func_L00_0030DD70(func_00288FB8(0x2FA3), -1); break;
        case 2: func_00288FB8(0x1241); func_0029CC50(0x1241, *(short *)(ctl + 0x32C), -1); break;
        case 1: func_00288FB8(0x1240); func_0029CC50(0x1240, D_L22_001B2ACC, -1); break;
        }
        D_L22_001B2AD0 = 0;
        func_00282948(&D_L22_001B2AD0);
        if (D_L22_001B2AD0 <= 0) D_L22_001B2AC8 = -1;
    }
    if (D_L22_001AF304) {
        func_002802E0(box, 240, 480, 44, 468, 256, (int)(D_L22_001B2984 * 320.0f + 0.5f), 16, 3);
        label = func_00288FB8(0x9FC);
        hint = func_00288FB8(0x2F2C);
        func_0029B888(box, 0x80F0F0F0, label, 0, 0, -1, 0, hint, 0, 0);
    }
    func_L00_0030CF60();
    return 1;
}
