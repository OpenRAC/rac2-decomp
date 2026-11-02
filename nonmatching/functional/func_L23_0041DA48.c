/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/*
 * Claude Opus 5.5 (xhigh effort), 1 November 2026. Tier: near miss, not linked.
 * USA v1.01: check.py says 2012 bytes, expected 2008; 0 of 1 places match.
 * About 74 of 502 instruction rows differ once relocations are masked.
 * Profile: -O2 -G16 -Wa,-G16 -ffunction-sections -g (GCSE on; -g gives the
 * pre-div nop pairs). Frame 0xE0 and seven saved GPRs now agree with retail.
 * Needs a unit with that cflags line and INCLUDE_ASM removed for this function.
 * Declarations it needs are below: each colour half is two U64 symbols (first
 * sda, second MACRO_ADDR), and D_L23_001B3000/3004 and the 1F90 block are
 * MACRO_ADDR or plain; the callee prototypes follow the catalogue.
 *
 * What found the shape: nested calls with the inline helpers as arguments; the
 * `1` in the rounding test is a local (`first`, `second`) passed as the inline's
 * mode, because bne has no constant form (retail: addiu s3,zero,1 and s4); and
 * separate ratio2/width2/textX locals, since reusing them merged pseudos.
 *
 * What differs. The main cause is a scheduling boundary at the four sites that
 * round without a test (images #1 and #2, text y, panel): retail issues every
 * other argument after the conversion's mfc1, and we fill the mul.s latency with
 * those loads. That costs the f20 and s3 constant placement, s1 at 1DC94, and the
 * panel's scale load, which retail puts in the branch slot in its GP form (the
 * extra 4 bytes). Separately:
 *   - 1DC48: third draw has ori a1 before mov.s f14, ours in the jal slot.
 *   - 1DED0: 1F90 base. Retail is lui v0,H; addiu s3,v0,LO; daddu s6,v0,zero in
 *     the jal slot. PRE inserts expression (high D_L23_001B1F90) at the end of
 *     the block before the icons branch, and cse2 keeps H in a saved register.
 *   - 1DF30: rasterY/textX are s1/s0 in retail, ours differ.
 *   - 1E128: lui/lw/bgtz on v1 in retail, v0 here.
 *   - Panel: pointer s0 and first id s1 in retail, the other way round here.
 *
 * Diagnostic only, not allowed to land: do { r = (int)p; } while (0); inside a
 * plain rounding helper at those four sites gives 2008/2008 bytes, 0/1 places,
 * 55 rows. It is NOT an exact-bytes form: combine still merges r = fix into
 * a2 = r past the loop notes, where retail keeps a0 = v0 and a2 = fix before the
 * boundary and the other arguments after it. A boundary that also blocks combine
 * (empty volatile asm after the fix, also not allowed) was worse: 2004 bytes,
 * 68 rows. No allowed construct gives a boundary without code: a real or folded
 * test leaves its loads or loses its labels before combine.
 */
