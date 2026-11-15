#include "common.h"

/* Homing shot. The short-lived t and the int reused for the trail delta are what keep retail's copies past cprop: it is reassigned in the loop. */
extern void func_00282D30(char *, char *, float);
extern void func_002AFFD8(void *, void *, int);
extern int func_L00_003EE228(char *);
extern char *func_002AB1F0(char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00300190(void *, void *);
extern float func_00283B98(float, float);
extern void func_L00_003EE100(char *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_L00_003EDB98(void *, int, int);
extern void func_00334160(void *, int, int);
extern int func_00282948(void *);
extern void func_L00_003EDEE0(void *);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern char *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void ref_L00_003ED198_00(void *, void *);
extern void func_0029F338(void *);
extern char D_00139568[];
typedef struct { unsigned char flag[4]; unsigned char enabled; char pad[0x6B]; float value; char tail[0x6C]; } B0714Entry;
extern B0714Entry D_L00_00262570[];
extern char *D_0018C0B0 NOT_SDA;
typedef struct { char pad[0x18]; char *target; char pad1[4]; float position[4]; } B0714Hit;
extern B0714Hit D_L00_001BF200;
extern char D_L00_001A8F20[] __attribute__((sda));
extern unsigned char *D_L00_001FEA14;
extern unsigned char *D_L00_001FE9F4;
extern int D_L00_001B19C8 __attribute__((sda));
extern char func_L00_003ED850[];

/* Updates the homing shot: it steers toward its target, hits things, leaves a trail and explodes. */
void func_L00_003ED198(char *obj)
{
    float old[4], scratch[4], previous[4], delta[4], temp[4];
    unsigned char hit[48];
    float particle[4];
    char *state = *(char **)(obj + 0x68);
    char *target;
    char *info;
    char *spark;
    float *trackingDelta;
    float length, speed, scale;
    int tempWord, i;

    qcopy(old, obj + 0x10);
    ComputeViewDirection(obj + 0x10, scratch, 1);
    qcopy(previous, obj + 0x10);
    target = *(char **)(state + 0x1C);
    if (target) {
        if (*(unsigned char *)(target + 0x20) == 0xFE) goto clear_target;
        if (*(unsigned char *)(target + 0x20) == 0xFD) goto clear_target;
        if (CanTargetObject(target)) goto clear_target;
        {
            { float *t = delta;
            FastVecSub(t, *(char **)(state + 0x1C) + 0x10, obj + 0x10);
            trackingDelta = t; }
            info = GetMobyPrivateValue0(*(char **)(state + 0x1C));
            if (info) {
                FastVecScale((char *)temp, *(char **)(state + 0x1C) + 0xE0, *(float *)(info + 0x10));
                FastVecAdd(trackingDelta, trackingDelta, temp);
            }
            length = FastVecLength(trackingDelta);
            if (length == 0.0f) goto clear_target;
            {
                speed = *(float *)(state + 0x2C);
                FastVecScale(state + 0x20, (char *)trackingDelta, speed / length);
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
        FastVecAdd(obj + 0x10, obj + 0x10, state + 0x20);
        TransformVectorOrCopy(obj + 0x10, obj + 0x10);
        *(float *)(obj + 0xF0) = FastAddRotations(*(float *)(obj + 0xF0), *(float *)(state + 0x44));
        *(float *)(obj + 0xF4) = FastAddRotations(*(float *)(obj + 0xF4), *(float *)(state + 0x48));
        *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(obj + 0xF8), *(float *)(state + 0x4C));
        PulseObjectAxisScale(obj);
        *(char **)(hit + 0x10) = obj;
        *(int *)(hit + 0x14) = 0x10000;
        *(float *)(hit + 0x1C) = ((B0714Entry *)((unsigned char)gItemSlotToRecord[0x1F] * 0xE0 + (char *)gWeaponTable_L00))->value;
        *(int *)(hit + 0x20) = 1;
        qcopy(hit, state + 0x20);
        vec_scale_to_length(hit, hit, 1.0f);
        *(float *)(hit + 0xC) = 5627.925f;
        *(short *)(hit + 0x1A) = *(unsigned short *)(obj + 0xAA);
        hit[0x18] = 1;
        hit[0x19] = 1;
        if (CollLine(previous, obj + 0x10, 0, gHeroMoby_0018C0B0, hit)) {
            if (!gCollisionResult.target) SpawnImpactSparkBurst_L00(gCollisionResult.position, 15, 0);
            else if (*(int *)(gCollisionResult.target + 0x98)) {
                SpawnImpactSparkBurst_L00(gCollisionResult.position, 10, 1);
                if (((B0714Entry *)((unsigned char)gItemSlotToRecord[0x1F] * 0xE0 + (char *)gWeaponTable_L00))->enabled)
                    StartHealthDrainOnTarget(gCollisionResult.target, 0x3D, *(int *)(obj + 0xB8));
                else
                    StartHealthDrainOnTarget(gCollisionResult.target, 0x1F, *(int *)(obj + 0xB8));
            }
            *(unsigned char *)(obj + 0x20) = 1;
            *(char **)(state + 0x1C) = 0;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            *(int *)(state + 0x38) = 6;
        } else if (FastFloatHelperD(state + 0x38)) {
            SpawnSparkBurst_L00_4(obj + 0x10);
            *(unsigned char *)(obj + 0x20) = 1;
            *(char **)(state + 0x1C) = 0;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            *(int *)(state + 0x38) = 6;
        }
        tempWord = RandomIntBelow(255);
        spark = SpawnGravityFadeParticle(obj + 0x10, D_L00_001A8F20, 2, 0x202080, tempWord, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (spark) spark[2] = *D_L00_001FEA14;
        spark = SpawnGravityFadeParticle(obj + 0x10, D_L00_001A8F20, 2, 0x202080, (tempWord + 128) % 255, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (spark) spark[2] = *D_L00_001FEA14;
        tempWord = (int)delta;
        FastVecSub((void *)tempWord, obj + 0x10, previous);
        FastVecScale((char *)tempWord, (char *)tempWord, 0.1f);
        qcopy(temp, previous);
        trackingDelta = (float *)tempWord;
        for (i = 4; i >= 0; i--) {
            tempWord = RandomIntBelow(255);
            scale = RandomFloatRange(0.1f, 0.3f);
            particle[0] = temp[0] + RandomSignedFloatRange(0.0f, 0.05f);
            particle[1] = temp[1] + RandomSignedFloatRange(0.0f, 0.05f);
            particle[2] = temp[2] + RandomSignedFloatRange(0.0f, 0.05f);
            SpawnGravityFadeParticle(particle, D_L00_001A8F20, 15, 0x808080, tempWord, 32, 0, scale * 210000.0f, scale * 42000.0f, 0.0f, 1);
            FastVecAdd(temp, temp, trackingDelta);
        }
        if (gFrameCounter_L00 % 10 == 0) {
            spark = SpawnGravityFadeParticle(obj + 0x10, D_L00_001A8F20, 30, 0x202080, 0, 32, 0, 2100.0f, 420000.0f, 0.0f, 1);
            if (spark) spark[2] = *D_L00_001FE9F4;
        }
        ref_L00_003ED198_00(DrawHomingShotTrail, obj);
        break;
    case 1:
        if (FastFloatHelperD(state + 0x38)) {
            MarkMobySpawned(obj);
            return;
        }
        ref_L00_003ED198_00(DrawHomingShotTrail, obj);
        break;
    }
    if (*(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
        *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
        *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f)
        MarkMobySpawned(obj);
}
