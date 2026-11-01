/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/*
 * Opus 5.5 xhigh (opus-1), task v1866, 31 October 2026.
 * Best check.py, USA v1.01 (level 05): 3520/3516 bytes, 0/1 places, instruction at +0xc differs,
 * 841 of 880 rows differ (most only because the listing is shifted). No linked build was run.
 * Compile as an isolated -g8.c unit: -O2 -G8 -ffunction-sections. Declarations needed follow.
 *
 * Closeness: by a private sequence alignment with relocated halves and call targets masked (not a
 * check.py result), 667 of 880 rows now line up; the previous draft (task v1580, 3516/3516) had 601.
 * On that masked comparison 0041E3A8..0041EB34, the whole gauge section, has no difference left.
 * What still differs: the switch arms (0041DF64..0041E3A4) and the last sprites (0041EB38..end).
 *
 * New over v1580:
 * - Behaviour repair at 0041E7DC: `bc1t` to the `sw v0,0x38(s3)` at 0041E800, `li v0,1` in its slot.
 *   Health above 0.3 stores 1 in state+0x38 (blink on); the old draft had no such path.
 * - scaled_screen_coord (same body as src/game/002D3390.c) gives 0041E444..0041E4A8 exactly.
 * - func_00283D38 is FastTweenColor(c0, c1, t), as in its other callers.
 * - sprintf's format and both table reads are nested in its call: format in s0 first, then two lookups.
 * - Keep func_00300968's (a0, x, y, colour, s, r) order here: the callee is (int, int, float x4) in
 *   other units, and writing that order here moved `ori a1` and lost the gauge (661 rows, not 667).
 *
 * What the arms need (dumps from tools/regalloc.py; the compiler source reasoning is inference):
 * - Retail keeps `1` in s0 and `mode` in v1. A local `one`, or `flag` with two definitions, folds
 *   (cse/gcse): no change. Reusing the switch's constant needs a later `r == 1` test on the same cse
 *   path. Probe `if (r == 1) return (int)f + adjust; return (int)f;` with a placeholder r put the 1 in
 *   a callee-saved register (s1, not retail's s0) and made the test vanish in the first draw, whose
 *   x then matched arm 2's shape (`lw v0; addiu a0,v0,-60`); the second draw kept its test (3592 bytes).
 * - In arms 0, 1, 3, x stays out of a0 (`addiu v0,v0,-60 ... daddu a0,v0`) and the argument moves
 *   follow the conversion, so something separates x from the moves. In the probe's second draw a local
 *   a0 caused that shape; retail shows no such instruction. D and fmt being s2/s1 rather than local
 *   allocation's s0/s1 suggests they span a block too. That same draw lost cse of .5 across the join;
 *   retail keeps .5 in f20 and D/fmt across both draws, which needs a one-armed `if`, not a join.
 * - Every one-armed body tried is gone before gcse or changes nothing: `y += adjust`, a copy, a dead
 *   local, `h += 4`. No real tested value exists either: the arms load no display mode.
 * - The last sprites show the same boundary after their (int) conversion and a fresh 0 in f22, not f25.
 * - Not landable, diagnostic only: `y; x; do { call } while (0);` fixes block order (659 rows on the
 *   v1580 base) but combine still folds x into a0. `long x` moves its addiu next to retail's place but
 *   adds dsll32/dsra32. Next: a real construct for that boundary; see MATCHING-BLOCKERS "A cse block
 *   boundary that leaves no instruction".
 */
#include "common.h"

