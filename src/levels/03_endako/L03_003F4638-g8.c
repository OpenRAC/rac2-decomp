/* The 15-state per-frame update of one Endako entity. -G8 for its small data;
 * -g (config/cflags.txt) gives the two nops retail has before state 12's div.s.
 *
 * func_002AA800 returns the angle still left, the result of its last call to
 * func_002AA738, as RAC1's ApproachValue returns the distance left. No caller
 * here reads it, but the call still defines $f0: that is why state 14's copy
 * right after it takes $f1.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define S(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define Q(p,o) (*(Quad *)((u8 *)(p)+(o)))
extern u8 D_L03_00189EA0[], D_L03_001BFB80[], D_L03_001B9980[];
typedef struct {u8 pad[0x80]; float position[4];} HeroState;
extern HeroState D_L03_00189E20;
extern u8 D_001395C2[2] NOT_SDA;
extern u8 *D_L03_001FE700[], *D_L03_001B2A1C;
extern u8 D_L03_00188660[];
extern int D_L03_001B104C __attribute__((sda)), D_L03_001B106C __attribute__((sda)), D_L03_001A8F00 __attribute__((sda));
extern float D_L03_001B1054 __attribute__((sda)), D_L03_001B103C __attribute__((sda)), D_L03_001B1068 __attribute__((sda));
extern int D_L03_001B1044 __attribute__((sda)), D_L03_001B1040 __attribute__((sda));
extern float D_L03_001B1030[3] SDATA(D_L03_001B1030);
extern float D_L03_001B105C __attribute__((sda));
extern int D_L03_001B2548;
extern void func_L03_003F5590(void *);
extern int func_002ACBC8(void *, int);
extern void func_002A7750(void *, int, int);
extern float func_00283248(float,float);
extern int func_00288AA0(void *,int);
extern void func_00288BE8(void *);
extern void func_L00_003294F0(void *,int);
extern void func_L01_00323310(int,int);
extern int func_002B3868(void *);
extern void func_002A7470(void *,int,int,int);
extern void func_L03_003F6458(void *,int);
extern int func_00282948(void *);
extern void func_L03_003F62C8(void *);
extern float func_00282C48(float);
extern void func_002AA2E8(void *,float,float);
extern float func_002A78D8(float,float);
extern void func_0029FC20(void *,int,void *);
extern void func_002830C0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern int func_002E5CF8(int,int,void *);
extern int func_L03_003D9820(void *,void *,void *,int);
extern void func_L03_003F68E8(void *,int);
extern int func_002A7820(int,int);
extern int func_002AEB60(void *,float);
extern void func_0029FCC0(void *,int,void *);
extern void func_L03_003E18D8(void *,void *,void *,void *,int,float,float,int,int,float);
extern void func_00283098(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_L03_003D09D0(void *,int,void *,void *,void *,int,int,int);
extern float func_002A7878(float,float);
extern void func_0032C700(void *,int,int,int,int,int,int,int,int,int,int,int,float,float);
extern float func_002AA800(void *,int,float,float);
extern void func_0032DA58(void *,void *,void *,float);
extern float func_00283B98(float,float);
extern float func_00283CE0(int);
extern void func_002A6C58(void *,int,int);
extern void func_L00_002D7140(int);
extern void func_0029F338(void *);
extern void func_002A0430(int);
extern void func_002E59F8(int);
extern void func_L03_003F6080(void *);

typedef struct {
    u8 pad[0x80];
    int paths[3], activation[2], trigger, ready[2];
    u8 padA0[0x2A0-0xA0];
    float angles[4];
    u8 pad2B0[0x2E8-0x2B0];
    float blend[4], target[2];
} AttackState;

/* Runs one frame of the Endako boss: waits for the hero, flies along its paths, picks
 * attacks (fire shots, throw bombs, spin up) and plays its death. */
