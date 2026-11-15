#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vec4;
extern void part_spawn_sparks_around_moby(void *, void *, void *);
extern float vec_length_xy(void *);
extern void ApproachValue(float *, float, float);
extern void vec_fast_normalize_helper(void *, void *, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern int GetCollHitMaterial(void);
extern void *moby_spawn_scaled_effect(void *, float);
extern float coll_get_ground_height_under_object(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_fabs(float);
extern float moby_get_anim_value(void *);
extern int math_solve_quadratic(float *, float *, float, float, float);
extern void MobySpringTurn(void *, void *, float, float, float, float);
extern int coll_process_hit(float, void *, int, void *, void *);
extern float IntToFloat(int);
extern int moby_is_in_special_class_range(void *);
extern void part_queue_impact_effect(void *, float, int, int, void *, void *);
extern float FastVecLength(void *);
extern int CollLine(void *, void *, int, void *, int);
extern int coll_test_point(void *, float, int, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern int *D_L06_001C3D00[];
extern Vec4 D_L06_001BFCA0, D_L06_001BFCB0;
/* Adapted from OpenRAC/rac1-decomp (GPL-3.0),
 * src/overlays/shared/moby_ground_collision.c, mine_fall. */
/* Drops a falling object under gravity, lands it on the ground and slides it along walls. Returns flags that say what it touched. */
int mine_fall(char *moby, char *st) {
    float startPos[4];
    float probePos[4];
    float endPos[4];
    float sweepEnd[4];
    float hitNormal[4];
    float slideVec[4];
    float speed, root0, root1, clampedSpeed;

    Vec4 *hit;
    char *hitRecord;
    int flags = 0;

    float unitScale, groundHeight, timeToLand, tmp, rate, one;
    int count, i;

    *(float *)(st + 0x8) = *(float *)(st + 0x8) - *(float *)(st + 0x10);
    if (*(unsigned char *)(st + 0x2E) == 1) {
        if (*(unsigned char *)(st + 0x2F) != 0) {
            part_spawn_sparks_around_moby(moby, st, (void *)(int)*(unsigned char *)(st + 0x2F));
        }
    }

    speed = vec_length_xy(st);
    tmp = (*(short *)(st + 0x3E) == 2) ? 0.0f : *(float *)(st + 0x4C);
    ApproachValue(&speed, tmp, *(float *)(st + 0x14));
    vec_fast_normalize_helper((float *)st, (float *)st, speed);
    if (*(float *)(st + 0x1C) < *(float *)(st + 0x8)) {
        *(float *)(st + 0x8) = *(float *)(st + 0x1C);
    }

    qcopy(probePos, moby + 0x10);
    probePos[2] = probePos[2] + *(float *)(st + 0x28);
    groundHeight = coll_probe_ground_height_below(probePos, 0, 0.5f);
    if (GetCollHitMaterial() == 0) {
        if (*(float *)(st + 0x5C) == 0.0f && groundHeight <= probePos[2] && probePos[2] + *(float *)(st + 0x8) < groundHeight) {
            *(float *)(st + 0x5C) = 1.0f;
            probePos[2] = groundHeight;
            moby_spawn_scaled_effect(probePos, 3.0f);
        }
        groundHeight = coll_get_ground_height_under_object((moby + 0x10));
    } else {
        if ((*(int *)(st + 0x24) & 0x10) || *(short *)(st + 0x3E) == 2) {
            FastVecAdd(endPos, (moby + 0x10), st);
            if (coll_get_ground_height_under_object(endPos) < groundHeight - 0.25f) {
                vec_fast_normalize_helper((float *)st, (float *)st, 0.0f);
            }
        }
    }

    if (*(float *)(st + 0x5C) != 0.0f) {
        if (*(float *)(st + 0x5C) < 4.0f) {
            FastVecScale(st, st, 0.7f);
        }
        if (*(float *)(st + 0x5C) < 7.0f) {
            *(float *)(st + 0x5C) = *(float *)(st + 0x5C) + 1.0f;
            *(float *)(st + 0x10) = *(float *)(st + 0x10) * 0.75f;
        }
    }
    if (*(float *)(moby + 0x10) < 2.0f || 1021.0f < *(float *)(moby + 0x10)
        || *(float *)(moby + 0x14) < 2.0f || 1021.0f < *(float *)(moby + 0x14)
        || *(float *)(moby + 0x18) < 2.0f || 1021.0f < *(float *)(moby + 0x18)) {
        flags = 0x100;
    }

    if (*(float *)(st + 0x54) != -1.0f && *(float *)(st + 0x50) != -1.0f) {
        switch (*(short *)(st + 0x3E)) {
        case 0: {
            float fallRate;
            float numerator0;
            fallRate = math_fabs(*(float *)(st + 0x8) / *(float *)(st + 0x10));
            if (2.0f < fallRate) {
                tmp = moby_get_anim_value(moby);
                numerator0 = *(float *)(st + 0x50) - tmp;
                rate = numerator0 / fallRate;
                if (0.0f < rate) {
                    ApproachValue((float *)(moby + 0x48), rate, 0.1f);
                }
            }
            break;
        }
        case 1:
            tmp = moby_get_anim_value(moby);
            if (*(float *)(st + 0x54) <= tmp) {
                *(int *)(moby + 0x48) = 0;
            } else {
                float numerator1;
                float halfDrop = *(float *)(st + 0x10) * -0.5f;
                timeToLand = 60.0f;
                count = math_solve_quadratic(&root0, &root1, halfDrop, *(float *)(st + 0x8) - halfDrop, *(float *)(moby + 0x18) - groundHeight);
                if (count > 0 && 0.0f < root0 && root0 < timeToLand) {
                    timeToLand = root0;
                }
                if (timeToLand < 0.0001f) {
                    timeToLand = 0.0001f;
                }
                tmp = moby_get_anim_value(moby);
                numerator1 = *(float *)(st + 0x54) - tmp;
                rate = numerator1 / timeToLand;
                if (2.0f < rate) {
                    rate = 2.0f;
                } else if (rate < 0.0f) {
                    rate = 0.0f;
                }
                ApproachValue((float *)(moby + 0x48), rate, 0.1f);
            }
            break;
        case 2:
            *(float *)(moby + 0x48) = 1.0f;
            break;
        }
    }

    if (*(unsigned char *)(moby + 0x60) & 2) {
        flags |= 0x40;
    }
    if (!(*(int *)(st + 0x24) & 4)) {
        MobySpringTurn(moby, (float *)(st + 0x44), *(float *)(st + 0x40), 0.02f, 0.3f, *(float *)(st + 0x48));
    }

    i = 0;
    qcopy(startPos, (moby + 0x10));
    startPos[2] = startPos[2] + *(float *)(st + 0x28);
    FastVecAdd((moby + 0x10), (moby + 0x10), st);
    qcopy(endPos, (moby + 0x10));
    endPos[2] = endPos[2] + *(float *)(st + 0x28);
    FastVecAdd(sweepEnd, endPos, st);
    count = coll_process_hit(IntToFloat(*(int *)(st + 0x20)) * 0.0010742187732830644f, sweepEnd, 16, moby, 0);
    if (i < count) {
        int **listPtr = D_L06_001C3D00;
        int remaining = count;
        do {
            if (moby_is_in_special_class_range(*listPtr) != 0) {
                part_queue_impact_effect((char *)*listPtr, 1.0f, (int)moby, 0x10000, (moby + 0x10), st);
            }
            listPtr++;
        } while (--remaining != 0);
    }

    unitScale = 0.0009765625f;
    tmp = FastVecLength(st);
    if ((float)*(int *)(st + 0x20) * unitScale < tmp) {
        CollLine(startPos, endPos, 36, moby, 0);
        qcopy(endPos, &D_L06_001BFCA0);
    }
    if (coll_test_point(endPos, IntToFloat(*(int *)(st + 0x20)) * unitScale, 36, moby) != 0) {
        flags |= 2;
        hit = &D_L06_001BFCB0;
        qcopy((moby + 0x10), hit);
        one = 1.0f;
        *(float *)(moby + 0x18) = *(float *)(moby + 0x18) - *(float *)(st + 0x28);
        vec_scale_to_length(hitNormal, (char *)hit + 0x10, one);
        if (0.7070000171661377f <= hitNormal[2]) {
            float impact = FastVecDot(st, hitNormal);
            if (impact < 0.0f) {
                hitRecord = (char *)hit - 0x30;
                if (*(int *)(hitRecord + 0x18) == 0 || *(int *)(hitRecord + 0x1C) > 0) {
                    flags |= 1;
                    *(short *)(st + 0x3E) = 2;
                }
                vec_scale_to_length(slideVec, hitNormal, impact);
                FastVecSub(st, st, slideVec);
                if (*(short *)(st + 0x3E) == 2) {
                    clampedSpeed = FastVecLength(st);
                    ApproachValue(&clampedSpeed, 0.0f, *(float *)(st + 0x10));
                    vec_scale_to_length(st, st, clampedSpeed);
                }
            }
        } else {
            float dot = FastVecDot(st, hitNormal);
            if (dot < 0.0f) {
                dot = dot * -(*(float *)(st + 0x30) + one);
                vec_scale_to_length(slideVec, hitNormal, dot);
                FastVecAdd(st, st, slideVec);
            }
        }
    }
    if (*(short *)(st + 0x3E) == 0) {
        if (*(float *)(st + 0x8) < 0.0f) {
            *(short *)(st + 0x3E) = 1;
        }
    }
    return flags;
}
