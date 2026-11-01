/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/*
 * Opus 5.5 xhigh (opus-1), USA v1.01, -O2 -G8 -ffunction-sections, own unit L15_0042E1B0-g8.c.
 * Best check.py: 3124 bytes, expected 3140; 0 of 1 places match. 725 of 785 retail rows align
 * once relocations are ignored. PAL, v2.00 and the linked build were not attempted.
 *
 * NOT LANDABLE AS WRITTEN: HudText tests a placeholder ((int)private) with arms that compile
 * alike and HudPanel uses do { } while (0). Both are forbidden; they are here only to measure.
 *
 * Recovered, keep these:
 * - if (D_L15_001A904C) closes before func_L00_0030CF60; the final three panels are unconditional.
 * - MACRO_ADDR on D_L15_001A904C gives lui+lw in ordinary flow and the $gp form in delay slots.
 * - int kind=1 reassigned by func_002ED8A0(6) gives retail's s2 and beq $v1,$s2 in the opening.
 * - The prototype func_00300968(char *,float,float,int,float,float) gives retail's argument order
 *   (a0,f12,f13,a1,f14,f15); it keeps each bank's order, so the ABI view is unchanged.
 * - Separate locals weapon, ratio, base, alpha and selection give retail's f20-f25, s0 and s3;
 *   reusing private for the second panel gives s3 (Sol's finding, confirmed).
 * - half in case 3 is set before the first text (f20, hoisted over calls by sched1). four and
 *   round before the panels do the same (f20, f23).
 * - The panel coordinates are at 0x1AC560, not the 0x1AB550 of the older draft.
 *
 * Main blocker: retail has a real boundary after every text y conversion and panel conversion.
 * Evidence: a2, a3 and a0 are all set after mfc1 $a1; 0.8f and 0.0f are not hoisted over calls;
 * x stays untied from a0 and f12 (a global pseudo); and only with a boundary does reorg steal
 * lw $a0 into the beqz delay slot at +0x60. Measured forms:
 * - Barrier only (do/while): the opening matches, but x ties to a0, so lw $a0 replaces lw $v0.
 * - x,y inside both arms, join before the call (HudText here): tails merge across cases, only
 *   v0/v1 are swapped, and a0=sp lands in the sprintf jal slot, saving 2 rows.
 * - x,y before the test, call in both arms: the chain and sprintf order are exact, but arms in
 *   front of a break are jump-threaded to the same label, so they do not merge (3340 bytes).
 * - Arms of one set, or of constants only, fold before sched and leave no boundary.
 * No real tested value was found: nothing is loaded for the test, so it must already be in a
 * live register. Next: find the real helper, since retail's y chain sits in the sprintf block.
 *
 * Other differences: +0x374 (200.0f/0.5f in f3/f2, swapped here, with a different order);
 * +0x3E0 to +0x428 (mtc1 $zero,$f21 and lui $s1 slot order); T3's x is addiu $v0,$v0 then
 * a0=v0, while T1's is addiu $a0,$v0; panels want lwc1 $f1 for px, S in f2 and mfc1 $v1.
 * Callee and data names were not verified by check.py beyond the first differing instruction.
 */
#include "common.h"

/* Gorn stage HUD: objective text, ship status bars and selection icons. */
#define FIELD(t,p,o) (*(t *)((char *)(p) + (o)))
typedef struct HudColors { u32 a,b,c,d; } HudColors;
typedef struct HudRecord { int active,words04[2],maximum,capacity,value; short words18[2],icon,enabled; int words20[2]; } HudRecord;
extern char *D_L15_001B1580 __attribute__((sda));
extern int D_L15_001B1530 __attribute__((sda));
extern int D_L15_001B15B0 __attribute__((sda));
extern int D_L15_001B15A4 __attribute__((sda));
extern int D_L15_001B1620 __attribute__((sda));
extern int D_L15_001B1638 __attribute__((sda));
extern int D_L15_001B1560 __attribute__((sda)),D_L15_001B1564 __attribute__((sda));
extern int D_L15_001B1568 __attribute__((sda)),D_L15_001B156C __attribute__((sda));
extern int D_L15_001B1570 __attribute__((sda)),D_L15_001B1574 __attribute__((sda));
extern int D_L15_001B163C[1],D_L15_001B1624[1],D_L15_001B2E80[1],D_L15_001B3698[1];
extern float D_L15_001B2E84[1];
extern int D_001A7340;
extern char *D_L15_001A904C MACRO_ADDR;
extern float D_L15_001AC560[2];
extern char D_L15_001B1640[],D_L15_001B1648[],D_L15_001B1690[];
extern HudColors D_L15_001B1660,D_L15_001B1670,D_L15_001B1680;
extern char D_L15_00221E10[];
extern HudRecord D_L15_0029FD80[];
extern void func_L15_00431590(int,int,int,int);
extern char *func_00288FB8(int);
extern char *func_L05_00379ED0(int);
extern int func_L10_0037D200(char *),func_L15_00381CF0(char *);
extern int func_00115DA8(char *,const char *,...);
extern void func_0027F5B8(int,int,u64,char *,int);
extern void func_0027F538(int,int,u64,char *,int);
extern void func_002ED578(int,int *,int *,int *);
extern int func_00336D50(void *,int);
extern float func_00283CE0(int);
extern void func_00300968(char *,float,float,int,float,float);
extern int func_002ED8A0(int);
extern int func_00283D38(int,int,float);
extern int func_00282948(int *);
extern void func_0027EAE8(int,int,int,int,int,u32 *);
extern int func_0028E588(int,int);
extern void func_0028EA58(int,int,int,int,int,HudColors *);
extern void func_L05_003263F8(int);
extern int func_L05_00324DB8(void);
extern void func_L00_0030CF60(void),func_L05_0037A5F8(void);

