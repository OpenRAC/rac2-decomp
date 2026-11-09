/* 9 November 2026 (o151, dump-driven, 1 check.py run): best C unchanged, 36 rows. Correction: the 2076 size is the missing store1 (-4) plus the group's `.p2align 3` nop before $L75 (+4), so only a no-group form is size-honest (2072). Tail mechanism (cc1 diagnostics, not landable): flow2 keeps store1 only if a memory read stays between the two stores in sched1 order. D_001AB984 always passes the struct store (fixed-scalar/struct rule, even with an unknown store base); the read that has to stay is lh win.s[7]. With the tail store through a pointer set twice (`l = (LabelSO *)w;` at the top and again in the tail) the base is unknown in sched1, so the lh stays below the store and store1 survives (div; sw; trap order). But l takes s0 (two sets), and sched2 also keeps the lh below. Retail hoists the lh above store1 in sched2, so retail needs a store pointer with an unknown base in sched1 (REG_N_SETS > 1, or set from a non-base source) whose hard reg after reload is s1 with its single `s1 = a0` set (base ADDRESS(a0)). No honest C form for that was found. Region +0x6CC: retail's lui s0 issues at t4 (after lw 0x30 at t2 and sra/lhu at t3), so it needs a latency-2 dependence on a load. There is no hard-reg dependence for it, and 4 statement orders of the g/y loads/and (cc1) keep `li s0` at t1. */
/* 9 November 2026 (o84, dump-driven): 40 -> 36 rows (2076 bytes, own row count, same in an int-helper build). Region +0x6A0 was local-alloc: y chain (lw 3C/sra/subu tied, 6 refs, pri 12/14) beat flags (lw 30/and tied, 8/10) and the s[0] copy (2/8), so y took v0. Fix: y built in the dead multi-block local id (`id = w->3C; id >>= 4; id = a21 - id;`, id is a0 in retail's 0x100/0x1000 arms) goes to global-alloc -> a0, and `g = w->30 & 0x20000; if (g)` (dead local g) leaves the copy alone in local-alloc -> v0, flags -> v1: retail's registers, no other row changed. Left: (1) sched2 issues li s0 (1250, ready at t=1, no deps) beside lw 3C; retail issues it at t=4, so retail's lui had a dependence ours lacks (not found); (2) region 2 is inside the do-while(0) group whose loop notes stop the arg moves interleaving, so the s[5] sum stays short-lived (a0, not t2); removing the group interleaves but gives 2072 bytes/53 rows; (3) flow2 div-guard store unchanged. */
/* 9 November 2026 (Sonnet round, o29, lesson 49): retail reads win.s[0], s[5], s[7] with lhu in both set_window_vertical blocks; helper parameters `unsigned short top, unsigned short anchor` give exactly that lhu/sh (41 rows, 24 mnemonic diffs against 40/28 for int parameters); what is left is local-alloc order (y in v0 not a0, s[5] sum not in t2: retail stores after the argument moves) and the flow2 div-guard store. Store order, parameter order, y inline/short/unsigned short, anchor-sum spellings and no do-while do not change it (41-62). 25-min permuter from the unsigned-short C: best 55 rows (fake 0x20000 local). Native-oriented variant block kept; best stays the C below. */
/* 8 November 2026 (Sonnet round, o13): set_window_vertical with int parameters gives 40 rows (was 41; own rdump count); swapped parameter order/store order, local top, self-assignment, no do-while, anchor local, += forms do not help (40-84). Lesson-48 move sweep (302 moves, depth 5) finds nothing under 40; 25-min permuter from the int-parameter C found only formatting/fake temporaries. Div-guard store remains the compiler flow2 issue. */
/* 8 November 2026 (Sonnet round, prototype audit, lesson 47): func_0027FC70 4th parameter is declared long but src/game/0027F128-fpw-g8.c has int len: corrected, 41 -> 41 rows, no change. */
/* 8 November 2026 (Sonnet round, o6b): new best 40 rows (2076 bytes; intermediate store still deleted): in */
/* 8 November 2026 (round 12b, m3x, const base): D_001AB984 read into a local before the +=
 * (block top, or once before the second set_window_vertical and kept across the call in s0)
 * puts every memory read before store1, so flow2 deletes it again (2072). +0x6A0: on the const
 * base, so>>4 stays in v0 and the s[0] copy in a0 for: inline expression, unsigned short y,
 * (unsigned short) top, so/top locals, LabelSO read, Win *p, one-pass groups around y, around the
 * helper call, around the 0x20000 test, flag test hoisted into a local. Direct self-assignment
 * win.s[0] = win.s[0] is dropped (retail keeps the lhu/sh). Not landed.
 */
