#include "common.h"

#define W(p, o) (*(int *)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))

typedef struct {
    char pad[0x80];
    float position[4];
} Hero;

extern int func_L14_004295D0(void *);
extern int func_002B3890(void *);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(void *);
extern int func_L01_00321178(void *, void *);
extern int func_L00_00329520(void *, int);
extern int func_L01_00322288(void *, float);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
/* Integer and FP arguments retain their respective EE register-bank order. */
extern int func_002A8C28(void *, void *, float, float, int, float, int, int, int);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_0029F530(void *);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_L14_00429A18(void *);
extern void func_0029F338(void *);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002B5258(void *);
extern void func_L14_003DF690(void *, int);
extern void func_0029FCC0(void *, int, void *);
extern void func_L14_004298F0(void *);

extern float D_L14_001B1924 __attribute__((sda));
extern float D_L14_001B1928 __attribute__((sda));
extern float D_L14_001B192C __attribute__((sda));
extern float D_L14_001B1930 __attribute__((sda));
extern int D_L14_001B20C8;
extern u8 D_00189E20[];
extern u8 *D_L14_001B259C;
extern int D_L14_001B1938[4];
extern char *D_L14_001C39C0[];

#define HERO ((Hero *)D_00189E20)
#define D_00189EA0 (HERO->position)