static __inline__ int HudY(int y,int mode,int adjust,float r)
{
    if(mode!=0) return (int)(y*D_L15_001B2E84[0]+r)+adjust;
    return (int)(y*D_L15_001B2E84[0]+r);
}

#define HudText(X,Y,TEXT,R) { int sx,sy; \
    if((int)private!=0) { sx=(X); sy=(int)((Y)*D_L15_001B2E84[0]+R)+zero; } \
    else { sx=(X); sy=(int)((Y)*D_L15_001B2E84[0]+R); } \
    func_0027F5B8(sx,sy,0x80808080,TEXT,128); }

#define HudPanel(P,C) { float px,py; \
    px=D_L15_001AC560[0]+four; py=(int)((D_L15_001AC560[1]+four)*D_L15_001B2E84[0]+round); \
    do { } while (0); \
    func_00300968(P,px,py,C,0.8f,0); }

int func_L15_0042E1B0(void)
{
    char text[128];
    u32 colors[4],colors2[4];
    HudColors icon0,icon1,icon2;
    int hours,minutes,seconds;
    char *private=FIELD(char *,D_L15_001B1580,0x68);
    int kind=1;
    int selection;
    const int zero=0;
    char *label;
    float half;
    float x,y,ratio,base,alpha,four,round;
    int frame0,frame1,frame2;

    switch(D_L15_001B1530) {
    case 0:
        func_L15_00431590(0,1,0,1);
        label=func_00288FB8(0x31D1);
        func_00115DA8(text,D_L15_001B1640,label,func_L10_0037D200(func_L05_00379ED0(0x1211)));
        HudText(D_L15_001B1638-60,D_L15_001B163C[0]-8,text,0.5f);
        break;
    case 1:
        func_L15_00431590(0,1,0,1);
        label=func_00288FB8(0x31D1);
        func_00115DA8(text,D_L15_001B1640,label,FIELD(int,D_L15_00221E10,0x10));
        HudText(D_L15_001B1638-60,D_L15_001B163C[0]-8,text,0.5f);
        break;
    case 2:
        func_L15_00431590(0,1,0,1);
        label=func_00288FB8(0x31D1);
        func_00115DA8(text,D_L15_001B1640,label,func_L15_00381CF0(func_L05_00379ED0(0x1211)));
        HudText(D_L15_001B1638-60,D_L15_001B163C[0]-8,text,0.5f);
        break;
    case 3:
        func_L15_00431590(1,1,0,1);
        half=0.5f;
        label=func_00288FB8(0x31D7);
        func_00115DA8(text,D_L15_001B1640,label,D_L15_001B15A4);
        HudText(D_L15_001B1638-60,D_L15_001B163C[0]-8,text,half);
        func_002ED578(D_L15_001B3698[0],&hours,&minutes,&seconds);
        label=func_00288FB8(0x2F83);
        func_00115DA8(text,D_L15_001B1648,label,hours,minutes,seconds);
        HudText(D_L15_001B1620-80,D_L15_001B1624[0]-8,text,half);
        break;
    }
    if(D_L15_001A904C) {
        D_L15_001B1560=func_00336D50(D_L15_001A904C+0x8710,128);
        D_L15_001B1564=func_00336D50(D_L15_001A904C+0x8710,129);
        D_L15_001B1568=func_00336D50(D_L15_001A904C+0x8710,130);
        D_L15_001B156C=func_00336D50(D_L15_001A904C+0x8710,131);
        D_L15_001B1570=func_00336D50(D_L15_001A904C+0x8710,132);
        D_L15_001B1574=func_00336D50(D_L15_001A904C+0x8710,133);
        x=func_00283CE0(D_001A7340)*0.5f;
        base=D_L15_001B2E84[0]*200.0f+0.5f;
        if(D_L15_001B2E80[0]==1) y=(int)(base+4.0f);
        else y=(int)base;
        func_00300968((char *)D_L15_001B1560,x,y,0x60442D00,1,0);
        func_00300968((char *)D_L15_001B1564,x,y,0x55F0C070,1,0);
        kind=func_002ED8A0(6);
        { float weapon;
        weapon=func_00283CE0(D_L15_0029FD80[kind].value)/func_00283CE0(D_L15_0029FD80[kind].maximum);
        switch(kind) {
        case 6:
            if(weapon>0) func_00300968((char *)D_L15_001B156C,x,y,(int)(float)func_00283D38(0x800000FF,0x8000FF00,weapon),1,0);
            break;
        case 12:
            if(weapon>0.5f) {
                weapon-=0.5f;
                func_00300968((char *)D_L15_001B1570,x,y,(int)(float)func_00283D38(0x800000FF,0x8000FF00,weapon*2),1,0);
                func_00300968((char *)D_L15_001B156C,x,y,0x8000FF00,1,0);
            } else if(weapon>0) func_00300968((char *)D_L15_001B156C,x,y,(int)(float)func_00283D38(0x800000FF,0x8000FF00,weapon*2),1,0);
            break;
        case 14:
            if(weapon>0.6666667f) {
                weapon-=0.6666667f;
                func_00300968((char *)D_L15_001B1574,x,y,(int)(float)func_00283D38(0x800000FF,0x8000FF00,weapon*3),1,0);
                func_00300968((char *)D_L15_001B1570,x,y,0x8000FF00,1,0);
                func_00300968((char *)D_L15_001B156C,x,y,0x8000FF00,1,0);
            } else if(weapon>0.33333334f) {
                weapon-=0.33333334f;
                func_00300968((char *)D_L15_001B1570,x,y,(int)(float)func_00283D38(0x800000FF,0x8000FF00,weapon*3),1,0);
                func_00300968((char *)D_L15_001B156C,x,y,0x8000FF00,1,0);
            } else if(weapon>0) func_00300968((char *)D_L15_001B156C,x,y,(int)(float)func_00283D38(0x800000FF,0x8000FF00,weapon*3),1,0);
            break;
        }
        }
        ratio=FIELD(int,D_L15_00221E10,0x28)*0.01f;
        if(ratio>0.3f) FIELD(int,private,0x38)=1;
        else if(func_00282948((int *)(private+0x34))) { FIELD(int,private,0x34)=5; FIELD(int,private,0x38)^=1; }
        colors[1]=func_00283D38(0x800000FF,0x8000FF00,ratio);
        colors[0]=0x800000FF;
        alpha=ratio*200+156;
        if(FIELD(int,private,0x38)) func_0027EAE8(156,14,(int)alpha,27,1,colors);
        kind=func_002ED8A0(7);
        ratio=func_00283CE0(D_L15_0029FD80[kind].value)/func_00283CE0(D_L15_0029FD80[kind].capacity);
        selection=func_00283D38(0x800000FF,0x8000FF00,ratio);
        { float a=func_00283CE0(450);
        float b=func_00283CE0(386);
        float c=func_00283CE0(450);
        alpha=a+(b-c)*ratio; }
        colors2[0]=0x800000FF;
        colors2[1]=selection;
        if(ratio>0) func_0027EAE8(450,8,(int)alpha,19,1,colors2);
        icon0=D_L15_001B1660; icon1=D_L15_001B1670; icon2=D_L15_001B1680;
        func_0028EA58(func_0028E588(0xEA97,1),21,7,30,30,&icon1);
        func_0028EA58(func_0028E588(0xEA97,0),21,7,30,30,&icon0);
        func_0028EA58(func_0028E588(0xEA97,D_L15_0029FD80[func_002ED8A0(D_L15_001B15B0)].icon),21,7,30,30,&icon2);
        func_0028EA58(func_0028E588(0xEA97,1),462,9,30,30,&icon1);
        func_0028EA58(func_0028E588(0xEA97,D_L15_0029FD80[func_002ED8A0(7)].icon),462,9,30,30,&icon2);
        func_00115DA8(text,D_L15_001B1690,D_L15_0029FD80[func_002ED8A0(D_L15_001B15B0)].value,D_L15_0029FD80[func_002ED8A0(D_L15_001B15B0)].capacity);
        func_0027F538(67,5,0x80808080,text,128);
        func_L05_003263F8(2);
        selection=func_L05_00324DB8();
        if(selection>=0) {
            D_L15_0029FD80[func_002ED8A0(D_L15_001B15B0)].active=0;
            D_L15_001B15B0=selection;
            D_L15_0029FD80[func_002ED8A0(selection)].active=1;
        }
        func_00300968((char *)D_L15_001B1568,x,y,0x80F0F0F0,1,0);
    }
    func_L00_0030CF60();
    four=4.0f;
    round=0.5f;
    frame0=func_00336D50(D_L15_001A904C+0x8710,186);
    private=(char *)func_00336D50(D_L15_001A904C+0x8710,187);
    frame2=func_00336D50(D_L15_001A904C+0x8710,188);
    HudPanel((char *)frame0,0x60442D00);
    HudPanel(private,0x60241700);
    HudPanel((char *)frame2,0x55F0C070);
    func_L05_0037A5F8();
    return 1;
}
