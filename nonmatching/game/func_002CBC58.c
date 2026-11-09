/* 9 November 2026 (o146, dumps): still 1 row. New: a second set-once pointer `StateCBC58 *cur = state;` with `if (state->page) panels = cur->page->panels;` and the arm empty keeps the entry zero (cprop has nothing to fold: cse1 sees two different loads, so jump.c does not if-convert after cse1), 2100 bytes, but the selection then never becomes a cmov: gcse PRE turns the second load into a copy, cse2 leaves that dead copy (r141 = r140) in the arm and no dead-insn pass runs before the post-loop/post-cse2 jumps, so the arm stays two insns (branch + bnel, fp/s7 swap, 58 rows; with panels = 0 in the arm 39). Same with cur = &D_001F2840 or the forms reversed; D_001F2840.page vs cur gives 2108 (branch). Retail needs the cmov formed before gcse AND the entry zero unavailable at the merge. */
/* 9 November 2026 (o112, L06_00382608 set-once-constant lever, local cc1 scorer, ~90 compiles): a set-once `PanelCBC58 **none = 0` for the arm's panels = 0, and set-once int zeros passed to func_00284F40 / func_0027DDC0 / each arm's func_0027C540, at every statement position up to the arm: best stays 1 row (+0x1A8 beql slot); gcse cprop still folds the set-once zero, so the merge stays constant. */
/* 9 November 2026 (Sonnet round o73, dumps): 1 row remains. Deciding rule: gcse CPROP pass 1 puts the entry 0 of panels (reg 85) into the merge cmov (insn 1440 -> movz, 2092) unless a non-constant def reaches it. The arm cmov (insn 1286, 85 = 135 ? 85 : 0) blocks that, but cprop makes it 135 ? 0 : 0, cse2 keeps it and combine folds it with the adjacent volatile load into 85 = 0 (load dropped). If the load cannot combine, the set stays (lw v0 + daddu s7, 406). Retail needs a non-constant def at gcse that leaves no code. Tried: panels = panels (507), (T)D_001AB910 (410), D_001AB910 ? panels : 0 (410), if (panels) panels = 0 (406), f = D_001AB910; if (!f) panels = (T)f (406), RAC1 ternary without init (151, entry zero lost), state->page forms (402, no cmov). */
/* 9 November 2026 (Sonnet round, s43, lesson 52): scripted do { real_op; } while (0) sweep over every 1-3 consecutive simple statements in the function (all positions) plus all disjoint pairs of groups, masked and unmasked scores, and every -frac2-* switch (single and pairs) on the unit: best stays 1 row (arm slot); also on the empty-arm base (2092); no group or switch improves it. */
/* 8 November 2026, Sonnet round (o24): still 1 row. RTL dumps: gcse cprop puts the entry zero into the panels cmov (movz) even with two separate `panels = 0` sets (no init; one in the D_001AB91C block, one in its else), since identical (reg, const) sets hash as one available set; a zero set in the D_0025A498 arm, a zero before the D_001AB91C block, or an else zero with the init: all 2092 bytes (movz). Only a non-constant set reaching the selection (the arm's folded cmov) gives retail's movn. */
/* 8 November 2026, Sonnet round (o12, lesson 48 sweep): scripted local-cc1 sweep of every simple statement moved up/down 1..6 lines within its block (148+68 variants) plus all 20 pairs of the neutral moves: none below 1 row. */
/* 8 November 2026 (Sonnet round, prototype audit, lesson 47): func_0026FEB8 is declared (void *) but src/game/0026EA00.c is (const char *format, ...): corrected, still 1 row. */
/* 8 November 2026, Sonnet round (o9, ~25 check.py runs, one 1500 s permuter run from the 1-row C: no gain over 200). Still 1 row. Empty arm alone: arm bytes match retail but the selection turns movz (2092). Tried, no gain: lesson 46 full tail copy in the D_0025A058 arm with return (3716, no cross-jump), panels = 0 in the D_0025A498 arm with the D_0025A058 arm empty (2092), "if (!D_001AB910) panels = 0;" or "if (D_001AB910); else" nested under the page test, goto to a label at the tail call from the arm or the D_0025A498 arm, "if (!D_001AB91C) goto tail;" form (all 1 row). */
/* 8 November 2026 (Sonnet round, arm push): retail's arm is beql page==X */
/* 8 November 2026 (Sonnet round): bounds loop solved; 2100/2100 bytes and
 * one row left (the C below). A loop-body local "StateCBC58 *st =
 * &D_001F2840;" with the page read after the D_001AA450[j] test
 * ("pg = st->page;", then "if (panels && panels[j])", first statement via pg,
 * the rest via st->page) gives the retail beqz s7 slot, the hoisted t2 and the
 * retail preheader order: st's lo_sum is set before any loop jump, so loop.c
 * may hoist it although it is used in several blocks. Same result as a comma
 * form; st set before the loop swaps the preheader lui pair (7 rows). With
 * "panels = 0;" in the D_0025A058 arm the only diff is that arm's delay slot
 * (daddu s7 for the volatile D_001AB910 load: combine folds "lw ? 0 : 0" and
 * drops the load). Without it, 47 rows (movz). Tried on this base, no gain:
 * "(void)D_001AB910; panels = 0;" either order (cse1 deletes the zero: 47),
 * empty arm plus "else panels = 0;" (47), "(panels = 0, !D_001AB910)" (47),
 * "panels = 0;" in the arm and an else (2124 bytes). A capped permuter run
 * from this C (score 200) only gained by adding a second volatile
 * D_001AB910 read (160; rejected, not honest C).
 */