typedef struct { int active; char pad[8]; int maximum, capacity, current; char gap[4]; short icon; char tail[10]; } HudItem;
typedef struct { int v[4]; } HudRect;
extern char *D_L05_001B13B0 __attribute__((sda));
extern int D_L05_001B1360 __attribute__((sda));
extern int D_L05_001B1390 __attribute__((sda));
extern int D_L05_001B1394 __attribute__((sda));
extern int D_L05_001B1398 __attribute__((sda));
extern int D_L05_001B139C __attribute__((sda));
extern int D_L05_001B13A0 __attribute__((sda));
extern int D_L05_001B13A4 __attribute__((sda));
extern int D_L05_001B13D0 __attribute__((sda));
extern int D_L05_001B13DC __attribute__((sda));
extern int D_L05_001B1428 __attribute__((sda));
extern int D_L05_001B1438 __attribute__((sda));
extern int D_L05_001B1440 __attribute__((sda));
extern char *D_L05_001A904C MACRO_ADDR;
extern int D_001A7340[] __attribute__((sda));
extern int D_L05_001B143C[] __attribute__((sda)), D_L05_001B1444[] __attribute__((sda)), D_L05_001B142C[] __attribute__((sda));
extern int D_L05_001B3550[] __attribute__((sda)), D_L05_001B2D80[] __attribute__((sda));
extern float D_L05_001B2D84[] __attribute__((sda)), D_L05_001AC4E0[] __attribute__((sda)), D_L05_001AC4E4[] __attribute__((sda));
extern char D_L05_001B1448[], D_L05_001B1450[], D_L05_001B1498[];
extern HudRect D_L05_001B1468, D_L05_001B1478, D_L05_001B1488;
typedef struct { int unused[4]; int objectives; int wave; int more[4]; int health; } SpaceHudStats;
extern SpaceHudStats D_L05_00221D10;
extern HudItem D_L05_002A1800[];
extern void func_L05_00421B98(int,int,int,int);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern void func_0027F5B8(int,int,unsigned long,char *,int);
extern void func_0027F538(int,int,unsigned long,char *,int);
extern void func_002ED578(int,int *,int *,int *);
extern int func_00336D50(void *,int);
extern float func_00283CE0(int);
/* Integer and floating arguments preserve their independent EE ABI bank orders. */
extern void func_00300968(int,float,float,int,float,float);
extern int func_002ED8A0(int);
/* Integer arguments before the float: each EE argument bank keeps its order. */
extern int func_00283D38(int,int,float);
extern int func_00282948(int *);
extern void func_0027EAE8(int,int,int,int,int,int *);
extern int func_0028E588(int,int);
extern void func_0028EA58(int,int,int,int,int,HudRect *);
extern void func_L05_003263F8(int);
extern int func_L05_00324DB8(void);
extern void func_L00_0030CF60(void);
extern void func_L05_0037A5F8(void);

