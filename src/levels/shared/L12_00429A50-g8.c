#include "common.h"

/* func_L12_00429A50 is a unit of its own: -G8 reads the turn rate through $gp, and
   func_L12_00429D60 (L12_003E1CB0-g8.c) is only referenced here. */

typedef struct { int a, b, c, d; } __attribute__((aligned(16))) Quad16;
typedef struct {
    Quad16 vector;
    int owner, flags;
    unsigned char enabled, kind;
    unsigned short id;
    float distance;
    int active;
} CollisionRequest;
typedef struct { Quad16 next; CollisionRequest move; Quad16 direction; CollisionRequest area; } ProjectileWorkspace;
extern int func_002A8C28(void *, float, float *, int, float, float, int, int, int);
extern void func_L12_0031E1D0(void *, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A8C00(char *, int, int, float, Quad16 *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern void func_00282D30(void *, void *, float);
extern int func_00277F48(void *, int, void *, void *, float);
extern void func_00282C88(void *);
extern void func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void func_0029F338(void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L12_00429D60(void *);
extern char D_L12_001C0258[];   /* collision result; +0x0 the object hit */
extern float D_L12_001B22E0 __attribute__((sda));

/* Updates a spinning blast projectile: it flies, checks for hits, damages what it touches and blows up after 240 frames or on impact. */
void func_L12_00429A50(char *object)
{
    ProjectileWorkspace local;
    char *state = *(char **)(object + 0x68);
    if (!*(unsigned char *)(object + 0xBC)) {
        (*(int *)(state + 0x24))++;
        if (*(int *)(state + 0x24) > 240 && !*(unsigned char *)(object + 0xBC)) {
            SweepCollisionFromObject(object, 0.6f, (float *)(object + 0x10), 0x10003, *(float *)(state + 0x14), 0.0f, 0, 1, 0);
            func_L12_0031E1D0(object, 1, -1);
        }
        switch (*(unsigned char *)(object + 0x20)) {
        case 0:
            FastVecAdd(&local.next, object + 0x10, state);
            make_hit_descriptor((char *)&local.move, (int)object, 3, *(float *)(state + 0x14), (Quad16 *)state);
            local.move.id = *(unsigned short *)(object + 0xAA);
            if (CollLine(object + 0x10, &local.next, 0, object, &local.move) != 0 || TestPointAgainstCollision(object + 0x10, 0, object, 0.3f) != 0) {
                if (*(char **)D_L12_001C0258 != 0) {
                    if (*(char **)D_L12_001C0258 != *(char **)(state + 0x10)) {
                        qcopy(&local.direction, state);
                        FastVecScale(&local.direction, &local.direction, 1.5f);
                        ((float *)&local.direction)[2] = 1.0f;
                        ((float *)&local.direction)[3] = 5627.9248f;
                        make_hit_descriptor((char *)&local.area, (int)object, 0x10003, *(float *)(state + 0x14), &local.direction);
                        local.area.kind = 1;
                        local.area.id = *(unsigned short *)(object + 0xAA);
                        local.area.enabled = 0;
                        ProcessCollisionHit(object + 0x10, 0, object, &local.area, 0.6f);
                        if (!*(unsigned char *)(object + 0xBC))
                            func_L12_0031E1D0(object, 1, -1);
                        return;
                    }
                } else {
                    qcopy(&local.direction, state);
                    FastVecScale(&local.direction, &local.direction, 3.0f);
                    ((float *)&local.direction)[2] = 1.0f;
                    ((float *)&local.direction)[3] = 5627.9248f;
                    make_hit_descriptor((char *)&local.area, (int)object, 0x10003, *(float *)(state + 0x14), &local.direction);
                    local.area.kind = 1;
                    local.area.id = *(unsigned short *)(object + 0xAA);
                    local.area.enabled = 0;
                    ProcessCollisionHit(object + 0x10, 0, object, &local.area, 0.6f);
                    if (!*(unsigned char *)(object + 0xBC))
                        func_L12_0031E1D0(object, 1, -1);
                    return;
                }
            }
            if (!*(unsigned char *)(object + 0xBC))
                qcopy(object + 0x10, &local.next);
            FastVecScale(&local.direction, state, -0.5f);
            ClearVector128(&local.area);
            break;
        case 1:
            SpawnExplosion(object + 0x10, 0, 25, 20, 20, 20, 0, 0, 1, 0, 0, 0, 0.25f, 20.0f);
            MarkMobySpawned(object);
            return;
        }
    }
    ApplyAxisRotationToQuaternion(object + 0xE0, object + 0xE0, object + 0xD0, D_L12_001B22E0 * 0.017453294f);
    ApplyAxisRotationToQuaternion(object + 0xC0, object + 0xC0, object + 0xD0, D_L12_001B22E0 * 0.017453294f);
    AddDrawCallbackToList3(SpawnTwoFlareEffects, object);
}
