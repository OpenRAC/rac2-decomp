#include "common.h"
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(s16 *)((char *)(p)+(o)))
#define U(p,o) (*(u16 *)((char *)(p)+(o)))
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern float D_L14_001B18B0 __attribute__((sda));
extern float D_L14_001B18B4 __attribute__((sda));
/* A float pair (lower, upper), read through two address forms as in func_L12_00426C08. */
extern float D_L14_001B18B8[] __attribute__((sda));
extern float D_L14_001B18B8_gp[] SDATA(D_L14_001B18B8);
extern int D_L14_001B20C8[] __attribute__((sda));
extern char D_0018A0E0[], D_00189EA0[];
extern int D_0018C0B0[];
extern void func_L14_004281D0(void *);
extern int func_002B3890(void *);
extern int func_002B3868(void *);
extern void func_002B60B0(void *,float,float,float,float);
extern int func_002A7820(int,int);
extern int func_002A77E0(int);
extern int func_00282978(void *);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern int func_002B1C20(void *,void *);
extern void func_L02_003CEA28(void *);
extern float func_00282DB0(void *,void *);
extern float func_00282E48(void *,void *);
extern float func_00282E80(void *,void *);
extern float func_002A7940(void);
extern float func_002A7878(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern void func_L02_0032EF10(void *,void *,void *,int,float);
extern int func_L02_003CE8B0(void *,void *,int);
extern int func_L02_00332630(void *,void *);
extern int func_L02_0032E390(void *,int,int);
extern void func_L02_003CEC70(void *);
extern float func_00283248(float,float);
extern void func_L01_00322288(void *,float);
extern int func_002AEB60(void *,float);
extern int func_002A8D70(void *,int,float,float,int,float,int,int,int);
extern int func_002A8C28(void *,void *,float,float,int,float,int,int,int);
extern void func_00282F20(void *,void *,float);
extern void func_L07_003F6F00(void *);
extern void func_L02_003CE908(void *);
extern void func_L14_00428A08(void *);

/* Updates the prison guard: it idles, wanders, walks toward the player, gets alerted and reacts to being hit. */
void func_L14_004275E0(char *obj) {
    char *vars = *(char **)(obj+0x68);
    typedef int Quad __attribute__((mode(TI)));
    Quad vec;
    int flags;
    float angle, speed;
    UpdatePrisonGuardCommon(obj);
    switch (B(obj,0x95)) {
    case 0:
        if (SetSecondPendingFlag(obj)) {
            SetControllerSpeedLimits(obj,0.005f,0.06666667f,0.006981317885220051f,0.4188791f);
            F(vars,0x1D0)=D_L14_001B18B4*0.016666668f;
            F(vars,0x124)=0.006666667f;
            F(vars,0x134)=0.5f;
            H(vars,0x33A)=RandomIntRange(0,30);
        }
        if (H(vars,0x314)==1 && FastDecTimer(vars+0x33A)) {
            if (RandomIntBelow(3)) SetMobyState(obj,9,2);
            else SetMobyState(obj,8,2);
        } else if (H(vars,0x316)) {
            if (RandomIntBelow(2)) SetMobyState(obj,7,1);
            else SetMobyState(obj,6,1);
            H(vars,0x316)=0;
            if (H(vars,0x310)<300) H(vars,0x310)=RandomIntRange(480,600);
        }
        break;
    case 1:
        if (SetSecondPendingFlag(obj)) {
            SetControllerSpeedLimits(obj,0.005f,0.06666667f,0.017453294f,1.0471977f);
            F(vars,0x1D0)=D_L14_001B18B0*0.016666668f;
            F(vars,0x134)=0.05f;
        }
        if (H(vars,0x314)==1) SetMobyState(obj,9,2);
        else if (H(vars,0x310)==0) SetMobyState(obj,1,0);
        break;
    case 2:
        if (SetSecondPendingFlag(obj)) {
            SetControllerSpeedLimits(obj,0.005f,0.06666667f,0.017453294f,1.0471977f);
            F(vars,0x1D0)=D_L14_001B18B0*0.016666668f;
            F(vars,0x124)=0.006666667f;
            F(vars,0x134)=0.05f;
            H(vars,0x33A)=RandomIntRange(0,30);
        }
        if (H(vars,0x314)!=1 && FastDecTimer(vars+0x33A)) {
            SetMobyState(obj,3,1);
            H(vars,0x310)=RandomIntRange(580,600);
        }
        break;
    case 3:
        flags=DispatchActionByKind(obj,vars+0x50);
        if (flags&1) ExplodeAndRemoveMoby_L02(obj);
        else if (flags&2) {
            if (H(vars,0x314)==1) SetMobyState(obj,9,2);
            else {
                SetMobyState(obj,3,1);
                H(vars,0x310)=RandomIntRange(580,600);
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
            H(vars,0x312)=RandomIntRange(60,120);
        }
        if (B(obj,0x43)==1) {
            if (B(obj,0x60)&2) StartAnimationBlended(obj,0,0,20);
        } else if (H(vars,0x312)==0) {
            if (!H(vars,0x338) || FastVecDot(vars+0x300,D_0018A0E0)>0.8f) SetMobyState(obj,2,-1);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43)!=6) StartAnimationBlended(obj,6,0,20);
            angle=RandomAngle(); speed=RandomFloatRange(2,5);
            F(vars,0x2F0)=FastSinOrCosA(angle)*speed;
            F(vars,0x2F4)=FastSinOrCosB(angle)*speed;
            W(vars,0x2F8)=0;
            FastVecAdd(vars+0x2F0,vars+0x2F0,vars+0x2E0);
            if (W(vars,0x218)!=-1) {
                vec=*(Quad *)(vars+0x2E0);
                ClampMoveToPathArea(&vec,vars+0x2F0,vars+0x2F0,W(vars,0x218),1.5f);
            }
        }
        RunEntryHookByMode(obj,vars+0x2F0,0);
        if (U(obj,0x96)>30 && (F(vars,0x1CC)<=0.5f || U(obj,0x96)>180)) SetMobyState(obj,1,-1);
        break;
    case 3:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43)!=RandomIntBelow(2)+4) StartAnimationBlended(obj,RandomIntBelow(2)+4,0,10);
        }
        if (fast_vec_dist(obj+0x10,gHeroPosition)<D_L14_001B18B8_gp[0]) SetMobyState(obj,4,-1);
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
            F(vars,0x334)=RandomFloatRange(D_L14_001B18B8_gp[0],D_L14_001B18B8[1])+0.5f;
        }
        if ((RunEntryHookByMode(obj,vars+0x2E0,0)&128) || vec_distance_xy(obj+0x10,gHeroPosition)>F(vars,0x334)) {
            if (RandomIntBelow(2)) SetMobyState(obj,6,-1);
            else SetMobyState(obj,7,-1);
        }
        break;
    case 5:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43)!=6) StartAnimationBlended(obj,6,0,20);
            angle=RandomAngle(); speed=RandomFloatRange(2,5);
            F(vars,0x2F0)=FastSinOrCosA(angle)*speed;
            F(vars,0x2F4)=FastSinOrCosB(angle)*speed;
            W(vars,0x2F8)=0;
            FastVecAdd(vars+0x2F0,vars+0x2F0,vars+0x2E0);
            if (W(vars,0x218)!=-1) {
                vec=*(Quad *)(vars+0x2E0);
                ClampMoveToPathArea(&vec,vars+0x2F0,vars+0x2F0,W(vars,0x218),1.5f);
            }
        }
        RunEntryHookByMode(obj,vars+0x2F0,0);
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
        if (!(U(obj,0x96)&3)) F(vars,0x31C)=(float)CountGroupSideFromObject(obj,gHeroMoby_0018C0B0[0],-1)*0.087266475f;
        RunEntryHookByMode(obj,vars+0x1F0,1);
        ClampAimYawPitch(obj);
        if (F(vars,0x1CC)<=1.25f) SetMobyState(obj,10,-1);
        break;
    case 10:
        if (SetFirstPendingFlag(obj)) {
            F(vars,0x320)=FastMatrixHelperA(F(vars,0x1F0)-F(obj,0x10),F(vars,0x1F4)-F(obj,0x14));
            if (B(obj,0x43)!=8) StartAnimationBlended(obj,8,2,10);
        }
        StartMobyEffectFromEntry(obj,F(vars,0x320));
        if (IsValueWithinStepOfThreshold(obj,13.0f)) {
            char *target=*(char **)(vars+0x200);
            int play=1;
            if (target && H(target,0xAA)==0x964 /* Gadgebot */ && U(obj,0x96)<=59) play=0;
            if (play) TestHitAtBone(obj,1,0.75f,1.0f,0x4000001,1.0f,0,1,0);
        }
        if ((B(obj,0x60)&2) && vec_distance_xy(obj+0x10,vars+0x1F0)>1.25f) SetMobyState(obj,9,-1);
        break;
    case 14:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43)!=10) StartAnimationBlended(obj,10,0,5);
            W(vars,0x1BC)=D_L14_001B20C8[0];
        }
        vec_scale_to_length(&vec,vars+0x1A0,1.0f);
        RunEntryHookByMode(obj,&vec,0);
        SpawnFallingParticlePuff(obj);
        SweepCollisionFromObject(obj,obj+0x10,0.6f,1.0f,0x4000000,1.0f,0,1,0);
        if (F(vars,0x190)>=F(obj,0x18)) {
            if (H(vars,0x314)==1) SetMobyState(obj,8,2);
            else SetMobyState(obj,2,0);
            W(vars,0x138)&=~0x11;
        }
        break;
    case 12: ExplodeAndRemoveMoby_L02(obj); break;
    }
    ResetTurnAndPlaceObject(obj);
    if (B(obj,0x31)) UpdateGroupMarkerPulse(obj);
}
