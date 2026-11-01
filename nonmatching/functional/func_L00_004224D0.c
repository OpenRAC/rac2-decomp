/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* func_L00_004224D0 (2,916 bytes, 27 level places; USA v1.01 only, in neither the PAL nor the
 * us2 catalogue). Tier: opus-1, Claude Opus 5.5 (xhigh), task v1867, not matched.
 *
 * Best check: 2916/2916 bytes; 0 of 27 places match; first mismatch +0x484. Twelve instruction rows
 * differ once relocated fields are set aside, all in +0x484..+0x4BC. check.py stops at the first
 * mismatch, so relocation binding after +0x484 is unqualified; the five nonzero local immediates
 * that differ later are symbol+addend low parts and agree by hand.
 *
 * To check it: save as src/levels/shared/L00_004224D0-g8.c, take the INCLUDE_ASM out of
 * L00_004224D0.c and append to config/cflags.txt:
 * src/levels/shared/L00_004224D0-g8.c<TAB>-O2 -G8 -ffunction-sections -frac2-qcopy
 * -frac2-qcopy-barrier -frac2-hazard-labels
 *
 * What still differs (the setup of the first func_00282D30 after func_L00_00423038):
 *   retail: lw v1,0x10(sp); a0=sp; lwc1 f12; a1=..; lw s3,0x70(v1); neg.s; daddu s1,s3;
 *           addiu s3,0x1F0; jal; addiu s0,s1,0x20
 *   here:   lwc1 f12; a0=sp; lw v1,0x10(sp); a1=..; neg.s; jal; lw s3,0x70(v1); daddu s1,s3; ...
 * All of it follows from one sched2 choice at the first clock after the call. The priorities
 * (sched2 dump, -fsched-verbose-5) are 35 for the height load and 33 for the reload of obj, and
 * retail needs the reload first. Worked by hand, issuing it first gives retail's order: neg.s then
 * waits three clocks for the call, and the pointer chain fits in front of the jal.
 *
 * Fixed here against the earlier drafts, all without volatile:
 *  - func_L00_00424C00 follows both ifs (this was both branch displacements);
 *  - the timer-reset stores are written 0x16, 0x12, 0x14: the last store in the source holds the
 *    base register's death, so sched1 issues it first (order a,b,c comes out c,a,b);
 *  - the parameter stores are written distance, then height, flags, f18, f10, f0c. This lengthens
 *    the follow pointer's life, which also flips local-alloc to retail's s3/s4;
 *  - aim (q->vector50) is initialized at the top of the block.
 *
 * Tried without closing the gap:
 *  - float h = -height or float h = height before the reload, a local for the direction or for
 *    the output argument: the same 12 rows (tie). params before the advance is worse (23 rows);
 *  - leaving out -frac2-qcopy-barrier (before aim moved up): the same rows in this region;
 *  - an empty do { } while (0) after the call (forbidden form, probe only): 30 rows. It adds a
 *    barrier, but the height load still goes first and the order at +0x458..+0x468 breaks;
 *  - a test right after the call (identical call arms, probe only): 430 rows. A block end there
 *    should give the needed priority (worked by hand from memory of GCC 2.95's
 *    add_branch_dependences, whose source is not in this checkout: unreferenced insns must precede
 *    a trailing call). But the pointers then cross blocks and leave local-alloc, q loses $fp and
 *    obj gains a register, so retail seems to have no real test there. Arms folded early
 *    (params ? local : &local[0], an inline Pick helper) left no boundary.
 * Next idea: something that makes the chain lw/daddu/addiu precede the call without a block end;
 * the reload needs priority above 35, so the chain must reach the call or one of its arguments.
 *
 * All declarations are below.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define I(p,n) (*(int *)((char *)(p)+(n)))
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define H(p,n) (*(short *)((char *)(p)+(n)))
#define B(p,n) (*(unsigned char *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
typedef struct CameraParams {
    short h0;
    short flags;
    float distance, height, f0c, f10;
    float f14;
    float f18;
} CameraParams;
typedef struct CameraOffsets {
    float position[4];
    char pad10[0x40-0x10];
    float vector40[4], vector50[4], vector60[4];
    char pad70[0x90-0x70];
    float vector90[4];
    char pada0[0xb0-0xa0];
    float distance;
    char padb4[0xe4-0xb4];
    float weight;
    char pade8[8];
    float fF0;
    int ticks;
    char padf8[8];
} CameraOffsets;
typedef struct FollowParameters {
    float vector[4], copy[4];
    char pad20[0xc];
    float distance, height;
    char pad34[0x90-0x34];
} FollowParameters;
typedef struct CameraRates {
    char pad0[0x30];
    int i30;
    char pad34[8];
    float f3c;
    int i40;
    float f44;
    char pad48[6];
    short h4e;
} CameraRates;
typedef struct CameraVars {
    float position[4];
    short h10, timer12, timer14, timer16;
    char pad18[8];
    CameraParams params;
    char pad3c[0x60-0x3c];
    CameraOffsets offsets;
    FollowParameters follow;
    CameraRates rates;
    int state[5];
} CameraVars;
typedef struct CameraMoby {
    char pad0[0x30];
    float position[4];
    char pad40[0x70-0x40];
    CameraVars *vars;
} CameraMoby;
typedef struct HeroCameraSource {
    char pad0[0x80];
    float position[4];
    char pad90[0x21a-0x90];
    short h21a;
    char pad21c[0x2c0-0x21c];
    float direction[4];
    char pad2d0[0x340-0x2d0];
    int i340;
    char pad344[0x574-0x344];
    float f574;
    char pad578[0x1450-0x578];
    char *p1450;
    short h1454;
    char pad1456[0x2290-0x1456];
    char *p2290;
    int state;
    int i2298;
    int moveState;
    char pad22a0[0x22b4-0x22a0];
    unsigned char b22b4;
    char pad22b5[0x24a0-0x22b5];
    int i24a0;
} HeroCameraSource;
extern HeroCameraSource D_00189E20;
typedef struct CameraInput {
    char pad0[0x100];
    float stickX, stickY;
    char pad108[0x1a0-0x108];
    int buttons;
} CameraInput;
extern CameraInput D_00138180;
extern int D_001A79F0 MACRO_ADDR;
typedef struct CameraHooks {
    char pad0[0x10];
    void (*update)(void);
} CameraHooks;
typedef struct FollowCameraGlobal {
    char pad0[0x284];
    char *target;
    int targetTicks;
    char pad28c[0x3a0-0x28c];
    CameraHooks hooks;
    char pad3b4[0x404-0x3b4];
    int state;
} FollowCameraGlobal;
extern FollowCameraGlobal D_L00_001B8C80;
typedef struct CameraInputSamples {
    char pad0[0xac];
    float samples[5];
} CameraInputSamples;
extern CameraInputSamples D_L00_001B8E20;
extern int D_L00_001A8FF0;
extern char *D_L00_001C3280[];
extern float D_L00_001B14A4 __attribute__((sda)), D_L00_001B1594 __attribute__((sda)), D_L00_001B1598 __attribute__((sda));
extern float D_L00_001B159C __attribute__((sda)), D_L00_001B15A0 __attribute__((sda)), D_L00_001B15A4 __attribute__((sda));
extern float D_L00_001B1578 __attribute__((sda)), D_L00_001B157C __attribute__((sda));
extern int D_L00_001B1590 __attribute__((sda));
extern float D_L00_001A8900;
extern int func_L00_002D71A0(void);
extern int func_00282948(int *);
extern int func_00282978(short *);
extern float func_00282C48(float), func_00283180(float), func_00283198(float);
extern float func_00283B98(float,float), func_00283C80(float,float), func_00283CE0(int);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *), func_00282CF0(void *,void *,void *);
extern int func_00277F48(void *,int,int,int,float);
extern char *func_002AB1F0(char *);
extern void func_L00_00423038(int);
extern void func_L00_00424BB8(float,float),func_L00_00424B20(float);
extern void func_L00_00424C60(void),func_L00_00424C28(void),func_L00_00424C00(void);
extern void func_L00_00424F00(char *,float,float),func_L00_00424F58(char *,float,float);
extern void func_L00_00424A50(float,float),func_L00_00424A08(int,float,float);
extern void func_L00_00424A88(int,float,float),func_L00_00424B70(float,float);
extern void func_L00_00424B48(int);

