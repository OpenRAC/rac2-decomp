#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern float D_L03_001B1BA4 SDATA(D_L03_001B1BA4) __attribute__((sda));
extern float D_L03_001B1BA0 SDATA(D_L03_001B1BA0) __attribute__((sda));
extern float D_L03_001B1B90 SDATA(D_L03_001B1B90) __attribute__((sda));
extern float D_L03_001B1B98 SDATA(D_L03_001B1B98) __attribute__((sda));
extern float D_L03_001B1BB0[4] SDATA(D_L03_001B1BB0) __attribute__((sda));
typedef struct {
    u8 pad00[0x80]; float position[4];
    u8 pad90[0x17A0]; u8 *target;
    u8 pad1834[0xA60]; int state;
} Player;
extern Player D_00189E20;
extern u8 D_L03_001B9980[];
extern u8 D_L03_001A8F20[] NOT_SDA __attribute__((sda));
/* Two bounds of the spin-angle range, with an absolute view of its upper bound. */
extern float D_L03_001B1B98_abs[] __asm__("D_L03_001B1B98") __attribute__((sda));
extern int D_L03_001A9044;
extern int D_L03_001A903C[] __attribute__((sda));
/* The 32 skill-point flags scanned by func_002B0E90. */
extern u8 D_001A7A60[32] __attribute__((sda));
/* The same path-table pointer is read absolutely and through GP. */
extern u8 *D_L03_001B2B0C[] __attribute__((sda));
extern u8 *D_L03_001B2B0C_gp SDATA(D_L03_001B2B0C) __attribute__((sda));
extern u8 *D_L03_001BFDD8 NOT_SDA;
extern void func_L03_0041CA78(void *);
extern int func_002ACBC8(void *,int);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern float func_00282E80(void *,void *);
extern int func_002B3890(void *);
extern float func_002A78D8(float,float);
extern int func_002B1C20(void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern int func_002E5CF8(int,int,void *);
extern void func_002AC728(void *,void *,int,float,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002B0A68(void *,int,void *,float,float,float,float,int);
extern int func_002E5E58(int,int,void *);
extern void func_002B0A18(int,int);
extern void func_002A6C58(void *,int,int);
extern void func_0029F338(void *);
extern int func_002A7820(int,int);
extern float func_002A7878(float,float),func_002A7940(void),func_00283180(float),func_00283198(float);
extern void func_L02_0032EF10(void *,void *,void *,int,float);
extern int func_002B3868(void *),func_L01_00321178(void *,void *);
extern float func_00283248(float,float);
extern int func_L01_00322288(void *,float);
extern int func_00282948(void *),func_002B38B8(void *);
extern int func_L03_0032CFD8(void *,void *,int,float,float,float);
extern int func_L02_00331440(void *,void *,int,float,float,float);
extern int func_002A8C28(void *,void *,int,int,int,int,float,float,float);
extern float func_002A89A8(void *,int,float);
extern int func_00277258(void *,int,void *,float);
extern void func_L00_003294F0(void *,int),func_L03_0041D128(void *);
extern int func_L02_002EF388(void *,void *,void *,int,int);
extern void func_002830C0(void *,void *,void *);
extern int func_L03_0041D1D8(void *);
extern void func_L03_0041CEB0(void *);
/* Updates the actor's combat and movement states, including hiding and respawning. */
void func_L03_0041BE50(u8 *moby) {
    u8 *vars=P(moby,0x68);
    Vec a,b;
    float speed,scale,angle;
    int hit;
    UpdateSweeperBotCore(moby);
    speed=I(vars,0x29c) ? D_L03_001B1BA4 : D_L03_001B1BA0;
    scale=I(vars,0x29c) ? 1.0f : D_L03_001B1B90;
    switch(moby[0x95]) {
    case 0:
        if(I(vars,0x2a8)!=-1) {
            hit=IsPointInCuboid(D_L03_001B9980,I(vars,0x2a8));
            if(!hit) { moby[0x31]=0; U(moby,0x34)|=1; return; }
            moby[0x31]=1; U(moby,0x34)&=0xfffe;
        }
        if(I(vars,0x204)!=1) {
            if(H(vars,0x2d6)) {
                SetMobyState(moby,3,1);
                H(vars,0x2d6)=0;
                if(H(vars,0x2d0)<300) H(vars,0x2d0)=RandomIntRange(480,600);
            }
            break;
        }
        /* Fall through to the active-state transition. */
    case 1:
        if(I(vars,0x204)==1) {
            SetMobyState(moby,5,2);
            if(moby[0x43]) StartAnimationBlended(moby,0,0,10);
        } else if(vec_distance_xy(moby+0x10,gHeroState.position)>24.0f && H(vars,0x2d0)==0) SetMobyState(moby,1,0);
        break;
    case 2:
        if(SetSecondPendingFlag(moby)) { float upper=D_L03_001B1B98_abs[1]; F(vars,0x2e0)=RandomSignedFloatRange(D_L03_001B1B98,upper)*0.017453294f; }
        if(I(vars,0x204)!=1) {
            SetMobyState(moby,3,1);
            if(moby[0x43]) StartAnimationBlended(moby,0,0,10);
            H(vars,0x2d0)=RandomIntRange(580,600);
        }
        break;
    case 3:
        hit=DispatchActionByKind(moby,vars+0x140);
        if(hit&1) {
            matrix_mul_vec3(&a,D_L03_001B1BB0,moby+0xc0);
            FastVecAdd(&a,&a,moby+0x10);
            PlayMobySound(2,0,moby);
            SpawnExplosionWithSparks(moby,&a,-1,0.333f,0.0f);
            FastVecSub(&b,moby+0x10,gHeroState.position);
            b.f[2]=0;
            vec_scale_to_length(&b,&b,0.10000001f);
            SpawnDebrisForMaskedParts(moby,31,D_L03_001A8F20,3.0f,6.0f,3.0f,6.0f,255);
            if(gHeroState.state==49) {
                D_L03_001A9044=D_L03_001A9044+1;
                if(D_L03_001A9044>=10 && !D_001A7A60[28]) {
                    D_001A7A60[28]=1; PlaySoundFromGlobalBank(1,0,0); SetEntryValueByIndex(0x1233,-1); D_L03_001A903C[0]=1;
                }
            }
            SetDeathBits(moby,0,3);
            if(I(vars,0x2a4)) {
                SetMobyState(moby,8,4); I(moby,0x98)=0; U(moby,0x34)=(U(moby,0x34)|0x41)&0xefff;
            } else {MarkMobySpawned(moby);return;}
        } else if(hit&2) {
            if(I(vars,0x204)==1) SetMobyState(moby,6,2);
            else {SetMobyState(moby,3,1); H(vars,0x2d0)=RandomIntRange(580,600);}
        }
        break;
    }
    switch(moby[0x20]) {
    case 1:
        if(moby[0x31] && U(moby,0x96)>10 && vec_distance_xy(moby+0x10,D_L03_001B9980)<50.0f) {
            speed=RandomFloatRange(2.0f,5.0f); angle=RandomAngle();
            F(vars,0x2c0)=FastSinOrCosA(angle)*speed;
            F(vars,0x2c4)=FastSinOrCosB(angle)*speed; I(vars,0x2c8)=0;
            FastVecAdd(vars+0x2c0,vars+0x2c0,vars+0x2b0);
            a.q=*(Quad *)(vars+0x2b0);
            ClampMoveToPathArea(&a,vars+0x2c0,vars+0x2c0,I(vars,0x290),1.5f);
            SetMobyState(moby,2,-1);
        }
        break;
    case 2:
        if(SetFirstPendingFlag(moby)) I(vars,0x88)&=~0x10;
        if((TurnMobyTowardTarget(moby,vars+0x2c0)&0x80)||U(moby,0x96)>300) SetMobyState(moby,1,-1);
        break;
    case 3:
        {
            float heading;
            if(gHeroState.state==49) {
                u8 *target=gHeroState.target;
                heading=FastMatrixHelperA(F(target,0x10)-F(moby,0x10),F(target,0x14)-F(moby,0x14));
            } else {
                heading=FastMatrixHelperA(gHeroState.position[0]-F(moby,0x10),gHeroState.position[1]-F(moby,0x14));
            }
            StartMobyEffectFromEntry(moby,heading);
        }
        if(U(moby,0x96)>10) SetMobyState(moby,4,-1);
        break;
    case 4:
        if(SetFirstPendingFlag(moby)) {
            I(vars,0x88)|=0x10;
            speed=RandomFloatRange(2.0f,5.0f); angle=RandomAngle();
            F(vars,0x2c0)=FastSinOrCosA(angle)*speed;
            F(vars,0x2c4)=FastSinOrCosB(angle)*speed; I(vars,0x2c8)=0;
            FastVecAdd(vars+0x2c0,vars+0x2c0,vars+0x2b0);
            a.q=*(Quad *)(vars+0x2b0);
            ClampMoveToPathArea(&a,vars+0x2c0,vars+0x2c0,I(vars,0x290),1.0f);
        }
        {
            float heading;
            if(gHeroState.state==49) {
                u8 *target=gHeroState.target;
                heading=FastMatrixHelperA(F(target,0x10)-F(moby,0x10),F(target,0x14)-F(moby,0x14));
            } else {
                heading=FastMatrixHelperA(gHeroState.position[0]-F(moby,0x10),gHeroState.position[1]-F(moby,0x14));
            }
            StartMobyEffectFromEntry(moby,heading);
        }
        if((TurnMobyTowardTarget(moby,vars+0x2c0)&0x80)||U(moby,0x96)>300) SetMobyState(moby,3,-1);
        break;
    case 5:
        if(SetFirstPendingFlag(moby)) PlayMobySound(5,0,moby);
        if(FastFloatHelperD(vars+0x2e4) && I(vars,0xd0)>60) {I(vars,0x2e4)=60; F(vars,0x2e0)=-F(vars,0x2e0);}
        angle=FastMatrixHelperA(F(vars,0x1f0)-F(moby,0x10),F(vars,0x1f4)-F(moby,0x14));
        StartMobyEffectFromEntry(moby,angle);
        AimEnemyTowardTarget(moby,vars+0x1f0,16,F(vars,0x2e0),-1.0f,-1.0f);
        if(U(moby,0x96)>60 && vec_distance_xy(moby+0x10,gHeroState.position)<scale*speed) {
            SetMobyState(moby,6,-1);
            if(moby[0x43]!=1) StartAnimationBlended(moby,1,0,10);
        }
        break;
    case 6: {
        if(U(moby,0x96)>45) {
            SetMobyState(moby,5,-1); if(moby[0x43]) StartAnimationBlended(moby,0,0,10);
        } else if(U(moby,0x96)>10) {
            qcopy(&a,moby+0x10); a.f[2]+=0.25f;
            SweepCollisionFromObject(moby,&a,0x4000001,0,1,0,speed*1.25f,(float)vars[0x34],1.0f);
        }
        {
            float *target=(float *)(vars+0x1f0);
            angle=FastMatrixHelperA(F(vars,0x1f0)-F(moby,0x10),F(vars,0x1f4)-F(moby,0x14)); StartMobyEffectFromEntry(moby,angle);
            {
                float x=target[0];
                angle=FastMatrixHelperA(x-F(moby,0x10),F(vars,0x1f4)-F(moby,0x14));
                MoveToTargetWithTempLimits(moby,target,16,angle,-1.0f,-1.0f);
            }
        }
        break;
    }
    case 8:
        if(IsThirdPendingFlagSet(moby) && FastFloatHelperD(vars+0x2d8)) {
            if(I(vars,0x2a0)!=-1) {
                qcopy(&a,D_L03_001B2B0C_gp+I(vars,0x2a0)*128+0x30);
                a.f[2]=ProbeGroundHeightBelow(&a,0,0.5f); qcopy(&b,&a);
                b.f[2]+=F(vars,0x50)+0.1f;
                TestPointAgainstCollision(&b,0,moby,F(vars,0x50));
                if(!D_L03_001BFDD8 || H(D_L03_001BFDD8,0xaa)!=0xff3 /* Megacorp Sweeper Bot */) {
                    SetObjectFlagBit(moby,0); I(vars,0x8c)=-1; ResetSweeperBotDelays(moby);SetMobyState(moby,9,-1);
                    U(moby,0x34)=(U(moby,0x34)&0xffbe)|0x1000; I(moby,0x98)=I(P(moby,0x24),0x10);
                    if(moby[0x43])StartAnimationBlended(moby,0,0,0);
                    H(vars,0x178)=0;
                    SweepCollisionFromObject(moby,&b,0x10001,0,1,0,F(vars,0x50),2.0f,1.0f);
                    FuseObjectWithLinkedObjects(moby,&a,D_L03_001B2B0C[0]+I(vars,0x2a0)*128+0x70,0,0);
                } else {I(vars,0x2d8)=RandomIntRange(10,20);}
            } else if(vec_distance_xy(gHeroState.position,vars+0x2b0)>5.0f) {
                SetObjectFlagBit(moby,0);ResetSweeperBotDelays(moby); H(vars,0x178)=0;F(vars,0x20)=(float)H(vars,0x24);
                SetMobyState(moby,9,-1);
                U(moby,0x34)=(U(moby,0x34)&0xffbe)|0x1000;I(moby,0x98)=I(P(moby,0x24),0x10);
                if(moby[0x43])StartAnimationBlended(moby,0,0,0);
                b.q=0;b.f[2]=RandomAngle();a.q=b.q;
                FuseObjectWithLinkedObjects(moby,vars+0x2b0,&a,0,0);
            }
        }
        break;
    case 9:
        if(!I(vars,0x2ac)) {PlayMobySound(3,0,moby);I(vars,0x2ac)=1;}
        a.q=0;a.f[0]=6.0f;a.f[3]=1.0f;
        transform_vector(&a,&a,D_L03_001B2B0C[0]+I(vars,0x2a0)*128);
        TurnMobyTowardTarget(moby,&a);
        if(CheckPathPointReached(moby)) {I(vars,0x8c)=I(vars,0x290);SetMobyState(moby,5,2);}
        break;
    }
    UpdateSweeperBotWarningLight(moby);
}
