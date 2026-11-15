#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vec4;
extern void func_002AB250(void *, void *, void *);
extern float func_00282E20(void *);
extern void func_002AA2E8(float *, float, float);
extern void func_00282F70(void *, void *, float);
extern float func_002A89A8(void *, int, float);
extern int func_00278E78(void);
extern void *func_00312D58(void *, float);
extern float func_002A8A20(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282C48(float);
extern float func_0029F530(void *);
extern int func_002A88A0(float *, float *, float, float, float);
extern void func_002A7CA0(void *, void *, float, float, float, float);
extern int func_00277F48(float, void *, int, void *, void *);
extern float func_00283CE0(int);
extern int func_002ABB78(void *);
extern void func_002A8F70(void *, float, int, int, void *, void *);
extern float func_00282DF0(void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00277258(void *, float, int, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern int *D_L06_001C3D00[];
extern Vec4 D_L06_001BFCA0, D_L06_001BFCB0;
/* Adapted from OpenRAC/rac1-decomp (GPL-3.0),
 * src/overlays/shared/moby_ground_collision.c, mine_fall. */
/* Drops a falling object under gravity, lands it on the ground and slides it along walls. Returns flags that say what it touched. */
int func_L06_0035EA68(char *moby, char *st) {
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
            SpawnSparksAroundMoby_002AB250(moby, st, (void *)(int)*(unsigned char *)(st + 0x2F));
        }
    }

    speed = vec_length_xy(st);
    tmp = (*(short *)(st + 0x3E) == 2) ? 0.0f : *(float *)(st + 0x4C);
    ApproachValue(&speed, tmp, *(float *)(st + 0x14));
    FastVectorNormalizeHelper((float *)st, (float *)st, speed);
    if (*(float *)(st + 0x1C) < *(float *)(st + 0x8)) {
        *(float *)(st + 0x8) = *(float *)(st + 0x1C);
    }

    qcopy(probePos, moby + 0x10);
    probePos[2] = probePos[2] + *(float *)(st + 0x28);
    groundHeight = ProbeGroundHeightBelow(probePos, 0, 0.5f);
    if (GetCollHitMaterial() == 0) {
        if (*(float *)(st + 0x5C) == 0.0f && groundHeight <= probePos[2] && probePos[2] + *(float *)(st + 0x8) < groundHeight) {
            *(float *)(st + 0x5C) = 1.0f;
            probePos[2] = groundHeight;
            SpawnScaledEffectMoby(probePos, 3.0f);
        }
        groundHeight = GetGroundHeightUnderObject((moby + 0x10));
    } else {
        if ((*(int *)(st + 0x24) & 0x10) || *(short *)(st + 0x3E) == 2) {
            FastVecAdd(endPos, (moby + 0x10), st);
            if (GetGroundHeightUnderObject(endPos) < groundHeight - 0.25f) {
                FastVectorNormalizeHelper((float *)st, (float *)st, 0.0f);
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
            fallRate = FloatAbs(*(float *)(st + 0x8) / *(float *)(st + 0x10));
            if (2.0f < fallRate) {
                tmp = GetMobyAnimationValue(moby);
                numerator0 = *(float *)(st + 0x50) - tmp;
                rate = numerator0 / fallRate;
                if (0.0f < rate) {
                    ApproachValue((float *)(moby + 0x48), rate, 0.1f);
                }
            }
            break;
        }
        case 1:
            tmp = GetMobyAnimationValue(moby);
            if (*(float *)(st + 0x54) <= tmp) {
                *(int *)(moby + 0x48) = 0;
            } else {
                float numerator1;
                float halfDrop = *(float *)(st + 0x10) * -0.5f;
                timeToLand = 60.0f;
                count = SolveQuadratic(&root0, &root1, halfDrop, *(float *)(st + 0x8) - halfDrop, *(float *)(moby + 0x18) - groundHeight);
                if (count > 0 && 0.0f < root0 && root0 < timeToLand) {
                    timeToLand = root0;
                }
                if (timeToLand < 0.0001f) {
                    timeToLand = 0.0001f;
                }
                tmp = GetMobyAnimationValue(moby);
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
    count = ProcessCollisionHit(IntToFloat(*(int *)(st + 0x20)) * 0.0010742187732830644f, sweepEnd, 16, moby, 0);
    if (i < count) {
        int **listPtr = D_L06_001C3D00;
        int remaining = count;
        do {
            if (IsMobyInSpecialClassRange(*listPtr) != 0) {
                QueueImpactEffect((char *)*listPtr, 1.0f, (int)moby, 0x10000, (moby + 0x10), st);
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
    if (TestPointAgainstCollision(endPos, IntToFloat(*(int *)(st + 0x20)) * unitScale, 36, moby) != 0) {
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
