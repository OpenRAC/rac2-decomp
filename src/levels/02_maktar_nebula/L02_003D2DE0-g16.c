#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef struct { u8 prefix[0x2C0]; float waypoint[4]; float previousPosition[4]; } WaypointView;
/* Partial current dispatch context; the payload's full extent is not inferred. */
typedef struct {
    u8 reserved_00[0x18]; u8 enabled, count, kind; u8 reserved_1b[0x65]; u8 payload[1];
} DispatchContext;
typedef unsigned long DispatchFlags;
typedef struct { u8 prefix[0x160]; float amount; int reserved164; int kind; int detail; } EffectTuning;
extern EffectTuning D_L02_001BA3C0;
#define EFFECT (&D_L02_001BA3C0)
extern float D_L02_001B3F58 __attribute__((sda));
extern float D_L02_001B01B0[4];
extern float arenaPosition[4] SDATA(D_L02_001B01B0);
extern float D_L02_001B01C0[4] __attribute__((sda));
extern float D_L02_001B01D0[4] __attribute__((sda));
extern int D_L02_001B01E0 __attribute__((sda));
extern int D_L02_001A903C;
extern unsigned char D_001A7A60[] MACRO_ADDR;
typedef struct { u8 prefix[0x80]; float position[4]; u8 reserved90[0x240C]; char *lockTarget; } HeroPositionView;
extern HeroPositionView D_00189E20;
extern void func_L02_003D4308(char *);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00283248(float, float);
extern float func_0029F530(char *);
extern int func_002B3890(u8 *);
extern int func_002B3868(u8 *);
extern void func_002B60B0(u8 *, float, float, float, float);
extern void func_L02_003D5B90(char *);
extern int func_L00_0042AB40(char *);
extern void func_002A7470(char *, int, int, int);
extern void func_002A7750(u8 *, s32, s32);
extern void func_L02_003D4ED0(char *);
extern void func_L02_003D4FD0(char *, Quadword *, float, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void func_L02_003D4A48(char *);
extern void func_L02_003DB880(char *);
extern void func_L02_003FC020(char *, char *);
/* Keeps func_002B50E0's int result in v0. */
extern int func_002B5258(char *);
extern void func_L02_003D4AF0(char *, int);
extern float func_L02_002F21C0(void *, void *);
extern int func_L01_00321178(char *, char *);
extern float func_00283C80(float, float);
/* Retail passes self at every site; the leaf does not read it. */
extern void func_L02_003D69F0(char *);
extern void func_L02_003D5118(char *, int);
extern void func_L02_003D6690(char *, int);
extern int func_L02_003D4D00(char *);
extern int func_L02_003D4A60(char *);
extern DispatchFlags func_002B1C20(void *, DispatchContext *);
/* Extra caller slots are retained at this legacy entry; its leaf ignores them. */
extern void func_L02_003FC248(void *, int, int);
extern int func_002E5E58(int, int, void *);
extern void func_002B0A18(int, int);
extern void func_L01_003E9CF8(char *, int, void (*)(char *));
extern void func_L02_003D4900(char *);
extern void func_002B5278(u8 *, float);
extern void func_L02_003D4E00(char *);
extern int func_00282978(short *);
extern int func_L02_003D4D68(char *);
extern int func_L02_003D52A8(char *);
extern void func_00282C88(Quadword *);
extern void func_L02_003D5660(char *, int);
extern int func_L02_003D5748(char *, int);
extern void func_L02_003D46B8(char *);
#define B(o) (*(u8 *)(state+(o)))
#define H(o) (*(short *)(state+(o)))
#define W(o) (*(int *)(state+(o)))
#define F(o) (*(float *)(state+(o)))
#define P(o) (*(char **)(state+(o)))
#define SET_MODE(m,r) func_002A7750((u8 *)self,(m),(r))

/* Drive the large Maktar sentry's locomotion and paired throw sequences. */
/* Per-frame update handler of the Chainblade moby (class 2552). */
void func_L02_003D2DE0(char *self)
{
    char *state=*(char **)(self+0x68);
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float distance, yaw, frame, value, scale;
    int result;
    DispatchFlags events, animFlags;
    unsigned char flags;

    D_L02_001B3F58=0.7853981633974483f;
    HandleChainbladeHits(self);
    qcopy(target, P(0x30C)+0x10);
    distance=vec_distance_xy(self+0x10,target);
    yaw=FastMatrixHelperA(target[0]-*(float *)(self+0x10),target[1]-*(float *)(self+0x14));
    frame=GetMobyAnimationValue(self);
    flags=*(u8 *)(self+0x95);
    switch (flags) {
    case 1:
        if (SetSecondPendingFlag((u8 *)self)) {
            B(0xD6)=0; B(0x70)=8; W(0xA8)=3; W(0x148)&=~4; F(0x30)=3.0f;
            SetControllerSpeedLimits((u8 *)self,0.0044444446f,0.13333334f,0.008435759f,0.20943955f);
            EndChainThrow(self); W(0x14C)=CameraHookReturnMinusOne(*(char **)(self+0xB8));
        }
    break;
    case 2:
        if (SetSecondPendingFlag((u8 *)self)) {
            B(0x70)=18; W(0xA8)=4; B(0xD6)=1; W(0x148)|=4;
            F(0x30)=5.0f; W(0x14C)=-1;
        }
        if (*(float *)(self+0x18)<D_L02_001B01B0[2]-1.0f)
            *(float *)(self+0x18)=D_L02_001B01B0[2]-1.0f;
    break;
    case 3:
    case 4:
        if (SetSecondPendingFlag((u8 *)self)) EndChainThrow(self);
    }
    switch (*(u8 *)(self+0x20)) {
    case 1: return;
    case 2:
        if (SetFirstPendingFlag((u8 *)self)) {
            D_L02_001B01E0=1; *(unsigned short *)(self+0x96)=0;
            if (*(u8 *)(self+0x43)) StartAnimationBlended(self,0,0,10);
        }
        if (*(unsigned short *)(self+0x96)>120) {
            if (*(u8 *)(self+0x42)!=9) {
                if (*(u8 *)(self+0x43)!=9) StartAnimationBlended(self,9,0,10);
                *(u8 *)(self+0x95)=2; qcopy(state+0x2D0, self+0x10);
                qcopy(((WaypointView *)state)->waypoint, D_L02_001B01D0);
            } else {
                StepChainbladeFollowPoint(self); *(Quadword *)position=*(Quadword *)(state+0x2D0);
                SteerChainbladeToward(self,(Quadword *)position,
                    FastMatrixHelperA(target[0]-*(float *)(self+0x10),target[1]-*(float *)(self+0x14)),0.0f);
            }
        }
        if (vec_distance_xy(self+0x10,arenaPosition)<18.0f) { H(0x32E)=0; SET_MODE(20,2); }
        break;
    case 3:
        if (SetFirstPendingFlag((u8 *)self)) {
            if (*(u8 *)(self+0x43)!=9) StartAnimationBlended(self,9,0,10);
            qcopy(state+0x2D0, self+0x10);
            value=RandomFloatRange(20.0f,40.0f);
            scale=0.017453294f;
            value*=scale;
            if (RandomIntBelow(2)) value=-value;
            F(0x308)=value; qcopy(((WaypointView *)state)->waypoint, D_L02_001B01C0);
            ClearChainbladePhaseFlag(self); AdvanceDamageStage(P(0x310));
            SetCurrentArenaBoss(*(char **)(self+0xB8),P(0x310));
        }
        StepChainbladeFollowPoint(self); *(Quadword *)position=*(Quadword *)(state+0x2D0);
        SteerChainbladeToward(self,(Quadword *)position,
            FastMatrixHelperA(gHeroState.position[0]-*(float *)(self+0x10),gHeroState.position[1]-*(float *)(self+0x14)),0.0f);
        if (fast_vec_dist(self+0x10,((WaypointView *)state)->waypoint)<0.5f) SET_MODE(4,1);
        break;
    case 4:
        if (SetFirstPendingFlag((u8 *)self) && *(u8 *)(self+0x43)) StartAnimationBlended(self,0,0,15);
        StepMovementAtOwnPosition(self);
        if (H(0x318)) SET_MODE(2,1);
        break;
    case 6:
        if (SetFirstPendingFlag((u8 *)self) && *(u8 *)(self+0x43)!=1) StartAnimationBlended(self,1,0,10);
        if (!RandomIntBelow(400)) PickChainbladeIdleAnimation(self,-1);
        if (DistanceSquaredXY(target,arenaPosition)<529.0f)
            TurnMobyTowardTarget(self,(char *)target);
        else PickChainbladeIdleAnimation(self,1);
        if ((*(u8 *)(self+0x42)==1 && frame>1.0f && frame<3.0f) || (frame>16.0f && frame<18.0f)) {
            EFFECT->amount=0.05f; EFFECT->kind=25; EFFECT->detail=0;
        }
        if (distance<9.0f && FastDiffRots(yaw,*(float *)(self+0xF8))<0.087266475f
                && frame>3.0f && frame<15.0f) SET_MODE(7,1);
        break;
    case 7:
        if (SetFirstPendingFlag((u8 *)self)) {
            if (*(u8 *)(self+0x43)!=2) StartAnimationBlended(self,2,0,10);
            ResetBladeTrail(self); *(u8 *)(self+0xBC)=0;
        }
        if (*(u8 *)(self+0x42)==2 && frame>19.0f && frame<23.0f) {
            StartBladeSwingHit(self,0); RecordBladeTrailSample(self,0);
        } else if (*(u8 *)(self+0xBC)==0 && *(u8 *)(self+0x42)==2 && frame>23.0f) {
            ResetBladeTrail(self); *(u8 *)(self+0xBC)=1;
        } else if (*(u8 *)(self+0x42)==2 && frame>32.0f && frame<36.0f) {
            StartBladeSwingHit(self,1); RecordBladeTrailSample(self,1);
        } else if (*(u8 *)(self+0xBC)==1 && *(u8 *)(self+0x42)==2 && frame>36.0f) {
            ResetBladeTrail(self); *(u8 *)(self+0xBC)=2;
        }
        if (*(u8 *)(self+0x60)&2) {
            if (ShouldChainbladeTakeOff(self) || IsHelperReadyAtHealthPhase(self)) SET_MODE(19,1); else SET_MODE(6,1);
            if (!RandomIntBelow(3) || gHeroState.lockTarget==self)
                PickChainbladeIdleAnimation(self,gHeroState.lockTarget==self ? 0 : -1);
        }
        break;
    case 8:
        qcopy(position,self+0x10);
        if (F(0x20)>0.0f) {
            events=DispatchActionByKind(self,(void *)(state+0x60));
            if ((events&2)==2) if (ShouldChainbladeTakeOff(self) || IsHelperReadyAtHealthPhase(self)) SET_MODE(19,1); else SET_MODE(6,1);
        } else if (frame>95.0f && frame<97.0f) {
            EFFECT->amount=0.4f; EFFECT->kind=25; EFFECT->detail=0;
        } else if (frame>110.0f) SET_MODE(9,-1);
        if (vec_distance_xy(self+0x10,arenaPosition)>18.0f)
            qcopy(self+0x10, position);
        break;
    case 9:
        if (SetFirstPendingFlag((u8 *)self)) {
            *(int *)(self+0x48)=0; *(short *)(self+0x96)=0;
            SetMobyAnimTypeThree(self,0,-1); *(int *)(self+0x98)=*(int *)(*(char **)(self+0x24)+0x10);
        }
        if (*(unsigned short *)(self+0x96)>60) {
            int storyActive = D_L02_001B01E0;
            *(float *)(self+0x48)=1.0f;
            if (storyActive && !D_001A7A60[1]) {
                D_001A7A60[1]=1; PlaySoundFromGlobalBank(1,0,0); SetEntryValueByIndex(0x1233,-1); D_L02_001A903C=1;
            }
            QueueMobyForGlowEffect(self,0,ResetChainbladeToIdle);
            if (P(0x310) && (u8)P(0x310)[0x20]!=254 && (u8)P(0x310)[0x20]!=253 && (u8)P(0x310)[0x20]>2) {
                AdvanceDamageStage(P(0x310)); SetCurrentArenaBoss(*(char **)(self+0xB8),P(0x310));
            }
        }
        break;
    case 10:
        if (*(u8 *)(self+0x95)==2) {
            *(Quadword *)position=*(Quadword *)((WaypointView *)state)->waypoint;
            SteerChainbladeToward(self,(Quadword *)position,yaw,0.0f);
        } else StepMovementAtOwnPositionWithFactor((u8 *)self,*(float *)(self+0xF8));
        if (*(u8 *)(self+0x60)&2) { SET_MODE(H(0x324),H(0x326)); *(int *)(self+0x48)=0; }
        break;
    case 11:
        if (SetFirstPendingFlag((u8 *)self)) {
            if (*(u8 *)(self+0x43)!=9) StartAnimationBlended(self,9,0,10);
            H(0x31C)=0; qcopy(state+0x2D0, self+0x10);
            value=RandomFloatRange(20.0f,40.0f);
            scale=0.017453294f;
            value*=scale;
            if (RandomIntBelow(2)) value=-value;
            F(0x308)=value;
        }
        PickChainbladeWanderGoal(self); StepChainbladeFollowPoint(self);
        *(Quadword *)position=*(Quadword *)(state+0x2D0);
        SteerChainbladeToward(self,(Quadword *)position,yaw,0.0f);
        if (!RandomIntBelow(400)) PickChainbladeIdleAnimation(self,0);
        if (distance<40.0f && distance>5.0f && FastDecTimer((short *)(state+0x31C))) {
            if (RandomIntBelow(2)) {
                SET_MODE(12,2);
                if (!RandomIntBelow(6)) PickChainbladeIdleAnimation(self,0);
            } else {
                SET_MODE(15,2);
                if (!RandomIntBelow(6)) PickChainbladeIdleAnimation(self,0);
            }
        }
        if (ShouldChainbladeLand(self)) SET_MODE(20,2);
        if (IsHelperReadyAtHealthPhase(self)) SET_MODE(3,2);
        break;
    case 12:
        if (SetFirstPendingFlag((u8 *)self)) H(0x328)=0;
        if (!H(0x328)) {
            result=MoveChainbladeIntoThrowPosition(self);
            switch (result) {
            case 0: EndChainThrow(self); SET_MODE(11,-1); break;
            case 2:
                if (*(u8 *)(self+0x42)!=10 && *(u8 *)(self+0x43)!=10) StartAnimationBlended(self,10,0,7);
                break;
            }
        } else {
            *(Quadword *)position=*(Quadword *)(self+0x10);
            SteerChainbladeToward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        }
        if (!H(0x328) && *(u8 *)(self+0x42)==10 && frame>19.0f) {
            ClearVector128((Quadword *)(state+0x1B0)); StartChainThrow(self,0); H(0x328)=1;
        }
        if (H(0x328)) {
            result=UpdateChainThrow(self,0);
            switch (result) {
            case 1: SET_MODE(14,2); break;
            case 2: EndChainThrow(self); H(0x328)=0; break;
            }
        }
        if (H(0x328)==1 && *(u8 *)(self+0x42)==10 && frame>27.0f) SET_MODE(13,2);
        break;
    case 13:
        if (SetFirstPendingFlag((u8 *)self) && *(u8 *)(self+0x43)!=11) StartAnimationBlended(self,11,0,7);
        *(Quadword *)position=*(Quadword *)(self+0x10);
        SteerChainbladeToward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (H(0x328) && UpdateChainThrow(self,0)==2) {
            SET_MODE(14,2); EndChainThrow(self); H(0x328)=0;
        }
        break;
    case 14:
        if (SetFirstPendingFlag((u8 *)self) && *(u8 *)(self+0x43)!=12) StartAnimationBlended(self,12,0,7);
        if (H(0x328) && UpdateChainThrow(self,0)==2) { EndChainThrow(self); H(0x328)=0; }
        *(Quadword *)position=*(Quadword *)(self+0x10);
        SteerChainbladeToward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (!H(0x328) && *(u8 *)(self+0x42)==12 && frame>6.0f) { EndChainThrow(self); SET_MODE(11,2); }
        break;
    case 15:
        if (SetFirstPendingFlag((u8 *)self)) H(0x328)=0;
        if (!H(0x328)) {
            result=MoveChainbladeIntoThrowPosition(self);
            switch (result) {
            case 0: EndChainThrow(self); SET_MODE(11,-1); break;
            case 2:
                if (*(u8 *)(self+0x42)!=13 && *(u8 *)(self+0x43)!=13) StartAnimationBlended(self,13,0,7);
                break;
            }
        } else {
            *(Quadword *)position=*(Quadword *)(self+0x10);
            SteerChainbladeToward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        }
        if (!H(0x328) && *(u8 *)(self+0x42)==13 && frame>19.0f) {
            ClearVector128((Quadword *)(state+0x1B0)); StartChainThrow(self,1); H(0x328)=1;
        }
        if (H(0x328)) {
            result=UpdateChainThrow(self,1);
            switch (result) {
            case 1: SET_MODE(17,2); break;
            case 2: EndChainThrow(self); H(0x328)=0; break;
            }
        }
        if (H(0x328)==1 && *(u8 *)(self+0x42)==13 && frame>27.0f) SET_MODE(16,2);
        break;
    case 16:
        if (SetFirstPendingFlag((u8 *)self) && *(u8 *)(self+0x43)!=14) StartAnimationBlended(self,14,0,7);
        *(Quadword *)position=*(Quadword *)(self+0x10);
        SteerChainbladeToward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (H(0x328) && UpdateChainThrow(self,1)==2) { SET_MODE(17,2); EndChainThrow(self); H(0x328)=0; }
        break;
    case 17:
        if (SetFirstPendingFlag((u8 *)self) && *(u8 *)(self+0x43)!=15) StartAnimationBlended(self,15,0,7);
        if (H(0x328) && UpdateChainThrow(self,1)==2) { EndChainThrow(self); H(0x328)=0; }
        *(Quadword *)position=*(Quadword *)(self+0x10);
        SteerChainbladeToward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (!H(0x328) && *(u8 *)(self+0x42)==15 && frame>6.0f) { EndChainThrow(self); SET_MODE(11,2); }
        break;
    case 18:
        *(Quadword *)position=*(Quadword *)(state+0x2D0);
        SteerChainbladeToward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        events=DispatchActionByKind(self,(void *)(state+0x60));
        if ((events&1)==1) { SET_MODE(20,2); H(0x32C)=1; break; }
        animFlags=events&2;
        goto modeEleven;
    case 19:
        if (SetFirstPendingFlag((u8 *)self) && *(u8 *)(self+0x43)!=17) StartAnimationBlended(self,17,0,10);
        { float animationFrame=GetMobyAnimationValue(self);
        if (*(u8 *)(self+0x42)==17 && animationFrame>9.0f) { *(u8 *)(self+0x95)=2; *(u8 *)(self+0xBE)&=~2; }
        animFlags=*(u8 *)(self+0x60)&2;
        }
    modeEleven:
        if (animFlags) SET_MODE(11,2);
        break;
    case 20:
        if (SetFirstPendingFlag((u8 *)self)) {
            W(0x148)&=~4;
            if (*(u8 *)(self+0x43)!=9) StartAnimationBlended(self,9,0,10);
            EndChainThrow(self);
        }
        if (*(float *)(self+0x18)<D_L02_001B01B0[2]+1.0f && *(float *)(self+0x18)>D_L02_001B01B0[2]) {
            if (*(u8 *)(self+0x42)!=18 && *(u8 *)(self+0x43)!=18) StartAnimationBlended(self,18,0,10);
            StepMovementAtOwnPositionWithFactor((u8 *)self,yaw);
        } else {
            qcopy_nc(position,self+0x10); position[2]=D_L02_001B01B0[2];
            SteerChainbladeToward(self,(Quadword *)position,yaw,0.0f);
        }
        if (*(u8 *)(self+0x42)==18 && (H(0x1D0)!=0 || *(float *)(self+0x18)<D_L02_001B01B0[2]+0.2f)) {
            if (H(0x32C)) { StartAnimationBlended(self,4,0,3); B(0x7A)=0; SET_MODE(8,3); }
            else SET_MODE(6,1);
            if (*(u8 *)(self+0x42)==18 && frame>8.0f && frame<10.0f) {
                EFFECT->amount=0.2f; EFFECT->kind=25; EFFECT->detail=0;
            }
        }
        break;
    }
    UpdateChainbladeEffectsAndTimers(self);
}
