#include "common.h"
#define I(p, o) (*(int *)((p)+(o)))
#define H(p, o) (*(unsigned short *)((p)+(o)))
#define B(p, o) (*(unsigned char *)((p)+(o)))
#define F(p, o) (*(float *)((p)+(o)))
extern int D_L07_001B1E08 MACRO_ADDR;
extern int D_L07_001C9780 NOT_SDA;
extern float D_L07_001B0AE8 __attribute__((sda));
extern float D_L07_001B0AEC __attribute__((sda));
extern float D_L07_001B0AF0 __attribute__((sda));
extern float D_L07_001B0AF4 __attribute__((sda));
extern float D_L07_001B0AF8 __attribute__((sda));
extern float D_L07_001B0AFC __attribute__((sda));
extern float D_L07_001B0B00 __attribute__((sda));
extern struct Choice61 {int a, b, c, d;} D_L07_001B0B08;
extern int func_L07_003E69B8(void *);
extern void func_L07_003E7240(void *);
extern void func_L07_003E6E00(void *);
extern void func_002A7750(void *, int, int);
extern int func_002A7820(int, int);
extern void func_L00_00424A08(int, float, float);
extern void func_L00_00424A50(float, float);
extern int func_002B3890(void *);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_002B1C20(void *, void *);
extern void func_0029F338(void *);
extern int func_002B3868(void *);
extern void func_002A7470(void *, int, int, int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern int func_L01_00321178(void *, void *);
extern int func_002A77E0(int);
extern void func_L02_00332630(void *, void *);
extern float func_00283248(float, float);
extern int func_L02_00331440(void *, void *, int, float, float, float);
extern void func_002B4FF0(void *, void *, float);
extern float func_00282E80(void *, void *);
extern float func_0029F530(void *);
extern void func_L01_00322288(void *, float);
extern int func_002A8C28(void *, void *, int, float, float, int, float, int, int);
extern float func_00283C80(float, float);
extern int func_002A8508(int, int);

/* Update the entity's submode, movement target and timed attack actions. */
void func_L07_003E61E0(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    float time;
    int result;
    int choices[4];
    if (D_L07_001B1E08 >= 2 && D_L07_001C9780 != I(state, 0x350)) return;
    if (InitAndUpdateShooterEntityBase(actor)) goto cleanup;
    {
        switch (B(actor, 0x95)) {
        case 0:
            if (I(state, 0x2D4) == 1) {SetMobyState(actor, 6, 2); break;}
            if (I(state, 0x2D0)) {
                SetMobyState(actor, 3, 1);
                I(state, 0x2D0) = 0;
                if (I(state, 0x344) < 300) I(state, 0x344) = RandomIntRange(480, 600);
            }
            break;
        case 1:
            if (I(state, 0x2D4) == 1) SetMobyState(actor, 6, 2);
            break;
        case 2:
            follow_camera_set_distance(0, D_L07_001B0AFC, 0.003f);
            follow_camera_set_height(D_L07_001B0B00, 0.003f);
            if (SetSecondPendingFlag(actor))
                SetControllerSpeedLimits(actor, D_L07_001B0AEC*0.00027777778f, D_L07_001B0AF0*0.016666668f, D_L07_001B0AF4*4.848137450608192e-06f, D_L07_001B0AF8*0.0002908882452175021f);
            if (I(state, 0x2D4) != 1 && B(actor, 0x20) != 7) {
                if (I(state, 0x338)) SetMobyState(actor, 3, 1);
                else SetMobyState(actor, 4, 1);
                I(state, 0x344) = RandomIntRange(580, 600);
            }
            break;
        case 3:
            result = DispatchActionByKind(actor, state + 0x140);
            if (result & 1) {
                SpawnEntityDeathEffects(actor);
cleanup:
                /* The initialization helper also reaches this shared cleanup. */
                MarkMobySpawned(actor);
                return;
            }
            if (result & 2) {SetMobyState(actor, 7, 2);I(state, 0x344) = RandomIntRange(580, 600);}
            break;
        }
    }
    switch (B(actor, 0x20)) {
    case 1:
        if (SetFirstPendingFlag(actor) && B(actor, 0x43) != 2) StartAnimationBlended(actor, 2, 0, 20);
        if ((B(actor, 0x60) & 2) && !I(state, 0x338)) SetMobyState(actor, 2, -1);
        break;
    case 2: {
        float radius, angle;
        if (SetFirstPendingFlag(actor)) {
            if (B(actor, 0x43) != 8) StartAnimationBlended(actor, 8, 0, 20);
            radius = RandomFloatRange(0, 5);
            angle = RandomAngle();
            F(state, 0x300) = FastSinOrCosA(angle)*radius;
            F(state, 0x304) = FastSinOrCosB(angle)*radius;
            F(state, 0x308) = 0;
            FastVecAdd(state + 0x300, state + 0x300, state + 0x2F0);
        }
        result = TurnMobyTowardTarget(actor, state + 0x300);
        if (result == 128 || (I(state, 0xD0) && H(actor, 0x96) > 40) || H(actor, 0x96) > 180) SetMobyState(actor, 1, -1);
        break;
    }
    case 3:
        if (SetFirstPendingFlag(actor)) {
            *(struct Choice61 *)choices = D_L07_001B0B08;
            if (B(actor, 0x43) != choices[RandomIntBelow(4)]) StartAnimationBlended(actor, choices[RandomIntBelow(4)], 0, 20);
        }
        if ((B(actor, 0x60) & 2) && !I(state, 0x338)) SetMobyState(actor, 4, -1);
        break;
    case 4: {
        float radius, angle;
        if (SetFirstPendingFlag(actor)) {
            if (B(actor, 0x43) != 8) StartAnimationBlended(actor, 8, 0, 20);
            radius = RandomFloatRange(0, 3);
            angle = RandomAngle();
            F(state, 0x300) = FastSinOrCosA(angle)*radius;
            F(state, 0x304) = FastSinOrCosB(angle)*radius;
            F(state, 0x308) = 0;
            FastVecAdd(state + 0x300, state + 0x300, state + 0x2F0);
        }
        CheckTargetPointFromOffset(actor, state + 0x210);
        angle = FastMatrixHelperA(F(state, 0x300)-F(actor, 0x10), F(state, 0x304)-F(actor, 0x14));
        result = MoveToTargetWithTempLimits(actor, state + 0x300, 16, angle, -1, -1);
        if (result == 128 || (I(state, 0xD0) && H(actor, 0x96) > 40) || H(actor, 0x96) > 180) SetMobyState(actor, 3, -1);
        break;
    }
    case 6:
        if (SetFirstPendingFlag(actor) && B(actor, 0x43) != 11) StartAnimationBlended(actor, 11, 0, 20);
        TurnTowardTargetAndStepMovement(actor, state + 0x210, 0);
        if (vec_distance_xy(actor + 0x10, state + 0x210) < D_L07_001B0AE8) SetMobyState(actor, 7, -1);
        break;
    case 7:
        if (SetFirstPendingFlag(actor) && B(actor, 0x43) != 12) StartAnimationBlended(actor, 12, 5, 10);
        time = GetMobyAnimationValue(actor);
        if (time < 19) StartMobyEffectFromEntry(actor, FastMatrixHelperA(F(state, 0x210)-F(actor, 0x10), F(state, 0x214)-F(actor, 0x14)));
        else if (time<=22) {
            SweepCollisionFromObject(actor, *(char **)(state + 0x330)+0x10, 1, 0.333f, (float)B(state, 0x34), 0, 1.0f, 1, 0);
            SweepCollisionFromObject(actor, *(char **)(state + 0x334)+0x10, 1, 0.333f, (float)B(state, 0x34), 0, 1.0f, 1, 0);
        }
        if (B(actor, 0x60) & 2) {
            time = vec_distance_xy(actor + 0x10, state + 0x210);
            if (D_L07_001B0AE8+0.5f < time ||
                FastDiffRots(F(actor, 0xF8), FastMatrixHelperA(F(state, 0x210)-F(actor, 0x10), F(state, 0x214)-F(actor, 0x14))) > 0.349065899848938f)
                SetMobyState(actor, 6, -1);
        }
        break;
    case 9:
        if (!CountMobysInGroupNotInState(I(state, 0x2B8), -1) || F(state, 0x20) < *(short *)(state + 0x24)) SetMobyState(actor, 10, -1);
        break;
    case 10:
        if (SetFirstPendingFlag(actor) && B(actor, 0x43) != 1) StartAnimationBlended(actor, 1, 0, 2);
        if (B(actor, 0x60) & 2) SetMobyState(actor, 6, -1);
        break;
    }
    FinishEntityUpdate(actor);
}