/* 8 November 2026 (round 3): the 8 extra bytes of the "panels = 0;" arm
 * form are not in the arm (there one word changes: daddu s7 replaces the dead
 * D_001AB910 load). They are the bounds loop: retail fills the beqz s7 slot
 * with the page load from before the branch; here the load comes after the
 * panels[j] test, so reorg uses beql with a copied j++ (+4), and the shift
 * adds a loop-alignment nop (+4). Reading the page between the
 * D_001AA450[j] test and the panels test, e.g.
 * "D_001AA450[j] && (pg = D_001F2840.page, panels) && panels[j]" with pg in
 * the first statement, gives 2100 bytes and the retail slot. But loop no
 * longer hoists the %lo(D_001F2840) addiu (t1/t2 swap, addiu in the loop), and
 * the arm word stays wrong. Tried, no gain: "panels = 0;" before the read in
 * the arm, "if (!D_001AB910) panels = 0; else panels = 0;", "panels = 0;"
 * at the join (movz again), "continue" forms of the page read (the same
 * hoisting loss), -fsched-spec-load(-dangerous) (sched1 uses one-block
 * regions here).
 */
/* 8 November 2026 (later): crop clamp solved. Writing each axis as RAC1's
 * pause renderer does but with its half-size computed just before its own
 * subtraction (left=..; right-=left; clamp left; top=..; bottom-=top; clamp
 * top; then "if (tw<right)" and "if (th<bottom)") gives retail's slt/movn/movz
 * order and registers; the retained C below now has it (2100 bytes, about 49
 * rows, all from the panels selection). With "panels = 0;" in the empty
 * D_0025A058 arm as well, only about 5 rows remain (2108 bytes): that arm's
 * delay slot (daddu s7 instead of the dead D_001AB910 load; combine folds the
 * cmov "lw ? 0 : 0" and drops the volatile load), the bounds-loop page load in
 * the beqz s7 delay slot, and one alignment nop.
 * Tried, no gain: "panels = panels;" or "panels = page->panels;" in the arm
 * (the second keeps the load but adds movn), "(panels = 0, !D_001AB910)" in
 * the arm test (cse1 deletes it), uninitialised panels (2100 bytes, movn, no
 * entry zero, s6/s7 swap: about 25 rows), state->page in the selection test
 * (branch, no cmov), -frac2-keep-block-order, -frac2-gcse-unsplit-edges,
 * -fsched-spec-load(-dangerous), and a comma page read in the bounds test.
 * jump.c forms the selection cmov right after cse1, so gcse cprop always sees
 * only the entry zero unless a second set reaches it; no set that leaves no
 * code was found.
 */
