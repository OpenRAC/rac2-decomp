#include "common.h"

typedef struct __attribute__((packed, aligned(4))) { long long a; int b; } QueryParams;
typedef struct { char *target; int zero; } QueryExclude;
typedef struct { char *item; } Candidate;
typedef struct { unsigned char pad[28]; unsigned char entry; } DamageClasses;
typedef struct { char pad[112]; float value; char tail[108]; } DamageClass;
typedef struct { char pad[0x2290]; char *player; } PlayerRef;
typedef struct { char pad[132]; int value; } SoundRecord;

extern char D_L00_001C3280[];
extern const QueryParams D_L00_001B0140;
extern char D_00139568[];
extern char D_L00_001BF220[];
extern char D_00188660[];
extern char D_00189E20[];
extern char D_L00_00262570[];
extern int D_L00_001B0134 SDATA(D_L00_001B0134);

extern void func_00300190(void *, void *);
extern void func_002FEE70(int, void *, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002E5F40(int, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282C88(void *);
extern void func_L00_003252A8(void *, void *, int);
extern void func_0031F6E8(void *, int, int);
extern void func_0032D758(void *, int, int);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_0031DC18(void *, void *, int);
extern void func_0031E960(void *);
extern void func_0031E6E8(void *);
extern void func_002E59F8(int);
extern void func_0031DEE8(void *);
extern void func_0031E3A8(void *);
extern void func_002FEE50(int);
extern void func_0029F338(void *);
extern void ref_L00_003CA730_00(void *, void *);
extern int func_002A7820(int, int);
extern int func_00277F48(void *, int, void *, int, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00277258(void *, int, void *, float);
extern int func_00282948(void *);
extern int func_002E5CF8(int, int, void *);
extern int func_002E59B0(void *, int);
extern int func_002B4038(int, int);
extern char *func_002AB1F0(void *);
extern char *func_002AF580(void *, void *, float, float, int *, void *, int, void *,
                           float, float, float, int, void *);

/* Per-frame update of a thrown shot. It flies forward, sticks to or hits things it touches, explodes to damage nearby enemies, plays its sound and removes itself when its time runs out. */
void func_L00_003CA730(char *self)
{
    char prevPos[16] __attribute__((aligned(16)));
    union { char v[16]; QueryParams params; } scratch __attribute__((aligned(16)));
    union {
        char raw[32];
        struct { char *targets[4]; QueryExclude exclude; } query;
    } message __attribute__((aligned(16)));
    int count, i, j, hitCount;
    char *vars = *(char **)(self + 0x68), *hitObject, *hitInfo;

    TransformVectorOrCopy(self + 0x10, self + 0x10);
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        *(unsigned char *)(self + 0x20) = 1;
        *(int *)(vars + 0x20) = -1;
        *(int *)(vars + 0x24) = -1;
    case 1:
        qcopy(prevPos, self + 0x10);
        SteerEffectDirection(*(int *)(vars + 0x44), vars, 0);
        FastVecAdd(self + 0x10, self + 0x10, vars);
        SetVoicePitchBend(*(int *)(vars + 0x20), *(int *)(vars + 0x24) + RandomIntRange(-200, 200));
        hitCount = ProcessCollisionHit(self + 0x10, 0, self, 0, 0.45f);
        for (i = 0; i < hitCount; i++) {
            hitObject = ((Candidate *)gAreaHitTargets)[i].item;
            hitInfo = GetMobyPrivateValue0(hitObject);
            if (*(short *)(hitObject + 0xAA) == 0xC4A /* Plasma Coil */ || hitObject == ((PlayerRef *)gHeroState)->player
                || !(*(short *)(hitObject + 0x34) & 0x1000))
                continue;
            if (hitInfo) {
                qcopy(self + 0x10, hitObject + 0x10);
                ForwardObjectPositionCall(hitObject, scratch.v, 1);
                FastVecScale(scratch.v, scratch.v, *(float *)(hitInfo + 0x10));
                FastVecAdd(self + 0x10, self + 0x10, scratch.v);
            }
            *(char **)(vars + 0x38) = hitObject;
            *(int *)(vars + 0x10) = 15;
            *(unsigned char *)(self + 0x20) = 2;
            qcopy(scratch.v, vars);
            ClearVector128(vars);
            vec_scale_to_length(scratch.v, scratch.v, 0.033333335f);
            make_hit_descriptor(message.raw, self, 0x210000, scratch.v,
                          ((DamageClass *)gWeaponTable_L00)[((DamageClasses *)gItemSlotToRecord)->entry].value);
            *(unsigned char *)(message.raw + 24) = 1;
            *(unsigned char *)(message.raw + 25) = 3;
            *(short *)(message.raw + 26) = *(short *)(self + 0xAA);
            QueueMobyImpact(hitObject, message.raw);
            SpawnHitSparks_0031F6E8(self + 0x10, 10, 1);
            StartAttachedEffect(hitObject, 28, *(int *)(self + 0xB8));
            break;
        }
        if (!*(char **)(vars + 0x38)) {
            int didHit;
            if (CollLine(prevPos, self + 0x10, 2, self, 0))
                didHit = 1;
            else
                didHit = TestPointAgainstCollision(self + 0x10, 2, self, 0.1f) != 0;
            if (didHit == 1) {
                qcopy(self + 0x10, D_L00_001BF220);
                FastVecScale(scratch.v, D_L00_001BF220 + 0x20, 0.0009765625f);
                vec_scale_to_length(scratch.v, scratch.v, 0.1f);
                FastVecAdd(self + 0x10, scratch.v, self + 0x10);
                *(int *)(vars + 0x10) = 15;
                *(unsigned char *)(self + 0x20) = 2;
                SpawnHitSparks_0031F6E8(self + 0x10, 15, 0);
            }
        }
        if (FastFloatHelperD(vars + 0x10)) {
            *(unsigned char *)(self + 0x20) = 4;
            *(int *)(vars + 0x10) = 161;
        }
        break;
    case 2: {
        char *hitInfo;
        if (*(char **)(vars + 0x38)) {
            hitInfo = GetMobyPrivateValue0(*(char **)(vars + 0x38));
            if (hitInfo) {
                ForwardObjectPositionCall(*(char **)(vars + 0x38), scratch.v, 1);
                FastVecScale(scratch.v, scratch.v, *(float *)(hitInfo + 0x10));
                FastVecAdd(self + 0x10, scratch.v, *(char **)(vars + 0x38) + 0x10);
            }
        }
        if (FastFloatHelperD(vars + 0x10)) {
            *(unsigned char *)(self + 0x20) = 4;
            scratch.params = D_L00_001B0140;
            message.query.exclude = (QueryExclude){*(char **)(vars + 0x38), 0};
            SelectBestTargetInCone(self + 0x10, self + 0xC0, 6.2831855f, 6.2831855f, &count,
                          message.query.targets, 3, &message.query.exclude,
                          10.0f, 0.0f, 0.0f, 0, &scratch.params);
            for (i = 0; i < count; i++) {
                for (j = 4; j >= 0; j--)
                    SpawnTargetedSpark(self, message.query.targets[i], 10);
                PlayMobySound(1, 0, self);
            }
        }
        break;
    }
    case 3:
        break;
    case 4: {
        char *hitInfo;
        if (*(char **)(vars + 0x38)) {
            if (!D_L00_001B0134) {
                D_L00_001B0134 = 1;
                PlayMobySound(3, 0, self);
            }
            hitInfo = GetMobyPrivateValue0(*(char **)(vars + 0x38));
            if (hitInfo) {
                ForwardObjectPositionCall(*(char **)(vars + 0x38), scratch.v, 1);
                FastVecScale(scratch.v, scratch.v, *(float *)(hitInfo + 0x10));
                FastVecAdd(self + 0x10, scratch.v, *(char **)(vars + 0x38) + 0x10);
            }
        }
        if (!*(int *)(vars + 0x1C)) {
            DestroyMobyAndFreeSparkSlot(self);
            if (!*(char **)(vars + 0x38)) {
                SpawnHitSparks_0031F6E8(self + 0x10, 10, 1);
                PlayMobySound(2, 0, self);
            }
        }
    }
    }
    if (*(unsigned char *)(self + 0x20) != 4) {
        if (!IsVoicePlayingForOwner(self, *(int *)(vars + 0x20)))
            *(int *)(vars + 0x20) = PlayMobySound(0, 4, self);
        if (*(int *)(vars + 0x24) == -1) {
            char *soundEntry = gSoundState + *(int *)(vars + 0x20) * 112;
            *(int *)(vars + 0x24) = ((SoundRecord *)soundEntry)->value;
        }
    } else if (*(int *)(vars + 0x20) != -1) {
        char *soundEntry = gSoundState + *(int *)(vars + 0x20) * 112;
        if (*(char **)(soundEntry + 0x88) == self && *(unsigned char *)(soundEntry + 0x74))
            StopSoundVoice(*(int *)(vars + 0x20));
        *(int *)(vars + 0x20) = -1;
    }
    UpdateTargetedSparks(self);
    UpdateGlowRingEntries(self);
    if (!IsSavedRecordValue(*(int *)(vars + 0x40), *(int *)(vars + 0x3C))) {
        ClearEntryFlag(*(int *)(vars + 0x44));
        MarkMobySpawned(self);
    } else {
        ref_L00_003CA730_00((void *)SpawnSparkBurst_0031E960, self);
    }
}
