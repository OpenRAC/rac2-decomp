#include "common.h"

typedef int Quad __attribute__((mode(TI)));

#define U8(p, o) (*(unsigned char *)((p) + (o)))
#define U16(p, o) (*(unsigned short *)((p) + (o)))
#define S(p, o) (*(short *)((p) + (o)))
#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))

extern char D_0018A0E0[], D_00189EA0[];
extern int D_0018C0B0 __attribute__((nosda));
extern int D_L02_001B30C8;

/* The distance bound is read absolutely in state 3 and through GP in state 4.
 * Both symbols resolve to the same word in each of the three programs. */
extern float D_L02_001B00F8 __attribute__((sda));
extern float D_L02_001B00F8_abs MACRO_ADDR;
/* State 4 snapshots the upper bound before reading the lower bound. */
extern volatile float D_L02_001B00FC MACRO_ADDR;

extern void func_L02_003CE4D0(void *);
extern void func_L02_003CEA28(void *);
extern void func_L02_003CE908(void *);
extern void func_L02_003CEE40(void *);
extern void func_L02_003CEC70(void *);
extern void func_L02_003CF1B8(void *);
extern int func_002B3890(void *);
extern int func_002B3868(void *);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern int func_00282978(void *);
extern int func_002B1C20(void *, void *);
extern int func_L02_003CE8B0(void *, void *, int);
extern int func_L02_0032E390(void *, int, int);
extern int func_002AEB60(void *, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282DB0(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern int func_L02_0032EF10(void *, void *, void *, int, float);
extern int func_L01_00322288(void *, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A8D70(void *, int, int, int, int, int, float, float, float);
extern int func_L02_00332630(char *, void *);
/* The integer and floating argument banks retain their independent order. */
extern int func_002A8C28(void *, float, float *, int, float, float, int, int, int);

/* Per-frame update of a creature with a state machine. It picks animations, wanders, turns toward the hero and runs, then checks the object's own state to move or attack. */
void func_L02_003CD970(char *object)
{
    char *vars = *(char **)(object + 0x68);
    float angle, speed;
    int r;
    Quad temp;

    InitEnemyMoby(object);
    switch (U8(object, 0x95)) {
    case 0:
        if (SetSecondPendingFlag(object)) {
            SetControllerSpeedLimits(object, 0.005f, 0.06666667f, 0.006981317885220051f,
                         0.41887909173965454f);
            F(vars, 0x1D0) = 0.06666667f;
            F(vars, 0x124) = 0.006666666828095913f;
            F(vars, 0x134) = 0.5f;
            S(vars, 0x33A) = RandomIntRange(0, 30);
        }
        if (S(vars, 0x314) == 1) {
            if (FastDecTimer(vars + 0x33A)) {
                if (RandomIntBelow(3))
                    SetMobyState(object, 9, 2);
                else
                    SetMobyState(object, 8, 2);
                break;
            }
        }
        if (S(vars, 0x316)) {
            if (RandomIntBelow(2))
                SetMobyState(object, 7, 1);
            else
                SetMobyState(object, 6, 1);
            S(vars, 0x316) = 0;
            if (S(vars, 0x310) < 300)
                S(vars, 0x310) = RandomIntRange(480, 600);
        }
        break;
    case 1:
        if (SetSecondPendingFlag(object)) {
            SetControllerSpeedLimits(object, 0.005f, 0.06666667f, 0.01745329424738884f,
                         1.047197699546814f);
            F(vars, 0x1D0) = 0.06666667f;
            F(vars, 0x134) = 0.05f;
        }
        if (S(vars, 0x314) == 1) {
            SetMobyState(object, 9, 2);
        } else if (S(vars, 0x310) == 0)
            SetMobyState(object, 1, 0);
        break;
    case 2:
        if (SetSecondPendingFlag(object)) {
            SetControllerSpeedLimits(object, 0.005f, 0.06666667f, 0.01745329424738884f,
                         1.047197699546814f);
            F(vars, 0x1D0) = 0.06666667f;
            F(vars, 0x124) = 0.006666666828095913f;
            F(vars, 0x134) = 0.05f;
            S(vars, 0x33A) = RandomIntRange(0, 30);
        }
        if (S(vars, 0x314) != 1 && FastDecTimer(vars + 0x33A)) {
            SetMobyState(object, 3, 1);
            S(vars, 0x310) = RandomIntRange(580, 600);
        }
        break;
    case 3: {
        unsigned int flags;
        flags = DispatchActionByKind(object, vars + 0x50);
        if (flags & 1)
            ExplodeAndRemoveMoby_L02(object);
        else if (flags & 2) {
            if (S(vars, 0x314) == 1)
                SetMobyState(object, 9, 2);
            else {
                SetMobyState(object, 3, 1);
                S(vars, 0x310) = RandomIntRange(580, 600);
            }
        }
        break;
    }
    }
    switch (U8(object, 0x20)) {
    case 1:
        if (U8(object, 0x31)) {
            if (SetFirstPendingFlag(object)) {
                r = !RandomIntBelow(4);
                if (U8(object, 0x43) != r)
                    StartAnimationBlended(object, r, 0, 10);
                S(vars, 0x312) = RandomIntRange(60, 120);
            }
            if (U8(object, 0x43) == 1) {
                if (U8(object, 0x60) & 2)
                    StartAnimationBlended(object, 0, 0, 20);
            } else if (!S(vars, 0x312) &&
                       (!S(vars, 0x338) || FastVecDot(vars + 0x300, D_0018A0E0) > 0.8f))
                SetMobyState(object, 2, -1);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(object)) {
            if (U8(object, 0x43) != 6)
                StartAnimationBlended(object, 6, 0, 20);
            angle = RandomAngle();
            speed = RandomFloatRange(2, 5);
            F(vars, 0x2F0) = FastSinOrCosA(angle) * speed;
            F(vars, 0x2F4) = FastSinOrCosB(angle) * speed;
            F(vars, 0x2F8) = 0;
            FastVecAdd(vars + 0x2F0, vars + 0x2F0, vars + 0x2E0);
            if (I(vars, 0x218) != -1) {
                temp = *(Quad *)(vars + 0x2E0);
                ClampMoveToPathArea(&temp, vars + 0x2F0, vars + 0x2F0, I(vars, 0x218), 1.5f);
            }
        }
        RunEntryHookByMode(object, vars + 0x2F0, 0);
        if (U16(object, 0x96) > 30 && (F(vars, 0x1CC) <= 0.5f || U16(object, 0x96) > 180))
            SetMobyState(object, 1, -1);
        break;
    case 3:
        if (SetFirstPendingFlag(object) && U8(object, 0x43) != RandomIntBelow(2) + 4)
            StartAnimationBlended(object, RandomIntBelow(2) + 4, 0, 10);
        if (fast_vec_dist(object + 0x10, gHeroPosition) < D_L02_001B00F8_abs)
            SetMobyState(object, 4, -1);
        else if (U8(object, 0x60) & 2) {
            switch (RandomIntBelow(3)) {
            case 0:
                SetMobyState(object, 6, -1);
                break;
            case 1:
                SetMobyState(object, 7, -1);
                break;
            case 2:
                SetMobyState(object, 5, -1);
                break;
            }
        }
        break;
    case 6:
        if (SetFirstPendingFlag(object) && U8(object, 0x43) != RandomIntBelow(2) + 2)
            StartAnimationBlended(object, RandomIntBelow(2) + 2, 0, 10);
        CheckTargetPointFromOffset(object, vars + 0x1F0);
        if (U8(object, 0x60) & 2)
            SetMobyState(object, 3, -1);
        break;
    case 7:
        if (SetFirstPendingFlag(object) && U8(object, 0x43) != 12)
            StartAnimationBlended(object, 12, 0, 10);
        CheckTargetPointFromOffset(object, vars + 0x1F0);
        if (U8(object, 0x60) & 2)
            SetMobyState(object, 3, -1);
        break;
    case 4:
        if (SetFirstPendingFlag(object)) {
            if (U8(object, 0x43) != 6)
                StartAnimationBlended(object, 6, 0, 10);
            {
                float upper = D_L02_001B00FC;
                F(vars, 0x334) = RandomFloatRange(D_L02_001B00F8, upper) + 0.5f;
            }
        }
        if ((RunEntryHookByMode(object, vars + 0x2E0, 0) & 0x80) ||
            vec_distance_xy(object + 0x10, gHeroPosition) > F(vars, 0x334)) {
            if (RandomIntBelow(2))
                SetMobyState(object, 6, -1);
            else
                SetMobyState(object, 7, -1);
        }
        break;
    case 5:
        if (SetFirstPendingFlag(object)) {
            if (U8(object, 0x43) != 6)
                StartAnimationBlended(object, 6, 0, 20);
            angle = RandomAngle();
            speed = RandomFloatRange(2, 5);
            F(vars, 0x2F0) = FastSinOrCosA(angle) * speed;
            F(vars, 0x2F4) = FastSinOrCosB(angle) * speed;
            F(vars, 0x2F8) = 0;
            FastVecAdd(vars + 0x2F0, vars + 0x2F0, vars + 0x2E0);
            if (I(vars, 0x218) != -1) {
                temp = *(Quad *)(vars + 0x2E0);
                ClampMoveToPathArea(&temp, vars + 0x2F0, vars + 0x2F0, I(vars, 0x218), 1.5f);
            }
        }
        RunEntryHookByMode(object, vars + 0x2F0, 0);
        if (U16(object, 0x96) > 30 && (F(vars, 0x1CC) <= 0.5f || U16(object, 0x96) > 180))
            SetMobyState(object, 3, -1);
        break;
    case 8:
        if (SetFirstPendingFlag(object) && U8(object, 0x43) != RandomIntBelow(2) + 2)
            StartAnimationBlended(object, RandomIntBelow(2) + 2, 0, 10);
        if (U8(object, 0x60) & 2)
            SetMobyState(object, 9, -1);
        break;
    case 9:
        if (SetFirstPendingFlag(object) && U8(object, 0x43) != 6)
            StartAnimationBlended(object, 6, 0, 5);
        if (!(U16(object, 0x96) & 3))
            F(vars, 0x31C) = CountGroupSideFromObject(object, gHeroMoby_0018C0B0, -1) * 0.087266475f;
        RunEntryHookByMode(object, vars + 0x1F0, 1);
        ClampAimYawPitch(object);
        if (F(vars, 0x1CC) <= 1.25f)
            SetMobyState(object, 10, -1);
        break;
    case 10:
        if (SetFirstPendingFlag(object)) {
            F(vars, 0x320) = FastMatrixHelperA(F(vars, 0x1F0) - F(object, 0x10),
                                       F(vars, 0x1F4) - F(object, 0x14));
            if (U8(object, 0x43) != 8)
                StartAnimationBlended(object, 8, 2, 10);
        }
        StartMobyEffectFromEntry(object, F(vars, 0x320));
        if (IsValueWithinStepOfThreshold(object, 13))
            TestHitAtBone(object, 1, 0x4000001, 0, 1, 0, 0.75f, U8(vars, 0x34), 1);
        if (U8(object, 0x60) & 2)
            SetMobyState(object, 9, -1);
        break;
    case 14:
        if (SetFirstPendingFlag(object)) {
            if (U8(object, 0x43) != 10)
                StartAnimationBlended(object, 10, 0, 5);
            I(vars, 0x1BC) = gFrameCounter_L02;
        }
        vec_scale_to_length(&temp, vars + 0x1A0, 1);
        RunEntryHookByMode(object, &temp, 0);
        SpawnTwoEffectPuffs(object);
        SweepCollisionFromObject(object, 0.6f, (float *)(object + 0x10), 0x4000000, 1, 1, 0, 1, 0);
        if (F(vars, 0x190) >= F(object, 0x18)) {
            if (S(vars, 0x314) == 1)
                SetMobyState(object, 8, 2);
            else
                SetMobyState(object, 2, 0);
            I(vars, 0x138) &= -18;
        }
        break;
    case 12:
        ExplodeAndRemoveMoby_L02(object);
        break;
    }
    ResetTurnAndPlaceObject(object);
    if (U8(object, 0x31))
        UpdateGroupPulseColor(object);
}
