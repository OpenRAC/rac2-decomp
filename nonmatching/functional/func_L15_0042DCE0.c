/* functional: high. Same stage state machine as retail on the captured calls; the states the captures never reach (cases past the ones exercised) are unproven. */
/* GPT-6.1 Sol high tier, USA v1.01, -O2 -G8 -ffunction-sections.
 * Best check.py: 1232/1232 bytes, 0 of 1 places; first mismatch +0x314.
 * Four instructions differ at 0042DFF4, 0042DFF8, 0042E00C and 0042E010:
 * the branch targets the mode load rather than its high-half materialization,
 * its delay slot preloads the next GP flag instead of forming that high half,
 * and the mode address uses v1 rather than v0. All other instructions match.
 * The opacity and flags fields are declared volatile because retail writes
 * each twice in case 0. State itself needs no volatile qualification.
 * Local case-1 enabled=1 recovers s0 reuse; channel snapshots must be declared
 * a,b,c,d (the scheduler loads d first). Both func_L00_002C42E0 and
 * func_00288E18 return int, as their current matched definitions demonstrate.
 * Scalar, single-field struct and explicit local mode views gave the same
 * remaining bytes: stopped on that tie. All required declarations are below.
 */
#include "common.h"
#define F(t,p,o) (*(t *)((char *)(p)+(o)))
typedef struct State { int initial; char pad[0x10]; int count; char pad18[0xc]; int active; char pad28[4]; int timer; float scale; char pad34[0x18]; void *hook1,*hook2,*hook3; char pad58[0x20]; void *object; } State;
extern State D_L15_00221E10;
typedef struct Channels { char pad[0x6b]; unsigned char a,b,c,d; } Channels;
extern Channels D_001395B8;
typedef struct Player { char pad[0x2290]; char *moby; } Player;
extern Player D_00189E20;
extern char D_L15_0029FD80[];
extern char D_L15_0042FDD8[],D_L15_0042FED0[],D_L15_0042FFB8[],D_L15_0042E1B0[];
extern int D_L15_001B369C,D_L15_001B36A0,D_L15_001B1524,D_L15_001B1528,D_L15_001B152C;
extern char *D_L15_001AA720,*D_L15_001AA728;
extern float D_L15_001B2E84;
extern char *D_L15_001B261C;
extern int D_L15_001A8F00[1],D_0013A184,D_L15_001A904C;
extern int func_L05_0037AA88(int);
extern void func_L05_00379F18(int),func_L05_00379F28(int),func_L05_00379B60(void),func_L05_0030C930(int,int),func_L00_003294F0(void *,int);
extern int func_L00_002C42E0(int,int),func_00288E18(int,int);
extern void func_L05_00379F48(int),func_L05_00445A98(void);
extern int func_L05_0041ED18(void),func_L10_0037F510(void),func_00282948(void *),func_L05_00442860(void);
extern void func_L15_004307E0(void *),func_L15_00430B30(void *),func_L15_00430C80(void *),func_L15_00430DF0(void *),func_0029B758(int,void *);
extern int D_L15_001B1530 __attribute__((sda));
extern char * D_L15_001B1580 __attribute__((sda));
extern int D_L15_001B15C4 __attribute__((sda));
extern int D_L15_001B15B0 __attribute__((sda));
extern int D_L15_001B1534 __attribute__((sda));
extern int D_L15_001B158C __attribute__((sda));
extern int D_L15_001B1560 __attribute__((sda));
extern int D_L15_001B1564 __attribute__((sda));
extern int D_L15_001B1568 __attribute__((sda));
extern int D_L15_001B1578 __attribute__((sda));
extern int D_L15_001B157C __attribute__((sda));
extern int D_L15_001B15AC __attribute__((sda));
extern int D_L15_001B15B8 __attribute__((sda));
extern int D_L15_001B1520 __attribute__((sda));
extern int D_L15_001B15D0 __attribute__((sda));
extern int D_L15_001B15A8 __attribute__((sda));
extern int D_L15_001B15B4 __attribute__((sda));
extern int D_L15_001B2148 __attribute__((sda));
extern int D_L15_001B15CC __attribute__((sda));
typedef struct StagePrivate { int initial; char pad04[0x20]; int index; char pad28[0xc]; int active; char pad38[0x18]; int time; int delay; char pad58[0xc]; int time2; int time3; int time4; } StagePrivate;
typedef struct StageMoby { char pad[0x20]; unsigned char state; char pad21[0xf]; volatile unsigned char opacity; char pad31; volatile unsigned short flags; char pad34[0x34]; StagePrivate *private; } StageMoby;