/* Updates the prison enemy that walks, climbs up and down to ledges and attacks the player, and is removed when destroyed. */
void func_L14_00428E68(char *self)
{
    char *vars = *(char **)(self + 0x68);
    int result, i;
    float angle, animTime;
    union {
        int choices[4];
        float pos[4];
    } scratch;

    if (UpdatePrisonEnemyCommon(self)) {
        MarkMobySpawned(self);
        return;
    }
    {
        switch (B(self, 0x95)) {
        case 0:
            if (W(vars, 0x2F0) == 1 && B(self, 0x20) == 1)
                SetMobyState(self, 5, 1);
            break;
        case 1:
            if (SetSecondPendingFlag(self))
                SetControllerSpeedLimits(self,
                    D_L14_001B1924 * 0.0002777777845f,
                    D_L14_001B1928 * 0.0166666675359f,
                    D_L14_001B192C * 4.848137450608192e-06f,
                    D_L14_001B1930 * 0.0002908882452175021f);
            if (W(vars, 0x2F0) != 1) {
                SetMobyState(self, 1, 0);
                W(vars, 0x30C) = RandomIntRange(580, 600);
            }
            break;
        case 2:
            result = DispatchActionByKind(self, vars + 0x140);
            if (result & 1) {
                FireEffectBurstWithSound(self);
                MarkMobySpawned(self);
                return;
            }
            if (result & 2) {
                if (W(vars, 0x2F0) == 1)
                    SetMobyState(self, 5, 1);
                else {
                    SetMobyState(self, 1, 0);
                    W(vars, 0x30C) = RandomIntRange(580, 600);
                }
            }
            break;
        }
    }

    switch (B(self, 0x20)) {
    case 1:
        if (SetFirstPendingFlag(self) && B(self, 0x43) != 6)
            StartAnimationBlended(self, 6, 0, 20);
        if (B(self, 0x60) & 2) {
            __builtin_memcpy(scratch.choices, D_L14_001B1938, 16);
            if (B(self, 0x43) != scratch.choices[RandomIntBelow(4)])
                StartAnimationBlended(self, scratch.choices[RandomIntBelow(4)], 0, 20);
        }
        if (W(vars, 0x2B8) != -1)
            StepMovementAtOwnPosition(self);
        if ((D_L14_001B20C8 & 15) == (((int)self >> 8) & 15)) {
            if (W(vars, 0x2B8) == -1)
                break;
            if (W(vars, 0x31C) && HERO->position[2] + 2.0f < F(self, 0x18) &&
                vec_distance_xy(self + 0x10, gHeroPosition) < 16.0f) {
                SetMobyState(self, 2, -1);
                break;
            }
            if (!W(vars, 0x31C) && F(self, 0x18) < HERO->position[2] - 2.0f &&
                vec_distance_xy(self + 0x10, gHeroPosition) < 8.0f)
                SetMobyState(self, 3, -1);
        } else {
            angle = FastMatrixHelperA(HERO->position[0] - F(self, 0x10),
                                 HERO->position[1] - F(self, 0x14));
            if (FastDiffRots(F(self, 0xF8), angle) > 0.7853982449f)
                SetMobyState(self, 4, -1);
        }
        break;
    case 4:
        if (SetFirstPendingFlag(self) && B(self, 0x43) != 8)
            StartAnimationBlended(self, 8, 0, 20);
        angle = FastMatrixHelperA(HERO->position[0] - F(self, 0x10),
                             HERO->position[1] - F(self, 0x14));
        StartMobyEffectFromEntry(self, angle);
        if (FastDiffRots(F(self, 0xF8), angle) < 0.05235988274f)
            SetMobyState(self, 1, -1);
        break;
    case 2:
        if (SetFirstPendingFlag(self)) {
            if (B(self, 0x43) != 8)
                StartAnimationBlended(self, 8, 0, 20);
            SetMobyStateValue(gMobyPool_L14 + W(vars, 0x2B8) * 256, 0);
        }
        if (TurnMobyTowardTarget(self, gMobyPool_L14 + W(vars, 0x2B8) * 256 + 0x10) & 128) {
            SetMobyStateValue(gMobyPool_L14 + W(vars, 0x2B8) * 256, 1);
            W(vars, 0x31C) = 0;
            SetMobyState(self, 1, -1);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(self)) {
            if (B(self, 0x43) != 8)
                StartAnimationBlended(self, 8, 0, 20);
            SetMobyStateValue(gMobyPool_L14 + W(vars, 0x2B8) * 256, 0);
        }
        if (TurnMobyTowardTarget(self, vars + 0x2E0) & 128) {
            W(vars, 0x31C) = 1;
            SetMobyState(self, 1, -1);
        }
        break;
    case 5:
        if (SetFirstPendingFlag(self) && B(self, 0x43) != 16)
            StartAnimationBlended(self, 16, 7, 7);
        animTime = GetMobyAnimationValue(self);
        if (animTime < 19.0f) {
            angle = FastMatrixHelperA(F(vars, 0x210) - F(self, 0x10),
                                 F(vars, 0x214) - F(self, 0x14));
            StartMobyEffectFromEntry(self, angle);
            W(vars, 0x320) = 1;
        } else if (animTime <= 22.0f && W(vars, 0x320)) {
            SweepCollisionFromObject(self, *(char **)(vars + 0x300) + 0x10,
                          0.57f, 2.0f, 1, 1.5f, 0, 1, 0);
            SweepCollisionFromObject(self, *(char **)(vars + 0x304) + 0x10,
                          0.57f, 2.0f, 1, 1.5f, 0, 1, 0);
            TransformMobyJointToWorld(self, 6, scratch.pos);
            result = SweepCollisionFromObject(self, scratch.pos, 0.57f, 2.0f, 1, 2.0f, 0, 1, 0);
            for (i = 0; i < result; i++)
                if (*(short *)(D_L14_001C39C0[i] + 0xAA) == 2404 /* Gadgebot */)
                    W(vars, 0x320) = 0;
        }
        break;
    case 7:
        if (IsPointInsideRegion(gHeroPosition, W(vars, 0x2BC)))
            SetMobyState(self, 8, -1);
        break;
    case 8:
        if (SetFirstPendingFlag(self) && B(self, 0x43) != 1)
            StartAnimationBlended(self, 1, 0, 2);
        if (B(self, 0x60) & 2)
            SetMobyState(self, 1, 0);
        break;
    }
    UpdateActorWalkMotion(self);
}