/* A screen coordinate scaled for the display; mode 1 also takes an offset in unscaled pixels. */
static __inline__ int scaled_screen_coord(int mode, float value, float offset)
{
    float scaled = value * D_L05_001B2D84[0] + 0.5f;
    if (mode == 1)
        return (int)(scaled + offset);
    return (int)scaled;
}
int func_L05_0041DF58(void) {
    char text[128];
    int colors[4], colors2[4];
    HudRect r0, r1, r2;
    int h,m,s;
    int drawX, drawY;
    char *label;
    char *state = *(char **)(D_L05_001B13B0 + 0x68);
    int index, color, selected;
    float x,y,ratio,a,b,health;
    float segmentColor, right;
    int i0,i1,i2;
    char *currentBase, *capacityBase;
    HudItem *items;
    { int mode = D_L05_001B1360;
    switch (mode) {
    case 0:
        func_L05_00421B98(0,1,1,1);
        label = func_00288FB8(0x31D1);
        func_00115DA8(text,D_L05_001B1448,label,D_L05_00221D10.objectives);
        drawY = (int)((D_L05_001B143C[0]-8)*D_L05_001B2D84[0]+.5f);
        drawX = D_L05_001B1438-60;
        func_0027F5B8(drawX,drawY,0x80808080UL,text,128);
        label = func_00288FB8(0x31D2);
        func_00115DA8(text,D_L05_001B1448,label,D_L05_00221D10.wave+1);
        drawY = (int)((D_L05_001B1444[0]-8)*D_L05_001B2D84[0]+.5f);
        drawX = D_L05_001B1440-60;
        func_0027F5B8(drawX,drawY,0x80808080UL,text,128);
        break;
    case 1:
        func_L05_00421B98(1,1,0,1);
        label = func_00288FB8(0x31D4);
        func_00115DA8(text,D_L05_001B1448,label,D_L05_00221D10.objectives);
        drawY = (int)((D_L05_001B1444[0]-8)*D_L05_001B2D84[0]+.5f);
        drawX = D_L05_001B1440-60;
        func_0027F5B8(drawX,drawY,0x80808080UL,text,128);
        func_002ED578(*(int *)(state+0x44),&h,&m,&s);
        label = func_00288FB8(0x2F83);
        func_00115DA8(text,D_L05_001B1450,label,h,m,s);
        drawY = (int)((D_L05_001B142C[0]-8)*D_L05_001B2D84[0]+.5f);
        drawX = D_L05_001B1428-80;
        func_0027F5B8(drawX,drawY,0x80808080UL,text,128);
        break;
    case 2:
        func_L05_00421B98(0,1,0,1);
        label = func_00288FB8(0x31D1);
        func_00115DA8(text,D_L05_001B1448,label,D_L05_00221D10.objectives);
        drawY = (int)((D_L05_001B1444[0]-8)*D_L05_001B2D84[0]+.5f);
        drawX = D_L05_001B1440-60;
        func_0027F5B8(drawX,drawY,0x80808080UL,text,128);
        break;
    case 3:
        func_L05_00421B98(1,1,0,1);
        label = func_00288FB8(0x31D7);
        func_00115DA8(text,D_L05_001B1448,label,D_L05_001B13D0);
        drawY = (int)((D_L05_001B1444[0]-8)*D_L05_001B2D84[0]+.5f);
        drawX = D_L05_001B1440-60;
        func_0027F5B8(drawX,drawY,0x80808080UL,text,128);
        func_002ED578(D_L05_001B3550[0],&h,&m,&s);
        label = func_00288FB8(0x2F83);
        func_00115DA8(text,D_L05_001B1450,label,h,m,s);
        drawY = (int)((D_L05_001B142C[0]-8)*D_L05_001B2D84[0]+.5f);
        drawX = D_L05_001B1428-80;
        func_0027F5B8(drawX,drawY,0x80808080UL,text,128);
        break;
    }
    }
    if (D_L05_001A904C) {
        D_L05_001B1390=func_00336D50(D_L05_001A904C+0x8710,128);
        D_L05_001B1394=func_00336D50(D_L05_001A904C+0x8710,129);
        D_L05_001B1398=func_00336D50(D_L05_001A904C+0x8710,130);
        D_L05_001B139C=func_00336D50(D_L05_001A904C+0x8710,131);
        D_L05_001B13A0=func_00336D50(D_L05_001A904C+0x8710,132);
        D_L05_001B13A4=func_00336D50(D_L05_001A904C+0x8710,133);
        x=func_00283CE0(D_001A7340[0])*.5f;
        y=scaled_screen_coord(D_L05_001B2D80[0],200.0f,4.0f);
        func_00300968(D_L05_001B1390,x,y,0x60442D00,1.0f,0.0f);
        func_00300968(D_L05_001B1394,x,y,0x55F0C070,1.0f,0.0f);
        index=func_002ED8A0(6);
        ratio=func_00283CE0(D_L05_002A1800[index].current);
        ratio/=func_00283CE0(D_L05_002A1800[index].maximum);
        switch(index) {
        case 6:
            if(ratio>0.0f) {
                segmentColor=(float)func_00283D38(0x800000FF,0x8000FF00,ratio);
                func_00300968(D_L05_001B139C,x,y,segmentColor,1.0f,0.0f);
            }
            break;
        case 12:
            if(ratio>.5f) {
                ratio-=.5f;
                segmentColor=(float)func_00283D38(0x800000FF,0x8000FF00,ratio+ratio);
                func_00300968(D_L05_001B13A0,x,y,segmentColor,1.0f,0.0f);
                func_00300968(D_L05_001B139C,x,y,0x8000FF00,1.0f,0.0f);
            } else if(ratio>0.0f) {
                segmentColor=(float)func_00283D38(0x800000FF,0x8000FF00,ratio+ratio);
                func_00300968(D_L05_001B139C,x,y,segmentColor,1.0f,0.0f);
            }
            break;
        case 14:
            if(ratio>0.6666667f) {
                ratio-=0.6666667f;
                segmentColor=(float)func_00283D38(0x800000FF,0x8000FF00,ratio*3.0f);
                func_00300968(D_L05_001B13A4,x,y,segmentColor,1.0f,0.0f);
                func_00300968(D_L05_001B13A0,x,y,0x8000FF00,1.0f,0.0f);
                func_00300968(D_L05_001B139C,x,y,0x8000FF00,1.0f,0.0f);
            } else if(ratio>0.33333334f) {
                ratio-=0.33333334f;
                segmentColor=(float)func_00283D38(0x800000FF,0x8000FF00,ratio*3.0f);
                func_00300968(D_L05_001B13A0,x,y,segmentColor,1.0f,0.0f);
                func_00300968(D_L05_001B139C,x,y,0x8000FF00,1.0f,0.0f);
            } else if(ratio>0.0f) {
                segmentColor=(float)func_00283D38(0x800000FF,0x8000FF00,ratio*3.0f);
                func_00300968(D_L05_001B139C,x,y,segmentColor,1.0f,0.0f);
            }
            break;
        }
        health=D_L05_00221D10.health*.01f;
        if(health>.3f) *(int *)(state+0x38)=1;
        else if(func_00282948((int *)(state+0x34))) {
            *(int *)(state+0x34)=5;
            *(int *)(state+0x38)^=1;
        }
        colors[1]=func_00283D38(0x800000FF,0x8000FF00,health);
        colors[0]=0x800000FF;
        right=health*200.0f+156.0f;
        if(*(int *)(state+0x38)) func_0027EAE8(156,14,(int)right,27,1,colors);
        index=func_002ED8A0(7);
        items=D_L05_002A1800;
        currentBase=(char *)&items[0].current;
        capacityBase=(char *)&items[0].capacity;
        ratio=func_00283CE0(*(int *)(currentBase + index*sizeof(HudItem)));
        health=ratio/func_00283CE0(*(int *)(capacityBase + index*sizeof(HudItem)));
        color=func_00283D38(0x800000FF,0x8000FF00,health);
        a=func_00283CE0(450);
        b=func_00283CE0(386);
        b-=func_00283CE0(450);
        colors2[0]=0x800000FF; colors2[1]=color;
        b*=health;
        right=a+b;
        if(health>0.0f) func_0027EAE8(450,8,(int)right,19,1,colors2);
        r0=D_L05_001B1468; r1=D_L05_001B1478; r2=D_L05_001B1488;
        func_0028EA58(func_0028E588(0xEA97,1),21,7,30,30,&r1);
        func_0028EA58(func_0028E588(0xEA97,0),21,7,30,30,&r0);
        func_0028EA58(func_0028E588(0xEA97,items[func_002ED8A0(D_L05_001B13DC)].icon),21,7,30,30,&r2);
        func_0028EA58(func_0028E588(0xEA97,1),462,9,30,30,&r1);
        func_0028EA58(func_0028E588(0xEA97,items[func_002ED8A0(7)].icon),462,9,30,30,&r2);
        func_00115DA8(text,D_L05_001B1498,*(int *)(currentBase + sizeof(HudItem)*func_002ED8A0(D_L05_001B13DC)),*(int *)(capacityBase + sizeof(HudItem)*func_002ED8A0(D_L05_001B13DC)));
        func_0027F538(67,5,0x80808080UL,text,128);
        func_L05_003263F8(2);
        selected=func_L05_00324DB8();
        if(selected>=0) {
            items[func_002ED8A0(D_L05_001B13DC)].active=0;
            D_L05_001B13DC=selected;
            items[func_002ED8A0(selected)].active=1;
        }
        func_00300968(D_L05_001B1398,x,y,0x80F0F0F0,1.0f,0.0f);
        func_L00_0030CF60();
        i0=func_00336D50(D_L05_001A904C+0x8710,186);
        i1=func_00336D50(D_L05_001A904C+0x8710,187);
        i2=func_00336D50(D_L05_001A904C+0x8710,188);
        func_00300968(i0,D_L05_001AC4E0[0]+4.0f,(float)(int)((D_L05_001AC4E4[0]+4.0f)*D_L05_001B2D84[0]+.5f),0x60442D00,.8f,0.0f);
        func_00300968(i1,D_L05_001AC4E0[0]+4.0f,(float)(int)((D_L05_001AC4E4[0]+4.0f)*D_L05_001B2D84[0]+.5f),0x60241700,.8f,0.0f);
        func_00300968(i2,D_L05_001AC4E0[0]+4.0f,(float)(int)((D_L05_001AC4E4[0]+4.0f)*D_L05_001B2D84[0]+.5f),0x55F0C070,.8f,0.0f);
        func_L05_0037A5F8();
    }
    return 1;
}
