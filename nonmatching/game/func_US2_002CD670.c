/* func_US2_002CD670 (2,108 bytes, USA v2.00): near miss, G8 (unit 002CD670-hud-g8.c).
 * The v2.00 copy of func_002CC6B0 (src/game/002CC6B0-hud-g8.c), adapted: text ids 0x31B9/0x31B8/
 * 0x2C56, gap constant 16 (s[8] = 16, scroll pitch 48), a new $gp word D_US2_001AB9D0 (the last
 * w+0x34 seen: a change of it restarts the scroll at -(height * 8)).
 * Flags: -O2 -G8 -ffunction-sections -frac2-flow2-trap-mem -frac2-la-multi-death-locals
 *        -frac2-sched-temp-store-after-args   (no -frac2-sched-const-first: it hoists the 16)
 * 14 November 2026: 2108/2108 bytes, 0/28 places. Left: (1) text and tex swap $fp/$s7 (text needs
 * a higher global-alloc priority than tex: regalloc.py gives text 45/806 against tex 8/138);
 * (2) after the w+0x34 test retail loads w+0x34 before w+0x30 and issues `lui s0,2` after the lhu
 * (regs a0/a3/v0/v1); ours loads w+0x30 first; (3) the scroll DRAW: `addiu a3,-1` before
 * `sh 0x4A`. FAKEMATCH sites: volatile store keeping the sum's store before the modulo (with the
 * gap constant nothing protects it from flow's dead-store deletion), y reuse in the scroll copy,
 * and the dead win_shift/unshift of func_002CC6B0 in the clip block. */