/* 8 November 2026: still a near miss (retained C below unchanged: 2100/2100
 * bytes, 0/28; 55 aligned rows differ, mostly the s5/s6/s7 renaming).
 * Cause found: jump.c turns "if (page) panels = page->panels" into a
 * conditional move with the old value of panels (reg_set_last stops at the
 * first label), then gcse cprop puts the entry 0 into it (movz). cprop skips
 * when panels has a second reaching set. "panels = 0;" in the empty
 * D_0025A058 arm gives 11 aligned rows (entry zero, movn and registers all
 * match) but the arm's own cmov folds and drops the dead D_001AB910 load
 * (2108 bytes). Left: that slot, the bounds-loop page load in the delay slot
 * of the panels test, one alignment nop, and the crop-clamp slt order.
 * Tried, no gain: ternary (44 rows), "panels = 0;" just before the if (44),
 * "panels = 0;" in the D_0025A498 arm (deleted by cse1), do/while(0) around
 * the selection (64), state->page in the test or arm (52), -fno-gcse (2072
 * bytes), -fsched-spec-load (no change), all 24 clamp orders and if-form
 * clamps (best 11). D_001AB910 stays volatile as in matched 002C7748-g8.c.
 */
/* 5 November 2026: retained reconstruction, not linked or counted.
 * Retain func_002A0380 as int and func_002FC3C0 with its 64-bit mask.
 * The repaired source still fails all 28 USA places at +0x14.
 * Panel lifetime and clamp scheduling remain open; the indirect callback contract is not newly qualified.
 * Earlier measurements below describe earlier sources or toolchains.
 */
/*
 * Opus 5.5 xhigh worker (v2069), USA v1.01, -O2 -G8 -ffunction-sections.
 * Best check.py result: 2100/2100 bytes, 0/28 places match; 58 of 525
 * aligned instructions differ.
 * Improvement over the Sol-high draft: declaring the callback D_00210AD0
 * nosda gives retail's split lui v0 / lw v1 load and its jalr register.
 * Remaining differences:
 * - panels: retail zeroes it at entry (daddu s7) and selects with movn. Here
 *   the jump pass after cse1 turns "if (page) panels = page->panels" into a
 *   conditional move, and gcse cprop then replaces its panels input with the
 *   constant 0, giving movz at the selection. Writing "panels = 0" in the
 *   empty D_0025A058 arm blocks the cprop and reproduces the prologue, the
 *   movn and the 8-byte loop-alignment nop at 0x2CBEA4. However, that arm
 *   then loses its volatile load (2108 bytes), so it is not a solution.
 * - The saved registers s5/s6/s7 are renamed throughout as a result.
 * - Bounds loop: retail loads page in the delay slot of the panels null
 *   branch. sched1 never moves loads speculatively, so the source must read
 *   page before it tests panels; no natural form was found.
 * - Crop clamp: the order of the slt and movn instructions differs. The order
 *   of the clamp statements makes no difference.
 * Also tried: an int-returning callback (no effect) and
 * "panels = page ? page->panels : 0" (64 rows differ instead of 58).
 * Sol-high notes still apply: a local page variable and a self-default
 * ternary give the same output as the if form. Splitting the panel
 * assignment keeps the entry zero but adds a branch. -fno-gcse gives movn
 * but spills panels (2072 bytes). A nested bounds null check makes
 * allocation worse.
 * All declarations it needs follow. Compile it in a separate -g8.c unit: the
 * 14-entry enabled array needs its SDATA declaration.
 * The crop arithmetic follows the renderer in RAC1's src/game/pause.c.
 * RAC2's screen layout, callbacks, capture gating and fade are derived from
 * retail.
 */
#include "common.h"

