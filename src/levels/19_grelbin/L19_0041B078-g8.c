#include "common.h"

extern int D_0018C0B4 NOT_SDA;
extern int D_L19_001B1D20 __attribute__((sda));
extern int D_L19_001B1D24 __attribute__((sda));
extern char *D_L19_001B2A1C __attribute__((sda));
extern void *D_L19_001FB5A0[];
extern int func_002ACD38(void *);
extern int func_L19_0041BFD0(void *);
extern void func_0029F338(void *);
extern int func_002A8508(int,int);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern int func_00282948(void *);
extern int func_002A7820(int,int);
extern int func_002B3890(void *);
extern int func_002B3868(void *);
extern int func_002B1C20(void *,void *);
extern void func_002A6C58(void *,int,int);
extern void func_L01_003E9CF8(void *,int,void *);
extern int func_002A77E0(int);
extern float func_002A7878(float,float);
extern float func_002A7940(void);
extern void func_002AF000(void *,float,float,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_002B60B0(void *,float,float,float,float);
extern int func_L01_00321178(void *,void *);
extern float func_00282E80(void *,void *);
extern float func_00283248(float,float);
extern int func_L01_00322288(void *,float);
extern int func_002AEB60(void *,float);
extern float func_00283C80(float,float);
extern void func_002B4FF0(void *,void *,float);
extern float func_0029F530(void *);
extern int func_002A8D70(float,float,float,void *,int,int,int,int,int);
extern float func_00283B98(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_L02_00331440(void *,void *,int,float,float,float);
extern void func_L19_0041C2B8(void *);

#define I(p,n) (*(int *)((p)+(n)))
#define F(p,n) (*(float *)((p)+(n)))
#define B(p,n) (*(u8 *)((p)+(n)))
typedef struct { char pad[0x34]; u16 flags; } GrelbinObjectFlags;
#define H(p) (((GrelbinObjectFlags *)(p))->flags)
#define ANIM(n,a,t) if(B(obj,0x43)!=(n)) func_002A7470(obj,n,a,t)
#define SOLID() H(obj)=(H(obj)&0xFFBE)|0x1000; I(obj,0x98)=I(*(char **)(obj+0x24),0x10)
#define HIDE() { B(obj,0x31)=1; H(obj)&=0xFFFE; I(obj,0x98)=I(*(char **)(obj+0x24),0x10); H(obj)|=0x1000; }
/* Written out in both state 2 and state 3: jump2 cross-jumps the two copies, which is what
 * shares the animation 13 and 2 calls while leaving the animation 6 call alone. */
#define PICK_FLEE_TARGET() { \
    qcopy(data+0x290,data+0x210); \
    distance=func_002A7878(6.0f,8.0f); \
    angle=func_002A7940(); \
    func_002AF000(vec,distance,angle,0.0f); \
    func_00282CC0(data+0x290,data+0x290,vec); \
    { int timer=RandomIntRange(580,600); int active=gActiveYetiCount; \
      I(data,0x230)=timer; gActiveYetiCount=active-1; } }
#define DISABLE_COLLISION() { B(obj,0x31)=1; H(obj)&=0xFFFE; I(obj,0x98)=I(*(char **)(obj+0x24),0x10); SOLID(); }

/* Updates a Y.E.T.I. every frame. It waits in hiding, runs toward the player, and attacks up close or with a leap. It runs away to a new spot when it is hurt. */
void func_L19_0041B078(char *obj)
{
    char *data;
    char *entity;
    float vec[4] __attribute__((aligned(16)));
    float distance, angle;
    int aiMode, pathResult;
    if (!IsObjectInSelectedZone(obj+0x10) || D_0018C0B4==111) return;
    data=*(char **)(obj+0x68);
    if (InitYetiStats(obj)) { MarkMobySpawned(obj); return; }
    if(B(obj,0x20)==1) H(obj)&=0xEFFF;
    aiMode=B(obj,0x95);
    switch(aiMode) {
    case 0:
        if(I(data,0x278)==1 && I(data,0x26C)==0 && gActiveYetiCount<gMaxActiveYetis) {
            if(I(data,0x264)==-1) {
                if(I(data,0x250)==255 || !D_L19_001FB5A0[I(data,0x250)]) {
                    HIDE(); SetMobyState(obj,10,2); ANIM(0,0,10); gActiveYetiCount++;
                } else if(!CountMobysInGroupNotInState(I(data,0x250),-1)) {
                    HIDE(); SetMobyState(obj,10,2); ANIM(0,0,10); gActiveYetiCount++;
                }
            } else {
                entity=gMobyArray_L19+(I(data,0x264)<<8);
                if(!entity || B(entity,0x20)==254 || B(entity,0x20)==253) {
                    HIDE(); SetMobyState(obj,10,2); ANIM(0,0,10); gActiveYetiCount++;
                }
            }
        } else if(I(data,0x240) && FastFloatHelperD(data+0x238)) {
            I(data,0x240)=0;
            if(I(data,0x230)<300) I(data,0x230)=RandomIntRange(480,600);
        }
        break;
    case 1:
        if ((I(data,0x278)==1 || I(data,0x27C)==1) && gActiveYetiCount<gMaxActiveYetis) {
            ANIM(3,0,10); SetMobyState(obj,14,2); gActiveYetiCount++;
        }
        break;
    case 2:
        if(SetSecondPendingFlag(obj)) {
            DISABLE_COLLISION();
        }
        if(I(data,0x278)!=1 && I(data,0x27C)!=1 && B(obj,0x20)!=15 && B(obj,0x20)!=16) {
            SetMobyState(obj,7,1); ANIM(7,0,10);
            if(!RandomIntBelow(3)) { ANIM(6,0,10); }
            else if(RandomIntBelow(2)) {
                ANIM(13,0,10);
            }
            PICK_FLEE_TARGET();
        } else { DISABLE_COLLISION(); }
        break;
    case 3:
        pathResult=DispatchActionByKind(obj,data+0x140);
        if(pathResult&1) {
            SetDeathBits(obj,0,3); QueueMobyForGlowEffect(obj,0,0); gActiveYetiCount--;
        } else if(pathResult&2) {
            if(I(data,0x204)==1 && gActiveYetiCount<=gMaxActiveYetis) {
                ANIM(3,0,10); SetMobyState(obj,14,2);
            } else {
                SetMobyState(obj,8,1);
                ANIM(2,0,10);
                PICK_FLEE_TARGET();
            }
        }
        break;
    }
    switch(B(obj,0x20)) {
    case 1:
    case 2:
        break;
    case 7:
        if(B(obj,0x60)&2) {SetMobyState(obj,8,-1); ANIM(2,0,13);}
        break;
    case 8:
        if(SetFirstPendingFlag(obj)) SetControllerSpeedLimits(obj,0.0016666667f,0.050000004f,0.0069813179f,0.8377582f);
        TurnMobyTowardTarget(obj,data+0x290);
        if(vec_distance_xy(obj+0x10,data+0x290)<0.5f) {SetMobyState(obj,3,-1); ANIM(1,0,10);}
        break;
    case 3:
        if(B(obj,0x60)&2) {
            ANIM(12,0,10);SetMobyState(obj,1,0);
            B(obj,0x31)=0; I(obj,0x98)=0;H(obj)=(H(obj)|1)&0xEFFF;
        }
        break;
    case 10:
        entity=*(char **)(data+0x200);
        StartMobyEffectFromEntry(obj,FastMatrixHelperA(F(entity,0x10)-F(obj,0x10),F(entity,0x14)-F(obj,0x14)));
        if(IsValueWithinStepOfThreshold(obj,23.0f)) {
            ANIM(7,1,2);
            if(RandomIntBelow(2)) {ANIM(6,0,2);}
            SetMobyState(obj,11,-1);
            if(I(data,0x274) || !RandomIntBelow(2)) { ANIM(3,0,6);SetMobyState(obj,14,-1); }
        }
        break;
    case 11:
        entity=*(char **)(data+0x200);
        StartMobyEffectFromEntry(obj,FastMatrixHelperA(F(entity,0x10)-F(obj,0x10),F(entity,0x14)-F(obj,0x14)));
        if(B(obj,0x60)&2) { ANIM(3,0,10);SetMobyState(obj,14,-1); }
        break;
    case 14:
        if(SetFirstPendingFlag(obj)) {
            SetControllerSpeedLimits(obj,0.0033333334f,0.10000001f,0.0069813179f,0.8377582f); SOLID();
        }
        if(vec_distance_xy(obj+0x10,*(char **)(data+0x200)+0x10)<7.0f && vec_distance_xy(obj+0x10,*(char **)(data+0x200)+0x10)>4.0f &&
            FastDiffRots(F(obj,0xF8),FastMatrixHelperA(F(data,0x1F0)-F(obj,0x10),F(data,0x1F4)-F(obj,0x14)))<0.52359885f) {
            SetControllerSpeedLimits(obj,0.02f,0.6f,0.0069813179f,0.8377582f);ANIM(4,0,10);SetMobyState(obj,15,-1);
        } else if(vec_distance_xy(obj+0x10,*(char **)(data+0x200)+0x10)<=3.0f &&
            FastDiffRots(F(obj,0xF8),FastMatrixHelperA(F(data,0x1F0)-F(obj,0x10),F(data,0x1F4)-F(obj,0x14)))<0.52359885f) {
            ANIM(10,0,10);SetMobyState(obj,16,-1);
        } else TurnTowardTargetAndStepMovement(obj,data+0x1F0,F(data,0x270));
        break;
    case 15: {
        float attackDistance;
        if(SetFirstPendingFlag(obj)) { SOLID(); }
        attackDistance=GetMobyAnimationValue(obj);
        if(attackDistance>4.0f && attackDistance<15.0f) TurnMobyTowardTarget(obj,data+0x1F0);
        if(IsValueWithinStepOfThreshold(obj,30.0f)) {
            ANIM(7,0,10);SetMobyState(obj,24,-1);
            if(RandomIntBelow(3)) {ANIM(6,0,10);} else if(RandomIntBelow(2)) {ANIM(13,41,10);}
            if(RandomIntBelow(5)) { ANIM(5,0,10);SetMobyState(obj,17,-1); }
        }
        if(attackDistance<19.0f) {
            TestHitAtBone(0.75f,(float)B(data,0x34),1.0f,obj,0,1,0,1,0);
        }
        break;
    }
    case 16:
        if(SetFirstPendingFlag(obj)) {SOLID();}
        if(IsValueWithinStepOfThreshold(obj,25.0f)) {
            ANIM(7,0,10);SetMobyState(obj,24,-1);
            if(RandomIntBelow(3)) {ANIM(6,0,10);} else if(RandomIntBelow(2)) {ANIM(13,41,10);}
            if(RandomIntBelow(3)) {ANIM(5,0,10);SetMobyState(obj,17,-1);}
        }
        if(GetMobyAnimationValue(obj)<14.0f) {
            TestHitAtBone(0.75f,(float)B(data,0x34),1.0f,obj,0,1,0,1,0);
        }
        break;
    case 17: {
        char *target;
        if(SetFirstPendingFlag(obj)) {
            vec[0]=FastSinOrCosA(FastAddRotations(F(obj,0xF8),3.141593f))*18.0f;
            vec[1]=FastSinOrCosB(FastAddRotations(F(obj,0xF8),3.141593f))*18.0f;
            vec[2]=0.0f;
            FastVecAdd(data+0x280,vec,obj+0x10);
            SetControllerSpeedLimits(obj,0.023333333f,0.8000001f,0.0069813179f,0.8377582f);
        }
        { float range=GetMobyAnimationValue(obj);
        if(range>4.0f && range<14.0f) {
            target=data+0x280;
            { float dx=F(data,0x280)-F(obj,0x10); float dy=F(data,0x284)-F(obj,0x14);
            angle=FastMatrixHelperA(dx,dy); }
            MoveToTargetWithTempLimits(obj,target,16,angle,-1.0f,-1.0f);
        }}
        if(IsValueWithinStepOfThreshold(obj,21.0f)) {
            ANIM(7,0,10);SetMobyState(obj,24,-1);
            if(RandomIntBelow(3)) {ANIM(6,0,10);} else if(RandomIntBelow(2)) {ANIM(13,41,10);}
        }
        break;
    }
    case 24:
        if(B(obj,0x60)&2) {ANIM(3,0,10);SetMobyState(obj,14,-1);}
        break;
    }
    UpdateMobyTimersAndAttachment(obj);
}
