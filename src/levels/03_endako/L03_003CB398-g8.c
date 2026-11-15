#include "common.h"

extern void func_002A04B8(void *, int *, int *, int *);
extern void func_002A7750(void *, int, int);
extern float func_00282E80(void *, void *);
extern void func_002B0C28(int, int, int);
extern int func_L03_0032AB20(int);
extern int func_002E5CF8(int, int, void *);
extern float func_00283B98(float, float);
extern void func_L00_002D40A0(void *, int, float);
extern void func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern int func_002B38B8(void *);
extern int func_L00_002D40F0(void);
extern void func_L03_002C6F08(int, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_L00_002C8BA8(int);
extern int func_002B3868(void *);
extern float func_002AA2E8(void *, float, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_002A89A8(void *, int, float);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_L00_0042A500(int);
extern void func_00282F20(void *, void *, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern int func_00283D38(int, int, float);
extern void func_002A0488(void *, int, int, int);
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void func_00282C88(void *);
extern float func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern void *func_002C3150(void *, void *, int, float, unsigned char, unsigned char, int);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L03_003CBC40(void *);
typedef struct {
    char pad00[0x80];
    float position[4];
    char pad90[0x60];
    float velocity[4];
    char pad100[0x23C];
    char *interaction;
    int interactionActive;
    char pad344[0x1CDC];
    float scale[3];
    char pad202C[0x28B];
    unsigned char interactionLock;
    char pad22B8[0x248];
    unsigned short transform;
} PlayerState;
extern PlayerState D_00189E20;
extern unsigned char D_001395C4[];
extern int D_00138324[];
extern char *D_L03_001B2B0C MACRO_ADDR;
extern float D_L03_001B03E0 __attribute__((sda));
extern float D_L03_001B03E8 __attribute__((sda));
extern float D_L03_001B03EC;
/* One 8-byte colour pair: retail loads the first word through $gp and the second as a bare
   symbol plus offset, which the compiler treats as a two-instruction load. */
extern int D_L03_001B03F0[2];
extern int D_L03_001B03F0_0 SDATA(D_L03_001B03F0);
extern int D_L03_001B03F8 __attribute__((sda));
extern float D_L03_001B03FC __attribute__((sda));
extern float D_L03_001B0400 __attribute__((sda));
extern float D_L03_001B0404 __attribute__((sda));

#define I(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))

/* Per-frame update of moby class 2437 (Tube Start): lets the player step in, shoots them along the tube and lights up its glow while it is active. */
void func_L03_003CB398(char *actor)
{
    float pos[4], rot[4];
    int red,green,blue;
    char *state = *(char **)(actor+0x68);
    int i, countdown, color, life, random, tint, tintB, tintG;
    float one;
    int packedGreen, packedBlue;
    unsigned int timer, oldTimer;
    unsigned char lifeByte;
    float angle, scale, alpha, speed, step, rate;
    char *basisRow, *scaleFactor, *scalePtr, *velocityPtr;
    switch (B(actor,0x20)) {
    case 0:
        get_moby_color(actor,&red,&green,&blue);
        packedGreen = (green << 8) | 0x80000000;
        packedBlue = (blue << 16) | packedGreen;
        I(state,0x20) = packedBlue | red;
        if (I(state,8) && !D_001395C4[0]) {
            I(actor,0x98)=0;
            H(actor,0x34)=(H(actor,0x34)|0x41)&0xEFFF;
            SetMobyState(actor,5,-1);
            B(actor,0x30)=255;
        } else SetMobyState(actor,1,-1);
        break;
    case 1:
        if (gHeroState.interaction==actor && gHeroState.interactionActive
            && vec_distance_xy(actor+0x10,gHeroState.position)<2.0f) {
            TryClaimNotice(8,0x27A9,1);
            if (IsHeroAllowedForMode(8) && (D_00138324[0]&0x10)) {
                PlayMobySound(0,0,actor);
                angle=FastAddRotations(F(actor,0xF8),1.57079637f);
                StartHeroTargetState(actor+0x10,0,angle);
                SweepCollisionFromObject(actor,actor+0x10,0x10000,0,1,0,2.5f,100.0f,1.0f);
                SetMobyState(actor,2,-1);
            }
        } else if (IsThirdPendingFlagSet(actor)) {
            SetMobyState(actor,5,-1);
            I(actor,0x98)=0;
            H(actor,0x34)=(H(actor,0x34)|0x41)&0xEFFF;
        }
        break;
    case 2:
        gHeroState.interactionLock=1;
        if (GetHeroTargetStateKind()==2) {
            SetMobyState(actor,3,-1);
            EnterHeroState_L03(0x6F,1);
        } else {
            timer = H(actor,0x96);
            oldTimer = timer++;
            H(actor,0x96) = timer;
            if (oldTimer < 0xB5) break;
            FastVecSub(pos,gHeroState.position,actor+0x10);
            if (FastVecDot(pos,gHeroState.velocity)<0.0f) qzero(gHeroState.velocity);
            if (H(actor,0x96)>=0x169) {
                SetMobyState(actor,1,-1);
                StartHeroLoaderState(0);
            }
        }
        break;
    case 3:
        if (SetFirstPendingFlag(actor)) { I(state,0x1C)=0; B(actor,0x30)=255; }
        H(actor,0x96)++;
        gHeroState.interactionLock=1;
        ApproachValue(state+0x1C,1.57079649f,0.104719773f);
        gHeroState.transform=1;
        gHeroState.scale[0]=gHeroState.scale[1]=1.0f-FastSinOrCosB(F(state,0x1C));
        gHeroState.scale[2]=2.0f-FastSinOrCosA(F(state,0x1C));
        if (H(actor,0x96)==0x30) {
            qcopy(pos,D_L03_001B2B0C+I(state,0)*128+0x30);
            pos[2]=ProbeGroundHeightBelow(pos,0,0.5f);
            qcopy(rot,D_L03_001B2B0C+I(state,0)*128+0x70);
            ResetHeroPositionAndDirection(pos,rot,0,1);
            if (I(state,0x10)!=-1) ResetCameraEntry(I(state,0x10));
            SetMobyState(actor,4,-1);
        }
        break;
    case 4:
        if (SetFirstPendingFlag(actor) && I(state,0xC)) D_001395C4[0]=1;
        ApproachValue(state+0x1C,0.0f,0.104719773f);
        gHeroState.transform=1;
        gHeroState.scale[0]=gHeroState.scale[1]=1.0f-FastSinOrCosB(F(state,0x1C));
        gHeroState.scale[2]=2.0f-FastSinOrCosA(F(state,0x1C));
        gHeroState.interactionLock=1;
        if (F(state,0x1C)<=0.0f) {
            B(actor,0x30)=B(actor,0x32);
            gHeroState.interactionLock=0;
            SetMobyState(actor,1,-1);
        }
        break;
    case 5:
        if ((!I(state,8) && !IsThirdPendingFlagSet(actor)) || (I(state,8) && D_001395C4[0])) {
            SetMobyState(actor,6,-1);
            H(actor,0x34)|=0x100;
            basisRow=actor+0xC0; scaleFactor=state+0x34;
            for (countdown=2;countdown>=0;countdown--) {
                F(scaleFactor,0)=0.02f;
                I(state,0x18)=0;
                vec_scale_to_length(basisRow,basisRow,F(scaleFactor,0)); basisRow+=0x10; scaleFactor+=4;
            }
            H(actor,0x34)=(H(actor,0x34)&0xFFBE)|0x1000;
            I(actor,0x98)=I(*(char **)(actor+0x24),0x10);
        }
        break;
    case 6:
        step=D_L03_001B0400*0.000277777785f;
        rate=D_L03_001B03FC*0.0166666675f;
        if (SetFirstPendingFlag(actor)) PlayMobySound(1,0,actor);
        scaleFactor=state+0x34;
        one=1.0f;
        i=0; basisRow=actor+0xC0; velocityPtr=state+0x24; scalePtr=scaleFactor;
        for (;i<3;i++,basisRow+=16,velocityPtr+=4,scalePtr+=4,scaleFactor+=4) {
            if (F(scaleFactor,0)<one && (!i || F(scaleFactor,-4)>D_L03_001B0404)) {
                StepValueTowardTarget(scalePtr,velocityPtr,1.0f,step,step,rate);
                if (F(scaleFactor,0)>one) F(scaleFactor,0)=one;
                vec_scale_to_length(basisRow,basisRow,F(scaleFactor,0));
            }
        }
        if (F(state,0x34)>=1.0f && F(state,0x38)>=1.0f && F(state,0x3C)>=1.0f) SetMobyState(actor,1,-1);
        tint=FastTweenColor(D_L03_001B03F8,I(state,0x20),F(state,0x3C));
        tintB=(tint>>16)&255;
        tintG=(tint>>8)&255;
        set_moby_color(actor,tint&255,tintG,tintB);
        break;
    }
    if (B(actor,0x20)<5) {
        F(state,0x30)=FastAddRotations(F(state,0x30),D_L03_001B03E0*0.000290888245f);
        if (F(state,0x18)<1.0f) ApproachValue(state+0x18,1.0f,0.0333333351f);
        if (RandomIntBelow(2)) {
            angle=RandomAngle();
            pos[0]=FastSinOrCosA(angle)*0.85f;
            pos[1]=FastSinOrCosB(angle)*0.85f;
            pos[2]=0;
            FastVecAdd(pos,pos,actor+0x10);
            pos[2]+=0.1f;
            alpha=RandomFloatRange(D_L03_001B03E8,D_L03_001B03EC);
            scale=RandomFloatRange(0,1);
            color=FastTweenColor(D_L03_001B03F0_0,D_L03_001B03F0[1],scale);
            speed=RandomFloatRange(2,3);
            life=RandomIntRange(60,180);
            lifeByte = life;
            ClearVector128(rot);
            rot[2]=speed/IntToFloat(life);
            random=RandomIntBelow(255);
            SpawnHeroRelativeParticle(pos,rot,color,alpha,lifeByte,random&255,0);
        }
        AddDrawCallbackToList1(DrawTubeStartEffect,actor);
    }
}
