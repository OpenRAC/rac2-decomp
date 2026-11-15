#include "common.h"

/* Homing missile, the sibling of func_L00_003ED198 (L00_003EA0E0-seeker.c). The lead correction
 * and the length call share a tail that jump2 cross-jumps, so func_00282CC0 is not the last call
 * of its block, which is what lets a1 be set before a0 for func_00282D30. The store to t on the
 * other arm is dead: it stops gcse propagating t over tracking_delta past the join, which would
 * keep t alive in a saved register. */
extern int func_002B4038(int, int);
extern void func_00282D30(char *, char *, float);
extern void func_002AFFD8(void *, void *, int);
extern int func_L00_003E39B8(char *);
extern char *func_002AB1F0(char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern float func_00283B98(float, float);
extern void func_L00_003E3890(char *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_L00_003E3258(void *, int, int);
extern void func_00334160(void *, int, int);
extern int func_002E5CF8(int, int, char *);
extern int func_00282948(void *);
extern void func_L00_003E3668(void *);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern char *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
/* func_L00_002E6EF8 in 23 programs, its twin in levels 08, 09, 19 and 30. */
extern void ref_L00_003E2510_00(void *, void *);
extern void func_002FEE50(int);
extern void func_0029F338(void *);
extern char D_00139568[];
typedef struct { unsigned char flag[4]; unsigned char enabled; char pad[0x6B]; float value; char tail[0x6C]; } B2510Entry;
extern B2510Entry D_L00_00262570[];
extern char *D_0018C0B0 NOT_SDA;
typedef struct { char pad[0x18]; char *target; char pad1[4]; float position[4]; } B2510Hit;
extern B2510Hit D_L00_001BF200;
extern char D_L00_001A8F20[] __attribute__((sda));
extern unsigned char *D_L00_001FEA14;
extern unsigned char *D_L00_001FE9F4;
extern int D_L00_001B19C8 __attribute__((sda));
extern char func_L00_003E2BD0[];

/* Per-frame update of the homing missile. It steers toward its target, flies forward, damages what it hits, leaves a smoke trail, then explodes and removes itself. */
void func_L00_003E2510(char *missile)
{
    float scratch[4], previous[4], delta[4], temp[4];
    unsigned char damageInfo[48];
    float particle[4];
    char *vars = *(char **)(missile + 0x68);
    char *target;
    char *info;
    char *effect;
    float *tracking_delta;
    float length, speed, scale;
    int randomValue, i;

    if (!IsSavedRecordValue(*(int *)(vars + 0x18), *(int *)(vars + 0x14))) {
        ClearEntryFlag(*(int *)(vars + 0x34));
        MarkMobySpawned(missile);
        return;
    }
    ComputeViewDirection(missile + 0x10, scratch, 1);
    qcopy(previous, missile + 0x10);
    target = *(char **)(vars + 0x1C);
    if (target) {
        if (*(unsigned char *)(target + 0x20) == 0xFE) goto clear_target;
        if (*(unsigned char *)(target + 0x20) == 0xFD) goto clear_target;
        if (IsLivingHittableTarget(target)) goto clear_target;
        {
            { float *t = delta;
            FastVecSub(t, *(char **)(vars + 0x1C) + 0x10, missile + 0x10);
            tracking_delta = t;
            info = GetMobyPrivateValue0(*(char **)(vars + 0x1C));
            if (info) {
                FastVecScale((char *)temp, (char *)scratch, *(float *)(info + 0x10));
                FastVecAdd(tracking_delta, tracking_delta, temp);
                length = FastVecLength(tracking_delta);
            } else {
                t = 0;
                length = FastVecLength(tracking_delta);
            } }
            if (length == 0.0f) goto clear_target;
            {
                speed = *(float *)(vars + 0x2C);
                FastVecScale(vars + 0x20, (char *)tracking_delta, speed / length);
                *(float *)(vars + 0x2C) = speed;
            }
        }
    }
    goto target_done;
clear_target:
    *(char **)(vars + 0x1C) = 0;
target_done:
    switch (*(unsigned char *)(missile + 0x20)) {
    case 0:
        SteerEffectDirection(*(int *)(vars + 0x34), vars + 0x20, 0);
        FastVecAdd(missile + 0x10, missile + 0x10, vars + 0x20);
        TransformVectorOrCopy(missile + 0x10, missile + 0x10);
        *(float *)(missile + 0xF0) = FastAddRotations(*(float *)(missile + 0xF0), *(float *)(vars + 0x44));
        *(float *)(missile + 0xF4) = FastAddRotations(*(float *)(missile + 0xF4), *(float *)(vars + 0x48));
        *(float *)(missile + 0xF8) = FastAddRotations(*(float *)(missile + 0xF8), *(float *)(vars + 0x4C));
        UpdateMobyColorScaleFromVars(missile);
        *(char **)(damageInfo + 0x10) = missile;
        *(int *)(damageInfo + 0x14) = 0x10000;
        *(float *)(damageInfo + 0x1C) = ((B2510Entry *)((unsigned char)gItemSlotToRecord[0x1E] * 0xE0 + (char *)gWeaponTable_L00))->value;
        *(int *)(damageInfo + 0x20) = 1;
        qcopy(damageInfo, vars + 0x20);
        vec_scale_to_length(damageInfo, damageInfo, 1.0f);
        *(float *)(damageInfo + 0xC) = 5627.925f;
        *(short *)(damageInfo + 0x1A) = *(unsigned short *)(missile + 0xAA);
        damageInfo[0x18] = 1;
        damageInfo[0x19] = 1;
        if (CollLine(previous, missile + 0x10, 0, gHeroMoby_0018C0B0, damageInfo)) {
            if (!gCollisionResult.target) SpawnSparkBurstAtPosition(gCollisionResult.position, 15, 0);
            else if (*(int *)(gCollisionResult.target + 0x98)) {
                SpawnSparkBurstAtPosition(gCollisionResult.position, 10, 1);
                StartHealthDrainOnTarget(gCollisionResult.target, 0x1E, *(int *)(missile + 0xB8));
            }
            PlayMobySound(0, 0, missile);
            *(unsigned char *)(missile + 0x20) = 1;
            *(char **)(vars + 0x1C) = 0;
            *(unsigned short *)(missile + 0x34) |= 0x41;
            *(int *)(vars + 0x38) = 6;
        } else if (FastFloatHelperD(vars + 0x38)) {
            SpawnSmallSparkSpray(missile + 0x10);
            *(unsigned char *)(missile + 0x20) = 1;
            *(char **)(vars + 0x1C) = 0;
            *(unsigned short *)(missile + 0x34) |= 0x41;
            *(int *)(vars + 0x38) = 6;
        }
        randomValue = RandomIntBelow(255);
        effect = SpawnGravityFadeParticle(missile + 0x10, D_L00_001A8F20, 2, 0x202080, randomValue, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (effect) effect[2] = *D_L00_001FEA14;
        effect = SpawnGravityFadeParticle(missile + 0x10, D_L00_001A8F20, 2, 0x202080, (randomValue + 128) % 255, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (effect) effect[2] = *D_L00_001FEA14;
        randomValue = (int)delta;
        FastVecSub((void *)randomValue, missile + 0x10, previous);
        FastVecScale((char *)randomValue, (char *)randomValue, 0.2f);
        qcopy(temp, previous);
        tracking_delta = (float *)randomValue;
        for (i = 4; i >= 0; i--) {
            randomValue = RandomIntBelow(255);
            scale = RandomFloatRange(0.1f, 0.3f);
            particle[0] = temp[0] + RandomSignedFloatRange(0.0f, 0.1f);
            particle[1] = temp[1] + RandomSignedFloatRange(0.0f, 0.1f);
            particle[2] = temp[2] + RandomSignedFloatRange(0.0f, 0.1f);
            SpawnGravityFadeParticle(particle, D_L00_001A8F20, 15, 0x808080, randomValue, 32, 0, scale * 210000.0f, scale * 42000.0f, 0.0f, 1);
            FastVecAdd(temp, temp, tracking_delta);
        }
        if (gFrameCounter_L00 % 10 == 0) {
            effect = SpawnGravityFadeParticle(missile + 0x10, D_L00_001A8F20, 30, 0x202080, 0, 32, 0, 2100.0f, 420000.0f, 0.0f, 1);
            if (effect) effect[2] = *D_L00_001FE9F4;
        }
        ref_L00_003E2510_00(UpdateGlowingTrailMoby, missile);
        break;
    case 1:
        if (FastFloatHelperD(vars + 0x38)) {
            ClearEntryFlag(*(int *)(vars + 0x34));
            MarkMobySpawned(missile);
            return;
        }
        ref_L00_003E2510_00(UpdateGlowingTrailMoby, missile);
        break;
    }
    if (*(float *)(missile + 0x10) < 2.0f || *(float *)(missile + 0x10) > 1021.0f ||
        *(float *)(missile + 0x14) < 2.0f || *(float *)(missile + 0x14) > 1021.0f ||
        *(float *)(missile + 0x18) < 2.0f || *(float *)(missile + 0x18) > 1021.0f) {
        ClearEntryFlag(*(int *)(vars + 0x34));
        MarkMobySpawned(missile);
    }
}
