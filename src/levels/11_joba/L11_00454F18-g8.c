#include "common.h"

/* Separate unit for GP-relative tuning and the state-machine jump table.
 * Unsplit GCSE edges share the goal pointer; disabling CSE jump following retains
 * the nullable target checks on frames when the group search is skipped.
 */

typedef int ActorQuadword __attribute__((mode(TI)));

typedef struct ActorObject ActorObject;
typedef struct {
    char pad00[0x34];
    u8 meleeDamage;
    u8 contactDamage;
    char pad36[0x50 - 0x36];
    char contact[0x10];
    char pad60[0x124 - 0x60];
    float step;
    char pad128[0x230 - 0x128];
    float goal[4];
    ActorObject *target;
    s32 group;
    float turnRate;
    s32 field24C;
    ActorObject *aimTarget;
    s16 field254;
    s16 attached;
    s16 idleDelay;
} ActorState;
struct ActorObject {
    char pad00[0x10];
    float pos[4];
    u8 state;
    char pad21[0x42 - 0x21];
    u8 animation;
    u8 nextAnimation;
    char pad44[4];
    float speed;
    char pad4C[0x60 - 0x4C];
    u8 animationFlags;
    char pad61[7];
    ActorState *data;
    char pad6C[0x95 - 0x6C];
    u8 secondaryState;
    u16 timer;
    char pad98[0xAA - 0x98];
    s16 classId;
    char padAC[0xB8 - 0xAC];
    char *controller;
    u8 idleStage;
    char padBD[0xF8 - 0xBD];
    float heading;
    char padFC[4];
};

