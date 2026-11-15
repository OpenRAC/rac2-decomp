/* Barlow object state and movement update. The object pool entries are 0x100
 * bytes; the array declaration preserves the measured small-data and absolute
 * references to its base. Integer and FP arguments to func_002A7CA0 retain their
 * order within each EE register bank.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
#define INT(p,o) (*(int *)((char *)(p)+(o)))
#define FLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define HALF(p,o) (*(short *)((char *)(p)+(o)))
#define UHALF(p,o) (*(u16 *)((char *)(p)+(o)))
typedef struct { u8 pad0[0xAA]; s16 oclass; u8 padAC[0xF8 - 0xAC]; float rotz; u8 padFC[0x100 - 0xFC]; } Moby;
extern int D_L04_001C9C00[];
extern int D_001A79F0 __attribute__((sda));
extern char *D_L04_001B24DC[] __attribute__((sda));
extern float D_L04_001B1874 __attribute__((sda)), D_L04_001B1878 __attribute__((sda));
extern void func_L04_0044D0C0(char *);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern void func_002A7398(char *,int,int);
extern int func_00282948(int *);
extern int func_00282978(short *);
extern int func_002A77E0(int);
extern int func_002A7820(int,int);
extern float func_002A7878(float,float);
extern int func_00283CF0(float);
extern unsigned int func_002B1C20(void *,void *);
extern void func_002A6C58(void *,int,int);
extern void func_L01_003E9CF8(void *,int,int);
extern float func_002AA2E8(float *,float,float);
extern float func_002AE8C0(void *,void *,float,float);
extern float func_00283248(float,float);
extern float func_00283B98(float,float);
extern float func_002A7CA0(void *,float,float *,float,float,float);
extern float func_00282E80(void *,void *);
extern int func_002AEB60(char *,float);
extern int func_002E5CF8(int,int,char *);
extern int func_002A8D70(float,float,float,void *,int,int,int,int,int);
extern float func_00283180(float), func_00283198(float);
extern void func_00282CD8(void *,void *,void *);
extern int func_L04_0044D860(char *);
extern void func_L04_0044D428(char *);
extern void func_L04_0044D6A0(u8 *);
extern void func_0029F338(void *);

/* Per-frame update for the Gadgetron Hound of Cuddly Death (moby class 4022): picks between idling, wandering, turning and attacking, falls back if it drops too low, and runs the shared enemy helpers. */
void func_L04_0044C598(u8 *object)
{
    char *vars;
    u8 *other;
    union { Quad q; float f[4]; } movement, position;
    unsigned int flags;
    int kind, choice, state;
    float delay;
    if (D_L04_001C9C00[0]) return;
    vars=*(char **)(object+0x68);
    UpdateBarlowEnemyCommon(object);
    kind=(u8)object[0x95];
    switch(kind) {
    case 0:
        if(INT(vars,0x328)==-1 || INT(vars,0x32c)==-1 || (other=(u8 *)gMobyPool_L04[0]+INT(vars,0x32c)*256)==object ||
            !other || other[0x20]==254 || other[0x20]==253) {
            FastFloatHelperD((int *)(vars+0x31c));
            if(INT(vars,0x254)==1) {
                if(INT(vars,0x328)!=-1) {
                    Moby *pool=(Moby *)gMobyPool_L04[0];
                    UHALF(object,0x34)&=0xffbe;
                    INT(object,0x98)=INT(*(char **)(object+0x24),0x10);
                    if(pool[INT(vars,0x328)].oclass==0x929 /* moby class 2345 */) {
                        SetMobyState(object,7,3); StartAnimationImmediate(object,7,0);
                        FLOAT(object,0xf8)=FLOAT(gMobyPool_L04[0]+INT(vars,0x328)*256,0xf8);
                        INT(vars,0x328)=-1;
                        goto heightCheck;
                    }
                    INT(vars,0x328)=-1;
                    SetMobyState(object,4,2);
                    if(object[0x43]!=7) StartAnimationBlended(object,7,0,14);
                } else {
                    if(RandomIntBelow(9)==0) {
                        if(RandomIntBelow(2)!=0) {
                            SetMobyState(object,3,2);
                            if(object[0x43]!=3) StartAnimationBlended(object,3,0,14);
                            if(RandomIntBelow(2)==1 && object[0x43]!=4) StartAnimationBlended(object,4,0,14);
                        } else {
                            SetMobyState(object,4,2);
                            if(object[0x43]!=7) StartAnimationBlended(object,7,0,14);
                        }
                    }
                }
                UHALF(object,0x34)&=0xffbe;
                INT(object,0x98)=INT(*(char **)(object+0x24),0x10);
            } else if(HALF(vars,0x306)!=0) {
                SetMobyState(object,2,1);
                HALF(vars,0x306)=0;
                INT(vars,0x2fc)=FloatToInt(RandomFloatRange(FLOAT(vars,0x2f8)*0.8f,FLOAT(vars,0x2f8)*1.2f)*60.0f);
                HALF(vars,0x300)=0;
            }
        }

        break;
    case 1:
        if(INT(vars,0x254)==1) {
            SetMobyState(object,4,2);
            if(object[0x43]!=7) StartAnimationBlended(object,7,0,14);
        } else if(INT(vars,0x2fc)==0) {
            SetMobyState(object,1,0);
            if(object[0x43]!=2) StartAnimationBlended(object,2,0,12);
        }

        break;
    case 2:
        if(INT(vars,0x254)!=1 && RandomIntBelow(19)==0) {
            SetMobyState(object,2,1);
            INT(vars,0x2fc)=FloatToInt(RandomFloatRange(FLOAT(vars,0x2f8)*0.8f,FLOAT(vars,0x2f8)*1.2f)*60.0f);
            HALF(vars,0x300)=0;
        }

        break;
    case 3:
        if(object[0x20]!=7) {
        flags=DispatchActionByKind(object,vars+0x60);
        if(flags&1) { HALF(vars,0x98)=0; SetDeathBits(object,0,3); QueueMobyForGlowEffect(object,0,0); return; }
        if(flags&2) {
            if(INT(vars,0x254)==1) {
                SetMobyState(object,4,2);
                if(object[0x43]!=7) StartAnimationBlended(object,7,0,14);
            } else {
                SetMobyState(object,2,1);
                INT(vars,0x2fc)=FloatToInt(RandomFloatRange(FLOAT(vars,0x2f8)*0.8f,FLOAT(vars,0x2f8)*1.2f)*60.0f);
                HALF(vars,0x300)=RandomIntRange(120,700);
            }
        }

        }
        break;
    }
heightCheck:
    if(FLOAT(object,0x18)-FLOAT(vars,0x2e8)>10.0f || FLOAT(object,0x18)<10.0f) {
        HALF(vars,0x98)=0; qzero(object+0xf0);
        SetDeathBits(object,0,3); MarkMobySpawned(object); return;
    }
    if(FLOAT(object,0x18)<75.0f && gCurrentMapIndex==11) {
        HALF(vars,0x98)=0; qzero(object+0xf0);
        SetDeathBits(object,0,3); MarkMobySpawned(object); return;
    }
    state=(u8)object[0x20];
    switch(state) {
    case 1:
        FastDecTimer((short *)(vars+0x300));
        if(object[0x43]==0 && HALF(vars,0x300)) StartAnimationBlended(object,7,0,14);
        if (HALF(vars,0x300)>=21)
            ApproachValue((float *)(vars+0x124),D_L04_001B1878*0.01666666753590107f,0.0019444444915279746f);
        else
            ApproachValue((float *)(vars+0x124),0.0f,0.0019444444915279746f);
        if(object[0x43]==7) {
            FLOAT(object,0x48)=0.8f;
            if(HALF(vars,0x300)==0) {
                if(object[0x43]!=RandomIntBelow(3)) {
                    choice=RandomIntBelow(3)+(0);
                    StartAnimationBlended(object,choice,0,12);
                }
            }
            WanderAroundHomePoint(object,vars+0x110,0.35f,0.25f);
        } else if(((u8)object[0x43]<=2) && (object[0x60]&2)) {
            HALF(vars,0x300)=RandomIntRange(120,500);
            if(object[0x43]!=7) StartAnimationBlended(object,7,0,12);
        }
        break;
    case 2:
        FastDecTimer((short *)(vars+0x300));
        if(object[0x43]==0 && HALF(vars,0x300)) StartAnimationBlended(object,7,0,14);
        if (HALF(vars,0x300)>=21)
            ApproachValue((float *)(vars+0x124),D_L04_001B1878*0.01666666753590107f,0.0019444444915279746f);
        else
            ApproachValue((float *)(vars+0x124),0.0f,0.0019444444915279746f);
        if(object[0x43]==7) {
            FLOAT(object,0x48)=0.8f;
            if(HALF(vars,0x300)==0) {
                if(object[0x43]!=RandomIntBelow(2)+5) {
                    choice=RandomIntBelow(2)+(5);
                    StartAnimationBlended(object,choice,0,12);
                }
            }
            WanderAroundHomePoint(object,vars+0x110,0.35f,0.25f);
        } else if(((u8)(object[0x43]-5)<2) && (object[0x60]&2)) {
            HALF(vars,0x300)=RandomIntRange(120,500);
            if(object[0x43]!=7) StartAnimationBlended(object,7,0,12);
        }
        FLOAT(object,0x48)=1.0f;
        break;
    case 4:
        FLOAT(object,0x48)=1.0f;
        if(vec_distance_xy(object+0x10,vars+0x240)<=D_L04_001B1874) {
            SetMobyState(object,5,2);
            if(object[0x43]!=8) StartAnimationBlended(object,8,2,6);
            FLOAT(vars,0x314)=0.0f;
        } else if(FastFloatHelperD((int *)(vars+0x318))) {
            delay=RandomFloatRange(0.2617994248867035f,0.523598849773407f);
            if(RandomIntBelow(2)==0) delay=-delay;
            FLOAT(vars,0x314)=delay;
            INT(vars,0x318)=RandomIntRange(45,60);
        }
        break;
    case 5:
        if(object[0x42]!=8) break;
        if(IsValueWithinStepOfThreshold(object,8.0f)) PlayMobySound(3,0,object);
        if(object[0x42]!=8) break;
        if(IsValueWithinStepOfThreshold(object,10.0f)) {
            TestHitAtBone(0.75f,FLOAT(vars,0x330),1.0f,object,0,0x4000001,0,1,0);
            break;
        }
        if(object[0x42]!=8) break;
        if((object[0x60]&2) && vec_distance_xy(object+0x10,vars+0x240)>D_L04_001B1874) {
            SetMobyState(object,4,2);
            if(object[0x43]!=7) StartAnimationBlended(object,7,0,6);
        }
        break;
    case 7:
        movement.f[0]=FastSinOrCosA(FLOAT(object,0xf8))*0.01666666753590107f*(FLOAT(vars,0x30c)+FLOAT(vars,0x30c));
        movement.f[1]=FastSinOrCosB(FLOAT(object,0xf8))*0.01666666753590107f*(FLOAT(vars,0x30c)+FLOAT(vars,0x30c));
        movement.f[2]=0.0f;
        add_vectors(&position,object+0x10,&movement);
        if(vec_distance_xy(object+0x10,vars+0x2e0)>6.0f) SetMobyState(object,4,2);
        break;
    case 3:
        delay=FastMatrixHelperA(FLOAT(vars,0x240)-FLOAT(object,0x10),FLOAT(vars,0x244)-FLOAT(object,0x14));
        delay=FastAddRotations(delay,FLOAT(vars,0x314));
        MobySpringTurn(object,delay,(float *)(vars+0x310),0.05f,0.3f,0.10471977293491364f);
        if(object[0x60]&2) {
            SetMobyState(object,4,-1);
            if(object[0x43]!=7) StartAnimationBlended(object,7,0,15);
        }
        break;
    case 8:
        if(PullObjectTowardHero(object)) {
            SetDeathBits(object,0,3); MarkMobySpawned(object); return;
        }
        break;
    }
    if((unsigned)((u8)object[0x20]-7)>1) UpdateBarlowEnemyMovement(object);
    TurnEnemyTowardHero((u8 *)object);
    return;
}