/* 8 November 2026 (round 12, m3x): `extern const int D_001AB984` (legitimate: value 16, only
 * read anywhere; a small const int lands in .sdata under -G8) with the %= span form (span read
 * after the +=) keeps retail's intermediate store: 2076/2076 bytes without any group. But const
 * drops the load's MEM_SCALAR_P (/f), so true_dependence pins the D load after the store in both
 * sched1 and sched2; retail hoists it to the block start (beqz delay slot). Tail order differs,
 * 43 differing rows against 41 for the plain form (same count method). Reasoning: flow2 keeps store1 only with a memory read
 * between the stores; the only asymmetry between sched1 and sched2 alias checks is pseudo vs hard
 * reg base values, and neither D (symbol vs argument base) nor win.s[7] (stack, never aliases)
 * gets one. -fno-schedule-insns scrambles from +0x14. Not landed.
 */
/* 8 November 2026 (round 9, wccT): flow-TRAP_IF hypothesis falsified. Upstream gcc-2.95.2
 * flow.c mark_used_regs clears mem_set_list at TRAP_IF/UNSPEC_VOLATILE/volatile asm (Jeff Law,
 * 27 March 1999); EE 991111's Cygnus tree (merged to ~18 March 1999) lacks it; div_trap is the
 * same separate trap_if insn in both. Backported env-gated: this function's tail becomes retail's
 * (div; sw v0,0x3C(s1); beql; mfhi; sw), first diff stays +0x6A0. All-units sweep: 7 of 8761
 * matched units change for the worse (L22_002BF1B0/L23_002C38B0 us/pal/us2, PAL L18_0043A56C
 * gain a store before a div guard that retail drops). SN cc1 under wine on a reduced pair:
 * 2.95.2/2.95.3 keep both stores, SN 2.9-ee-991111 drops both, so retail's flow is 991111's and
 * this store needs another cause. Not landed.
 */
/* 8 November 2026: retained reconstruction, not linked or counted.
 * Tail: the source is RAC1's span-first form (span computed into a local, then
 * += and %=; RAC1 matches it 100%). As a diagnostic, RAC1's local SN ee-gcc
 * 2.95.2 and 2.95.3 cc1 (under wine, nothing added to the repo) keep retail's
 * intermediate `sw v0,0x3C(s1)` between div and the guard with exactly this C, in
 * a reduced test and in this whole function. This tree's flow2 deletes it: its
 * flow.c mark_used_regs does not treat TRAP_IF as using memory (GCC 3 clears
 * mem_set_list there), so store1 -> trap_if -> store2 looks dead. Closing it
 * needs a compiler transformer; no source form can, and none was added.
 * Remaining source differences (identical under SN, so real): +0x6A0..+0x6EC the
 * so>>4 chain takes v0 and the s[0] copy a0 (retail reverse); +0x73C..+0x780
 * allocation/order of the second set_window_vertical. A do/while(0) group around
 * that second call (below) cuts the region's rows 31 -> 24 (D in a0, s[7] in v1
 * like retail), but adds a word: 2076/2076, 38 aligned rows differ (without the
 * group: 2072, 36). Tried without effect for +0x6A0: helper store order, param
 * types, y split/rewritten, so/top locals, groups around the so load, top or y.
 */
/* 5 November 2026: retained reconstruction, not linked or counted.
 * Retain the actual func_0029DB28 and func_00289FC8 interfaces.
 * A consistent volatile scroll-field experiment preserved the two tail stores and reached 2076 bytes, but changed earlier branch slots and still failed 0/28 USA places at +0x25C.
 * The better nonvolatile source remains below; its missing intermediate store is unresolved.
 * Earlier measurements below describe earlier sources or toolchains.
 */