typedef struct {
    char pad00[0x80];
    float position[4];
    char pad90[0x249C - 0x90];
    ActorObject *attackTarget;
} ActorPlayerBlock;
extern ActorPlayerBlock D_00189E20;
extern s32 D_L11_001B30C8[] __attribute__((sda));
extern ActorObject *D_L11_001B359C[] __attribute__((sda));
extern s32 D_L11_001B35B8[] __attribute__((sda));
extern u16 *D_L11_001FC420[];
extern float D_L11_001B1D60 SDATA(D_L11_001B1D60);
extern s32 D_L11_001B1D64 SDATA(D_L11_001B1D64);
extern float D_L11_001B1D6C SDATA(D_L11_001B1D6C);
extern float D_L11_001B1D70 SDATA(D_L11_001B1D70);
extern float D_L11_001B1D74 SDATA(D_L11_001B1D74);
extern float D_L11_001B1D78 SDATA(D_L11_001B1D78);
extern float D_L11_001B1D7C SDATA(D_L11_001B1D7C);
extern float D_L11_001B1D80 SDATA(D_L11_001B1D80);
extern float D_L11_001B1D84 SDATA(D_L11_001B1D84);
extern float D_L11_001B1D88 SDATA(D_L11_001B1D88);
extern float D_L11_001B1D8C SDATA(D_L11_001B1D8C);
extern void func_002A7750(void *, int, int);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern float func_L02_002F21C0(void *, void *);
extern float func_002A7878(float, float);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_002A7470(void *, int, int, int);
extern float func_0029F530(void *);
extern float func_00283C80(float, float);
extern int func_002B3890(void *);
extern int func_002B3868(void *);
extern char *func_L11_004417E8(void *);
extern int func_L11_00441808(void *, void *);
extern int func_L11_00441858(void *);
extern int func_002A77E0(int);
extern void func_L11_004565D8(void *, void *);
extern int func_L01_00321178(void *, void *);
extern int func_002B1C20(void *, void *);
extern void func_L02_003FC248(void *, int, int);
extern void func_L01_003E9CF8(void *, int, void (*)(char *));
extern void func_L11_00456938(void *);
extern void func_L11_00456540(char *);
extern void func_L11_00455DF8(void *);
extern void func_L11_00456010(void *);
extern int func_L11_004566C0(void *);
extern void func_L11_00456070(void *, void *);
extern void func_002A7CA0(void *, float, float, float, float *, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_L11_00456A48(void *, int, float, float, float, float, float, float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A8D70(void *, float, float, int, int, float, int, int, int);

/* Per-frame update of the Joba fighter (moby class 3577): it walks toward its goal or the player, charges, and swings at close range. */
void func_L11_00454F18(ActorObject *actor)
{
    ActorState *data = actor->data;
    float target[4];
    float scratch[4];
    float hit[4];
    float distance, heading, delta, animationFrame;
    int flags, secondaryState;
    u16 *ids;
    ActorObject *entity;

    if (actor->state == 1) return;
    UpdateJobaFighterContacts(actor);
    if (actor->state == 1) return;
    if (data->attached == 0) {
        data->target = 0;
        if (actor->secondaryState == 3) SetMobyState(actor, 4, 2);
    }
    animationFrame = GetMobyAnimationValue(actor);
    if (data->target) {
        *(ActorQuadword *)target = *(ActorQuadword *)(data->target->pos);
        heading = FastMatrixHelperA(data->target->pos[0] - actor->pos[0],
                                data->target->pos[1] - actor->pos[1]);
    } else {
        *(ActorQuadword *)target = *(ActorQuadword *)gHeroState.position;
        heading = FastMatrixHelperA(gHeroState.position[0] - actor->pos[0],
                                gHeroState.position[1] - actor->pos[1]);
    }
    delta = FastDiffRots(actor->heading, heading);
    distance = vec_distance_xy(actor->pos, target);
    /* The entry substate also selects the initial walking animation. */
    secondaryState = actor->secondaryState;
    switch (secondaryState) {
    case 2:
        if (SetSecondPendingFlag(actor)) {
            actor->speed = RandomFloatRange(0.5f, 1.25f);
            SetControllerSpeedLimits(actor, 0.00222222228f, 0.0666666701f, 0.00116355298f, 0.104719773f);
            if (actor->nextAnimation != secondaryState) StartAnimationBlended(actor, 2, 0, 10);
            actor->idleStage = 0;
            PickJobaFighterGoalNearTarget(actor, GetArenaCenterPoint(actor->controller));
            actor->timer = 10000;
        }
        if (actor->idleStage == 1 && actor->timer >= 301) {
            if (actor->nextAnimation) StartAnimationBlended(actor, 0, 0, 10);
            actor->timer = RandomIntBelow(100);
        }
        if (data->attached) {
            actor->speed = 1.0f;
            SetMobyState(actor, 5, 3);
        }
        if (actor->idleStage == 0 && vec_distance_xy(actor->pos, data->goal) < 0.5f)
            actor->idleStage = 1;
        else TurnMobyTowardTarget(actor, data->goal);
        break;
    case 3:
        break;
    case 4:
        flags = DispatchActionByKind(actor, data->contact);
        if (flags & 1) {
            SetMobyAnimTypeThree(actor, 0, -1);
            QueueMobyForGlowEffect(actor, 0, ResetJobaFighterToIdle);
        } else if (flags & 2) ChooseJobaFighterAction(actor);
        break;
    }
    switch (actor->state) {
    case 3:
        if (SetFirstPendingFlag(actor)) {
            actor->idleStage = 0;
            if (actor->nextAnimation != 0) StartAnimationBlended(actor, 0, 0, 0);
            actor->timer = 0;
        }
        if (actor->idleStage == 0 && data->idleDelay < actor->timer) {
            if (actor->nextAnimation != 3) StartAnimationBlended(actor, 3, 0, 10);
            actor->idleStage = 1;
        } else if (actor->idleStage == 1) {
            if (IsPointInArenaPolygon(actor->controller, actor->pos))
                SetMobyState(actor, 4, 2);
            TurnMobyTowardTarget(actor, GetArenaCenterPoint(actor->controller));
        }
        break;
    case 5:
        if (SetFirstPendingFlag(actor)) {
            if (actor->nextAnimation != RandomIntBelow(2) + 1)
                StartAnimationBlended(actor, RandomIntBelow(2) + 1, 0, 10);
        }
        MobySpringTurn(actor, heading, 0.001f, 0.01f, &data->turnRate, 0.1f);
        if (actor->animationFlags & 2) ChooseJobaFighterAction(actor);
        break;
    case 6:
        if (SetFirstPendingFlag(actor)) {
            SetControllerSpeedLimits(actor, 0.00222222228f, 0.0666666701f, 0.00116355298f, 0.104719773f);
            if (actor->nextAnimation != 2) StartAnimationBlended(actor, 2, 0, 10);
        }
        TurnMobyTowardTarget(actor, target);
        if (D_L11_001B1D60 < distance) ChooseJobaFighterAction(actor);
        else if (distance < 2.7f) ChooseJobaFighterAction(actor);
        break;
    case 7:
        if (SetFirstPendingFlag(actor)) {
            SetControllerSpeedLimits(actor, 0.00333333341f, 0.100000009f, 0.00116355298f, 0.104719773f);
            if (actor->nextAnimation != 3) StartAnimationBlended(actor, 3, 0, 10);
            actor->timer = 0;
        }
        if (data->aimTarget == 0 && (D_L11_001B30C8[0] & 0x3F) == (((s32)actor >> 8) & 0x3F)) {
            for (ids = gGroupIdLists[GetArenaGroupIndex(actor->controller)];
                 (GetArenaGroupIndex(actor->controller) & 0xFF) != 0xFF &&
                 GetArenaGroupIndex(actor->controller) <= D_L11_001B35B8[0] && ids != 0 &&
                 ((s16)ids[-1] >= 0 || ids == gGroupIdLists[GetArenaGroupIndex(actor->controller)]); ids++) {
                entity = gMobyTable_L11[0] + (*ids & 0x7FFF);
                if (entity == 0) break;
                if (entity->classId == 0xDF9) continue;
                if (FastDiffRots(actor->heading, FastMatrixHelperA(entity->pos[0] - actor->pos[0],
                                                        entity->pos[1] - actor->pos[1])) < 0.52359885f &&
                    DistanceSquaredXY(actor->pos, entity->pos) < 20.0f) {
                    data->aimTarget = entity;
                    break;
                }
            }
        } else if (data->aimTarget == 0 || (data->aimTarget->state == 0xFE || (data->aimTarget->state == 0xFD || data->aimTarget->state < 2))) {
            data->aimTarget = 0;
        }
        if (!TurnTowardNearbyGroupEntity(actor)) {
            if (data->aimTarget) WalkJobaFighterWithDust(actor, data->aimTarget->pos);
            else WalkJobaFighterWithDust(actor, target);
        }
        TransformMobyJointToWorld(actor, 1, scratch);
        DamageObjectsInRadius(actor, (int)scratch, D_L11_001B1D6C, 0.0f, 100.0f, D_L11_001B1D70,
                          D_L11_001B1D78, D_L11_001B1D80, D_L11_001B1D88);
        if (distance < 2.7f && delta < 0.3490659f) SetMobyState(actor, 11, -1);
        if (D_L11_001B1D64 < actor->timer) SetMobyState(actor, 6, -1);
        break;
    case 9:
        if (SetFirstPendingFlag(actor)) {
            if (actor->nextAnimation != 4) StartAnimationBlended(actor, 4, 0, 10);
            data->step = 0.0069444445f;
            SetControllerSpeedLimits(actor, 0.00666666683f, 0.200000018f, 0.000218166184f, 0.00639954163f);
        }
        if (data->aimTarget == 0 && (D_L11_001B30C8[0] & 0x3F) == (((s32)actor >> 8) & 0x3F)) {
            for (ids = gGroupIdLists[GetArenaGroupIndex(actor->controller)];
                 (GetArenaGroupIndex(actor->controller) & 0xFF) != 0xFF &&
                 GetArenaGroupIndex(actor->controller) <= D_L11_001B35B8[0] && ids != 0 &&
                 ((s16)ids[-1] >= 0 || ids == gGroupIdLists[GetArenaGroupIndex(actor->controller)]); ids++) {
                entity = gMobyTable_L11[0] + (*ids & 0x7FFF);
                if (entity == 0) break;
                if (entity->classId == 0xDF9) continue;
                if (FastDiffRots(actor->heading, FastMatrixHelperA(entity->pos[0] - actor->pos[0],
                                                        entity->pos[1] - actor->pos[1])) < 0.52359885f &&
                    DistanceSquaredXY(actor->pos, entity->pos) < 20.0f) {
                    data->aimTarget = entity;
                    break;
                }
            }
        } else if (data->aimTarget == 0 || (data->aimTarget->state == 0xFE || (data->aimTarget->state == 0xFD || data->aimTarget->state < 2))) {
            data->aimTarget = 0;
        }
        if (data->aimTarget) {
            TurnMobyTowardTarget(actor, data->aimTarget->pos);
            MobySpringTurn(actor,
                          FastMatrixHelperA(data->aimTarget->pos[0] - actor->pos[0],
                                        data->aimTarget->pos[1] - actor->pos[1]),
                          0.001f, 0.01f, &data->turnRate, 0.1f);
        } else {
            TurnMobyTowardTarget(actor, target);
            MobySpringTurn(actor, heading, 0.001f, 0.01f, &data->turnRate, 0.1f);
        }
        TransformMobyJointToWorld(actor, 1, scratch);
        DamageObjectsInRadius(actor, (int)scratch, D_L11_001B1D6C, (float)data->contactDamage, 100.0f, D_L11_001B1D74,
                          D_L11_001B1D7C, D_L11_001B1D80, D_L11_001B1D88);
        if (gHeroState.attackTarget == actor) SetMobyState(actor, 10, -1);
        if (0.38397247f < delta) SetMobyState(actor, 8, -1);
        break;
    case 10:
        if (SetFirstPendingFlag(actor)) {
            if (actor->nextAnimation != 5) StartAnimationBlended(actor, 5, 0, 3);
            SetControllerSpeedLimits(actor, 0.00416666688f, 0.0333333351f, 0.000436332368f, 0.0130899716f);
        }
        scratch[0] = 4.0f * FastSinOrCosA(actor->heading);
        scratch[1] = 4.0f * FastSinOrCosB(actor->heading);
        scratch[2] = 0.0f;
        FastVecAdd(scratch, actor->pos, scratch);
        TurnMobyTowardTarget(actor, scratch);
        TransformMobyJointToWorld(actor, 1, hit);
        DamageObjectsInRadius(actor, (int)hit, D_L11_001B1D6C, (float)data->contactDamage, 100.0f, D_L11_001B1D74,
                          D_L11_001B1D7C, D_L11_001B1D84, D_L11_001B1D8C);
        if (actor->animationFlags & 2) SetMobyState(actor, 8, -1);
        break;
    case 8:
        if (SetFirstPendingFlag(actor)) {
            if (actor->nextAnimation != 4) StartAnimationBlended(actor, 4, 0, 10);
        }
        scratch[0] = 4.0f * FastSinOrCosA(actor->heading);
        scratch[1] = 4.0f * FastSinOrCosB(actor->heading);
        scratch[2] = 0.0f;
        FastVecAdd(scratch, actor->pos, scratch);
        TurnMobyTowardTarget(actor, scratch);
        MobySpringTurn(actor, heading, 0.001f, 0.01f, &data->turnRate, 0.1f);
        TransformMobyJointToWorld(actor, 1, hit);
        DamageObjectsInRadius(actor, (int)hit, D_L11_001B1D6C, 0.0f, 100.0f, D_L11_001B1D70,
                          D_L11_001B1D78, D_L11_001B1D80, D_L11_001B1D88);
        if (actor->animationFlags & 2) ChooseJobaFighterAction(actor);
        break;
    case 11:
        if (SetFirstPendingFlag(actor)) {
            if (actor->nextAnimation != 6) StartAnimationBlended(actor, 6, 0, 5);
        }
        if (actor->animation == 6 && animationFrame >= 10.0f && animationFrame <= 15.0f)
            TestHitAtBone(actor, 1.0f, (float)data->meleeDamage, 1, 1, 1.0f, 0, 1, 0);
        if (actor->animationFlags & 2) {
            if (distance < 2.7f && delta < 0.3490659f) SetMobyState(actor, 11, -1);
            else ChooseJobaFighterAction(actor);
        }
        break;
    case 12:
        if (actor->animationFlags & 2) ChooseJobaFighterAction(actor);
        break;
    }
    CountFrameAndCheckContact(actor);
}
