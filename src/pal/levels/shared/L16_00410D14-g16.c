/* func_PAL_L16_00410D14, the PAL copy of func_L16_0040BED0: the same C, where 0.00027777778f becomes
   0.00040000002f, the timer 10 becomes 8, the limit 1080 becomes 900, the callees take their PAL names, and
   D_001A7390 is read through the 50 Hz scale ((s32)(x) * 5 + 2) / 6 and without $gp. */
/* Update the launch target, hero motion, fade state, tutorial and looping sound. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { float f0,f4,f8,f12,f16,f20; u8 f24,f25; s16 f26; u8 f28,f29,f30,f31,pad32[16]; s16 f48,f50; int f52,f56,f60; } PoolRecord64;
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
typedef struct { u8 pad0[0x88]; float height; u8 pad8C[0x6C]; float upward; u8 padFC[0x10]; float velocityW; u8 pad110[0x90]; float heading; u8 pad1A4[0x38]; s16 timer; u8 pad1DE[0x15E]; u8 *owner; u8 pad340[0x1F54]; int mode; } ResidentView;
extern ResidentView D_00189E20;
extern u8 D_00188660[];
typedef struct { u16 count, pad; u32 time, levels; } SubtitleHistory;
extern SubtitleHistory D_0018C958[];
extern u32 D_001A79F0[] __attribute__((sda));
extern u32 level_gp SDATA(D_001A79F0);
extern u32 D_001A7390[] __attribute__((sda));
extern int D_L16_001A8F00[] __attribute__((sda));
extern float D_L16_001A7CD8[] __attribute__((sda));
extern float launch_gp SDATA(D_L16_001A7CD8);
extern float D_L16_001A7CDC[] __attribute__((sda));
extern u32 D_L16_001B2648 __attribute__((sda));
extern u8 (*D_L16_001B2B1C[])[256] __attribute__((sda));
extern u8 (*objects_gp)[256] SDATA(D_L16_001B2B1C);
extern u8 (*D_L16_001B2C0C)[128] __attribute__((sda));
extern float D_L16_001B15B8 __attribute__((sda));
extern float D_L16_001B15BC __attribute__((sda)),D_L16_001B15C0 __attribute__((sda));
extern float D_L16_001B15C4 __attribute__((sda));
extern Quad D_L16_001B15D0 __attribute__((sda));
typedef struct { s32 targetIndex, objectIndex, pad8; float rate; float velocity[4], position[4]; s32 sound, pad34, active, pad3C; PoolRecord64 *effect; } LaunchState;
extern void func_0029F338(void *);
extern float func_00283248(float,float);
extern void func_002A7750(u8 *,s32,s32);
extern void func_L16_0040C7E8(u8 *,void *);
extern int func_002E5CF8(int,int,char *);
extern float func_00282E80(void *,void *);
extern float func_00282E20(void *);
extern float func_00282C10(float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F70(void *,void *,float);
extern float func_00282DB0(void *,void *);
extern PoolRecord64 *func_PAL_L00_002D7850(int);
extern void func_L00_002D7140(u8 *);
extern void func_PAL_L16_004114A0(u8 *);
extern float func_L02_002F21C0(void *,void *);
extern int func_PAL_00289730(int,int);
extern void func_002E59F8(s32);
void func_PAL_L16_00410D14(u8 *object)
{
    float difference[4],value,distance,rate,multiplier;
    LaunchState *state=*(LaunchState **)(object+0x68);
    u8 *target;
    PoolRecord64 *effect;
    int handle;
    if (D_L16_001A8F00[0]==2) return;
    switch (object[0x20]) {
    case 0:
        if (level_gp==16) D_L16_001A7CDC[0]=D_L16_001B15B8;
        if (state->targetIndex!=-1) {
            target=(u8 *)((state->targetIndex<<7)+(u32)D_L16_001B2C0C);
            F(object,0xF8)=func_00283248(F(object,0x10)-F(target,0x30),F(object,0x14)-F(target,0x34));
        } else {
            if (state->objectIndex==-1) { func_0029F338(object); return; }
            target=(u8 *)((state->objectIndex<<8)+(u32)objects_gp);
            F(object,0xF8)=func_00283248(F(object,0x10)-F(target,0x10),F(object,0x14)-F(target,0x14));
        }
        state->sound=-1;
        object[0x30]=255;
        *(u16 *)(object+0x34)|=0x2000;
        func_002A7750(object,1,-1);
        break;
    case 1:
        if (D_00189E20.owner==object) {
            func_L16_0040C7E8(object,state->position);
            launch_gp=(state->position[2]-D_00189E20.height)*2.5f;
            if (launch_gp<37.0f) D_L16_001A7CD8[0]=37.0f;
        }
        if (D_00189E20.mode==0x81) {
            if (D_00189E20.owner==object && D_00189E20.upward>0.0f) {
                multiplier=0.5f;
                func_002E5CF8(1,0,(char *)object);
                if (D_001A79F0[0]==16) multiplier=0.3f;
                distance=func_00282E80((u8 *)&D_00189E20+0x80,state->position);
                rate=D_L16_001A7CDC[0]*(distance*0.00040000002f)*multiplier/D_L16_001A7CD8[0];
                value=func_00282C10((rate+rate)*distance);
                func_00282CF0(difference,state->position,(u8 *)&D_00189E20+0x80);
                difference[2]=0.0f;
                func_00282F70(state->velocity,difference,value);
                func_00282F70((u8 *)&D_00189E20+0xF0,(u8 *)&D_00189E20+0xF0,0.0f);
                state->rate=rate;
                func_002A7750(object,2,-1);
            }
        } else if ((D_L16_001B2648&15)==(((s32)object>>8)&15)) {
            if (state->objectIndex!=-1 && (*(u16 *)(objects_gp[state->objectIndex]+0x34)&1)) func_002A7750(object,3,-1);
        }
        break;
    case 2:
        if (D_00189E20.mode==0x81) {
            value=func_00282E20(state->velocity);
            distance=func_00282E80((u8 *)&D_00189E20+0x80,state->position);
            if (distance<0.5f) value=0.0f;
            else if (value!=0.0f) {
                func_00282CF0(difference,state->position,(u8 *)&D_00189E20+0x80);
                difference[2]=0.0f;
                if (func_00282DB0(difference,state->velocity)<0.0f) value=0.0f;
            }
            value-=state->rate;
            func_00282F70(state->velocity,state->velocity,value);
            func_00282F70((u8 *)&D_00189E20+0xF0,(u8 *)&D_00189E20+0xF0,0.0f);
            qcopy((u8 *)&D_00189E20+0x100,state->velocity);
            D_00189E20.velocityW=0.0f;
            if (value!=0.0f) D_00189E20.heading=func_00283248(state->velocity[0],state->velocity[1]);
            D_00189E20.timer=8;
            if (D_001A79F0[0]==17 && !state->active) {
                effect=func_PAL_L00_002D7850(5);
                state->effect=effect;
                if (effect) {
                    state->active=1;
                    qcopy(effect->pad32,&D_L16_001B15D0);
                    effect->f0=D_L16_001B15BC;
                    state->effect->f4=D_L16_001B15C0;
                    state->effect->f12=D_L16_001B15C4*0.017453294f;
                    state->effect->f30=1;
                    state->effect->f26=1;
                }
            }
        } else {
            if (state->active) {
                state->effect->f26=0;
                func_L00_002D7140((u8 *)state->effect);
                state->active=0;
            }
            func_002A7750(object,1,-1);
        }
        break;
    case 3: {
        u8 *fadeTarget=D_L16_001B2B1C[0][state->objectIndex];
        if ((*(u16 *)(fadeTarget+0x34)&1)) {
            if (object[0x23]) {
                I(object,0x98)=0;
                if (object[0x23]>3) object[0x23]-=4;
                else object[0x23]=0;
                break;
            }
        }
        if (((*(u16 *)(fadeTarget+0x34)^1)&1)) {
            if (object[0x23]<124) object[0x23]+=4;
            else {
                object[0x23]=128;
                func_002A7750(object,1,-1);
                I(object,0x98)=I(*(u8 **)(object+0x24),0x10);
            }
        }
        break;
    }
    }
    if (object[0x31] && object[0x20]!=3) func_PAL_L16_004114A0(object);
    if (D_001A79F0[0]==16 && func_L02_002F21C0((u8 *)&D_00189E20+0x80,object+0x10)<9.0f) {
        if (D_0018C958[99].count!=0) {
            if (((s32)(D_001A7390[0])*5+2)/6-D_0018C958[99].time>900 || D_0018C958[99].time==0) func_PAL_00289730(0xA0C,99);
            else if (((s32)(D_001A7390[0])*5+2)/6>D_0018C958[99].time) D_0018C958[99].time=((s32)(D_001A7390[0])*5+2)/6;
        } else {
            D_0018C958[99].count++;
            if (D_0018C958[99].time<((s32)(D_001A7390[0])*5+2)/6) D_0018C958[99].time=((s32)(D_001A7390[0])*5+2)/6;
            D_0018C958[99].levels=(D_0018C958[99].levels|(1U<<D_001A79F0[0]))|0x80000000U;
        }
    }
    if (object[0x20]==2) D_0018C958[99].count=-1;
    if (((*(u16 *)(object+0x34)^1)&1) && I(object,0x98)!=0) {
        u8 *sound=state->sound*0x70+D_00188660;
        if (*(u8 **)(sound+0x88)==object && sound[0x74]) return;
        state->sound=func_002E5CF8(0,4,(char *)object);
        return;
    }
    handle=state->sound;
    if (handle!=-1) {
        u8 *sound=handle*0x70+D_00188660;
        if (*(u8 **)(sound+0x88)==object && sound[0x74]) func_002E59F8(handle);
    }
    state->sound=-1;
}
