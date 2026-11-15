#include "common.h"

typedef int ProjectileQuad __attribute__((mode(TI)));
typedef union { ProjectileQuad quad; struct { float x, y, z, w; } v; } ProjectileVector;
typedef struct { float x, y, z; } ProjectileOffset;
typedef struct {
    ProjectileVector previous, position, velocity;
    unsigned char *hitObject;
    int *excluded;
    int mode;
    float radius, response, friction;
    int flags0, flags1, enabled, surface, active;
    float tolerance;
} ProjectileQuery;
extern int D_L03_001AEFCC __attribute__((sda));
extern float D_L03_001AEFB0 __attribute__((sda));
extern float D_L03_001AEFB8 __attribute__((sda));
extern void *D_L03_001B31B0 __attribute__((sda));
extern int D_L03_001B31B8[] __attribute__((sda));
extern unsigned char *D_L03_001ADAAC[] __attribute__((sda));
typedef struct { int row0[64]; int row1[64]; int row2[8]; int count; int flag; int limit; } ProjectilePool;
extern ProjectilePool D_L03_0023B300 __attribute__((nosda));
extern unsigned char *D_L03_0023B530[] __attribute__((nosda));
extern ProjectileOffset D_L03_0023B6C0[] __attribute__((nosda));
extern unsigned char D_L03_00189E20[] __attribute__((nosda));
extern void func_002FE8D8(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00283198(float);
extern void func_00282D30(void *, void *, float);
extern float func_00283180(float);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002FEE70(int, void *, int);
extern void func_002FE880(float, void *, void *);
extern void func_00300190(void *, void *);
extern int func_002FE9D0(ProjectileQuery *);
extern int func_00300540(int);
extern void func_002FD1B8(void *, int, int, float, float, float, float);
extern unsigned char *func_00312D58(float, void *);
extern signed char func_00300280(void *, void *);
extern void func_L00_00387F98(void);
extern int func_002E5CF8(int, int, void *);
extern void func_002A75E0(void *, int, int, int, int);
extern void func_002FEE50(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern float func_0029F530(void *);
extern void func_00304D38(void *);
extern void func_00304F28(void *);
extern void func_00305058(void *);
extern signed char func_002FED90(float, float, float, void *, int);
extern int func_002FEC78(void *, int);
extern void func_L00_00387370(void *);
extern void func_L00_00387408(void *);
extern void func_002AC728(float, float, void *, void *, int);
extern void func_002FED28(int);
extern void func_00300300(void *, int);
extern void func_0029F338(void *);
extern void func_00283098(void *, void *, void *);
extern void func_L00_00387AC8(void *);
extern void func_002829D8(void *);
extern int func_00282948(void *);
extern void func_003054E8(void *);
extern void func_00304C18(void *);
extern void func_L00_00387518(void *);
typedef void (*ProjectileDrawCallback)(void *);
extern void func_L00_002E6EF8(ProjectileDrawCallback, void *);
extern void func_003058C8(void *);
#define PI(p,o) (*(int *)((p)+(o)))
#define PF(p,o) (*(float *)((p)+(o)))
#define PP(p,o) (*(unsigned char **)((p)+(o)))
#define PV(p,o) (*(ProjectileVector *)((p)+(o)))

/* Updates the Miniturret moby (class 4966): moves it, bounces it off what it hits, sticks it to surfaces and blows it up. */
void func_L03_0038BCC0(unsigned char *object) {
    unsigned char *state = PP(object, 0x68);
    unsigned char *attached, *created;
    ProjectileVector oldPosition;
    int excluded[2];
    ProjectileVector normal, forward, quaternion, cross;
    float matrix[12];
    ProjectileQuery query;
    ProjectileVector relative;
    float inverse[16];
    float halfAngle;
    int collision, response, index;
    switch (object[0x20]) {
    case 0:
        object[0x20] = 1;
        { int counter = D_L03_001AEFCC;
        PI(state, 0x6C) = counter;
        D_L03_001AEFCC = (counter + 1) % 100; }
        PI(object, 0x98) = 0;
    case 1:
        GetObjectFacingDirection(object + 0x10, &normal);
        vec_scale_to_length(&forward, object + 0xE0, 1.0f);
        FastVecCross(&cross, &forward, &normal);
        halfAngle = FastVecDot(&forward, &normal) * 0.5f;
        FastVecScale(&quaternion, &cross, FastSinOrCosB(halfAngle));
        quaternion.v.w = FastSinOrCosA(halfAngle);
        quaternion_to_rotation_basis(&quaternion, matrix);
        multiply_matrix3x3(object + 0xC0, matrix, object + 0xC0);
        qcopy(&oldPosition, object + 0x10);
        FastVecAdd(object + 0x10, object + 0x10, state);
        SteerEffectDirection((signed char)state[0x4F], state, 0);
        AddObjectDirectionScaled(D_L03_001AEFB0 * 0.00027777778450399637f, object + 0x10, state);
        TransformVectorOrCopy(object + 0x10, object + 0x10);
        excluded[0] = 0;
        excluded[1] = 0xC5A; /* Miniturret Glove */
        qcopy(&query.previous, &oldPosition);
        qcopy(&query.position, object + 0x10);
        qcopy(&query.velocity, state);
        query.hitObject = object;
        query.excluded = excluded;
        query.mode = 2;
        query.radius = 0.1f;
        query.response = D_L03_001AEFB8;
        query.friction = 0.5555555820465088f;
        query.flags0 = 0;
        query.flags1 = 0;
        query.tolerance = 0.07400000095367432f;
        query.active = 1;
        query.enabled = 1;
        collision = CollideSweptSphere(&query);
        qcopy(object + 0x10, &query.position);
        qcopy(state, &query.velocity);
        if (collision == 2) {
            unsigned char *hit = query.hitObject;
            if (!hit || (*(short *)(hit + 0xAA) != 0xCB /* Decoy */ &&
                *(short *)(hit + 0xAA) != 0x1366 /* Miniturret */ && *(short *)(hit + 0xAA) != 0x1367 /* Megaturret */)) {
                qzero_nc(state);
                PP(state, 0x70) = hit;
                if (hit) {
                    PF(state, 0x74) = PF(hit, 0x10);
                    PF(state, 0x78) = PF(hit, 0x14);
                    PF(state, 0x7C) = PF(hit, 0x18);
                }
                response = GetWeaponGroup(query.surface);
                if (response == 2) {
                    PF(state, 8) = -0.02500000223517418f;
                    object[0x20] = 7;
                    if (!query.surface) {
                        RippleDisturb(D_L03_001B31B0, D_L03_001B31B8[0], 1, PF(object, 0x10), PF(object, 0x14), 0.5f, -0.35f);
                        created = SpawnScaledEffectMoby(2.0f, object + 0x10);
                        if (created)
                            created[0x23] = 0x70;
                    }
                } else if (response == 1) {
                    object[0x20] = 8;
                } else {
                    state[0x4E] = AddToSlotList(&D_L03_0023B300, object);
                    ApplySharedResetToStateWords();
                    if (D_L03_0023B300.row1[(signed char)state[0x4E]]) {
                        object[0x20] = 2;
                        PlayMobySound(1, 0, object);
                        StartAnimationBlendedWithFlags(object, 1, 0, 0, 0);
                    } else {
                        object[0x20] = 6;
                    }
                }
                ClearEntryFlag((signed char)state[0x4F]);
                { unsigned char *owner = D_L03_001ADAAC[0];
                D_L03_0023B530[PI(state, 0x6C)] = owner;
                if (owner) {
                    FastVecSub(&relative, object + 0x10, owner + 0x10);
                    matrix_from_basis_rows(inverse, D_L03_0023B530[PI(state, 0x6C)] + 0xC0);
                    transform_vector(&relative, &relative, inverse);
                    { int entry = PI(state, 0x6C) * 12;
                    entry += (int)D_L03_0023B6C0;
                    ((ProjectileOffset *)entry)->x = relative.v.x;
                    ((ProjectileOffset *)entry)->y = relative.v.y;
                    ((ProjectileOffset *)entry)->z = relative.v.z; }
                } }
                PI(object, 0x98) = PI(PP(object, 0x24), 0x10);
            } else {
                FastVecScale(state, state, 1.1f);
            }
        }
        break;
    case 2:
        if (GetMobyAnimationValue(object) >= 6.0f) {
            StartAnimationBlendedWithFlags(object, 2, 0, 0, 0);
            object[0x20] = 3;
        }
        break;
    case 3:
        LaunchProjectileAtTarget(object);
        goto checkAttached;
    case 4:
        AimMiniturretAtTarget(object);
        FireMiniturretShot(object);
checkAttached:
        attached = PP(state, 0x70);
        if (attached) {
            if (attached[0x20] != 0xFE) {
                if (attached[0x20] != 0xFD)
                    break;
            }
            PI(object, 0x98) = 0;
            state[0x4F] = AllocEffectSlot_002FED90(1.0f, 1.0f, 1.0f, object, 0);
            object[0x20] = 1;
            PP(state, 0x70) = 0;
        }
        break;
    case 5:
        if (GetMobyAnimationValue(object) <= 1.0f) {
            StartAnimationBlendedWithFlags(object, 0, 0, 0, 0);
            PF(object, 0x48) = 1.0f;
            object[0x20] = 6;
        }
        break;
    case 6:
        if (D_L03_0023B300.row1[(signed char)state[0x4E]]) {
            object[0x20] = 2;
            PlayMobySound(1, 0, object);
            StartAnimationBlendedWithFlags(object, 1, 0, 0, 0);
            PI(state, 0x48) = AllocateSlotForObject(object, 0);
        }
        break;
    case 7:
        MoveProjectileAndCheckHit_L00(object);
        SpawnObjectEffectBurst(object);
        break;
    case 8:
        PlayMobySound(3, 0, object);
        SpawnExplosionWithSparks(0.5f, 13.0f, object, object + 0x10, -1);
        object[0x20] = 9;
        *(unsigned short *)(object + 0x34) |= 0x41;
        break;
    case 9:
        if (!PI(state, 0x64)) {
            if (PI(state, 0x48) != -1)
                FreeSlot(PI(state, 0x48));
            if ((signed char)state[0x4E] != -1)
                RemoveFromSlotList(&D_L03_0023B300, (signed char)state[0x4E]);
            MarkMobySpawned(object);
            return;
        }
        break;
    }
    if (object[0x20] >= 2 && D_L03_0023B530[PI(state, 0x6C)]) {
        index = PI(state, 0x6C);
        { int entry = index * 12;
        entry += (int)D_L03_0023B6C0;
        normal.v.x = ((ProjectileOffset *)entry)->x;
        normal.v.y = ((ProjectileOffset *)entry)->y;
        normal.v.z = ((ProjectileOffset *)entry)->z; }
        normal.v.w = 0;
        matrix_mul_vec3(&normal, &normal, D_L03_0023B530[PI(state, 0x6C)] + 0xC0);
        FastVecAdd(object + 0x10, D_L03_0023B530[PI(state, 0x6C)] + 0x10, &normal);
    }
    if ((unsigned int)(object[0x20] - 3) < 2)
        AdvanceChildBlend(object);
    FastVectorHelperB(state + 0x5C);
    if ((FastFloatHelperD(state + 0x40) || PI(D_L03_00189E20, 0x2294) == 0x6F) && object[0x20] != 9)
        object[0x20] = 8;
    UpdateOwnedParticleTrails(object);
    if ((unsigned int)(object[0x20] - 3) < 2) {
        CheckProjectileHitBreak(object);
        if (!D_L03_0023B300.row1[(signed char)state[0x4E]]) {
            StartAnimationBlendedWithFlags(object, 1, 9, 0, 0);
            object[0x20] = 5;
            PF(object, 0x48) = -1.0f;
            FreeSlot(PI(state, 0x48));
            PI(state, 0x48) = -1;
            *(short *)(state + 0x4C) = 1;
            PI(state, 0x50) = 0;
            PI(state, 0x44) = 0;
            PI(state, 0x68) = 0;
            qcopy(state + 0x30, state + 0x10);
            qcopy(state + 0x20, state + 0x10);
        }
    }
    if (object[0x20] < 8 && PP(state, 0x70))
        FollowSourceObjectPosition(object);
    AddDrawCallbackToList3(DrawProjectileEffects, object);
}