void func_L00_004224D0(CameraMoby *obj)
{
    float local[4];
    CameraVars *p=obj->vars;
    int *state=p->state;
    CameraRates *r=&p->rates;
    CameraOffsets *q=&p->offsets;
    int special=0, mode=func_L00_002D71A0(), i, count;
    float a,b;
    if (D_00189E20.state==124 || D_00189E20.state==120) r->h4e=1;
    if (!D_00189E20.i340 || q->ticks) {
        float a=q->fF0;
        if (a>2.0f) a=2.0f;
        q->weight=(D_L00_001B14A4-0.002f)*(a*0.5f)+0.002f;
        if (D_00189E20.i340) func_00282948(&q->ticks);
        else q->ticks=15;
    }
    if (D_00189E20.moveState==30) {
        obj->vars->offsets.distance=0.75f;
        func_L00_00424BB8(0.04f,0.2f);
    }
    if (D_001A79F0==1 && D_00189E20.state==48 && D_00189E20.position[2]>75.0f && D_00189E20.position[2]<105.0f) {
        func_L00_00424B20(0.8726646900177002f);
        func_L00_00424C60();
    }
    if (D_00189E20.i24a0==13 && D_00189E20.h21a) {
        a=func_00283B98(D_00189E20.f574,3.1415929794311523f);
        local[0]=func_00283180(a);
        local[1]=func_00283198(a);
        local[2]=0;
        func_L00_00424F00((char *)local,0.20943953f,local[2]);
        func_L00_00424C28();
    }
    if (D_00189E20.moveState==17) {
        obj->vars->offsets.distance=0.25f;
        func_L00_00424A50(0.5f,0.003f);
    }
    if (D_00189E20.moveState==5 && !D_L00_001A8FF0) {
        CameraOffsets *specialVars=&obj->vars->offsets; special=1;
        if (D_00189E20.b22b4==1 && mode==-1) {
            specialVars->distance=0.25f;
            func_L00_00424A50(1.5f,0.003f);
        } else {
            specialVars->distance=0.25f;
            func_L00_00424A50(2.5f,0.003f);
        }
    }
    if (D_00189E20.moveState==16) obj->vars->offsets.distance=0.25f;
    if (D_00189E20.b22b4==1) {
        if (!I(state,0) && mode==-1) {
            CameraOffsets *followVars=&obj->vars->offsets;
            func_L00_00424A08(1,3.0f,0.003f);
            if (!special) { followVars->distance=1.0f;func_L00_00424A50(1.0f,0.003f); }
        }
        obj->vars->rates.f3c=0.6f;
    }
    if (D_00189E20.b22b4==2) {
        if (I(state,0x10)<2) {
            func_L00_00424A88(0,D_L00_001B1594,0.005f);
            func_L00_00424A08(1,D_L00_001B1598,0.003f);
            func_L00_00424A50(D_L00_001B159C,0.003f);
            if (D_L00_001B8C80.state<2) {
                CameraVars *base=obj->vars;
                FollowParameters *follow=&base->follow;
                float *pos=obj->position,*dir=D_00189E20.position,*aim=q->vector50;
                follow->distance=D_L00_001B1598;
                follow->height=D_L00_001B159C;
                q->distance=D_L00_001B1594;
                func_L00_00423038(1);
                {
                CameraRates *end=(CameraRates *)obj->vars;
                CameraVars *reloaded=(CameraVars *)end;
                CameraParams *params;
                end=(CameraRates *)((char *)end+0x1f0);
                params=&reloaded->params;
                func_00282D30(local,D_00189E20.direction,-follow->height);
                func_00282CC0(aim,dir,local);
                func_00282CF0(follow,pos,aim);
                qcopy(base->follow.copy,follow->vector);
                func_00282D30(local,D_00189E20.direction,-q->distance);
                func_00282CC0(q->vector40,dir,local);
                qcopy(q->vector90,q->vector40);
                qcopy(q->position,dir);
                qcopy(q->vector60,q->position);
                qcopy(reloaded,pos);
                qcopy((char *)reloaded+0x210,pos);
                end->i30=0;params->f14=0.0f;
                params->distance=q->distance;
                {
                    float zero=params->f14;
                    params->height=follow->height;
                    params->flags=0;
                    params->f18=zero;
                    params->f10=zero;
                    params->f0c=zero;
                }
                }
            }
        }
        func_L00_00424C00();
        {
            CameraRates *rates=&obj->vars->rates;
            rates->f3c=D_L00_001B15A4;
            rates->f44=D_L00_001B15A0;
        }
    }
    {
    CameraHooks *hooks=&D_L00_001B8C80.hooks;
    FollowCameraGlobal *camera;
    char *target;
    if (hooks->update) hooks->update();
    camera=(FollowCameraGlobal *)((char *)hooks-0x3a0);
    target=camera->target;
    if (target && I(state,0x10)<2) {
        int targetState=B(target,0x20);
        if (targetState==254) camera->target=0;
        else if (targetState==253) camera->target=0;
        else {
            if (func_00282C48(D_00138180.stickX)>=0.3f || func_00282C48(D_00138180.stickY)>=0.3f) camera->targetTicks=640;
            if (D_L00_001B8C80.targetTicks>400) {
                func_00282948(&D_L00_001B8C80.targetTicks);
                if (D_L00_001B8C80.targetTicks<401) D_L00_001B8C80.targetTicks=0;
            } else {
                D_L00_001B8C80.targetTicks++;
                if (D_L00_001B8C80.targetTicks>400) D_L00_001B8C80.targetTicks=400;
                a=func_00283CE0(D_L00_001B8C80.targetTicks);a/=func_00283CE0(400);
                func_L00_00424F58(D_L00_001B8C80.target+0x10,a*1.5707964897155762f,0.0f);
                func_L00_00424C28();func_L00_00424B70(0.03f,0.2f);
            }
        }
    }
    }
    if (D_00189E20.p1450 && *(signed char *)(D_00189E20.p1450+0x20)>=0) {
        D_L00_001B8C80.targetTicks++;
        if (D_L00_001B8C80.targetTicks>400) D_L00_001B8C80.targetTicks=400;
        a=func_00283CE0(D_L00_001B8C80.targetTicks);a/=func_00283CE0(400);
        func_L00_00424F58(D_00189E20.p1450+0x10,a*1.5707964897155762f,0.0f);
        func_L00_00424C28();func_L00_00424B70(0.03f,0.2f);
    }
    if (!D_L00_001B8C80.target && !D_00189E20.p1450) D_L00_001B8C80.targetTicks=0;
    if (D_00189E20.state==129) {
        func_L00_00424C28();func_L00_00424B70(1,1);
        func_L00_00424BB8(0.06f,0.2f);func_L00_00424C00();
    }
    if (D_00189E20.state==123) {
        func_L00_00424B70(0.04f,0.2f);
        func_L00_00424F00(D_00189E20.p2290+0xc0,0.7853982448577881f,0);
        func_L00_00424A08(0,3,0.003f);func_L00_00424C00();
    }
    if (I(state,0x10)<2 && D_00189E20.state!=129 &&
        (D_00189E20.state==126 || D_00189E20.state==130 || D_00189E20.h1454) && (D_00138180.buttons&3)) {
        char *resetVars;
        func_L00_00424B48(0);func_L00_00424C28();func_L00_00424B70(0.04f,0.2f);
        resetVars=((char *)obj->vars);H(resetVars,0x16)=0;H(resetVars,0x12)=0;H(resetVars,0x14)=0;
    } else if (D_L00_001B1590) {
        char *timerVars=((char *)obj->vars);a=0;
        for(i=0;i<4;i++) { local[i]=func_00283C80(D_L00_001B8E20.samples[i],D_L00_001B8E20.samples[i+1]);a+=local[i]; }
        b=5.0f;a*=0.25f;b=a*b;if(b>1)b=1;b=1-b;
        if (b<D_L00_001B1578) H(timerVars,0x12)=32;
        if (H(timerVars,0x12)) {
            if (func_00282978((short *)(timerVars+0x12))) H(timerVars,0x14)=45;
            func_L00_00424C28();H(timerVars,0x16)++;
            if (H(timerVars,0x16)>30) H(timerVars,0x16)=30;
            a=func_00283CE0(H(timerVars,0x16));a/=func_00283CE0(30);
            func_L00_00424B70((D_L00_001B157C-0.015f)*a+0.015f,0.2f);
            D_L00_001A8900=0;
        } else {
            if (H(timerVars,0x14)) {
                func_00282978((short *)(timerVars+0x14));
                a=func_00283CE0(H(timerVars,0x14));a/=func_00283CE0(45);
                a*=-0.85f;
                a+=0.85f;
                D_L00_001A8900=a;
                H(timerVars,0x16)=0;
            } else {
                H(timerVars,0x16)=0;
                D_L00_001A8900=0.85f;
            }
        }
    }
    I(state,0x10)=0;
    count=func_00277F48(D_00189E20.position,1,(int)D_00189E20.p2290,0,15.0f);
    if (count>0) {
    int targetIndex;
    for(targetIndex=0;targetIndex<count;targetIndex++) {
        char *candidate=func_002AB1F0(D_L00_001C3280[targetIndex]);
        if (candidate && (float)B(candidate,0xd)!=0.0f) { I(state,0x10)=1;break; }
    }
    }
}