#include "common.h"
typedef struct { short s[12]; } Win;
typedef struct { char pad[0x3C]; int so; } LabelSO;
extern char D_001AB988[], D_001AB990[], D_001AB998[], D_001AB9A0[];
extern unsigned char D_00263B50[], D_00264290[], D_00263EF0[], D_00139568[];
extern unsigned char D_001A7AF8[] MACRO_ADDR, D_001395B8[] MACRO_ADDR, D_001A7A60[] MACRO_ADDR;
extern int D_001C51D0 NOT_SDA;
extern int D_001A7B90[] MACRO_ADDR;
extern int D_001A79F0 __attribute__((sda));
extern int D_001AA440 __attribute__((sda));
extern int D_001AB984 __attribute__((sda));
extern int D_001AB9A8 __attribute__((sda));
extern int D_001AB974 __attribute__((sda));
extern int D_001AB9AC __attribute__((sda));
extern int D_US2_001AB9D0 __attribute__((sda));
extern int D_00138320[];
extern char *D_001F2854 NOT_SDA;
extern char D_0025A498[];
extern void func_002FC560(int, long);
extern int func_0029DB28(int *, unsigned int *, int *, int);
extern int func_00289FC8(short, int, unsigned short *);
typedef struct { unsigned char pad[4]; unsigned char available; unsigned char tail[0xDB]; } ItemConfig;
extern ItemConfig D_00239BA0[];
extern int func_00115DA8(char *, const char *, ...);
extern void *func_00115484(void *, int, int);
extern void func_0027C540(int);
extern long func_0027C878(int);
extern void func_0027C660(void), func_0027F120(void), func_0027F110(void);
extern char *func_00288FB8(int);
extern void func_0027FC70(void *, long, char *, long, long, unsigned char *);
extern void func_0027ECC8(int, int, int, int, int);
#define ST (*(char **)(D_001F2854 + 0xE8))
#define TEXT(id) func_00288FB8(id)
#define DRAW(c,t) func_0027FC70(&win,c,t,-1,tex,glyphs)
static inline int translated_edge(int extent, int origin) { return extent + origin; }
static inline void set_anchor(Win *p, unsigned short anchor) { p->s[5] = anchor; }
static inline void set_top(Win *p, unsigned short top) { p->s[0] = top; }
static inline void set_window_vertical(Win *p, unsigned short top, unsigned short anchor) { p->s[5] = anchor; p->s[0] = top; }
int func_US2_002CD670(unsigned char *w) {
    char buf[0x40];
    int id;
    int helpResult;
    int originY, originX;
    Win win;
    Win tmp;
    char *text = D_001AB988;
    unsigned char *glyphs = D_00263B50;
    int font;
    int f0, flags, g, f, content, variant = 0, a21, a23, colour, t, wflags;
    /* func_0027C878's TEX0 is 64 bits, and FontPrintWindow reads all of them: on the console the
       register keeps them whatever the C says, on a PC an int keeps only the low half. */
    long tex;
    int clip, anchor, k;
    int y, x; /* FAKEMATCH: y/x only serve the second scroll block below */

    font = 1;
    f0 = *(int *)(w + 0x30);
    if (f0 & 8) {
        font = 3;
        glyphs = D_00264290;
    }
    if (f0 & 0x10) {
        font = 2;
        glyphs = D_00263EF0;
    }
    func_002FC560(0x42, 0x44);
    ((void (*)(int, long))func_002FC560)(0x47, 0x2004B);

    flags = *(int *)(w + 0x30);
    if (flags & 0x20) {
        content = D_001A79F0 - 1;
        if ((unsigned int)content >= 0x12) {
            content = -1;
        }
    } else if (flags & 0x40) {
        content = D_001C51D0 - 1;
    } else if (flags & 4) {
        t = D_001AA440;
        if (*(int *)(w + 0x44) < t) {
            *(int *)(w + 0x44) = D_001AA440;
        }
        content = 0;
        *(int *)(w + 0x48) = 0;
        *(int *)(w + 0x4C) = 0;
    } else if (flags & 0x80) {
        content = *(int *)(ST + 0x40);
        if (flags & 0x8000) {
            variant = D_001A7B90[0] != 0;
        }
    } else if (flags & 0x100) {
        char *cell;
        content = *(int *)(ST + 0x3C);
        cell = *(char **)(ST + 0x48) + content * 10;
        if (*(short *)(cell + 4) == 0) {
            id = D_001A7AF8[*(short *)(cell + 6)];
        } else {
            id = D_001395B8[*(short *)(cell + 6)];
        }
        if (id == 0) {
            content = -1;
            t = 0;
        }
    } else if (flags & 0x1000) {
        char *st = ST;
        content = *(int *)(st + 0x40);
        id = *(short *)(*(char **)(st + 0x34) + content * 12);
        *(int *)(w + 0x34) = 0xFFFF;
        func_00289FC8(id, 0, (unsigned short *)(w + 0x34));
    } else {
        char *cell;
        int k;
        cell = (char *)(*(int *)(ST + 0x3C) * 10 + *(int *)(ST + 0x48));
        k = *(short *)(cell + 6);
        variant = 0;
        if (*(short *)(cell + 4) == 0)
            variant = ((ItemConfig *)(D_00139568[k] * 0xE0 + (int)D_00239BA0))->available != 0;
        content = k;
    }

    if (*(int *)(w + 0x44) == -1) {
        *(int *)(w + 0x44) = D_001AA440;
        *(int *)(w + 0x48) = content;
        *(int *)(w + 0x4C) = variant;
    }
    if (content != *(int *)(w + 0x48)) {
        int fade;
        t = D_001AA440;
        if (t < *(int *)(w + 0x44)) {
            *(int *)(w + 0x44) = D_001AA440;
        }
        fade = *(int *)(w + 0x44);
        { int was = fade < 1; fade--; if (was) fade = 0; }
        { int was = fade < 1; fade--; if (was) fade = 0; }
        { int was = fade < 1; fade--; if (was) fade = 0; }
        *(int *)(w + 0x44) = fade;
        if (fade != 0) {
            content = *(int *)(w + 0x48);
            variant = *(int *)(w + 0x4C);
        } else {
            *(int *)(w + 0x48) = content;
            *(int *)(w + 0x4C) = variant;
            *(int *)(w + 0x30) &= ~0x400;
            *(int *)(w + 0x3C) = 0;
        }
    } else {
        *(int *)(w + 0x44) += 3;
    }

    g = *(int *)(w + 0x30);
    if (g & 4) {
        if (*(int *)(w + 0x34) == 0) {
            return 1;
        }
        text = TEXT(*(int *)(w + 0x34));
    } else if (g & 0x1000) {
        if (*(int *)(w + 0x34) == 0xFFFF) {
            return 1;
        }
        if (*(int *)(w + 0x34) == 0) return 1;
        text = TEXT(*(int *)(w + 0x34));
    } else if ((g & 0x100) && content == -1) {
        text = D_001AB990;
    } else if (*(int *)(w + 0x34) != 0) {
        unsigned int at = (unsigned int)(content * *(int *)(w + 0x38)) >> 2 << 2;
        char *table = *(char **)(w + 0x34);
        text = TEXT(*(int *)(at + (unsigned int)(table + variant * 4)));
    }
    if ((*(int *)(w + 0x30) & 0x11E4) == 0 && ((unsigned char *)&D_001A7AF8)[content] == 0) {
        text = D_001AB990;
    }
    if (*(int *)(w + 0x30) & 0x200) {
        unsigned int at = (unsigned int)(content * *(int *)(w + 0x38)) >> 2 << 2;
        char *table = *(char **)(w + 0x34);
        int id = *(int *)(at + (unsigned int)table);
        if (id != 0xB4B && id != 0xB52 && id != 0xB56) {
            func_00115DA8(buf, D_001AB998, TEXT(0xB44), text);
            text = buf;
        }
    }
    f = *(int *)(w + 0x30);
    a23 = *(int *)(w + 0x18) + *(int *)(w + 0x20) / 2;
    a21 = *(int *)(w + 0x1C) + *(int *)(w + 0x24) / 2;
    if ((f & 0x4004) == 0x4004 && *(int *)(w + 0x34) == 0x31B9) {
        func_0029DB28((int *)0x70000000, (unsigned int *)&helpResult, 0, 0);
        if (helpResult < 0) text = TEXT(0x31B8);
        a21 += 8;
    }
    if (*(int *)(w + 0x30) & 0x800) if (D_001A7A60[content] == 0) {
        text = TEXT(0x2C56);
        f |= 3;
    }
    if (text == 0) {
        text = D_001AB9A0;
    }
    wflags = 8;
    if (f & 1) {
        wflags = 9;
        a23 = *(int *)(w + 0x20) / 2;
    }
    if (f & 2) {
        wflags |= 2;
        a21 = *(int *)(w + 0x24) / 2;
    }

    func_0027C540(0);
    tex = func_0027C878(font);
    if (D_001F2854 == D_0025A498 || D_001AB9A8 != 0) { originY = a21; originX = a23 + 1; } else { originX = 1; originY = D_001AB974; }
    func_00115484(&tmp, 0, 0x18);
    tmp.s[0] = originY;
    tmp.s[1] = *(unsigned short *)(w + 0x24) + originY;
    tmp.s[2] = originX;
    tmp.s[3] = translated_edge(*(unsigned short *)(w + 0x20), originX - 4);
    tmp.s[4] = a23;
    tmp.s[5] = a21 - (*(int *)(w + 0x3C) >> 4);
    tmp.s[8] = 16;
    tmp.s[9] = wflags;
    tmp.s[11] = -(*(unsigned short *)(w + 0x3C) & 0xF);
    win = tmp;
    if (D_001AB9AC) func_0027ECC8(win.s[0], win.s[1], win.s[2], win.s[3], 0x40303030);
    if (*(int *)(w + 0x30) & 0x10000) {
        win.s[1] = *(unsigned short *)(w + 0x24) - 1;
    }
    colour = 0x80F0F0F0;
    win.s[9] |= 4;
    DRAW(colour, text);
    win.s[9] ^= 4;
    if (!(*(int *)(w + 0x30) & 0x2000) && !(win.s[7] + 4 < win.s[1] - win.s[0])) {
        if (!(*(int *)(w + 0x30) & 0x400)) {
            *(int *)(w + 0x30) |= 0x400;
        }
    } else {
        if (*(int *)(w + 0x30) & 0x400)
            *(int *)(w + 0x30) ^= 0x400;
        *(int *)(w + 0x3C) = 0;
    }
    if (D_US2_001AB9D0 != *(int *)(w + 0x34) && (*(int *)(w + 0x30) & 0x400)) {
        *(int *)(w + 0x3C) = -(*(int *)(w + 0x24) * 8);
    }
    anchor = *(int *)(w + 0x3C);
    anchor >>= 4;
    anchor = a21 - anchor;
    set_anchor(&win, anchor);
    /* FAKEMATCH: dead shift/unshift on stand-in globals (RAC1 win_shift/win_unshift without the
       shadow DRAW), as in func_002CC6B0: combine cancels it and leaves USE insns at the block head. */
    clip = D_001AB974; k = D_001AB9A8;
    win.s[5] += clip; win.s[5] += k; win.s[5] -= clip;
    clip = *(int *)(w + 0x30);
    D_US2_001AB9D0 = *(int *)(w + 0x34);
    set_top(&win, win.s[0]);
    win.s[5] -= k; /* FAKEMATCH: unshift after the s[0] copy */
    k = 0x20000; /* FAKEMATCH: mask kept in the reused stand-in */
    clip &= k;
    if (clip) {
        func_0027F120();
    }
    DRAW(colour, text);
    if (*(int *)(w + 0x30) & 0x20000) {
        func_0027F110();
    }
    if (*(int *)(w + 0x30) & 0x400) {
        /* FAKEMATCH: y holds s[5] + 48 and then the s[0] copy, so the lhu waits for the add
           that reads it (anti dependence) as in retail. */
        y = (unsigned short)win.s[5] + 48;
        x = (unsigned short)win.s[7] + y;
        y = (unsigned short)win.s[0];
        win.s[0] = y;
        win.s[5] = x;
        DRAW(colour, text);
        if (*(int *)(w + 0x30) & 0x400) {
            /* FAKEMATCH: volatile store keeps the sum's store, which the constant gap no longer
               protects from flow's dead-store deletion */
            int so = ((LabelSO *)w)->so + ((D_00138320[0] & 0xF) == 0xF ? 10 : 3);
            ((volatile LabelSO *)w)->so = so;
            ((LabelSO *)w)->so = so % ((win.s[7] + 48) << 4);
        }
    }
    func_0027C660();
    return 2;
}
