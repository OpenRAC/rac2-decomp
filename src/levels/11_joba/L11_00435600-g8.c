#include "common.h"
struct AnimationView { char pad[0x43]; unsigned char animation; };
#define ANIM(p) (((struct AnimationView *)(p))->animation)
typedef int Quad __attribute__((mode(TI)));
#define COPY(d,s) (*(Quad *)(d)=*(Quad *)(s))
#define B(p,n) (*(unsigned char *)((char *)(p)+(n)))
#define H(p,n) (*(short *)((char *)(p)+(n)))
#define U(p,n) (*(unsigned short *)((char *)(p)+(n)))
#define I(p,n) (*(int *)((char *)(p)+(n)))
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
extern int D_L11_001A8FF4 __attribute__((sda));
extern char D_00189EA0[];
extern char *D_L11_001C0D18 NOT_SDA;
extern char *D_0018C2BC NOT_SDA;
extern void func_L11_00436350(char *),func_L11_00436768(char *),func_L11_00436A78(char *);
extern void func_L11_00436B78(char *,char *);
extern int func_L11_00436D08(char *,void *);
extern char *func_L11_004417E8(char *);
extern int func_L11_00441808(char *,void *);
extern void func_L02_003FC248(char *,int,int);
extern void func_002A7750(void *,int,int),func_002A7470(void *,int,int,int);
extern int func_002A77E0(int),func_002B3890(void *),func_002B3868(void *),func_002B1C20(void *,void *);
extern float func_002B04E0(void *,void *,void *),func_00283248(float,float),func_00283C80(float,float),func_00282E48(void *,void *),func_00282E80(void *,void *),func_0029F530(void *),func_002A7878(float,float);
extern void func_00282CF0(void *,void *,void *),func_00282CC0(void *,void *,void *),func_00282F20(void *,void *,float),func_00282D30(void *,void *,float),func_002833F0(void *,void *),func_002AB6D8(void *,void *);
extern void func_002B60B0(void *,float,float,float,float),func_L01_00321178(void *,void *),func_L02_00333438(void *,void *),func_002B4FF0(void *,void *,float),func_002B50E0(void *,void *,float),func_002B5278(void *,float),func_L07_00321D68(void *,void *),func_002B4090(void *,void *,float,float,float);
extern int func_00277258(void *,int,void *,float);
extern void func_002A8D70(void *,int,int,int,int,int,float,float,float);
static __inline__ void SetAnimation(char *moby, int animation, int mode, int blend)
{
    if (ANIM(moby) != animation) StartAnimationBlended(moby, animation, mode, blend);
}
/* Flies to one point from afar and another up close; case 7 uses one point for both. */
static __inline__ void FlyByDistance(char *moby, float *farPoint, float *nearPoint, float distance)
{
    if (distance>3.0f) AimAtTargetOffset(moby,farPoint);
    else AimAtTargetOffset(moby,nearPoint);
}
/* Runs the flying enemy: it hovers, chases and attacks the hero, and plays the matching animations in each state. */
void func_L11_00435600(char *moby)
{
    float target[4],delta[4],zero[4],matrix[4][4];
    char *vars=P(moby,0x68), *node;
    float angle,turn,distance;
    int i,flags,clear;
    float *spin;
    if (B(moby,0x20)==1) return;
    if (H(vars,0x286) && !D_L11_001A8FF4 && B(moby,0x20)!=11 && B(moby,0x20)!=10) return;
    UpdateFlyingEnemyHitAndInit(moby);
    if (B(moby,0x20)==1) return;
    if (H(vars,0x286) && !D_L11_001A8FF4) return;
    if (!H(vars,0x282)) {
        I(vars,0x270)=0;
        if (B(moby,0x95)==3) {
            SetMobyState(moby,5,2);
            if (RandomIntBelow(2)) {
                SetAnimation(moby,1,0,10);
            } else SetAnimation(moby,4,0,10);
        }
    }
    node=0;
    if (P(moby,0xB8)) node=GetArenaCenterPoint(P(moby,0xB8));
    if (I(vars,0x270)) COPY(target,P(vars,0x270)+0x10); else COPY(target,gHeroPosition);
    if (H(vars,0x286)) {
        FastVecSub(delta,target,moby+0x10);
        angle=0;
        turn=GetHeadingAngleOfVector(moby,delta,vars+0x210);
    } else {
        angle=FastMatrixHelperA(target[0]-F(moby,0x10),target[1]-F(moby,0x14));
        turn=FastDiffRots(angle,F(moby,0xF8));
    }
    distance=fast_vec_dist(moby+0x10,target);
    if (B(moby,0x95)==2) {
        if (SetSecondPendingFlag(moby)) {
            SetAnimation(moby,6,0,10);
            B(moby,0xBC)=0;
            SetControllerSpeedLimits(moby,0.00444444455f,0.1333333403f,0.006981317885f,0.2094395459f);
            PickRandomHomeSpot(moby,node);
            U(moby,0x96)=10000;
        }
        if (B(moby,0xBC)==1 && U(moby,0x96)>=301) {
            switch (RandomIntBelow(2)) {
            case 0:
                SetAnimation(moby,1,0,10);
                break;
            case 1:
                SetAnimation(moby,4,0,10);
                break;
            }
            U(moby,0x96)=RandomIntBelow(100);
        }
        if (H(vars,0x282)) {
            SetMobyState(moby,6,3);
            SetAnimation(moby,2,0,10);
        }
        {
            char *home=vars+0x250;
            if (!B(moby,0xBC) && vec_distance_xy(moby+0x10,home)<0.5f) B(moby,0xBC)=1;
            else if (H(vars,0x286)) AimAtTargetOffset(moby,home);
            else TurnMobyTowardTarget(moby,home);
        }
    }
    switch (B(moby,0x20)) {
    case 3:
        if (SetFirstPendingFlag(moby)) {
            B(moby,0xBC)=0;
            SetAnimation(moby,1,0,0);
            U(moby,0x96)=0;
        }
        if (!B(moby,0xBC) && H(vars,0x284)<U(moby,0x96)) {
            SetAnimation(moby,6,0,10);
            B(moby,0xBC)=1;
        } else if (B(moby,0xBC)==1) {
            if (IsPointInArenaPolygon(P(moby,0xB8),moby+0x10)) SetMobyState(moby,5,2);
            TurnMobyTowardTarget(moby,GetArenaCenterPoint(P(moby,0xB8)));
        }
        break;
    case 4:
        if (SetFirstPendingFlag(moby)) {
            SetAnimation(moby,6,0,10);
            U(moby,0x96)=0;
        }
        vec_scale_to_length(zero,moby+0xE0,F(vars,0x104)+F(vars,0x100));
        FastVecAdd(delta,moby+0x10,zero);
        clear=1;
        if (TestPointAgainstCollision(delta,5,moby,F(vars,0x100)) && D_L11_001C0D18 && H(D_L11_001C0D18,0xAA)==0xB3A /* Arachnoid */) clear=0;
        if (clear) {
            I(moby,0x98)=I(P(moby,0x24),0x10);
            SetMobyState(moby,5,2);
        }
        F(moby,0x18)+=0.1333333403f;
        break;
    case 5: break;
    case 6:
        if (B(moby,0x60)&2) SetMobyState(moby,7,-1);
        break;
    case 7:
        if (SetFirstPendingFlag(moby)) SetAnimation(moby,6,0,15);
        if (B(moby,0x42)==5 && distance>14.0f) {
            SetAnimation(moby,6,0,4);
            SetControllerSpeedLimits(moby,0.00444444455f,0.1333333403f,0.006981317885f,0.2094395459f);
        } else if (B(moby,0x42)==6 && distance<9.0f) {
            SetAnimation(moby,5,0,4);
            SetControllerSpeedLimits(moby,0.002222222276f,0.06666667014f,0.006981317885f,0.2094395459f);
        }
        if (H(vars,0x286)) {
            if (distance<3.0f && turn<0.01745329425f) {
                SetMobyState(moby,9,-1);
                SetAnimation(moby,3,4,3);
            } else FlyByDistance(moby,target,target,distance);
        } else {
            if (distance<3.0f && turn<0.01745329425f) {
                SetMobyState(moby,9,-1);
                SetAnimation(moby,3,4,3);
            } else if (distance>3.0f) {
                if (!AimAtGroupEntityInConeShort(moby,moby+0x10)) TurnTowardTargetAndStepMovement(moby,target,F(vars,0x274));
            } else StepMovementController(moby,moby+0x10,angle);
        }
        break;
    case 8:
        if (SetFirstPendingFlag(moby)) SetControllerSpeedLimits(moby,0.1388888955f,1.666666746f,0.00349065894f,0.1047197729f);
        if (B(moby,0x42)==7) {
            if (GetMobyAnimationValue(moby)<=14.0f) {
                if (H(vars,0x286)) AimAtTargetOffset(moby,target);
                else StepMovementController(moby,target,angle);
                TestHitAtBone(moby,0,1,0,1,0,0.4f,B(vars,0x34),1.0f);
            } else {
                SetControllerSpeedLimits(moby,0.05555555597f,0.03333333507f,0.00349065894f,0.1047197729f);
                vec_scale_to_length(delta,moby+0xC0,-4.0f);
                FastVecAdd(delta,moby+0x10,delta);
                I(vars,0x138)|=0x10;
                if (H(vars,0x286)) AimAtTargetOffset(moby,delta); else TurnMobyTowardTarget(moby,delta);
                I(vars,0x138)&=~0x10;
                TestHitAtBone(moby,0,1,0,1,0,0.4f,B(vars,0x34),1.0f);
            }
        }
        if (B(moby,0x60)&2) {
            if (gActiveAttackerRobot==moby) {
                SetAnimation(moby,2,0,10);
                SetMobyState(moby,6,-1);
            } else SetMobyState(moby,7,-1);
        }
        break;
    case 9:
        if (!H(vars,0x286)) StepMovementAtOwnPositionWithFactor(moby,angle);
        if (B(moby,0x60)&2) {
            SetAnimation(moby,7,4,3);
            SetMobyState(moby,8,-1);
        }
        break;
    case 10:
        flags=DispatchActionByKind(moby,vars+0x50);
        if (B(moby,0x42)==8) {
            if (!RandomIntBelow(30) || (flags&1)) {
                if (GetMobyAnimationValue(moby)<10.0f && H(vars,0x286) && !RandomIntBelow(2)) SetMobyState(moby,11,-1);
                else { SetMobyAnimTypeThree(moby,0,-1); ResetEnemyToIdle(moby); }
            }
        } else if (flags&2) {
            SetAnimation(moby,2,0,10);
            SetMobyState(moby,6,3);
        }
        break;
    case 11:
        if (SetFirstPendingFlag(moby)) {
            FastVecSub(vars+0x1A0,GetArenaCenterPoint(P(moby,0xB8)),moby+0x10);
            F(vars,0x1A8)=0;
            vec_scale_to_length(vars+0x1A0,vars+0x1A0,RandomFloatRange(3.0f,5.0f)*0.0166666675f);
            H(vars,0x286)=0;
            spin=(float *)(vars+0x260);
            for (i=0;i<3;i++) {
                spin[i]=RandomFloatRange(240.0f,720.0f)*0.0002908882452175021f;
                qcopy(matrix[i],moby+0xC0+i*16);
            }
            GetEulerAnglesFromMatrix(matrix,moby+0xF0);
            SetAnimation(moby,9,0,30);
            U(moby,0x34)&=0xEFFF;
        }
        F(vars,0x1A8)-=F(vars,0x12C);
        SetControlMotionAndStep(moby,vars+0x1A0);
        FastVecScale(vars+0x260,vars+0x260,0.98f);
        *(Quad *)zero=0;
        zero[2]=F(vars,0x30);
        COPY(delta,zero);
        RotateObjectAboutPoint(moby,delta,F(vars,0x260),F(vars,0x264),F(vars,0x268));
        euler_rotation_basis(moby+0xC0,moby+0xF0);
        if (F(moby,0x18)<F(GetArenaCenterPoint(P(moby,0xB8)),8)+5.0f || !RandomIntBelow(450) || U(moby,0x96)>=301) {
            SetMobyAnimTypeThree(moby,0,-1);
            ResetEnemyToIdle(moby);
        }
        break;
    }
    CountFramesAndDrawEnemyGlow(moby);
}
