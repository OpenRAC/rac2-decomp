/* Nonmatching: US/US2 740/736 bytes, 0/2; absent from PAL.
 * Five checks. Retained profile -O2 -G0 -ffunction-sections
 * -fno-rerun-loop-opt. First array-index form736 has two extra saved registers;
 * no-split740 retains them. GCSE off704 merges array cursors and keeps wrong
 * invariant maxima. Explicit independent array cursors and real loop scale
 * parameters, plus loop2 off, produce740; adding GCSE off ties byte for byte.
 * Remaining: maximum-configuration addresses hoisted out of initialization
 * into saved registers (frame0x60 versus0x50), resident counter/table base
 * priorities, and setup scheduling. Reopen with independently established
 * global identities/extents or a measured first-loop invariant control.
 * Unknown configuration owners stay incomplete, with GP views only at
 * actual GP sites. No guessed scalar/SDA extent was used for maxima.
 * CounterRow is independently12 bytes: 288E18 indexes the same owner with31,
 * agreeing with observed count/timestamp/level-mask offsets0x174/178/17C.
 * State views describe existing fields only; full16-byte position/direction
 * operands are verified. Callback registration has the real void(ptr) ABI.
 */
#include "common.h"

/* Existing state and resident-field prefixes only; no owners are allocated
 * from these partial views. Four-array accesses below establish their lanes. */
typedef struct {
    float focus,phase;
    unsigned char reserved08[8];
    float radius[4],offset[4],rate[4];
} PulseState;
extern struct {
    unsigned char reserved00[0x80];
    float position[4];
    unsigned char reserved90[0x1B8-0x90];
    int frame;
    unsigned char reserved1BC[0x2C0-0x1BC];
    float direction[4];
    unsigned char reserved2D0[0x33C-0x2D0];
    void *owner;
    unsigned char reserved340[0x2294-0x340];
    int action;
} D_00189E20 NOT_SDA;
/* 288E18 indexes this same12-byte table with selection31. */
typedef struct { unsigned short count,reserved02; unsigned int last,levels; } CounterRow;
extern CounterRow D_0018C958[] NOT_SDA;
extern unsigned int D_001A7390 MACRO_ADDR;
extern int D_001A79F0 MACRO_ADDR;
extern float D_L22_001A7CD8[] NOT_SDA;
extern float D_L22_001AFF08[] NOT_SDA;
extern float D_L22_001AFF08_gp[] SDATA(D_L22_001AFF08);
extern float D_L22_001AFF0C[] NOT_SDA;
extern float D_L22_001AFF10[] NOT_SDA;
extern float D_L22_001AFF10_gp[] SDATA(D_L22_001AFF10);
extern float D_L22_001AFF14[] NOT_SDA;
extern int D_L22_001AFF18[] NOT_SDA;
extern int D_L22_001AFF18_gp[] SDATA(D_L22_001AFF18);
extern int D_L22_001AFF1C[] NOT_SDA;
extern float D_L22_001AFF20[] NOT_SDA;
extern float D_L22_001AFF20_gp[] SDATA(D_L22_001AFF20);
extern void func_002A7750(void *,int,int);
extern float func_002A7878(float,float);
extern float func_00282E48(void *,void *);
extern int func_002E5CF8(int,int,void *);
extern int func_00288E18(int,int);
extern float func_00282DB0(void *,void *);
extern void func_L22_003C9B60(void *);
extern void func_L22_003C9D48(void *);
extern void func_L00_002E6CF0(void (*)(void *),void *);
extern float func_00283B98(float,float);
extern float func_00283198(float);
extern int func_00283D38(int,int,float);

void func_L22_003C9880(unsigned char *object)
{
    int mode=object[0x20];
    PulseState *state=*(PulseState **)(object+0x68);
    switch(mode) {
    case 0: {
        float phaseSpacing=0.25f;
        func_002A7750(object,1,-1);
        {
            float perFrame=0.01666666753590107f;
            float *radius=state->radius;
            float *rate=state->rate;
            float *offset=state->offset;
            int i;
            *(unsigned short *)(object+0x32)=255;
            for(i=0;i<4;i++) {
                *offset++=(float)i*phaseSpacing;
                *rate++=func_002A7878(D_L22_001AFF08_gp[0],D_L22_001AFF0C[0])*perFrame;
                *radius++=func_002A7878(D_L22_001AFF10_gp[0],D_L22_001AFF14[0]);
            }
        }
        break;
    }
    case 1: {
        CounterRow *row;
        if(func_00282E48(D_00189E20.position,object+0x10)<3.0f)
            D_L22_001A7CD8[0]=state->focus;
        if(D_00189E20.action==0x81 && D_00189E20.frame==1)
            func_002E5CF8(0,0,object);
        row=&D_0018C958[31];
        {
        unsigned short count=row->count;
        if((unsigned int)count<=65534u) {
            if(D_00189E20.action==0x81) row->count=65535;
            else if(D_00189E20.owner==object) {
                unsigned int now=D_001A7390;
                if(count) {
                    unsigned int last=row->last;
                    if(now-last>1080 || !last) func_00288E18(0x9C8,31);
                    else if(last<now) row->last=now;
                } else {
                    row->count=count+1;
                    if(row->last<now) row->last=now;
                    row->levels|=(1u<<D_001A79F0)|0x80000000;
                }
            }
        }
        }
        if(func_00282DB0(object+0xE0,D_00189E20.direction)<-0.6f) {
            func_L22_003C9B60(object);
            func_L00_002E6CF0(func_L22_003C9D48,object);
        }
        break;
    }
    }
    if(object[0x31]) {
        float pulse;
        state->phase=func_00283B98(state->phase,D_L22_001AFF20_gp[0]*0.0002908882452175021f);
        pulse=func_00283198(state->phase);
        pulse*=pulse;
        pulse*=pulse;
        pulse*=pulse;
        *(int *)(object+0x78)=func_00283D38(D_L22_001AFF18_gp[0],D_L22_001AFF1C[0],pulse);
    }
}