#include "common.h"
/* 4 November 2026: an alias-model control declares D_001AB984 as an
 * incomplete SDA array and reads element zero, following the documented
 * fixed-scalar/struct-store distinction. It keeps the intermediate store
 * but grows 2072 to 2084 bytes against 2076, still 0/28 USA placements.
 * The broader reload/scheduling regression is rejected; the better C
 * below is retained. No extra volatile access or barrier was introduced.
 */
/* Claude Opus 5.5, xhigh effort, 2 November 2026 (task v2080).
 * USA v1.01, current pinned game compiler, -O2 -G8 -ffunction-sections:
 * check.py: 2072/2076 bytes, 0/28 places match (53 differing rows, all of the
 * shortfall is the one deleted store). Builds on GPT-6.1 Sol's v1320 draft
 * (adapted from RAC1 src/game/pause.c render_configured_text_label, GPL-3.0).
 *
 * Fixed here: the item-table lookup at +0x164 (index the two tables directly
 * from the cell, with no table variable, so no global pseudo takes $a1). The
 * scroll tail now follows RAC1: the span is computed inside the %= (after the
 * add) and the field is written as a struct member (LabelSO). Through reload
 * this keeps the intermediate store between the div and the trap, which is
 * retail's order, and every register in the tail matches retail.
 *
 * Remaining: (1) flow2 still deletes the intermediate `sw v0,0x3C(s1)`.
 * sched1 hoists the fixed-scalar D_001AB984 load above the struct store
 * (true_dependence allows that), so at flow2 nothing reads memory between
 * the two stores (the b1013 pattern). Retail must have kept that load below
 * the store until after flow2 and hoisted it only in sched2. The span-first
 * or cast `*(int *)(w + 0x3C)` forms lose the store in flow1, or keep it with
 * the load scheduled after it. (2) The marquee window sets at +0x6A0..+0x6EC
 * put the scroll chain in v0 and s[0] in a0, where retail is the reverse.
 * Argument order, store order and a temporary did not change this. (3) At
 * +0x73C..+0x780, s[0] is loaded early into t1, where retail loads it late
 * into v0.
 * No volatile, register pins or barriers. Needs a dedicated -g8.c unit
 * (sda declarations); replace the marker before running check.py.
 */
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
static inline void set_window_vertical(Win *p, unsigned short top, unsigned short anchor) { p->s[5] = anchor; p->s[0] = top; }
int func_002CC6B0(unsigned char *w) {
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
    if ((f & 0x4004) == 0x4004 && *(int *)(w + 0x34) == 0x112D) {
        func_0029DB28((int *)0x70000000, (unsigned int *)&helpResult, 0, 0);
        if (helpResult < 0) text = TEXT(0x112C);
        a21 += 8;
    }
    if (*(int *)(w + 0x30) & 0x800) if (D_001A7A60[content] == 0) {
        text = TEXT(0x2DC0);
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
    tmp.s[8] = *(int *)&D_001AB984;
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

    id = *(int *)(w + 0x3C);
    id >>= 4;
    id = a21 - id;
    set_window_vertical(&win, win.s[0], id);
    g = *(int *)(w + 0x30) & 0x20000;
    if (g) {
        func_0027F120();
    }
    DRAW(colour, text);
    if (*(int *)(w + 0x30) & 0x20000) {
        func_0027F110();
    }
    if (*(int *)(w + 0x30) & 0x400) {
        do { set_window_vertical(&win, win.s[0], win.s[5] + (win.s[7] + *(int *)&D_001AB984 * 3)); } while (0);
        DRAW(colour, text);
        if (*(int *)(w + 0x30) & 0x400) {
            int span = (win.s[7] + *(int *)&D_001AB984 * 3) << 4;
            ((LabelSO *)w)->so += (D_00138320[0] & 0xF) == 0xF ? 10 : 3;
            ((LabelSO *)w)->so %= span;
        }
    }
    func_0027C660();
    return 2;
}