typedef struct PanelCBC58 PanelCBC58;
struct PanelCBC58 {
    int unused;
    int (*draw)(PanelCBC58 *);
    int pad8[2];
    int flags, pad14;
    int x, y, width, height;
};
typedef struct { int x, y, width, height; } RectCBC58;
typedef struct { RectCBC58 bounds[14]; char padE0[12]; PanelCBC58 *panels[14]; } PageCBC58;
typedef struct {
    int mode, active;
    char pad8[12];
    PageCBC58 *page;
    char pad18[8];
    void *buffer;
    char pad24[0x144];
    int field168, field16C;
    char pad170[0x50];
    float fade, step, target;
} StateCBC58;
extern StateCBC58 D_001F2840;
extern int D_001A7344, D_001A72DC;
extern int D_001AB91C __attribute__((sda));
extern volatile int D_001AB910 __attribute__((sda));
extern int D_001AA450[14] SDATA(D_001AA450);
extern int D_001AA43C __attribute__((sda));
extern int D_001AB92C __attribute__((sda));
extern int D_001AB930 __attribute__((sda));
extern long D_001A7470 __attribute__((sda));
extern char D_00259018[], D_0025A738[], D_0025A498[], D_0025A190[], D_0025A058[];
extern PanelCBC58 D_00259EE0;
extern char D_001AB920[], D_001AB928[];
typedef struct { char pad[0x1A0]; int flags; char pad1A4[0x20]; int pressed; } PadCBC58;
extern PadCBC58 D_00138180;
extern void (*D_00210AD0)(void) __attribute__((nosda));
extern void func_00284F40(int);
extern void func_002FC990(void *, int, int);
extern void func_0027B858(void);
extern void func_0027DDC0(int,int,int,int);
extern void func_0027C540(int), func_0027C660(void);
extern void func_0028E458(void), func_0029BF08(void), func_0029C2D0(void), func_0029C340(void);
extern void func_002FC560(int, long);
extern void func_002A0250(void), func_002A01C8(void), func_002A01F0(void);
extern void func_0026FEB8(void *);
extern int func_002DBAD0(PanelCBC58 *), func_002DA118(PanelCBC58 *);
extern int func_002D84B0(PanelCBC58 *), func_002DA9A8(PanelCBC58 *);
extern void func_00280510(int,int,int,float);
extern void func_0028FDD8(int,int,int,int,long,int,int);
extern void func_00280600(void);
extern void func_0027E018(int,int,int,int,int,int,int,int,long,long);
extern void func_002A0220(void),func_0029FEE0(void);
extern int func_002A0380(void);
extern void func_002FC3C0(unsigned long);
extern int func_00283CF0(float);

