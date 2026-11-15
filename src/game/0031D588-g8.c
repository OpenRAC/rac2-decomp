#include "common.h"

typedef struct __attribute__((packed, aligned(4))) { long long a; int b; } QueryParams;
typedef struct { char *target; int zero; } QueryExclude;
typedef struct { char *item; } Candidate;
typedef struct { unsigned char pad[28]; unsigned char entry; } DamageClasses;
typedef struct { char pad[112]; float value; char tail[108]; } DamageClass;
typedef struct { char pad[0x2290]; char *player; } PlayerRef;
typedef struct { char pad[132]; int value; } SoundRecord;

extern char D_001BF000[];
extern const QueryParams D_001AFE00;
extern char D_00139568[];
extern char D_001BAFA0[];
extern char D_00188660[];
extern char D_00189E20[];
extern char D_00239BA0[];
extern int D_001AFDF4 SDATA(D_001AFDF4);

extern void func_00300190(void *, void *);
extern void func_002FEE70(int, void *, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002E5F40(int, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282C88(void *);
extern void func_002B00B0(void *, void *, int);
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
extern void func_0027CFD0(void *, void *);
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

/* Updates a flying shot. It moves, damages what it touches, bursts into sparks, sets off a blast around it and then goes away. */
void func_0031D588(char *self)
{
    char old[16] __attribute__((aligned(16)));
    union { char v[16]; QueryParams params; } temp __attribute__((aligned(16)));
    union {
        char raw[32];
        struct { char *targets[4]; QueryExclude exclude; } query;
    } event __attribute__((aligned(16)));
    int count, i, j, n;
    char *state = *(char **)(self + 0x68), *obj, *data;

    TransformVectorOrCopy(self + 0x10, self + 0x10);
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        *(unsigned char *)(self + 0x20) = 1;
        *(int *)(state + 0x20) = -1;
        *(int *)(state + 0x24) = -1;
    case 1:
        qcopy(old, self + 0x10);
        SteerEffectDirection(*(int *)(state + 0x44), state, 0);
        FastVecAdd(self + 0x10, self + 0x10, state);
        SetVoicePitchBend(*(int *)(state + 0x20), *(int *)(state + 0x24) + RandomIntRange(-200, 200));
        n = ProcessCollisionHit(self + 0x10, 0, self, 0, 0.45f);
        for (i = 0; i < n; i++) {
            obj = ((Candidate *)D_001BF000)[i].item;
            data = GetMobyPrivateValue0(obj);
            if (*(short *)(obj + 0xAA) == 0xC4A /* Plasma Coil */ || obj == ((PlayerRef *)gHeroState)->player
                || !(*(short *)(obj + 0x34) & 0x1000))
                continue;
            if (data) {
                qcopy(self + 0x10, obj + 0x10);
                GetGravityDirectionAtObject(obj, temp.v, 1);
                FastVecScale(temp.v, temp.v, *(float *)(data + 0x10));
                FastVecAdd(self + 0x10, self + 0x10, temp.v);
            }
            *(char **)(state + 0x38) = obj;
            *(int *)(state + 0x10) = 15;
            *(unsigned char *)(self + 0x20) = 2;
            qcopy(temp.v, state);
            ClearVector128(state);
            vec_scale_to_length(temp.v, temp.v, 0.033333335f);
            make_hit_descriptor(event.raw, self, 0x210000, temp.v,
                          ((DamageClass *)gWeaponTable_00239BA0)[((DamageClasses *)gItemSlotToRecord)->entry].value);
            *(unsigned char *)(event.raw + 24) = 1;
            *(unsigned char *)(event.raw + 25) = 3;
            *(short *)(event.raw + 26) = *(short *)(self + 0xAA);
            QueueMobyImpact(obj, event.raw);
            SpawnHitSparks_0031F6E8(self + 0x10, 10, 1);
            StartAttachedEffect(obj, 28, *(int *)(self + 0xB8));
            break;
        }
        if (!*(char **)(state + 0x38)) {
            int hit;
            if (CollLine(old, self + 0x10, 2, self, 0))
                hit = 1;
            else
                hit = TestPointAgainstCollision(self + 0x10, 2, self, 0.1f) != 0;
            if (hit == 1) {
                qcopy(self + 0x10, D_001BAFA0);
                FastVecScale(temp.v, D_001BAFA0 + 0x20, 0.0009765625f);
                vec_scale_to_length(temp.v, temp.v, 0.1f);
                FastVecAdd(self + 0x10, temp.v, self + 0x10);
                *(int *)(state + 0x10) = 15;
                *(unsigned char *)(self + 0x20) = 2;
                SpawnHitSparks_0031F6E8(self + 0x10, 15, 0);
            }
        }
        if (FastFloatHelperD(state + 0x10)) {
            *(unsigned char *)(self + 0x20) = 4;
            *(int *)(state + 0x10) = 161;
        }
        break;
    case 2: {
        char *info;
        if (*(char **)(state + 0x38)) {
            info = GetMobyPrivateValue0(*(char **)(state + 0x38));
            if (info) {
                GetGravityDirectionAtObject(*(char **)(state + 0x38), temp.v, 1);
                FastVecScale(temp.v, temp.v, *(float *)(info + 0x10));
                FastVecAdd(self + 0x10, temp.v, *(char **)(state + 0x38) + 0x10);
            }
        }
        if (FastFloatHelperD(state + 0x10)) {
            *(unsigned char *)(self + 0x20) = 4;
            temp.params = D_001AFE00;
            event.query.exclude = (QueryExclude){*(char **)(state + 0x38), 0};
            SelectBestTargetInCone(self + 0x10, self + 0xC0, 6.2831855f, 6.2831855f, &count,
                          event.query.targets, 3, &event.query.exclude,
                          10.0f, 0.0f, 0.0f, 0, &temp.params);
            for (i = 0; i < count; i++) {
                for (j = 4; j >= 0; j--)
                    SpawnTargetedSpark(self, event.query.targets[i], 10);
                PlayMobySound(1, 0, self);
            }
        }
        break;
    }
    case 3:
        break;
    case 4: {
        char *info;
        if (*(char **)(state + 0x38)) {
            if (!D_001AFDF4) {
                D_001AFDF4 = 1;
                PlayMobySound(3, 0, self);
            }
            info = GetMobyPrivateValue0(*(char **)(state + 0x38));
            if (info) {
                GetGravityDirectionAtObject(*(char **)(state + 0x38), temp.v, 1);
                FastVecScale(temp.v, temp.v, *(float *)(info + 0x10));
                FastVecAdd(self + 0x10, temp.v, *(char **)(state + 0x38) + 0x10);
            }
        }
        if (!*(int *)(state + 0x1C)) {
            DestroyMobyAndFreeSparkSlot(self);
            if (!*(char **)(state + 0x38)) {
                SpawnHitSparks_0031F6E8(self + 0x10, 10, 1);
                PlayMobySound(2, 0, self);
            }
        }
    }
    }
    if (*(unsigned char *)(self + 0x20) != 4) {
        if (!IsVoicePlayingForOwner(self, *(int *)(state + 0x20)))
            *(int *)(state + 0x20) = PlayMobySound(0, 4, self);
        if (*(int *)(state + 0x24) == -1) {
            char *rec = gSoundState + *(int *)(state + 0x20) * 112;
            *(int *)(state + 0x24) = ((SoundRecord *)rec)->value;
        }
    } else if (*(int *)(state + 0x20) != -1) {
        char *rec = gSoundState + *(int *)(state + 0x20) * 112;
        if (*(char **)(rec + 0x88) == self && *(unsigned char *)(rec + 0x74))
            StopSoundVoice(*(int *)(state + 0x20));
        *(int *)(state + 0x20) = -1;
    }
    UpdateTargetedSparks(self);
    UpdateGlowRingEntries(self);
    if (!IsSavedRecordValue(*(int *)(state + 0x40), *(int *)(state + 0x3C))) {
        ClearEntryFlag(*(int *)(state + 0x44));
        MarkMobySpawned(self);
    } else {
        RegisterOverlayDrawCallback((void *)SpawnSparkBurst_0031E960, self);
    }
}
