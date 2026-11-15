#include "common.h"

/* func_L00_0041A5C0 reads its entry table through $gp, hence -G8. */

typedef unsigned int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;
typedef struct { V pos, vel, accel; int next, active, handle, pad; } Entry;
typedef struct {
    char pad[0x18];
    char *target;
    int count;
    V point;
    char gap[0x10];
    V normal;
} Collision;
typedef struct { char pad[0x70]; float direct, splash; char rest[0x68]; } ClassEntry;

extern Entry *D_L00_001B144C __attribute__((sda));
extern Collision D_L00_001BF200;
extern char D_L00_001C3280[];
extern unsigned char D_00139568[];
extern char D_00189E20[];
extern ClassEntry D_L00_00262570[] NOT_SDA;

extern void func_00300190(void *, void *);
extern void func_002FEE70(int, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_00282F20(void *, void *, float);
extern void func_002FEE50(int);
extern void func_00283410(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_002BE278(void *, void *, int, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_0032D758(void *, int, void *);
extern void func_002E5CF8(int, int, void *);
extern void func_002FE880(void *, void *, float);
extern void func_L00_0041B840(void *, void *, void *, void *);
extern void func_L00_0041AD40(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00277F48(void *, int, void *, int, float);
extern int func_001163B0(void);
extern float func_002A7878(float, float);

/* Moves the Lava Gun blobs one step. A blob that lands sticks to the surface and splashes, and it hurts any enemy nearby. */
void func_L00_0041A5C0(char *object)
{
    V next, temp, small, angles, rot[4], direction;
    struct {
        V direction;
        char pad[8];
        unsigned char type, flag;
        unsigned short id;
        int pad2, enabled;
        char tail[12];
    } hit;
    char *state = *(char **)(object + 0x68);
    int i, index = *(int *)(state + 0x48);
    char *hero;
    Entry *entry;
    char *target;
    int hitCount, hitIndex, nextIndex;
    ClassEntry *classEntry;

    for (i = 0; i < *(int *)(state + 0x44); i++) {
        hero = gHeroState;
        entry = gLavaGunRingEntries + index;
        if (i)
            TransformVectorOrCopy(entry, entry);
        if (entry->handle >= 0)
            SteerEffectDirection(entry->handle, &entry->vel, entry);
        FastVecAdd(&next, entry, &entry->vel);
        if (!entry->active) {
            if (CollLine(entry, &next, 0x10, object, 0)) {
                qcopy(entry, &gCollisionResult.point);
                ClearVector128(&entry->vel);
                vec_scale_to_length(&temp, &gCollisionResult.normal, 0.1f);
                FastVecAdd(entry, entry, &temp);
                entry->active = 1;
                ClearEntryFlag(entry->handle);
                entry->handle = -1;
                qcopy_nc(&entry->accel, &temp);
                vec_scale_to_length(&small, &temp, 0.01f);
                angles.f[0] = RandomFloatRange(-0.7853981853f, 0.7853981853f);
                angles.f[1] = RandomFloatRange(-0.7853981853f, 0.7853981853f);
                angles.f[2] = RandomFloatRange(-0.7853981853f, 0.7853981853f);
                euler_to_matrix(rot, &angles);
                rot[3].f[0] = 0;
                rot[3].f[1] = 0;
                rot[3].f[2] = 0;
                transform_vector(&small, &small, rot);
                SpawnWhiteFlashParticle(entry, &small, 0, -1);
                ClearVector128(&angles);
                target = gCollisionResult.target;
                if (target && target != *(char **)(hero + 0x2290)
                    && ((*(unsigned short *)(target + 0x34) & 0x1000)
                        || *(short *)(*(char **)(target + 0x24) + 0x46) == 5)) {
                    nextIndex = index - 1;
                    FastVecSub(&direction, target + 0x10, object + 0x10);
                    vec_scale_to_length(&direction, &direction, 1);
                    vec_scale_to_length(&hit, &hit, 1);
                    classEntry = &gWeaponTable_L00[gItemSlotToRecord[0x1d]];
                    make_hit_descriptor(&hit, object, 0x910000, &direction, classEntry->direct);
                    hit.direction.q = direction.q;
                    hit.direction.f[3] = 5627.9248046875f;
                    hit.type = 9;
                    hit.enabled = 1;
                    hit.flag = 1;
                    hit.id = *(unsigned short *)(gCollisionResult.target + 0xaa);
                    QueueMobyImpact(gCollisionResult.target, &hit);
                    StartAttachedEffect(gCollisionResult.target, 0x1d, object);
                    PlayMobySound(1, 0, object);
                    hitCount = ProcessCollisionHit(gCollisionResult.target + 0x10, 0x10, object, 0, 1.5f);
                    for (hitIndex = 0; hitIndex < hitCount; hitIndex++) {
                        target = ((char **)gAreaHitTargets)[hitIndex];
                        if (target == *(char **)(hero + 0x2290))
                            continue;
                        FastVecSub(&direction, target + 0x10, object + 0x10);
                        vec_scale_to_length(&direction, &direction, 1);
                        vec_scale_to_length(&hit, &hit, 1);
                        classEntry = &gWeaponTable_L00[gItemSlotToRecord[0x1d]];
                        make_hit_descriptor(&hit, object, 0x910000, &direction, classEntry->splash);
                        hit.direction.q = direction.q;
                        hit.direction.f[3] = 5627.9248046875f;
                        hit.type = 9;
                        hit.enabled = 1;
                        hit.flag = 1;
                        hit.id = *(unsigned short *)(((char **)gAreaHitTargets)[hitIndex] + 0xaa);
                        QueueMobyImpact(((char **)gAreaHitTargets)[hitIndex], &hit);
                        StartAttachedEffect(((char **)gAreaHitTargets)[hitIndex], 0x1d, object);
                        PlayMobySound(1, 0, object);
                        /* The block must not end in the call: flow would pad it with a
                         * (use 0) insn, which lengthens the inner pointers' live ranges
                         * and hands `object` the wrong saved register. */
                        target = 0;
                    }
                } else {
                    nextIndex = index - 1;
                    if (Rand() % 11 == 0)
                        SpawnRandomTaperedQuadPair(object, &gCollisionResult.point, &temp, &angles);
                }
            } else {
                AddObjectDirectionScaled(entry, &entry->vel, 0.006f);
                nextIndex = index - 1;
            }
        } else {
            nextIndex = index - 1;
        }
        FastVecAdd(entry, entry, &entry->vel);
        index = nextIndex;
        if (nextIndex < 0)
            index = 0x22;
        if (Rand() % 7 == 0) {
            vec_scale_to_length(&temp, &entry->vel, 0.05f);
            SpawnDebrisPiece_L00(object, entry, &entry->vel);
        }
        if (Rand() % 22 == 0) {
            vec_scale_to_length(&temp, &entry->vel, 0.05f);
            SpawnWhiteFlashParticle(entry, &temp, 0, -1);
        }
    }
}