void func_002CBC58(int mode)
{
    PanelCBC58 **panels = 0;
    StateCBC58 *state = &D_001F2840;
    int pass, i, j, x, y, w, h, lw, lh, result;
    int left, top, right, bottom, tw, th;
    float delta;
    func_00284F40(0);
    func_002FC990(state->buffer, D_001A72DC, D_001A7344 << 11);
    if (!mode) {
    func_0027B858();
    func_0027DDC0(0,0,0,0x38);
    if (D_001F2840.mode == 4 && state->active) {
    if (D_001AB91C) {
        void *page = state->page;
        if (page == D_00259018) {
            func_0027C540(0); D_00210AD0(); func_0027C660(); return;
        }
        if (page == D_0025A738) {
            func_0027C540(0); func_0028E458(); func_0029BF08(); func_0027C660(); return;
        }
        if (page == D_0025A498 && !D_001AB910) {
            func_0027C540(0); func_0029C2D0(); func_0027C660();
        } else if (D_001F2840.page == (void *)D_0025A190 && !D_001AB910) {
            func_0027C540(0); func_0029C340(); func_0027C660(); return;
        } else if (D_001F2840.page == (void *)D_0025A058 && !D_001AB910) {
            panels = 0;
        }
    }
    func_002FC560(0x47,0x5360B);
    if (D_001F2840.field168) {
        func_002A0250(); func_002A01C8(); func_002A01F0();
    }
    if (D_001F2840.page) {
        panels = D_001F2840.page->panels;
    }
    if ((D_00138180.flags&15)==15 && (D_00138180.pressed&15))
        func_0026FEB8(D_001AB920);
    for (j=0;j<14;j++) {
        StateCBC58 *st = &D_001F2840;
        if (D_001AA450[j]) {
            PageCBC58 *pg = st->page;
            if (panels && panels[j]) {
                panels[j]->x = pg->bounds[j].x - pg->bounds[j].width/2;
                panels[j]->y = st->page->bounds[j].y - st->page->bounds[j].height/2;
                panels[j]->width = st->page->bounds[j].width;
                panels[j]->height = st->page->bounds[j].height;
                if (panels[j] == &D_00259EE0) panels[j]->height=256;
            }
        }
    }
    if ((D_00138180.flags&15)==15 && (D_00138180.pressed&15))
        func_0026FEB8(D_001AB928);
    for (pass=0;pass<2;pass++) {
        for (i=0;i<14;i++) {
            PanelCBC58 *p;
            if (!panels || !(p=panels[i]) || (p->flags&4) || !D_001AA450[i] || !p->draw) continue;
            if (!pass && !(p->flags&2)) continue;
            if (pass==1 && (p->flags&2)) continue;
            if (p->flags&1) { p->draw(p); continue; }
            x=p->x; y=p->y; w=p->width; h=p->height;
            lw=7; while ((1<<lw)<w) lw++;
            lh=7; while ((1<<lh)<h) lh++;
            while (lw+lh>=18) lh--;
            if ((panels[i]->draw == func_002DBAD0 || panels[i]->draw == func_002DA118 ||
                 panels[i]->draw == func_002D84B0 || panels[i]->draw == func_002DA9A8) && !(panels[i]->flags&8)) {
                func_00280510(lw,lh,0,1.0f);
                func_0028FDD8(0,0,1<<lw,1<<lh,D_001AA43C,0,0);
                result=panels[i]->draw(panels[i]);
                func_00280600();
            } else result=panels[i]->draw(panels[i]);
            func_002FC560(0x42,0x8000000064L);
            func_002FC560(0x47,0x43);
            if (result&1) continue;
            tw=1<<lw; th=1<<lh; left=0; right=tw; top=0; bottom=th;
            if (result&2) { right=w; bottom=h; }
            else if (result&8) {
                left=(right-w)/2;
                right-=left;
                left=left > -1 ? left : 0;
                top=(bottom-h)/2;
                bottom-=top;
                top=top > -1 ? top : 0;
                if (tw<right) right=tw;
                if (th<bottom) bottom=th;
            } else if (result&4) {
                if (w<h) { left=right/2-w*right/(h*2); right-=left; }
                else { top=bottom/2-h*bottom/(w*2); bottom-=top; }
            } else if (!(result&16)) continue;
            if (D_001AB92C)
                func_0027E018(x,y,w,h,left,top,right-left,bottom-top,0x80808080L,D_001A7470);
        }
        if (D_001AB930 && !pass && D_001F2840.field168) {
            func_002A0220(); func_002A0380(); func_002FC3C0(16); func_0029FEE0();
            D_001F2840.field168=0; D_001F2840.field16C=0;
        }
    }
    func_0027B858();
    if (D_001F2840.fade != D_001F2840.target) {
        delta=D_001F2840.target-D_001F2840.fade;
        if (delta>D_001F2840.step) delta=D_001F2840.step;
        else if (delta < -D_001F2840.step) delta=-D_001F2840.step;
        D_001F2840.fade+=delta;
    }
    if (D_001F2840.fade != 0.0f)
        func_0027DDC0(0,0,0,func_00283CF0(D_001F2840.fade*128.0f));
    func_002FC560(0x42,0x8000000044L);
    func_002FC560(0x47,0x5360B);
    }
    }
}
