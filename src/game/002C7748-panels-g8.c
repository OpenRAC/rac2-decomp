/* func_002CBC58 (2,100 bytes, 28 places): draws the pause-menu panels. -G8 sibling of 002C7748.c.
 * The crop arithmetic follows the renderer in RAC1's src/game/pause.c.
 * Retail keeps `panels` zero from the entry and selects the page's list with movn. gcse's constant
 * propagation would fold that entry zero into a conditional move formed by the jump pass after
 * cse1 (movz, 2092 bytes), so the selection has to stay a branch until gcse is over:
 *   panels = page->panels; panels = (T)((char *)panels + none);
 * `none` is a set-once zero (allowed by owner ruling, 9 November 2026). The arm is two insns for
 * the first jump pass; cprop turns the add into a no-op, the jump pass before cse2 (the only one
 * that deletes dead sets, jump.c after_regscan) leaves one insn and forms the cmov there.
 * The D_0025A058 arm is empty: its test leaves retail's dead load of D_001AB910.
 * The bounds loop reads the page after the D_001AA450[j] test through a loop-local `st`, which
 * gives retail's beqz slot and preheader order.
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
            func_0027C540(0); func_0028E458(); func_0029BF08(); func_0027C660(); return;
        }
        if (page == D_0025A498 && !D_001AB910) {
            func_0027C540(0); func_0029C2D0(); func_0027C660();
        } else if (D_001F2840.page == (void *)D_0025A190 && !D_001AB910) {
            func_0027C540(0); func_0029C340(); func_0027C660(); return;
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
