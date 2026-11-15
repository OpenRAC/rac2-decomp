#include "common.h"

/* Homing shot, the twin of func_L00_003E2510 (L00_003D37E8-missile.c), with the same shape: the
 * lead correction and the length call share a tail that jump2 cross-jumps, and the store to t on
 * the other arm stops gcse propagating t over tracking_delta past the join. */
extern int func_002B4038(int, int);
extern void func_00282D30(char *, char *, float);
extern void func_002AFFD8(void *, void *, int);
extern int func_L00_00420310(char *);
extern char *func_002AB1F0(char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_L00_0041FC20(void *, int, int);
extern void func_00334160(void *, int, int);
extern int func_002E5CF8(int, int, char *);
extern int func_00282948(void *);
extern void func_L00_004200F0(void *);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern char *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
/* func_L00_002E6EF8 in 23 programs, its twin in levels 08, 09, 19 and 30. */
extern void ref_L00_0041EE58_00(void (*)(void *), void *);
extern void func_002FEE50(int);
extern void func_0029F338(void *);
extern char D_00139568[];
typedef struct { unsigned char flag[4]; unsigned char enabled; char pad[0x6B]; float value; char tail[0x6C]; } BEE58Entry;
extern BEE58Entry D_L00_00262570[];
extern char *D_0018C0B0 NOT_SDA;
typedef struct { char pad[0x18]; char *target; char pad1[4]; float position[4]; } BEE58Hit;
extern BEE58Hit D_L00_001BF200;
extern char D_L00_001A8F20[] __attribute__((sda));
extern unsigned char *D_L00_001FEA14;
extern unsigned char *D_L00_001FE9F4;
extern int D_L00_001B19C8 MACRO_ADDR;
extern void func_L00_0041F570(void *);

/* Flies the homing shot (class 3209): steers it toward its target, hits things, spawns sparks and a trail, and removes it when it ends or leaves the map. */
void func_L00_0041EE58(char *obj)
{
    float previous[4], scratch[4], delta[4], temp[4];
    unsigned char hit[48];
    float particle[4];
    char *state = *(char **)(obj + 0x68);
    char *target;
    char *info;
    char *sprite;
    float *tracking_delta;
    float length, speed, scale;
    int work, i;

    if (!IsSavedRecordValue(*(int *)(state + 0x18), *(int *)(state + 0x14))) {
        MarkMobySpawned(obj);
        ClearEntryFlag(*(int *)(state + 0x34));
        return;
    }
    TransformVectorOrCopy(obj + 0x10, obj + 0x10);
    qcopy(previous, obj + 0x10);
    ComputeViewDirection(obj + 0x10, scratch, 1);
    target = *(char **)(state + 0x1C);
    if (target) {
        if (*(unsigned char *)(target + 0x20) == 0xFE) goto clear_target;
        if (*(unsigned char *)(target + 0x20) == 0xFD) goto clear_target;
        if (IsMobyTargetDead(target)) goto clear_target;
        {
            { float *t = delta;
            FastVecSub(t, *(char **)(state + 0x1C) + 0x10, obj + 0x10);
            tracking_delta = t;
            info = GetMobyPrivateValue0(*(char **)(state + 0x1C));
            if (info) {
                FastVecScale((char *)temp, *(char **)(state + 0x1C) + 0xE0, *(float *)(info + 0x10));
                FastVecAdd(tracking_delta, tracking_delta, temp);
                length = FastVecLength(tracking_delta);
            } else {
                t = 0;
                length = FastVecLength(tracking_delta);
            } }
            if (length == 0.0f) goto clear_target;
            {
                speed = *(float *)(state + 0x2C);
                FastVecScale(state + 0x20, (char *)tracking_delta, speed / length);
                *(float *)(state + 0x2C) = speed;
            }
        }
    }
    goto target_done;
clear_target:
    *(char **)(state + 0x1C) = 0;
target_done:
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        SteerEffectDirection(*(int *)(state + 0x34), state + 0x20, 0);
        FastVecAdd(obj + 0x10, obj + 0x10, state + 0x20);
        *(char **)(hit + 0x10) = obj;
        *(int *)(hit + 0x14) = 0x10000;
        *(float *)(hit + 0x1C) = ((BEE58Entry *)((unsigned char)gItemSlotToRecord[0x1E] * 0xE0 + (char *)gWeaponTable_L00))->value;
        *(int *)(hit + 0x20) = 1;
        qcopy(hit, state + 0x20);
        vec_scale_to_length(hit, hit, 1.0f);
        *(float *)(hit + 0xC) = 5627.925f;
        *(short *)(hit + 0x1A) = *(unsigned short *)(obj + 0xAA);
        hit[0x18] = 1;
        hit[0x19] = 1;
        if (CollLine(previous, obj + 0x10, 0, gHeroMoby_0018C0B0, hit)) {
            qcopy(obj + 0x10, gCollisionResult.position);
            if (!gCollisionResult.target) SpawnImpactSparkBurst_L00_2(gCollisionResult.position, 15, 0);
            else if (*(int *)(gCollisionResult.target + 0x98)) {
                SpawnImpactSparkBurst_L00_2(gCollisionResult.position, 10, 1);
                StartHealthDrainOnTarget(gCollisionResult.target, 0x3C, *(int *)(obj + 0xB8));
            }
            PlayMobySound(0, 0, obj);
            *(unsigned char *)(obj + 0x20) = 1;
            *(char **)(state + 0x1C) = 0;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            *(int *)(state + 0x38) = 6;
        } else if (FastFloatHelperD(state + 0x38)) {
            SpawnRocketSmokeBurst(obj + 0x10);
            *(unsigned char *)(obj + 0x20) = 1;
            *(char **)(state + 0x1C) = 0;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            *(int *)(state + 0x38) = 6;
        }
        work = RandomIntBelow(255);
        sprite = SpawnGravityFadeParticle(obj + 0x10, D_L00_001A8F20, 2, 0x205080, work, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (sprite) sprite[2] = *D_L00_001FEA14;
        work = (work + 128) % 255;
        sprite = SpawnGravityFadeParticle(obj + 0x10, D_L00_001A8F20, 2, 0x205080, work, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (sprite) sprite[2] = *D_L00_001FEA14;
        sprite = SpawnGravityFadeParticle(obj + 0x10, D_L00_001A8F20, 2, 0xFFFFFF, (work + 64) % 255, 48, 16, 252000.02f, 252000.02f, 0.0f, 1);
        if (sprite) sprite[2] = *D_L00_001FEA14;
        work = (int)delta;
        FastVecSub((void *)work, obj + 0x10, previous);
        FastVecScale((char *)work, (char *)work, 0.4f);
        qcopy(temp, previous);
        tracking_delta = (float *)work;
        for (i = 4; i >= 0; i--) {
            work = RandomIntBelow(255);
            scale = RandomFloatRange(0.2f, 0.6f);
            particle[0] = temp[0] + RandomSignedFloatRange(0.0f, 0.1f);
            particle[1] = temp[1] + RandomSignedFloatRange(0.0f, 0.1f);
            particle[2] = temp[2] + RandomSignedFloatRange(0.0f, 0.1f);
            SpawnGravityFadeParticle(particle, D_L00_001A8F20, 15, 0x808080, work, 32, 0, scale * 210000.0f, scale * 42000.0f, 0.0f, 1);
            FastVecAdd(temp, temp, tracking_delta);
        }
        if (gFrameCounter_L00 % 10 == 0) {
            sprite = SpawnGravityFadeParticle(obj + 0x10, D_L00_001A8F20, 30, 0x202080, 0, 32, 0, 2100.0f, 420000.0f, 0.0f, 1);
            if (sprite) sprite[2] = *D_L00_001FE9F4;
        }
        ref_L00_0041EE58_00(UpdateAndDrawShotTrail, obj);
        break;
    case 1:
        if (FastFloatHelperD(state + 0x38)) {
            ClearEntryFlag(*(int *)(state + 0x34));
            MarkMobySpawned(obj);
            return;
        }
        ref_L00_0041EE58_00(UpdateAndDrawShotTrail, obj);
        break;
    }
    if (*(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
        *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
        *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f) {
        ClearEntryFlag(*(int *)(state + 0x34));
        MarkMobySpawned(obj);
    }
}
