/* 10 November 2026: exact in USA v2.00 (tools/check.py func_US2_002CCC18 --version us2: "28 of 28 places
 * match", compiled as src/us2/game/002CCC18-g8.c with the default `-O2 -G8 -ffunction-sections`), but only
 * with the qualifier `volatile` on D_001AB910, which C that links may not carry: no code is known
 * to write D_001AB910 (AGENTS.md, "`volatile` describes the memory"). The v1.01 original
 * func_002CBC58 (src/game/002C7748-panels-g8.c) has the same qualifier; the same question holds
 * func_US2_002CCAA0. This is that C with the release's callees:
 * func_00280600 is func_US2_00280FB8, func_0029BF08 is func_US2_0029CD18, func_0029C2D0 is func_US2_0029D108,
 * func_0029C340 is func_US2_0029D178, func_002D84B0 is func_US2_002D9178, func_002DA9A8 is func_US2_002DB700.
 *
 * What the qualifier buys is eight instructions, all in one place. The third page test
 *     else if (D_001F2840.page == D_0025A058 && !D_001AB910) { }
 * has an empty arm, and retail keeps its page load, compare and the read of D_001AB910
 * (`beql $a0,$v1,<next>` with `lw $v0,D_001AB910($gp)` in the slot). Plain `int D_001AB910`:
 * 2068 bytes for 2100. The first two tests (D_0025A498, D_0025A190) are already exact without
 * the qualifier; the jump pass deletes the whole third test and with it the second
 * `lui`/`addiu` of &D_001F2840.
 *
 * Tried without `volatile` (PAL; all compiled, none closer than the last):
 * 1. `if (page == D_0025A058) { if (!D_001AB910) { func_002FC560(0x47,0x5360B); goto drawn; } }`
 *    before the shared `func_002FC560(0x47,0x5360B); drawn:` (equal arms for jump2 to
 *    cross-jump, which would leave the dead load): 2132 bytes, the two copies stay.
 * 2. The call written in every arm (D_0025A498 arm, the D_0025A058 arm, its `else`, and the
 *    `else` of `if (D_001AB91C)`): 2124 bytes. The three inner copies cross-jump and the
 *    `beql`/dead `lw` come out as in retail, but the outer copy stays, behind a `b`.
 * 3. As 2 with `pending = D_001F2840.field168;` after each call, so that no copy ends in a
 *    call: 2140 bytes; the copies load the field through different registers and none merge.
 * Why 1 and 2 stop there (-da dumps): flow's find_basic_blocks puts `(use (const_int 0))`
 * after a call that ends a block before a label, so the copy that falls into the join is
 * `call; use; label` and find_cross_jump (jump.c) stops at the `use` against the copy that
 * ends `call; jump`. Only copies that all end in a jump merge with each other, and the copy
 * retail keeps is the one that falls through. An equal-arms form therefore needs arms that
 * do not end in a call, and this arm has nothing but the shared call after it.
 * Next useful input: evidence of a second writer of D_001AB910 (it is only ever read: a
 * debugger-set switch would be declared exactly so), or a ruling on it, which would also
 * settle func_002CBC58 and func_002CBAE0 and their copies.
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
extern void func_0028E458(void), func_US2_0029CD18(void), func_US2_0029D108(void), func_US2_0029D178(void);
extern void func_002FC560(int, long);
extern void func_002A0250(void), func_002A01C8(void), func_002A01F0(void);
extern void func_0026FEB8(void *);
extern int func_002DBAD0(PanelCBC58 *), func_002DA118(PanelCBC58 *);
extern int func_US2_002D9178(PanelCBC58 *), func_US2_002DB700(PanelCBC58 *);
extern void func_00280510(int,int,int,float);
extern void func_0028FDD8(int,int,int,int,long,int,int);
extern void func_US2_00280FB8(void);
extern void func_0027E018(int,int,int,int,int,int,int,int,long,long);
extern void func_002A0220(void),func_0029FEE0(void);
extern int func_002A0380(void);
extern void func_002FC3C0(unsigned long);
extern int func_00283CF0(float);

void func_US2_002CCC18(int mode)
{
    PanelCBC58 **panels = 0;
    int none = 0;
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
            func_0027C540(0); func_0028E458(); func_US2_0029CD18(); func_0027C660(); return;
        }
        if (page == D_0025A498 && !D_001AB910) {
            func_0027C540(0); func_US2_0029D108(); func_0027C660();
        } else if (D_001F2840.page == (void *)D_0025A190 && !D_001AB910) {
            func_0027C540(0); func_US2_0029D178(); func_0027C660(); return;
        } else if (D_001F2840.page == (void *)D_0025A058 && !D_001AB910) {
            ;
        }
    }
    func_002FC560(0x47,0x5360B);
    if (D_001F2840.field168) {
        func_002A0250(); func_002A01C8(); func_002A01F0();
    }
    if (D_001F2840.page) {
        panels = D_001F2840.page->panels;
        panels = (PanelCBC58 **)((char *)panels + none);
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
                 panels[i]->draw == func_US2_002D9178 || panels[i]->draw == func_US2_002DB700) && !(panels[i]->flags&8)) {
                func_00280510(lw,lh,0,1.0f);
                func_0028FDD8(0,0,1<<lw,1<<lh,D_001AA43C,0,0);
                result=panels[i]->draw(panels[i]);
                func_US2_00280FB8();
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
