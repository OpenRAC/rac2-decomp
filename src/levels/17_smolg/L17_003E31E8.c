/*
 * Smolg level object update (USA v1.01, level 17 only): state machine on the object's
 * state byte (0x20) with a second dispatch on its mode byte (0x95).  In its own unit
 * because its symbol declarations differ from those in L17_003C7C70.c.
 */

#include "common.h"

#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u16 *)((char *)(p)+(o)))
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))

extern int D_L17_001CA140[];
extern int D_L17_001A8F00 MACRO_ADDR;
extern int D_001A79F0 __attribute__((sda));
extern char *D_L17_001B2C1C[] __attribute__((sda));
extern float D_L17_001B0CAC SDATA(D_L17_001B0CAC);
extern float D_L17_001B0CB0 SDATA(D_L17_001B0CB0);
extern float D_L17_001B0CB4 SDATA(D_L17_001B0CB4);
typedef struct { char pad[0x80]; float x,y; } L17HeroRecord;
extern L17HeroRecord D_00189E20;
extern void func_L17_003E41A8(char *);
extern void func_L17_003C7250(char *,char *);
extern int func_L17_003C5B68(char *);
extern void func_L17_003C5AF8(char *);
extern void func_L17_003E3148(char *);
extern void func_L17_003E4560(char *);
extern void func_L17_003E47E8(char *);
extern int func_L17_003E48E0(char *);
extern int func_00282948(int *);
extern int func_00282978(short *);
extern void func_002A7750(char *,int,int);
extern void func_002A7470(char *,int,int,int);
extern void func_002A7398(char *,int,int);
extern int func_002A77E0(int);
extern int func_002A7820(int,int);
extern float func_002A7878(float,float);
extern int func_00283CF0(float);
extern int func_002B3890(char *);
extern int func_002B1C20(char *,void *);
extern void func_002A6C58(char *,int,int);
extern void func_L01_003E9CF8(char *,int,int);
extern void func_0029F338(char *);
extern void func_002AA2E8(float *,float,float);
extern void func_002AE8C0(char *,void *,float,float);
extern float func_00283248(float,float);
extern void func_002AA800(float *,int,float,float);
extern int func_002B3868(char *);
extern float func_00282E80(void *,void *);
extern int func_002AEB60(char *,float);
extern void func_002E5CF8(int,int,char *);
extern int func_002A8C28(char *,float,void *,int,float,float,int,int,int);
extern void func_002B60B0(char *,float,float,float,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_L02_00331440(char *,void *,int,float,float,float);
extern float func_00283180(float),func_00283198(float);
extern void func_00282CD8(void *,void *,void *);
extern float func_00283B98(float,float);
extern void func_002A7CA0(char *,float,float *,float,float,float);

/* Updates a Grulch (moby class 2952): it wanders, notices the player, walks up, attacks and
   is removed when it dies or falls out of the level. */
void func_L17_003E31E8(char *object)
{
    float movement[4], position[4];
    char *vars, *other;
    int flags;
    float angle;
    if (D_L17_001CA140[0]) return;
    vars=P(object,0x68);
    if (D_L17_001A8F00==2) {
        if (!B(object,0x31)) return;
        I(vars,0x454)=1;
        I(object,0x98)=0;
        U(object,0x34)=(U(object,0x34)|0x41)&0xEFFF;
        return;
    }
    if (I(vars,0x454)) {
        U(object,0x34)=(U(object,0x34)&0xFFBE)|0x1000;
        I(object,0x98)=I(P(object,0x24),0x10);
        I(vars,0x454)=0;
    }
    InitGrulchStateAndCheckHits(object);
    FastFloatHelperD((int *)(vars+0x440));
    if (I(vars,0x450)!=-1) {
        other=(char *)((I(vars,0x450)<<8)+(u32)gMobyPool_L17[0]);
        if (H(other,0xAA)==0x929 /* moby class 2345 */) SetPlatformPathIndex(other,object);
    }
    switch(B(object,0x95)) {
    case 0:
        if (I(vars,0x428)==-1 || I(vars,0x42C)==-1 ||
            gMobyPool_L17[0]+(I(vars,0x42C)<<8)==object ||
            !(gMobyPool_L17[0]+(I(vars,0x42C)<<8)) ||
            B(gMobyPool_L17[0]+(I(vars,0x42C)<<8),0x20)==0xFE ||
            B(gMobyPool_L17[0]+(I(vars,0x42C)<<8),0x20)==0xFD ||
            !CanRidePlatformStart(gMobyPool_L17[0]+(I(vars,0x428)<<8))) {
            FastFloatHelperD((int *)(vars+0x41C));
            if(H(vars,0x404)==1 && I(vars,0x440)==0) {
                ActivateGroupMembers(object);
                if(I(vars,0x428)!=-1) {
                    if(!CanRidePlatformStart(gMobyPool_L17[0]+(I(vars,0x428)<<8))) break;
                    StartRidePlatform(gMobyPool_L17[0]+(I(vars,0x428)<<8));
                    { char *entityBase = gMobyPool_L17[0];
                    U(object,0x34)&=0xFFBE;
                    I(object,0x98)=I(P(object,0x24),0x10);
                    if(H((I(vars,0x428)<<8)+(u32)entityBase,0xAA)==0x929) {
                        SetMobyState(object,8,3);
                        StartAnimationImmediate(object,9,0);
                        F(object,0xF8)=F((char *)((I(vars,0x428)<<8)+(u32)gMobyPool_L17[0]),0xF8);
                        I(vars,0x428)=-1;
                    } else {
                        I(vars,0x428)=-1;
                        SetMobyState(object,10,2);
                        if(B(object,0x43)!=2) StartAnimationBlended(object,2,0,14);
                        goto restoreCollision;
                    }
                    }
                } else {
                    SetMobyState(object,10,2);
                    if(B(object,0x43)!=2) StartAnimationBlended(object,2,0,14);
restoreCollision:
                    U(object,0x34)&=0xFFBE;
                    I(object,0x98)=I(P(object,0x24),0x10);
                }
            } else if(H(vars,0x406)) {
                SetMobyState(object,2,1);
                H(vars,0x406)=0;
                I(vars,0x3FC)=FloatToInt(RandomFloatRange(F(vars,0x3F8)*0.8f,F(vars,0x3F8)*1.2f)*60.0f);
                H(vars,0x400)=0;
            }
        }
        break;
    case 1:
        if(H(vars,0x404)==1 && I(vars,0x440)==0) {
            ActivateGroupMembers(object);
            SetMobyState(object,10,2);
            if(B(object,0x43)!=2) StartAnimationBlended(object,2,0,14);
        } else if(I(vars,0x3FC)==0) {
            SetMobyState(object,1,0);
            if(B(object,0x43)!=0) StartAnimationBlended(object,0,0,12);
        }
        break;
    case 2:
        if(H(vars,0x404)!=1 && RandomIntBelow(19)==0) {
            SetMobyState(object,2,1);
            I(vars,0x3FC)=FloatToInt(RandomFloatRange(F(vars,0x3F8)*0.8f,F(vars,0x3F8)*1.2f)*60.0f);
            H(vars,0x400)=0;
        }
        break;
    case 3:
        if(SetSecondPendingFlag(object) && F(object,0x48)<0.0f) F(object,0x48)=1.0f;
        if(B(object,0x20)!=8) {
            flags=DispatchActionByKind(object,vars+0x60);
            if(flags&1) {
                H(vars,0x98)=0;
                SetDeathBits(object,0,3);
                QueueMobyForGlowEffect(object,0,0);
                return;
            }
            if(flags&2) {
                if(H(vars,0x404)==1 && I(vars,0x440)==0) {
                    ActivateGroupMembers(object);
                    SetMobyState(object,4,2);
                    if(B(object,0x43)!=9) StartAnimationBlended(object,9,0,14);
                } else {
                    SetMobyState(object,2,1);
                    I(vars,0x3FC)=FloatToInt(RandomFloatRange(F(vars,0x3F8)*0.8f,F(vars,0x3F8)*1.2f)*60.0f);
                    H(vars,0x400)=RandomIntRange(120,700);
                }
            }
        }
        break;
    }
    if(F(object,0x18)-F(vars,0x3D8)>10.0f || F(object,0x18)<10.0f) {
        H(vars,0x98)=0;
        qzero(object+0xF0);
        SetDeathBits(object,0,3);
        MarkMobySpawned(object);
        return;
    }
    if(F(object,0x18)<75.0f && gCurrentMapIndex==11) {
        H(vars,0x98)=0;
        qzero(object+0xF0);
        SetDeathBits(object,0,3);
        MarkMobySpawned(object);
        return;
    }
    switch(B(object,0x20)) {
    case 1:
        FastDecTimer((short *)(vars+0x400));
        if(B(object,0x43)==0 && H(vars,0x400)!=0) {
            if(B(object,0x43)!=9) StartAnimationBlended(object,9,0,14);
        }
        if(H(vars,0x400)>20) ApproachValue((float *)(vars+0x124),D_L17_001B0CB0*(1.0f/60.0f),0.0019444445f);
        else ApproachValue((float *)(vars+0x124),0.0f,0.0019444445f);
        if(B(object,0x43)==9) {
            F(object,0x48)=0.8f;
            if(H(vars,0x400)==0) {
                if(B(object,0x43)!=RandomIntBelow(2)) StartAnimationBlended(object,RandomIntBelow(2),0,12);
            }
            WanderAroundHomePoint(object,vars+0x110,0.35f,0.25f);
        } else if((B(object,0x43)==0 || B(object,0x43)==1) && (B(object,0x60)&2)) {
            H(vars,0x400)=RandomIntRange(120,500);
            if(B(object,0x43)!=9) StartAnimationBlended(object,9,0,12);
        }
        break;
    case 2:
        FastDecTimer((short *)(vars+0x400));
        if(B(object,0x43)!=9 && B(object,0x43)!=5 && B(object,0x43)!=4) {
            if(B(object,0x43)!=9) StartAnimationBlended(object,9,0,14);
        }
        if(H(vars,0x400)>20) ApproachValue((float *)(vars+0x124),D_L17_001B0CB4*(1.0f/60.0f),0.0019444445f);
        else ApproachValue((float *)(vars+0x124),0.0f,0.0019444445f);
        if(B(object,0x43)==9) {
            if(H(vars,0x400)==0) {
                StartAnimationBlended(object,5,0,12);
                if(RandomIntBelow(2)==1 && B(object,0x43)!=4) StartAnimationBlended(object,4,0,12);
            }
            WanderAroundHomePoint(object,vars+0x110,0.35f,0.25f);
        } else if((B(object,0x43)==4 || B(object,0x43)==5) && (B(object,0x60)&2)) {
            H(vars,0x400)=RandomIntRange(120,200);
            if(B(object,0x43)!=9) StartAnimationBlended(object,9,0,12);
        }
        goto restoreAnimationSpeed;
    case 10:
        if(B(object,0x60)&2) {
            SetMobyState(object,4,-1);
            if(B(object,0x43)!=9) StartAnimationBlended(object,9,0,14);
        }
        StepAngleTowardTarget((float *)(object+0xF8),0,FastMatrixHelperA(gHeroState.x-F(object,0x10),gHeroState.y-F(object,0x14)),0.10471977f);
        break;
    case 4:
        if(SetFirstPendingFlag(object)) I(vars,0x418)=RandomIntRange(80,100);
        F(object,0x48)=1.0f;
        if(vec_distance_xy(object+0x10,P(vars,0x408)+0x10)<=D_L17_001B0CAC) {
            SetMobyState(object,5,2);
            if(B(object,0x43)!=6) StartAnimationBlended(object,6,2,6);
            F(vars,0x414)=0;
        } else if(FastFloatHelperD((int *)(vars+0x418))) {
            /* The separate magnitude lets angle avoid crossing the side call, so its store
               schedules after the arguments of the timer call below. */
            {
                float magnitude=RandomFloatRange(0.26179942f,0.52359884f);
                int side=RandomIntBelow(2);
                angle=magnitude;
                if(side==0) angle=-angle;
                F(vars,0x414)=angle;
            }
            I(vars,0x418)=RandomIntRange(150,200);
            SetMobyState(object,5,2);
            if(B(object,0x43)!=6) StartAnimationBlended(object,6,2,6);
        }
        break;
    case 5:
        if(B(object,0x42)==6) {
            if(IsValueWithinStepOfThreshold(object,8.0f)) PlayMobySound(3,0,object);
            if(B(object,0x42)==6) {
                if(IsValueWithinStepOfThreshold(object,10.0f)) {
                    if(SweepCollisionFromObject(object,1.0f,object+0x10,0x4000001,F(vars,0x430),1.0f,0,1,0)>0) I(vars,0x448)=1;
                    else I(vars,0x448)=0;
                } else if(B(object,0x42)==6 && ((B(object,0x60)&2) || IsValueWithinStepOfThreshold(object,11.0f))) {
                    if(vec_distance_xy(object+0x10,P(vars,0x408)+0x10)>D_L17_001B0CAC) {
                        if((vec_distance_xy(object+0x10,P(vars,0x408)+0x10)==0.0f ? 1.0f : 0.0f)>D_L17_001B0CAC) {
                            if(RandomIntRange(0,7)>0) {
                                SetMobyState(object,11,2);
                                if(B(object,0x43)!=7) StartAnimationBlended(object,7,0,14);
                            }
                        } else {
                            SetMobyState(object,6,2);
                            if(B(object,0x43)!=9) StartAnimationBlended(object,9,0,14);
                        }
                    }
                }
            }
        }
        break;
    case 11:
        if(B(object,0x60)&2) {
            SetMobyState(object,4,2);
            if(B(object,0x43)!=9) StartAnimationBlended(object,9,0,0);
        }
        break;
    case 6:
        SetControllerSpeedLimits(object,0.005f,0.10000001f,0.017453294f,1.0471977f);
        if(SetFirstPendingFlag(object)) {
            FastVecSub(vars+0x3E0,object+0x10,P(vars,0x408)+0x10);
            F(vars,0x3E8)=0;
            vec_scale_to_length(vars+0x3E0,vars+0x3E0,10.0f);
            FastVecAdd(vars+0x3E0,vars+0x3E0,object+0x10);
            F(object,0x48)=-1.0f;
        }
        MoveToTargetWithTempLimits(object,vars+0x3E0,16,FastMatrixHelperA(F(vars,0x3E0)-F(object,0x10),F(vars,0x3E4)-F(object,0x14)),-1.0f,-1.0f);
        if(B(object,0x42)==2 && (B(object,0x60)&2)) {
            if(B(object,0x43)!=9) StartAnimationBlended(object,9,0,10);
            F(object,0x48)=1.0f;
        }
        if(B(object,0x42)==9 && (B(object,0x60)&2)) {
            if(I(vars,0x448)==0) {
                SetMobyState(object,4,2);
                if(B(object,0x43)!=9) StartAnimationBlended(object,9,0,6);
            } else {
                SetMobyState(object,11,2);
                if(B(object,0x43)!=7) StartAnimationBlended(object,7,0,14);
                I(vars,0x448)=0;
            }
restoreAnimationSpeed:
            F(object,0x48)=1.0f;
        }
        break;
    case 8:
        movement[0]=FastSinOrCosA(F(object,0xF8))*(1.0f/60.0f)*(F(vars,0x40C)+F(vars,0x40C));
        movement[1]=FastSinOrCosB(F(object,0xF8))*(1.0f/60.0f)*(F(vars,0x40C)+F(vars,0x40C));
        movement[2]=0;
        add_vectors(position,object+0x10,movement);
        if(vec_distance_xy(object+0x10,vars+0x3D0)>6.0f) SetMobyState(object,4,2);
        break;
    case 3:
        angle=FastAddRotations(FastMatrixHelperA(F(P(vars,0x408),0x10)-F(object,0x10),F(P(vars,0x408),0x14)-F(object,0x14)),F(vars,0x414));
        MobySpringTurn(object,angle,(float *)(vars+0x410),0.05f,0.3f,0.10471977f);
        if(B(object,0x60)&2) {
            SetMobyState(object,4,-1);
            if(B(object,0x43)!=9) StartAnimationBlended(object,9,0,15);
        }
        break;
    case 9:
        if(UpdateCreaturePulledIn(object)) {
            SetDeathBits(object,0,3);
            MarkMobySpawned(object);
            return;
        }
        break;
    }
    if(B(object,0x20)!=8 && B(object,0x20)!=9 && B(object,0x20)!=6) TurnToTargetAndApplyGravity(object);
    UpdateCreatureAnimation(object);
}
