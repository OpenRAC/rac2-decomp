#include "common.h"
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(s16 *)((char *)(p)+(o)))
#define U(p,o) (*(u16 *)((char *)(p)+(o)))
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern float D_L12_001B21C0 __attribute__((sda));
extern float D_L12_001B21C4 __attribute__((sda));
/* A float pair (lower, upper) read through two address forms. The sda incomplete array has no
 * .extern, so the assembler builds the upper bound with $at, and read as symbol+offset that load
 * stays ahead of the call while the lower bound takes the delay slot. The SDATA view gives the
 * $gp lower bound. */
extern float D_L12_001B21C8[] __attribute__((sda));
extern float D_L12_001B21C8_gp[] SDATA(D_L12_001B21C8);
extern int D_L12_001B29C8[] __attribute__((sda));
extern char D_0018A0E0[], D_00189EA0[];
extern int D_0018C0B0[];
extern void func_L12_004277F0(void *);
extern int func_002B3890(void *);
extern int func_002B3868(void *);
extern void func_002B60B0(void *,float,float,float,float);
extern int func_002A7820(int,int);
extern int func_002A77E0(int);
extern int func_00282978(void *);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern int func_002B1C20(void *,void *);
extern void func_L12_00427DD0(void *);
extern int func_L00_00329520(void *,int);
extern void func_00282C88(void *);
extern float func_00282DB0(void *,void *);
extern float func_00282E48(void *,void *);
extern float func_00282E80(void *,void *);
extern float func_002A7940(void);
extern float func_002A7878(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern void func_L02_0032EF10(void *,void *,void *,int,float);
extern int func_L12_00427C58(void *,void *,int);
extern int func_L02_00332630(void *,void *);
extern int func_L02_0032E390(void *,int,int);
extern void func_L09_004051F8(void *);
extern float func_00283248(float,float);
extern void func_L01_00322288(void *,float);
extern int func_002AEB60(void *,float);
extern int func_002A8D70(void *,int,int,int,int,int,float,float,float);
extern int func_002A8C28(void *,void *,int,int,int,int,float,float,float);
extern void func_00282F20(void *,void *,float);
extern void func_L07_003F6F00(void *);
extern void func_L12_00427CB0(void *);
extern void func_L12_00428040(void *);

/* Updates the hopping enemy (moby class 4587): it waits, walks, hops, jumps and charges around, and blows up when it is hit hard enough. */
void func_L12_00426C08(char *obj) {
    char *vars = *(char **)(obj+0x68);
    /* The aligned local preserves the old position or a temporary vector. */
    typedef int Quad __attribute__((mode(TI)));
    Quad vec;
    int flags;
    float angle, speed;
    InitAndReactHoppingEnemy(obj);
    switch (B(obj,0x95)) {
    case 0:
        if (SetSecondPendingFlag(obj)) {
            SetControllerSpeedLimits(obj,0.005f,0.06666667f,0.006981317885220051f,0.4188791f);
            F(vars,0x1D0)=D_L12_001B21C4*0.016666668f;
            F(vars,0x124)=0.006666667f;
            F(vars,0x134)=0.5f;
            H(vars,0x35A)=RandomIntRange(0,30);
        }
        if (H(vars,0x334)==1 && FastDecTimer(vars+0x35A)) {
            if (RandomIntBelow(3)) SetMobyState(obj,9,2);
            else SetMobyState(obj,8,2);
        } else if (H(vars,0x336)) {
            if (RandomIntBelow(2)) SetMobyState(obj,7,1);
            else SetMobyState(obj,6,1);
            H(vars,0x336)=0;
            if (H(vars,0x330)<300) H(vars,0x330)=RandomIntRange(480,600);
        }
        break;
    case 1:
        if (SetSecondPendingFlag(obj)) {
            SetControllerSpeedLimits(obj,0.005f,0.06666667f,0.017453294f,1.0471977f);
            F(vars,0x1D0)=D_L12_001B21C0*0.016666668f;
            F(vars,0x134)=0.05f;
        }
        if (H(vars,0x334)==1) SetMobyState(obj,9,2);
        else if (H(vars,0x330)==0) SetMobyState(obj,1,0);
        break;
    case 2:
        if (SetSecondPendingFlag(obj)) {
            SetControllerSpeedLimits(obj,0.005f,0.06666667f,0.017453294f,1.0471977f);
            F(vars,0x1D0)=D_L12_001B21C0*0.016666668f;
            F(vars,0x124)=0.006666667f;
            F(vars,0x134)=0.05f;
            H(vars,0x35A)=RandomIntRange(0,30);
        }
        if (H(vars,0x334)!=1 && FastDecTimer(vars+0x35A)) {
            SetMobyState(obj,3,1);
            H(vars,0x330)=RandomIntRange(580,600);
        }
        break;
    case 3:
        vec=*(Quad *)(obj+0x10);
        flags=DispatchActionByKind(obj,vars+0x50);
        if (flags&1) PlayHoppingEnemyDeathBlast(obj);
        else if (!IsPointInsideRegion(obj+0x10,W(vars,0x230))) {
            qcopy(obj+0x10,&vec);
            ClearVector128(vars+0xD0);
        } else if (flags&2) {
            if (H(vars,0x334)==1) SetMobyState(obj,9,2);
            else {
                SetMobyState(obj,3,1);
                H(vars,0x330)=RandomIntRange(580,600);
            }
        }
        break;
    }
    switch (B(obj,0x20)) {
    case 1:
        if (!B(obj,0x31)) break;
        if (SetFirstPendingFlag(obj)) {
            int choice=!RandomIntBelow(4);
            if (B(obj,0x43)!=choice) StartAnimationBlended(obj,choice,0,10);
            H(vars,0x332)=RandomIntRange(60,120);
        }
        if (B(obj,0x43)==1) {
            if (B(obj,0x60)&2) StartAnimationBlended(obj,0,0,20);
        } else if (H(vars,0x332)==0) {
            if (!H(vars,0x358) || FastVecDot(vars+0x320,D_0018A0E0)>0.8f) SetMobyState(obj,2,-1);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43)!=6) StartAnimationBlended(obj,6,0,20);
            angle=RandomAngle(); speed=RandomFloatRange(2,5);
            F(vars,0x310)=FastSinOrCosA(angle)*speed;
            F(vars,0x314)=FastSinOrCosB(angle)*speed;
            W(vars,0x318)=0;
            FastVecAdd(vars+0x310,vars+0x310,vars+0x300);
            if (W(vars,0x238)!=-1) {
                vec=*(Quad *)(vars+0x300);
                ClampMoveToPathArea(&vec,vars+0x310,vars+0x310,W(vars,0x238),1.5f);
            }
        }
        StepObjectBySharedMovement(obj,vars+0x310,0);
        if (U(obj,0x96)>30 && (F(vars,0x1CC)<=0.5f || U(obj,0x96)>180)) SetMobyState(obj,1,-1);
        break;
    case 3:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43)!=RandomIntBelow(2)+4) StartAnimationBlended(obj,RandomIntBelow(2)+4,0,10);
        }
        if (fast_vec_dist(obj+0x10,gHeroPosition)<D_L12_001B21C8_gp[0]) SetMobyState(obj,4,-1);
        else if (B(obj,0x60)&2) {
            switch (RandomIntBelow(3)) {
            case 0:SetMobyState(obj,6,-1);break;
            case 1:SetMobyState(obj,7,-1);break;
            case 2:SetMobyState(obj,5,-1);break;
            }
        }
        break;
    case 6:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43)!=RandomIntBelow(2)+2) StartAnimationBlended(obj,RandomIntBelow(2)+2,0,10);
        }
        CheckTargetPointFromOffset(obj,vars+0x1F0);
        if (B(obj,0x60)&2) SetMobyState(obj,3,-1);
        break;
    case 7:
        if (SetFirstPendingFlag(obj) && B(obj,0x43)!=12) StartAnimationBlended(obj,12,0,10);
        CheckTargetPointFromOffset(obj,vars+0x1F0);
        if (B(obj,0x60)&2) SetMobyState(obj,3,-1);
        break;
    case 4:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43)!=6) StartAnimationBlended(obj,6,0,10);
            F(vars,0x354)=RandomFloatRange(D_L12_001B21C8_gp[0],D_L12_001B21C8[1])+0.5f;
        }
        if ((StepObjectBySharedMovement(obj,vars+0x300,0)&128) || vec_distance_xy(obj+0x10,gHeroPosition)>F(vars,0x354)) {
            if (RandomIntBelow(2)) SetMobyState(obj,6,-1);
            else SetMobyState(obj,7,-1);
        }
        break;
    case 5:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43)!=6) StartAnimationBlended(obj,6,0,20);
            angle=RandomAngle(); speed=RandomFloatRange(2,5);
            F(vars,0x310)=FastSinOrCosA(angle)*speed;
            F(vars,0x314)=FastSinOrCosB(angle)*speed;
            W(vars,0x318)=0;
            FastVecAdd(vars+0x310,vars+0x310,vars+0x300);
            if (W(vars,0x238)!=-1) {
                vec=*(Quad *)(vars+0x300);
                ClampMoveToPathArea(&vec,vars+0x310,vars+0x310,W(vars,0x238),1.5f);
            }
        }
        StepObjectBySharedMovement(obj,vars+0x310,0);
        if (U(obj,0x96)>30 && (F(vars,0x1CC)<=0.5f || U(obj,0x96)>180)) SetMobyState(obj,3,-1);
        break;
    case 8:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43)!=RandomIntBelow(2)+2) StartAnimationBlended(obj,RandomIntBelow(2)+2,0,10);
        }
        if (B(obj,0x60)&2) SetMobyState(obj,9,-1);
        break;
    case 9:
        if (SetFirstPendingFlag(obj) && B(obj,0x43)!=6) StartAnimationBlended(obj,6,0,5);
        if (!(U(obj,0x96)&3)) F(vars,0x33C)=(float)CountGroupSideFromObject(obj,gHeroMoby_0018C0B0[0],-1)*0.087266475f;
        StepObjectBySharedMovement(obj,vars+0x1F0,1);
        TurnObjectTowardTargetLimited(obj);
        if (F(vars,0x1CC)<=1.25f) SetMobyState(obj,10,-1);
        break;
    case 10:
        if (SetFirstPendingFlag(obj)) {
            F(vars,0x340)=FastMatrixHelperA(F(vars,0x1F0)-F(obj,0x10),F(vars,0x1F4)-F(obj,0x14));
            if (B(obj,0x43)!=8) StartAnimationBlended(obj,8,2,10);
        }
        StartMobyEffectFromEntry(obj,F(vars,0x340));
        if (IsValueWithinStepOfThreshold(obj,13.0f)) TestHitAtBone(obj,1,0x4000001,0,1,0,0.75f,(float)B(vars,0x34),1.0f);
        if (B(obj,0x60)&2) SetMobyState(obj,9,-1);
        break;
    case 14:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43)!=10) StartAnimationBlended(obj,10,0,5);
            W(vars,0x1BC)=D_L12_001B29C8[0];
        }
        vec_scale_to_length(&vec,vars+0x1A0,1.0f);
        StepObjectBySharedMovement(obj,&vec,0);
        SpawnFallingParticlePuff(obj);
        SweepCollisionFromObject(obj,obj+0x10,0x4000000,0,1,0,0.6f,(float)B(vars,0x34),1.0f);
        if (F(vars,0x190)>=F(obj,0x18)) {
            if (H(vars,0x334)==1) SetMobyState(obj,8,2);
            else SetMobyState(obj,2,0);
            W(vars,0x138)&=~0x11;
        }
        break;
    case 12: PlayHoppingEnemyDeathBlast(obj); break;
    }
    TickHoppingEnemyTimers(obj);
    if (B(obj,0x31)) UpdatePulsingGroupEntities(obj);
}
