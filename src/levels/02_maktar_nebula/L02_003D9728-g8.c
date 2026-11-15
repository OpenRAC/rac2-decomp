#include "names.h"
/* func_L02_003D9728: state handler of a Maktar walker: ten-state switch, footstep and
 * impact camera shakes (D_L02_001BA3C0), beam pursuit. */
extern int D_L02_001B359C;
extern int D_L02_001B03F0 __attribute__((sda));
typedef struct { char pad[0x160]; float amount; int pad2; int time; int phase; } Shake;
extern Shake D_L02_001BA3C0;
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_0029F530(char *);
extern void func_002B60B0(char *, float, float, float, float);
extern void func_002B5278(char *, float);
extern float func_L02_00321C30(void *, void *, float);
extern void *func_L02_003FC0B8(void *);
extern float *func_L02_003FC098(void *);
extern int func_L00_003206B8(void *, void *);
extern void func_L01_00321178(char *, void *);
extern void *func_0029FCC0(char *, int, void *);
extern void func_002833F0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L01_00322288(char *, float);
extern float func_00283C28(float);
extern void func_L02_003DAB68(char *);
extern float func_002AA2E8(float *, float, float);

/* Makes the walker move and shake the camera with its footsteps and impacts, based on its current walking mode. */
void func_L02_003D9728(char *moby) {
    float jointBefore[4];
    float jointAfter[4];
    float moveDelta[4];
    char *vars = *(char **)(moby + 0x68);
    float *targetPos = (float *)(vars + 0x230);
    float distance = vec_distance_xy(moby + 0x10, targetPos);
    float heading = FastMatrixHelperA(targetPos[0] - *(float *)(moby + 0x10), targetPos[1] - *(float *)(moby + 0x14));
    float animFrame = GetMobyAnimationValue(moby);
    char *legsMoby = (char *)((*(int *)(*(char **)(moby + 0x68) + 0x244) << 8) + gMobyPool_L02);
    int savedValue = *(int *)(legsMoby + 0x98);
    unsigned int walkMode;
    float pursuitSpeed;
    *(int *)(legsMoby + 0x98) = 0;
    SetControllerSpeedLimits(moby, 0.0016666667f, 0.05166667f, 0.003490659f, 0.10471977f);
    walkMode = *(unsigned char *)(moby + 0x42);
    switch (walkMode) {
    case 0:
    if (*(unsigned char *)(moby + 0x20) != 4)
        StepMovementAtOwnPositionWithFactor(moby, *(float *)(moby + 0xF8));
    else
        StepPositionTowardTargetLimited(moby + 0x10, &D_L02_001B03F0, 0.16666667f);
    break;
    case 1:
    if (IsPointInsideRecordVolume(moby + 0x10, GetArenaStateWord84(*(void **)(moby + 0xB8))))
        TurnMobyTowardTarget(moby, targetPos);
    else
        TurnMobyTowardTarget(moby, GetArenaCameraPoint(*(void **)(moby + 0xB8)));
    if ((animFrame > 0.0f && animFrame < 2.0f) || (animFrame > 15.0f && animFrame < 17.0f) ||
        (animFrame > 30.0f && animFrame < 32.0f) || (animFrame > 45.0f && animFrame < 47.0f)) {
        D_L02_001BA3C0.amount = 0.05f;
        D_L02_001BA3C0.time = 15;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 2:
    if (animFrame > 12.0f && animFrame < 25.0f) {
        TransformMobyJointToWorld(moby, 4, jointBefore);
        StepMovementAtOwnPositionWithFactor(moby, heading);
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        TransformMobyJointToWorld(moby, 4, jointAfter);
        FastVecSub(moveDelta, jointBefore, jointAfter);
        FastVecAdd(moby + 0x10, moby + 0x10, moveDelta);
    } else if (animFrame > 42.0f && animFrame < 55.0f) {
        TransformMobyJointToWorld(moby, 8, jointBefore);
        StepMovementAtOwnPositionWithFactor(moby, heading);
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        TransformMobyJointToWorld(moby, 8, jointAfter);
        FastVecSub(moveDelta, jointBefore, jointAfter);
        FastVecAdd(moby + 0x10, moby + 0x10, moveDelta);
    }
    if ((animFrame > 0.0f && animFrame < 2.0f) || (animFrame > 29.0f && animFrame < 31.0f)) {
        D_L02_001BA3C0.amount = 0.1f;
        D_L02_001BA3C0.time = 15;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 3:
        if (animFrame < 23.0f)
            break;
    case 4:
    StartMobyEffectFromEntry(moby, FastMatrixHelperA(*(float *)(vars + 0xF0), *(float *)(vars + 0xF4)));
    *(float *)(vars + 0xF8) -= *(float *)(vars + 0x7C);
    FastVecAdd(moby + 0x10, moby + 0x10, vars + 0xF0);
    break;
    case 5:
    if (animFrame > 3.0f && animFrame < 5.0f) {
        D_L02_001BA3C0.amount = 0.4f;
        D_L02_001BA3C0.time = 25;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 6:
    if (animFrame > 20.0f && animFrame < 22.0f) {
        D_L02_001BA3C0.amount = 0.2f;
        D_L02_001BA3C0.time = 25;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 7:
    if ((unsigned int)(*(unsigned char *)(moby + 0x20) - 10) >= 2) {
        *(float *)(moby + 0xF8) += ((*(float *)(vars + 0x20) / (float)*(short *)(vars + 0x24)) * -90.0f + 160.0f) * 0.00029088825f;
        *(float *)(moby + 0xF8) = FastFloatHelperG(*(float *)(moby + 0xF8));
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        SpawnBeamHitEffects(moby);
        if (distance > 12.0f && *(unsigned char *)(moby + 0x20) != 10) {
            if (IsPointInsideRecordVolume(moby + 0x10, GetArenaStateWord84(*(void **)(moby + 0xB8)))) {
                pursuitSpeed = ((*(float *)(vars + 0x20) / (float)*(short *)(vars + 0x24)) * -2.2f + 3.0f) * 0.016666668f;
                ApproachValue((float *)(moby + 0x10), targetPos[0], pursuitSpeed);
                ApproachValue((float *)(moby + 0x14), targetPos[1], pursuitSpeed);
            } else {
                ApproachValue((float *)(moby + 0x10), GetArenaCameraPoint(*(void **)(moby + 0xB8))[0], 0.33333334f);
                ApproachValue((float *)(moby + 0x14), GetArenaCameraPoint(*(void **)(moby + 0xB8))[1], 0.33333334f);
            }
        }
    }
    break;
    case 8:
    if (animFrame > 30.0f && animFrame < 32.0f) {
        D_L02_001BA3C0.amount = 0.2f;
        D_L02_001BA3C0.time = 25;
        D_L02_001BA3C0.phase = 0;
    }
    case 9:
        break;
    }
    if (*(float *)(moby + 0x18) < GetArenaCameraPoint(*(void **)(moby + 0xB8))[2])
        *(float *)(moby + 0x18) = GetArenaCameraPoint(*(void **)(moby + 0xB8))[2];
    *(int *)((*(int *)(*(char **)(moby + 0x68) + 0x244) << 8) + gMobyPool_L02 + 0x98) = savedValue;
}