void func_L15_0042DCE0(StageMoby *p)
{
    StagePrivate *s=p->private;
    switch(p->state) {
    case 0: {
        State *r=&D_L15_00221E10;
        p->flags=511;
        p->opacity=255;
        p->state=1;
        r->initial=s->initial;
        r->scale=8;
        D_L15_001B1530=-2; r->active=1;
        D_L15_001B1580=p; D_L15_001B15C4=1; D_L15_001B15B0=0; D_L15_001B1534=0; D_L15_001B158C=0;
        D_L15_001B1560=0;D_L15_001B1564=0;D_L15_001B1568=0;D_L15_001B1578=0;D_L15_001B157C=0;
        p->flags=511;
        p->opacity=255;
        p->state=1;
        s->active=0;D_L15_001B15AC=0;
        s->time=5400;s->delay=120;
        s->time2=240;s->time4=180;s->time3=360;
        D_L15_001B369C=540;D_L15_001B36A0=360;
        r->hook1=D_L15_0042FDD8;
        r->hook2=D_L15_0042FED0;
        D_L15_001B15B8=0;
        r->hook3=D_L15_0042FFB8;
        r->object=p;
        func_L05_00379F18(1);func_L05_00379F28(0);
        while(!F(int,D_L15_0029FD80+func_L05_0037AA88(D_L15_001B15B0)*40,0) ||
              !F(short,D_L15_0029FD80+func_L05_0037AA88(D_L15_001B15B0)*40,0x1e)) D_L15_001B15B0++;
        { int a=D_001395B8.a, b=D_001395B8.b, c=D_001395B8.c, d=D_001395B8.d;
        D_L15_001AA720=D_L15_0042FDD8;D_L15_001AA728=D_L15_0042FED0;
        D_L15_001B1524=b;
        D_L15_001B1528=c;
        D_L15_001B152C=d;
        D_L15_001B1520=a; }
        if(!D_L15_001B1520) D_L15_001B15D0=1;
        else D_L15_001B15D0=0;
        if(D_00189E20.moby) F(unsigned short,D_00189E20.moby,0x34)|=0x41;
        }
        /* fall through */
    case 1: {
        int enabled=1;
        func_L05_00379B60();func_L05_0030C930((int)(D_L15_001B2E84*-230.0f+.5f),2);
        if(!D_L15_001B15A8) {
            func_L00_003294F0(D_L15_001B261C+(s->index<<8),1);
            D_L15_001B15A8=enabled;D_L15_001B15AC=0;
        }
        if(D_L15_001B15AC++<5) break;
        if(D_L15_001A8F00[0]==2) break;
        func_L00_002C42E0(49,0);
        if(D_L15_001B15C4) {
            func_L05_00379F48(1);
            D_L15_001B1530=func_L05_0041ED18();
            if(D_L15_001B1530!=-2) func_L05_00445A98();
            break;
        }
        if(!D_L15_001B15B4) { func_00288E18(0xa17,0x6e);D_L15_001B15B4=enabled; }
        if((D_0013A184==enabled || D_0013A184==5 || D_0013A184==10) && !func_L10_0037F510() && !D_L15_001B15B8) {
            func_00288E18(0xa18,0x6f);D_L15_001B15B8=1;
        }
        if(func_00282948(&s->time3)) *(int *)((char *)&D_L15_00221E10+0x2c)=0;
        else *(int *)((char *)&D_L15_00221E10+0x2c)=1;
        func_L05_00379F48(0);
        if(D_L15_001B1530!=-2 && D_L15_001B2148>=3) {
            switch(D_L15_001B1530) {
            case 0:func_L15_004307E0(p);break;
            case 1:func_L15_00430B30(p);break;
            case 2:func_L15_00430C80(p);break;
            case 3:func_L15_00430DF0(p);break;
            }
        }
        if(D_L15_001A904C && !D_L15_001B1578 && !D_L15_001B15CC) {
            func_0029B758(0,D_L15_0042E1B0);D_L15_001B157C=0;D_L15_001B1578=1;
        }
        break;
        }
    case 2: break;
    case 3:
        if(!func_L05_00442860()) {
            State *r=&D_L15_00221E10;
            r->timer=0;r->count++;
            p->state=1;
        }
        break;
    }
}
