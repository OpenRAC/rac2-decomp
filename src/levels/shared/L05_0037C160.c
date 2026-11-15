#include "common.h"

extern char *func_002ED688(char *);
extern int func_001163B0(void);
extern float func_002A7878(float, float);
extern void func_00282CC0(void *, void *, void *), func_00283098(void *, void *, void *);
extern int func_002EE6A8(char *);
extern void func_002ED6B0(char *), func_002EE6E0(char *), func_002EE238(char *), func_002EE610(char *), func_002EE000(char *);
extern void func_002EE920(char *, void *), func_002EE678(char *, int);
extern int func_002EEB00(char *), func_002ED948(char *);
extern void func_002ED9C0(char *), func_002EE7B8(char *), func_002EE8B0(char *);
extern float func_00283198(float), func_00283180(float), func_00283B98(float, float);
extern void func_00282F20(void *, void *, float), func_00282DD8(void *, void *, void *);
extern int func_00283DB8(void *, float), func_002A7820(int, int);
extern char *D_L05_001B9710;

typedef unsigned int U128_C160 __attribute__((mode(TI)));

/* Update the movement state and target position of this object. */
void func_L05_0037C160(char *obj)
{
    float v[4], v1[4], v2[4], v3[4], v4[4];
    U128_C160 axes[2];
    float v7[4], v8[4], v9[4], probe[4], tmp[4];
    char *s = GetMobyMotionData(obj);
    char *player, *p;
    float direction;
    if (!s) return;
    axes[0] = 0;
    axes[1] = 0;
    ((float *)&axes[0])[2] = 1.0f;
    ((float *)&axes[1])[0] = 1.0f;
    qcopy(s + 0xB0, obj + 0x10);
    if (GetFollowerState(obj) != 8) FastVecAdd(obj + 0x10, s + 0x90, obj + 0x10);
    ClampFollowerToRangeAndSpawnSparks(obj);
    CheckFollowerHazardContact(obj);
    MoveFollowerTowardTarget(obj);
    LimitObjectSpeed(obj);
    UpdateBankedOrientation(obj);
    player = D_L05_001B9710;
    switch (GetFollowerState(obj)) {
    case 7:
        vec_scale_to_length(v, *(char **)(s + 0x120) + 0xC0, -50.0f);
        FastVecAdd(v, *(char **)(s + 0x120) + 0x10, v);
        SetFollowerPushVector(obj, v);
        if (HasFollowerReachedTarget(obj)) {
            SetFollowerState(obj, 8);
            *(int *)(s + 0x130) = 900;
            direction = (Rand() & 1) ? -1.0f : 1.0f;
            *(float *)(s + 0x140) = direction;
            *(float *)(s + 0x134) = direction < 0.0f ? 1.5707964f : -1.5707964f;
            *(float *)(s + 0x144) = RandomFloatRange(5.0f, 15.0f);
        }
        break;
    case 8: {
            float *basis;
            v[2] = 0;
            v[0] = FastSinOrCosB(*(float *)(s + 0x134)) * *(float *)(s + 0x144);
            v[1] = -FastSinOrCosA(*(float *)(s + 0x134)) * *(float *)(s + 0x144);
            v[3] = 0;
            *(float *)(s + 0x134) = FastAddRotations(*(float *)(s + 0x134), *(float *)(s + 0x140) * 0.013089972f);
            qcopy(v9, player + 0x20);
            basis = v7;
            FastVecCross(v8, &axes[1], v9);
            vec_scale_to_length(v8, v8, 1.0f);
            FastVecCross(basis, v9, v8);
            matrix_mul_vec3(v, v, basis);
            FastVecAdd(obj + 0x10, *(char **)(s + 0x120) + 0x10, v);
            SetFollowerPushVector(obj, v);
            if (TryPlaceFollowerAtSavedSpot(obj))SetFollowerState(obj, 9);
            if (HasFollowerReachedTarget(obj)) {
                qcopy(probe, obj + 0x10);
                probe[3] = 5;
                if (FastMathHelperA(probe, 256.0f) == -1) {
                    ReleaseMotionSlot(obj);
                    SetFollowerState(obj, 1);
                }
            }
            break;
        }
    case 9:
        qcopy(probe, obj + 0x10);
        probe[3] = 5;
        if (FastMathHelperA(probe, 256.0f) == -1) {
            ReleaseMotionSlot(obj);
            SetFollowerState(obj, 1);
        }
        break;
    case 4:
        if (!*(char **)(s + 0x120)) {
            ReleaseMotionSlot(obj);
            SetFollowerState(obj, 1);
            break;
        }
        vec_scale_to_length(v, *(char **)(s + 0x120) + 0xC0, 25.0f);
        if (*(int *)(s + 0xFC)) {
            matrix_mul_vec3(tmp, s + 0x70, *(char **)(s + 0x120) + 0xC0);
            FastVecAdd(v, tmp, v);
        }
        FastVecAdd(v, *(char **)(s + 0x120) + 0x10, v);
        SetFollowerPushVector(obj, v);
        if (HasFollowerReachedTarget(obj)) {
            SetFollowerState(obj, 5);
            *(int *)(s + 0x130) = RandomIntRange(300, 600);
        }
        break;
    case 5:
        if (!*(char **)(s + 0x120)) {
            ReleaseMotionSlot(obj);
            SetFollowerState(obj, 1);
            break;
        }
        vec_scale_to_length(v, *(char **)(s + 0x120) + 0xC0, 5.0f);
        if (*(int *)(s + 0xFC)) {
            matrix_mul_vec3(tmp, s + 0x70, *(char **)(s + 0x120) + 0xC0);
            FastVecAdd(v, tmp, v);
        }
        FastVecAdd(v, *(char **)(s + 0x120) + 0x10, v);
        SetFollowerPushVector(obj, v);
        if (HasFollowerReachedTarget(obj)) {
            ReleaseMotionSlot(obj);
            SetFollowerState(obj, 1);
        }
        break;
    case 6:
        if (!*(char **)(s + 0x120)) {
            ReleaseMotionSlot(obj);
            SetFollowerState(obj, 1);
            break;
        }
        vec_scale_to_length(v, *(char **)(s + 0x120) + 0xC0, 10.0f);
        vec_scale_to_length(v1, *(char **)(s + 0x120) + 0xE0, 0.05f);
        if (*(int *)(s + 0xFC)) {
            matrix_mul_vec3(tmp, s + 0x70, *(char **)(s + 0x120) + 0xC0);
            FastVecAdd(v, tmp, v);
        }
        FastVecAdd(v, v1, v);
        FastVecAdd(v, *(char **)(s + 0x120) + 0x10, v);
        SetFollowerPushVector(obj, v);
        if (HasFollowerReachedTarget(obj)) {
            ReleaseMotionSlot(obj);
            SetFollowerState(obj, 1);
        }
        break;
    case 3:
        p = *(char **)(s + 0x10);
        qcopy(v2, p + 0xC0);
        FastVecCross(v3, v2, &axes[0]);
        vec_scale_to_length(v3, v3, 1.0f);
        FastVecCross(v4, v3, v2);
        matrix_mul_vec3(v, s, v2);
        FastVecAdd(v, p + 0x10, v);
        SetFollowerPushVector(obj, v);
        break;
    case 1: if (HasFollowerReachedTarget(obj))StartFollowerRandomPush(obj);
        break;
    case 13: if (HasFollowerReachedTarget(obj))StartFollowerPushFromTarget(obj);
        break;
    }
}
