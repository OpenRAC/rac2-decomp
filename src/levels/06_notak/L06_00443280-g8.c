#include "common.h"

extern float D_L06_001B1090 __attribute__((sda));
extern float D_L06_001B1094 __attribute__((sda));
extern int D_L06_001B2348;
extern void func_L06_00443A38(char *);
extern int func_002B3890(char *);
extern int func_002B3868(char *);
extern void func_002B60B0(char *, float, float, float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);
extern int func_002B1C20(char *, char *);
extern void func_L06_00443F30(char *);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(char *, char *, char *);
extern int func_L06_00443DE0(char *, char *, int);
extern int func_L02_0032E390(char *, int, int);
extern void func_L06_00444068(char *);
extern float func_00283248(float, float);
extern void func_L01_00322288(char *, float);
extern int func_002AEB60(char *, float);
extern void func_002A8D70(char *, int, int, int, int, int, float, float, float);
extern void func_00282F20(char *, char *, float);
extern void func_L06_00443E18(char *);
extern void func_L06_00444168(char *);

#define F(p,o) (*(float *)((p)+(o)))
#define H(p,o) (*(short *)((p)+(o)))
#define U(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))

/* Updates a walking creature: it picks animations, wanders, turns toward its target and switches between its states. */
void func_L06_00443280(char *obj)
{
    char *vars = *(char **)(obj + 0x68);
    char aimVec[16];
    float angle, speed;
    int flags, anim;
    UpdateNotakEnemyMoby(obj);
    if (!obj || B(obj,0x20) == 0xFE || B(obj,0x20) == 0xFD) return;
    switch (B(obj,0x95)) {
    case 0:
        if (SetSecondPendingFlag(obj)) {
            SetControllerSpeedLimits(obj, 0.005f, 0.06666667f, 0.0034906589f, 0.41887909f);
            F(vars,0x124) = 0.006666667f;
            F(vars,0x134) = 0.5f;
        }
        F(vars,0x1D0) = D_L06_001B1094 * 0.016666667f;
        if (H(vars,0x314) == 1) {
            if (RandomIntBelow(5) == 0) {
                SetMobyState(obj,5,2);
            } else {
                SetMobyState(obj,6,2);
            }
        } else if (H(vars,0x316)) {
            SetMobyState(obj,3,1);
            H(vars,0x316) = 0;
            if (H(vars,0x310) < 300) H(vars,0x310) = RandomIntRange(480,600);
        }
        break;
    case 1:
        if (SetSecondPendingFlag(obj)) {
            SetControllerSpeedLimits(obj, 0.005f, 0.06666667f, 0.0034906589f, 0.41887909f);
            F(vars,0x134) = 0.05f;
        }
        F(vars,0x1D0) = D_L06_001B1090 * 0.016666667f;
        if (H(vars,0x314) == 1) SetMobyState(obj,6,2);
        else if (!H(vars,0x310)) SetMobyState(obj,1,0);
        break;
    case 2:
        if (SetSecondPendingFlag(obj)) {
            SetControllerSpeedLimits(obj, 0.005f, 0.06666667f, 0.0034906589f, 0.41887909f);
            F(vars,0x124) = 0.006666667f;
            F(vars,0x134) = 0.05f;
        }
        F(vars,0x1D0) = D_L06_001B1090 * 0.016666667f;
        if (H(vars,0x314) == 1) break;
        else {
            SetMobyState(obj,3,1);
            H(vars,0x310) = RandomIntRange(580,600);
        }
        break;
    case 3:
        flags = DispatchActionByKind(obj,vars+0x50);
        if (flags & 1) ExplodeAndRemoveMoby_L06(obj);
        else if (flags & 2) {
            if (H(vars,0x314) == 1) {
                SetMobyState(obj,6,2);
            } else {
                SetMobyState(obj,3,1);
                H(vars,0x310) = RandomIntRange(580,600);
            }
        }
        break;
    }
    switch (B(obj,0x20)) {
    case 1:
        if (SetFirstPendingFlag(obj)) {
            anim = RandomIntBelow(4) == 0;
            if (B(obj,0x43) != anim) StartAnimationBlended(obj,anim,0,10);
            H(vars,0x312) = RandomIntRange(60,120);
        }
        if (B(obj,0x43) == 1) {
            if (B(obj,0x60) & 2) StartAnimationBlended(obj,0,0,20);
        } else if (!H(vars,0x312)) SetMobyState(obj,2,-1);
        break;
    case 2:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43) != 6) StartAnimationBlended(obj,6,0,20);
            angle = RandomAngle();
            speed = RandomFloatRange(2.0f,5.0f);
            F(vars,0x2F0) = FastSinOrCosA(angle)*speed;
            F(vars,0x2F4) = FastSinOrCosB(angle)*speed;
            F(vars,0x2F8) = 0;
            FastVecAdd(vars+0x2F0,vars+0x2F0,vars+0x2E0);
        }
        SetActorGlowEffect(obj,vars+0x2F0,0);
        if (U(obj,0x96)>30 && (F(vars,0x1CC)<=0.5f || U(obj,0x96)>180)) SetMobyState(obj,1,-1);
        break;
    case 3:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43) != RandomIntBelow(2)+4) StartAnimationBlended(obj,RandomIntBelow(2)+4,0,10);
        }
        break;
    case 4:
        if (SetFirstPendingFlag(obj) && B(obj,0x43)!=6) StartAnimationBlended(obj,6,0,10);
        if (SetActorGlowEffect(obj,vars+0x2E0,0)&0x80) SetMobyState(obj,3,-1);
        break;
    case 5:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43) != RandomIntBelow(2)+2) StartAnimationBlended(obj,RandomIntBelow(2)+2,0,10);
        }
        if (B(obj,0x60)&2) SetMobyState(obj,6,-1);
        break;
    case 6:
        if (SetFirstPendingFlag(obj) && B(obj,0x43)!=6) StartAnimationBlended(obj,6,0,5);
        if (!(U(obj,0x96)&3)) F(vars,0x31C) = (float)CountGroupSideFromObject(obj,I(vars,0x200),-1)*0.087266475f;
        SetActorGlowEffect(obj,vars+0x1F0,1);
        AimHeadAtHero(obj);
        if (F(vars,0x1CC)<=1.25f) SetMobyState(obj,7,-1);
        break;
    case 7:
        if (SetFirstPendingFlag(obj)) {
            F(vars,0x320) = FastMatrixHelperA(F(vars,0x1F0)-F(obj,0x10),F(vars,0x1F4)-F(obj,0x14));
            if (B(obj,0x43)!=8) StartAnimationBlended(obj,8,3,6);
        }
        StartMobyEffectFromEntry(obj,F(vars,0x320));
        if (IsValueWithinStepOfThreshold(obj,13.0f)) TestHitAtBone(obj,1,0x4000001,0,1,0,0.75f,(float)B(vars,0x34),1.0f);
        if (B(obj,0x60)&2) SetMobyState(obj,6,-1);
        break;
    case 10:
        if (SetFirstPendingFlag(obj)) {
            if (B(obj,0x43)!=10) StartAnimationBlended(obj,10,0,5);
            I(vars,0x1BC) = D_L06_001B2348;
        }
        vec_scale_to_length(aimVec,vars+0x1A0,1.0f);
        SetActorGlowEffect(obj,aimVec,0);
        if (F(vars,0x190)>=F(obj,0x18)) {
            SetMobyState(obj,5,2);
            I(vars,0x138) &= ~0x11;
        }
        break;
    }
    TickActorTimersAndEffects(obj);
    if (B(obj,0x31)) UpdateMarkerPulse(obj);
}