void func_L03_003F4638(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68);
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[16] __attribute__((aligned(16)));
    int i;
    UpdateEndakoBossDamage(moby);
    switch(moby[0x20]) {
    case 1:
        if (IsPointInCuboid(D_L03_00189EA0,((AttackState *)vars)->activation[I(vars,0x2D4)])) {
            u8 *p;
            SetMobyState(moby,2,-1);
            H(moby,0x34)=(H(moby,0x34)&0xFFBE)|0x1000;
            I(moby,0x98)=I(*(u8 **)(moby+0x24),0x10);
            p=D_L03_001FE700[((AttackState *)vars)->paths[I(vars,0x2D4)]];
            I(vars,0x2D8)=0; *(u8 **)(vars+0x2CC)=p; I(vars,0x2DC)=0;
            qcopy(vars+0x290,p+0x10);
            F(vars,0x298)-=7.0f;
            qcopy(moby+0x10,vars+0x290); qzero(vars+0x2A0);
            F(vars,0x2A8)=FastMatrixHelperA(D_L03_00189E20.position[0]-F(moby,0x10),D_L03_00189E20.position[1]-F(moby,0x14));
            F(vars,0x2D0)=0.16666667f;
        }
        if(IsPointInCuboid(D_L03_00189EA0,I(vars,0x94))) SetMobyState(moby,4,-1);
        break;
    case 2:
        if(IsPointInCuboid(D_L03_00189EA0,((AttackState *)vars)->ready[I(vars,0x2D4)])) {
            D_001395C2[0]=1; SetMobyState(moby,3,-1);
            I(vars,0x2DC)=I(*(u8 **)(vars+0x2CC),0)-1;
        }
        break;
    case 3:
        if(I(vars,0x2D8)==I(vars,0x2DC)) {
            if(I(vars,0x2D4)==0) {
                I(moby,0x98)=0; H(moby,0x34)=(H(moby,0x34)|0x41)&0xEFFF;
                SetMobyState(moby,1,-1); I(vars,0x2D4)++;
            } else {
                I(moby,0x98)=0; H(moby,0x34)=(H(moby,0x34)|0x41)&0xEFFF;
                SetMobyState(moby,4,-1);
            }
        }
        break;
    case 4:
        if(D_L03_001B104C && IsPointInCuboid(D_L03_00189EA0,I(vars,0x94))) {
            if(D_L03_001B106C) SetMobyState(moby,5,-1);
            else if(PushRequestQueue(D_L03_001BFB80,0x36)) {
                D_L03_001B106C=1;LaunchQueuedRequest(D_L03_001BFB80);SetMobyState(moby,5,-1);
            }
        }
        break;
    case 5:
        if(H(moby,0x96)>=21 && D_L03_001A8F00!=2) {
            u8 *p;
            SetMobyState(moby,6,2);
            H(moby,0x34)=(H(moby,0x34)&0xFFBE)|0x1000;
            I(moby,0x98)=I(*(u8 **)(moby+0x24),0x10);
            p=D_L03_001FE700[I(vars,0x88)];
            I(vars,0x2DC)=I(vars,0x320); *(u8 **)(vars+0x2CC)=p; I(vars,0x2D8)=I(vars,0x320);
            qcopy(vars+0x290,p+I(vars,0x320)*16+0x10); qcopy(moby+0x10,vars+0x290);
            F(vars,0x2A8)=FastMatrixHelperA(D_L03_00189E20.position[0]-F(moby,0x10),D_L03_00189E20.position[1]-F(moby,0x14));
            F(moby,0xF8)=F(vars,0x2A8);
            {u8 *linked=D_L03_001B2A1C+(I(vars,0xA8)<<8);
            F(vars,0x2D0)=0.16666667f; I(vars,0x2E0)=60; F(vars,0x298)-=7.0f;
            SetObjectFlagBit(linked,0);}
            QueueKeyedRequest(I(vars,0xB0),-1);
        }
        break;
    case 6:
        if(SetFirstPendingFlag(moby)) {
            if(moby[0x43]!=0) StartAnimationBlended(moby,0,0,5);
            if(moby[0x94]!=4) PickEndakoBossPose(moby,moby[0x94]!=8);
        }
        if(I(vars,0x2D8)==I(vars,0x2DC) && FastFloatHelperD(vars+0x2E0)) ChooseNextBehaviourState(moby);
        break;
    case 7: {
        int done=1;
        F(vars,0x178)=F(vars,0x2F8); F(vars,0x1F8)=F(vars,0x2FC);
        if(FloatAbs(F(vars,0x158)-F(vars,0x2F8))>0.01f) done=0;
        else if(FloatAbs(F(vars,0x1D8)-F(vars,0x2FC))>0.01f) done=0;
        if(done) {
            if(F(vars,0x2F8)!=0 && F(vars,0x2FC)!=0) {if(moby[0x43]!=3) StartAnimationBlended(moby,3,0,5);}
            else if(F(vars,0x2F8)!=0) {if(moby[0x43]!=1) StartAnimationBlended(moby,1,0,5);}
            else {if(moby[0x43]!=2) StartAnimationBlended(moby,2,0,5);}
            SetMobyState(moby,8,-1);
            {float first=((AttackState *)vars)->target[0],second=((AttackState *)vars)->target[1];
            ((AttackState *)vars)->blend[2]=(((AttackState *)vars)->blend[0]=first,((AttackState *)vars)->blend[1]=second,((AttackState *)vars)->blend[3]=0.0f);}
        }
        break;
    }
    case 8: {
        int done=1,n;
        for(i=0;i<2;i++) {
            if(((AttackState *)vars)->target[i]!=0) {
                ApproachValue(&((AttackState *)vars)->blend[i],-((AttackState *)vars)->target[i],D_L03_001B1054*0.0002908882452175021f);
                F(vars,0x178+i*0x80)=((AttackState *)vars)->blend[i];
                if(FloatAbs(((AttackState *)vars)->blend[i]+((AttackState *)vars)->target[i])>0.01f) done=0;
                if(((gFrameCounter_L03+i*4)&7)==0) {
                    Q(b,0)=0; b[1]=RandomSignedFloatRange(0,0.1f);b[2]=RandomSignedFloatRange(0,0.1f);b[3]=1;
                    Q(a,0)=Q(b,0);TransformMobyJointPoint(moby,i+2,c);transform_vector(a,a,c);
                    vec_scale_to_length(b,c,D_L03_001B103C*0.016666668f);
                    PlayMobySound(3,0,moby);n=SpawnSparkShotMoby(moby,a,b,vars[0x34]);AddBossTarget(moby,n);
                }
            }
        }
        if(done) {F(vars,0x2F8)=F(vars,0x2FC)=0;SetMobyState(moby,6,2);}
        break;
    }
    case 9: break;
    case 10:
        if(SetFirstPendingFlag(moby)) {
            switch(S(vars,0x3C2)) {
            case 3: I(vars,0x33C)=RandomIntRange(4,6); break;
            case 2: I(vars,0x33C)=RandomIntRange(3,5); break;
            case 1: default: I(vars,0x33C)=RandomIntRange(2,3); break;
            }
            if(moby[0x43]!=4) StartAnimationBlended(moby,4,0,5);
        }
        if(moby[0x60]&2) SetMobyState(moby,11,-1);
        break;
    case 11: {
        int n;
        if(SetFirstPendingFlag(moby) && moby[0x43]!=6) StartAnimationBlended(moby,6,0,5);
        if(IsValueWithinStepOfThreshold(moby,2.0f)) {
            TransformMobyJointToWorld(moby,4,a);qcopy(b,moby+0xC0);b[2]=0;
            vec_scale_to_length(b,b,D_L03_001B1068*0.016666668f);
            n=vars[0x36];PlayMobySound(4,0,moby);
            SpawnClass2843Object(moby,a,b,b,30,(float)n,(float)n,80,1,1.0f);
        }
        if((moby[0x60]&2) && FastFloatHelperD(vars+0x33C)) SetMobyState(moby,6,2);
        break;
    }
    case 12: {
        int n;
        if(FastFloatHelperD(vars+0x2E4)) {SetMobyState(moby,6,2);break;}
        if(H(moby,0x96) && H(moby,0x96)%D_L03_001B1044==0) {
            TransformMobyJointToWorld(moby,I(vars,0x330)>0?6:5,a);
            {float limit=D_L03_001B105C, height, side, lateral;
            n=D_L03_001B1040; I(vars,0x330)=-I(vars,0x330);
            height=limit-a[2];
            Q(c,0)=0; c[0]=0.016666668f;
            side=(float)I(vars,0x330)*0.016666668f;
            lateral=D_L03_001B1030[S(vars,0x3C2)-1]*side;
            c[2]=2*height/(float)n; c[1]=lateral;}
            Q(b,0)=Q(c,0);matrix_mul_vec3(b,b,moby+0xC0);
            FastVecScale(c,b,(float)(n>>1));FastVecAdd(c,c,a);FastVecSub(c,vars+0x50,c);c[2]=0;
            vec_scale_to_length(c,c,D_L03_001B1030[S(vars,0x3C2)-1]*0.016666668f);
            CreateInterpolatedParticleEmitter(moby,0,a,b,c,n,300,vars[0x35]);
        }
        break;
    }
    case 13:
        if(SetFirstPendingFlag(moby) && moby[0x43]!=8) StartAnimationBlended(moby,8,0,5);
        if(moby[0x60]&2) {SetMobyState(moby,10,4);PickEndakoBossPose(moby,1);I(vars,0x2D0)=0;}
        break;
    case 14:
        if(SetFirstPendingFlag(moby)) {if(moby[0x43]!=8)StartAnimationBlended(moby,8,0,5);}
        else if(moby[0x43]!=0)StartAnimationBlended(moby,0,0,5);
        if(H(moby,0x96)%45==0) {
            Q(b,0)=0;b[0]=RandomFloatRange(-2,2);b[1]=RandomFloatRange(-4,4);b[2]=RandomFloatRange(-1,3);
            Q(a,0)=Q(b,0);matrix_mul_vec3(a,a,moby+0xC0);FastVecAdd(a,a,moby+0x10);PlayMobySound(2,0,moby);
            SpawnExplosion(a,0,25,20,20,20,45,1,0,0,0,0,1,20);
        }
        StepAngleTowardTarget(vars+0x2A0,0,0.26179942f,0.0014544413425028324f);
        ((AttackState *)vars)->angles[1]=((AttackState *)vars)->angles[0];I(vars,0x2DC)=I(vars,0x2D8);
        if(H(moby,0x96)>=180) {
            FastVecSub(a,D_L03_001B9980,moby+0x10);vec_scale_to_length(a,a,1);SpawnBlastEffectMoby(moby,moby+0x10,a,0);
            SetMobyState(moby,15,-1);I(vars,0x2CC)=0;F(vars,0x2D0)=-0.083333336f;
        } else F(vars,0x2C0)=FastAddRotations(F(vars,0x2C0),(float)H(moby,0x96)*0.0024240687489509583f);
        break;
    case 15: {
        int n;
        float x;
        if(H(moby,0x96)%15==0) {
            Q(b,0)=0;b[0]=RandomFloatRange(-2,2);b[1]=RandomFloatRange(-2,2);b[2]=RandomFloatRange(0,3);
            Q(a,0)=Q(b,0);matrix_mul_vec3(a,a,moby+0xC0);FastVecAdd(a,a,moby+0x10);PlayMobySound(2,0,moby);
            SpawnExplosion(a,0,25,20,20,20,45,0,0,0,0,0,1,20);
        }
        StepAngleTowardTarget(vars+0x2A0,0,0.78539824f,0.02617994323372841f);StepAngleTowardTarget(vars+0x2A4,0,1.5707965f,0.02617994323372841f);
        x=IntToFloat(H(moby,0x96));F(vars,0x2D0)-=x*9.259259968530387e-05f;F(vars,0x298)+=F(vars,0x2D0);
        if(!S(vars,0x3C0) && F(vars,0x298)<F(vars,0x2B8)-1) {S(vars,0x3C0)=1;SetDeathBits(moby,0,3);}
        if(F(vars,0x298)<F(vars,0x2B8)-12) {
            EndCameraOverride(I(vars,0x2C8));SetObjectFlagBit(D_L03_001B2A1C+(I(vars,0xA4)<<8),0);QueueKeyedRequest(I(vars,0xB4),I(vars,0xB8));
            if(I(vars,0x2C4))MarkMobySpawned(*(void **)(vars+0x2C4));
            D_001395C2[1]=1;MarkTableEntryFlagged(moby[0xB0]);n=I(vars,0x3CC);
            if(n!=-1) {u8 *sound=D_L03_00188660+n*0x70;if(*(u8 **)(sound+0x88)==moby && sound[0x74])StopSoundVoice(n);}
            I(vars,0x3CC)=-1;MarkMobySpawned(moby);return;
        }
        break;
    }
    }
    UpdateEndakoBossHelpers(moby);
}