#include "common.h"
typedef unsigned long long U64;
typedef union ColorView { U64 half[2]; unsigned int word[4]; } ColorView;
extern char *D_L23_001A904C;
extern char *D_L23_001B1484 __attribute__((sda));
extern float D_L23_001B16D8 __attribute__((sda));
extern float D_L23_001B16D4 __attribute__((sda));
extern float D_L23_001B3004 MACRO_ADDR;
extern int D_L23_001B3000 MACRO_ADDR;
extern char D_00189E20[];
extern int D_001A7340 MACRO_ADDR;
extern U64 D_L23_001B16E0 __attribute__((sda));
extern U64 D_L23_001B16E8 MACRO_ADDR;
extern U64 D_L23_001B16F0 __attribute__((sda));
extern U64 D_L23_001B16F8 MACRO_ADDR;
extern int D_L23_001B1770[4] __attribute__((sda));
extern char D_L23_001B1788[];
typedef struct { char pad[0x18]; int counter; int icons; } HudCounters;
extern HudCounters D_L23_001B1F90;
extern int D_L23_001B374C MACRO_ADDR;
extern int D_L23_001B3750 MACRO_ADDR;
extern int D_L23_001B3754 MACRO_ADDR;
extern int D_L23_001B3748 __attribute__((sda));
extern int D_L23_001B1424 __attribute__((sda));
extern int D_L23_001B1700 __attribute__((sda));
extern int D_L23_001B1704 __attribute__((sda));
extern int D_L23_001B1708 __attribute__((sda));
extern int D_L23_001B170C __attribute__((sda));
extern int D_L23_001B1710 __attribute__((sda));
extern int D_L23_001B1714 __attribute__((sda));
extern int D_L23_001B1718 __attribute__((sda));
extern int D_L23_001B171C __attribute__((sda));
extern int D_L23_001B1720 __attribute__((sda));
extern int D_L23_001B1724 __attribute__((sda));
extern int D_L23_001B1728 __attribute__((sda));
extern int D_L23_001B172C __attribute__((sda));
extern int D_L23_001B1730 __attribute__((sda));
extern int D_L23_001B1734 __attribute__((sda));
extern int D_L23_001B1738 __attribute__((sda));
extern int D_L23_001B173C __attribute__((sda));
extern int D_L23_001B1740 __attribute__((sda));
extern int D_L23_001B1744 __attribute__((sda));
extern int D_L23_001B1748 __attribute__((sda));
extern int D_L23_001B174C __attribute__((sda));
extern int D_L23_001B1750 __attribute__((sda));
extern int D_L23_001B1754 __attribute__((sda));
extern int D_L23_001B1758 __attribute__((sda));
extern int D_L23_001B175C __attribute__((sda));
extern int D_L23_001B1760 __attribute__((sda));
extern int D_L23_001B1764 __attribute__((sda));
extern int D_L23_001B1768 __attribute__((sda));
extern int D_L23_001B176C __attribute__((sda));
extern int D_L23_001B1780 __attribute__((sda));
extern int func_00336D50(unsigned char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern int func_0028E588(int, int);
extern void func_0028EA58(int, int, int, int, int, int *);
extern void func_0027EAE8(int, int, int, int, int, void *);
extern int func_00115DA8(char *, char *, ...);
extern int func_001157AC(char *);
extern int func_0027FB40(int, int, U64, unsigned char *, int);
extern int func_00288FB8(int);
extern int func_L00_0030DD70(int, int);
extern void func_0029CC50(int, int, int);
extern void func_00282948(char *);
extern void func_002802E0(unsigned short *, int, int, int, int, int, int, int, int);
extern void func_0029B888(int, int, int, int, int, int, int, int, int, int);
extern void func_L00_0030CF60(void);

static inline int HudRound(float value, float nudge, int mode) {
    float p = value * D_L23_001B3004 + 0.5f;
    return D_L23_001B3000 == mode ? (int)(p + nudge) : (int)p;
}

static inline int HudPlain(float value) {
    float p = value * D_L23_001B3004 + 0.5f;
    return (int)p;
}

/* Draw the encounter's meters, counters and optional prompt panel. */
int func_L23_0041DA48(void) {
    char text[64];
    ColorView color;
    unsigned short panel[16];
    char *state = *(char **)(D_L23_001B1484 + 0x68);
    int x, y, right, message, a, b, rasterY, width, width2, textX, first, second;
    float ratio, ratio2;
    char *textPtr;

    func_00300A00(func_00336D50((unsigned char *)D_L23_001A904C + 0x8710, 195), 0x60442D00, D_L23_001B16D4, (float)HudRound(D_L23_001B16D8, 3.0f, 1), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50((unsigned char *)D_L23_001A904C + 0x8710, 196), 0x60241700, D_L23_001B16D4, (float)HudRound(D_L23_001B16D8, 3.0f, 1), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50((unsigned char *)D_L23_001A904C + 0x8710, 197), 0x55F0C070, D_L23_001B16D4, (float)HudRound(D_L23_001B16D8, 3.0f, 1), 1.0f, 1.0f, 0.0f);
    first = 1;
    func_0028EA58(func_0028E588(0xEAA4, 1), D_L23_001B171C, HudPlain((float)D_L23_001B1720), D_L23_001B1724, D_L23_001B1728, D_L23_001B1770);
    func_0028EA58(func_0028E588(0xEAA4, 2), D_L23_001B172C, HudPlain((float)D_L23_001B1730), D_L23_001B1734, D_L23_001B1738, D_L23_001B1770);
    ratio = (float)*(int *)(D_00189E20 + 0x1874) / (float)*(short *)(state + 0x2F4);
    x = D_L23_001B1708 + D_L23_001B1700 + D_L23_001B1718;
    y = D_L23_001B170C + D_L23_001B1704 / 2 - D_L23_001B1710 / 2;
    width = D_L23_001B1714;
    color.half[0] = D_L23_001B16E0;
    color.half[1] = D_L23_001B16E8;
    color.word[1] = (color.word[1] & 0xFFFF00FF) | ((int)(ratio * 255.0f) << 8);
    D_L23_001B1780++;
    func_0027EAE8(x, y, x + (int)(ratio * (float)width), y + D_L23_001B1710, 0xFFFFF1, &color);
    ratio2 = *(float *)(state + 0x20) / (float)*(short *)(state + 0x2F6);
    width2 = D_L23_001B1714;
    color.half[0] = D_L23_001B16F0;
    color.half[1] = D_L23_001B16F8;
    right = D_001A7340 - D_L23_001B1708 - D_L23_001B1700 - 4;
    color.word[0] = (color.word[1] & 0xFFFF00FF) | ((int)(ratio2 * 255.0f) << 8);
    func_0027EAE8(right - (int)(ratio2 * (float)width2), y, right, y + D_L23_001B1710, 0xFFFFF1, &color);
    func_0028EA58(func_0028E588(0xEAA5, 0), D_L23_001B173C, HudRound((float)D_L23_001B1740, 1.0f, first), D_L23_001B1744, D_L23_001B1748, D_L23_001B1770);
    second = 1;
    func_00115DA8(text, D_L23_001B1788, D_L23_001B1F90.counter);
    rasterY = HudPlain((float)D_L23_001B1758);
    textPtr = text;
    textX = D_L23_001B174C;
    func_0027FB40(D_L23_001B1754, rasterY, textX, (unsigned char *)textPtr, func_001157AC(textPtr));
    if (D_L23_001B1F90.icons) {
        func_0028EA58(func_0028E588(0xEAA5, 1), D_L23_001B175C, HudRound((float)D_L23_001B1760, 1.0f, second), D_L23_001B1764, D_L23_001B1768, D_L23_001B1770);
    }
    if (D_L23_001B1F90.icons > 1) {
        func_0028EA58(func_0028E588(0xEAA5, 1), D_L23_001B175C + D_L23_001B176C, HudRound((float)D_L23_001B1760, 1.0f, 1), D_L23_001B1764, D_L23_001B1768, D_L23_001B1770);
    }
    message = D_L23_001B374C;
    if (message != -1 && D_L23_001B3748 == 0) {
        switch (message) {
        case 0:
            func_L00_0030DD70(func_00288FB8(0x2FA3), -1);
            break;
        case 2:
            func_00288FB8(0x1241);
            func_0029CC50(0x1241, *(short *)(state + 0x2FC), -1);
            break;
        case 1:
            func_00288FB8(0x1240);
            func_0029CC50(0x1240, D_L23_001B3750, -1);
            break;
        }
        D_L23_001B3754 = 0;
        func_00282948((char *)&D_L23_001B3754);
        if (D_L23_001B3754 < 1) D_L23_001B374C = -1;
    }
    if (D_L23_001B1424) {
        func_002802E0(panel, 240, 480, 44, 468, 256, HudPlain(320.0f), 16, 3);
        a = func_00288FB8(0x9FC);
        b = func_00288FB8(0x2F2C);
        func_0029B888((int)panel, 0x80F0F0F0, a, 0, 0, -1, 0, b, 0, 0);
    }
    func_L00_0030CF60();
    return 1;
}
