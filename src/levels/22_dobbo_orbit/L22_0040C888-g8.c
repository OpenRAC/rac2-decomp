#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern unsigned char *D_L22_001AF314[] __attribute__((sda));
extern unsigned char *D_L22_001C00D8 NOT_SDA;
extern unsigned char D_00189F00[], D_L22_001B9C80[];
extern int D_L22_001AF304[] __attribute__((sda));
extern float D_L22_001AF308 __attribute__((sda));
extern float D_L22_001B2AA0;
extern float D_L22_001B2AA4;
extern float D_L22_001B11A0 __attribute__((sda));
extern float D_L22_001B11A4 __attribute__((sda));
extern float D_L22_001B11A8 __attribute__((sda));
extern float D_L22_001B11AC __attribute__((sda));
extern float D_L22_001B11B0 __attribute__((sda));
extern float D_L22_001B11B4 __attribute__((sda));
extern float D_L22_001B11BC __attribute__((sda));
extern float D_L22_001B11C0 __attribute__((sda));
extern float D_L22_001B11C4 __attribute__((sda));
extern void func_L22_0040D638(void *), func_L22_0040DA80(void *), func_L22_0040DD20(void *);
extern float func_00282E48(void *, void *), func_L02_00329C48(void *, void *, int), func_002B0360(void *);
extern void func_002A7750(void *, int, int), func_002A7470(void *, int, int, int);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *), func_00283098(void *, void *, void *);
extern int func_L22_003A2780(void *, void *, void *), func_002B3890(void *), func_002B1C20(void *, void *);
extern void func_L22_003A2988(void *, float);
extern int func_00277258(void *, int, void *, float);
extern void func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void func_0029F338(void *);
extern int func_002A77E0(int), func_002A7820(int, int);
extern void func_L22_0040DB20(void *, void *, float), func_L22_0040DC40(void *, void *, int, float);
extern void func_L02_00332630(void *, void *);
extern int func_L00_0035F5A0(int, int, int);
extern int func_L22_003A6620(void);
extern void func_L22_003A3C70(void *, int), func_002A7A00(void *, float, float);
extern float func_00282C48(float);
extern unsigned char *func_00273730(void *, int, int, int, void *, void *, void *, int, float, float);
extern void func_00310C88(void);
extern void func_00282F20(void *, void *, float), func_00282D30(void *, void *, float);
extern void func_L22_003A2B90(void *, void *, void *, int);
extern int func_002AEB60(void *, float);
extern float func_002A7878(float, float);
extern void func_002A7988(void *, float, float);

typedef struct { unsigned char pad[0x80]; Vec position; unsigned char gap[0x2200]; unsigned char *moby; } HeroView;
extern HeroView D_00189E20;

/* Per-frame update of a flying enemy. It chases and attacks the hero, dodges, and breaks off with a burst when it hits something. */
void func_L22_0040C888(unsigned char *obj) {
    Vec delta, temp, push, old, posx, negx, posy, negy, offset, scatter;
    unsigned char *ctx = *(unsigned char **)(obj + 0x68);
    unsigned char *hit, *part;
    int collision, facing, visible, flags, i, choice;
    float distance;
    UpdateFlyingEnemyStates_L22(obj);
    if (!D_L22_001AF314[0]) return;
    collision = 0; facing = 0; distance = 0.0f; visible = 0;
    if (obj[0x20] != 6 && obj[0x95] != 5) {
        if (fast_vec_dist(D_L22_001AF314[0] + 0x10, obj + 0x10) < D_L22_001B11A0) {
            collision = 1;
            SetMobyState(obj, 5, 3);
        }
        FastVecSub(&delta, (&gHeroState.position), obj + 0x10);
        if (MeasureStepAngle(obj, &delta, 0) <= 0.785398185f) facing = 1;
        if (WalkPathIsClear(D_L22_001AF314[0], (&gHeroState.position), obj + 0x10)) visible = 1;
        distance = fast_vec_dist((&gHeroState.position), obj + 0x10);
        if (GetDistanceFromGravityCenter(obj + 0x10) - D_L22_001B2AA4 > 9.19999981f) {
            qcopy(&temp, obj + 0x10);
            PushPointOutOfArena(&temp, 2.0f);
            if (TestPointAgainstCollision(&temp, 0, obj, 5.0f) && (hit = D_L22_001C00D8) && *(short *)(hit + 0xAA) == 0xDCE /* moby class 3534 */) {
                SpawnExplosion(hit + 0x10, 0, 0x19, 0x14, 0x14, 0xA, 0xF, 1, 1, 0, 0, 0, 1.5f, 20.0f);
                MarkMobySpawned(hit);
            }
        }
    }
    switch (obj[0x95]) {
        case 0:
            if (SetSecondPendingFlag(obj) && obj[0x43] != 1) StartAnimationBlended(obj, 1, 0, 20);
            if (D_L22_001AF304[0]) break;
            if (visible && distance < 40.0f) {
                SetMobyState(obj, 3, 1);
                if (*(int *)(ctx + 0x258) < 300) *(int *)(ctx + 0x258) = RandomIntRange(480, 600);
            } else if (obj[0x31] && distance < 80.0f) {
                SteerMobyTowardTarget_L22(obj, ctx + 0x2A0, 1, D_L22_001B11AC);
            } else CallWithZeroedVector(obj);
            break;
        case 1:
            if (SetSecondPendingFlag(obj) && obj[0x43] != 1) StartAnimationBlended(obj, 1, 0, 20);
            if (!*(int *)(ctx + 0x258)) {
                SetMobyState(obj, 2, 0);
            } else if (visible && facing && distance < 30.0f) {
                SetMobyState(obj, 4, 2);
                CallWithZeroedVector(obj);
            } else SteerMobyTowardTarget_L22(obj, (&gHeroState.position), 1, D_L22_001B11B4);
            break;
        case 2:
            if (facing || SetSecondPendingFlag(obj)) {
                if (obj[0x43] != 3) StartAnimationBlended(obj, 3, 0, 10);
                *(float *)(obj + 0x48) = D_L22_001B2AA0;
            } else if ((obj[0x60] & 2) && obj[0x43] == 3) StartAnimationBlended(obj, 1, 0, 10);
            if (!visible || distance > 50.0f) {
                SetMobyState(obj, 2, 0);
                *(int *)(ctx + 0x258) = 0;
            } else if (distance > 20.0f) SteerMobyTowardTarget_L22(obj, (&gHeroState.position), 1, D_L22_001B11B4);
            else CheckTargetPointFromOffset(obj, (&gHeroState.position));
            break;
        case 3:
            flags = DispatchActionByKind(obj, ctx + 0x140);
            if ((flags & 1) || collision) {
                Vec *saved_position;
                StartEffectInSlot(17, 0, 0);
                if (*(void **)(ctx + 0x38) == gHeroState.moby && IsCounterBelowOwnerLimit()) ForwardToStoredObject((&gHeroState.position), 0);
                for (i = 0; i < 5; i++) {
                    RandomDirectionVector(&delta, D_L22_001B11BC * 0.0166666675f, D_L22_001B11C0 * 0.0166666675f);
                    delta.f[2] = FloatAbs(delta.f[2]) * D_L22_001B11C4;
                    matrix_mul_vec3(&delta, &delta, obj + 0xC0);
                    part = CreateCameraMoby(obj, 1, *(short *)(obj + 0xAA), i, obj + 0x10, obj + 0xF0, &delta, 255, 30.0f, 15.0f);
                    *(void **)(part + 0x64) = UpdateFadeOutMoby;
                }
                FastVecSub(&temp, D_L22_001B9C80, &delta);
                vec_scale_to_length(&temp, &temp, 1.0f);
                SpawnExplosion(obj + 0x10, 0, 25, 20, 20, 10, 15, 1, 1, 0, 0, 0, 1.5f, 20.0f);
                *(short *)(ctx + 0x178) = 0;
                *(int *)(obj + 0x98) = *(int *)(*(char **)(obj + 0x24) + 0x10);
                *(float *)(ctx + 0x20) = *(short *)(ctx + 0x24);
                saved_position = &old;
                /* This fresh scratch vector is consumed through calls; no C field
                 * access depends on moving across its copy. */
                qcopy_nc(saved_position, (&gHeroState.position));
                PushPointOutOfArena(saved_position, 0.0f);
                FastVecScale(&push, gHeroState.moby + 0xE0, -80.0f);
                switch (RandomIntBelow(7)) {
                case 0: FastVecScale(&offset, gHeroState.moby + 0xC0, -50.0f); break;
                case 1: FastVecScale(&offset, gHeroState.moby + 0xD0, 50.0f); break;
                case 2: FastVecScale(&offset, gHeroState.moby + 0xD0, -50.0f); break;
                case 3:
                    FastVecScale(&posy, gHeroState.moby + 0xD0, 50.0f);
                    FastVecScale(&posx, gHeroState.moby + 0xC0, 50.0f);
                    FastVecAdd(&offset, &posy, &posx); FastVecScale(&offset, &offset, 0.5f); break;
                case 4:
                    FastVecScale(&posx, gHeroState.moby + 0xC0, 50.0f);
                    FastVecScale(&negy, gHeroState.moby + 0xD0, -50.0f);
                    FastVecAdd(&offset, &posx, &negy); FastVecScale(&offset, &offset, 0.5f); break;
                case 5:
                    FastVecScale(&negy, gHeroState.moby + 0xD0, -50.0f);
                    FastVecScale(&negx, gHeroState.moby + 0xC0, -50.0f);
                    FastVecAdd(&offset, &negy, &negx); FastVecScale(&offset, &offset, 0.5f); break;
                case 6:
                    FastVecScale(&negx, gHeroState.moby + 0xC0, -50.0f);
                    FastVecScale(&posy, gHeroState.moby + 0xD0, 50.0f);
                    FastVecAdd(&offset, &negx, &posy); FastVecScale(&offset, &offset, 0.5f); break;
                }
                FastVecAdd(&push, &push, &offset);
                FastVecAdd(&push, &push, saved_position);
                FindNearestLanePoint(D_L22_001AF314[0], obj + 0x10, &push, 1);
                PushPointOutOfArena(obj + 0x10, 7.19999981f);
                if (TestPointAgainstCollision(obj + 0x10, 1, 0, 3.0f) && *(short *)(D_L22_001C00D8 + 0xAA) == 0xEDD /* moby class 3805 */ && D_L22_001C00D8[0x20] != 6) {
                    FastVecScale(&scatter, obj + 0xC0 + RandomIntBelow(2) * 16,
                                  2.0f * (RandomIntBelow(2) ? D_L22_001AF308 : -D_L22_001AF308));
                    FastVecAdd(obj + 0x10, obj + 0x10, &scatter);
                    PushPointOutOfArena(obj + 0x10, 7.19999981f);
                }
                qcopy(ctx + 0x2A0, obj + 0x10);
                SetMobyState(obj, 2, 0);
            } else if (flags & 2) {
                SetMobyState(obj, 3, 1);
                *(int *)(ctx + 0x258) = RandomIntRange(580, 600);
            }
            break;
        case 4: case 5: break;
        }
    switch (obj[0x20]) {
    case 2: case 3: case 5: case 6: break;
    case 4:
        if (IsValueWithinStepOfThreshold(obj, 1.5f)) SpawnJointTrailEffects(obj, D_00189F00, 0.0f);
        break;
    case 9:
        qcopy(&delta, obj + 0x10);
        PushPointOutOfArena(&delta, 7.19999981f);
        if (*(unsigned short *)(obj + 0x96) >= 61 && !(*(unsigned short *)(obj + 0x96) & 63)) SpawnJointTrailEffects(obj, ctx + 0x2A0, 50.0f);
        if (fast_vec_dist(obj + 0x10, &delta) < 0.1f) {
            SetMobyState(obj, 2, 0);
            *(int *)(ctx + 0x88) &= ~0x10;
        } else SteerMobyTowardTarget_L22(obj, &delta, 0, D_L22_001B11B0);
        break;
    case 7:
        if ((*(unsigned short *)(obj + 0x96) & 7) == 7) {
            qcopy(&delta, *(void **)(ctx + 0x2B0));
            vec_scale_to_length(&delta, &delta, *(float *)(ctx + 0x2B4));
            FastVecAdd(&delta, (&gHeroState.position), &delta);
            PushPointOutOfArena(&delta, 7.19999981f);
            qcopy(ctx + 0x2A0, &delta);
        }
        if (*(unsigned short *)(obj + 0x96) >= 61 && !(*(unsigned short *)(obj + 0x96) & 511)) SpawnJointTrailEffects(obj, ctx + 0x2A0, 50.0f);
        if (fast_vec_dist(obj + 0x10, ctx + 0x2A0) < 2.0f || fast_vec_dist(obj + 0x10, (&gHeroState.position)) < 20.0f) {
            SetMobyState(obj, 9, 5);
            *(int *)(ctx + 0x280) = 0;
        } else SteerMobyTowardTarget_L22(obj, ctx + 0x2A0, 0, D_L22_001B11B4);
        break;
    case 8: {
        float min, max;
        *(float *)(ctx + 0x2B4) = RandomFloatRange(0.0f, 15.0f) + 10.0f;
        choice = RandomIntBelow(4);
        switch (choice) {
        case 0: qcopy(&temp, gHeroState.moby + 0xD0); FastVecScale(&temp, &temp, -1.0f); break;
        case 1: qcopy(&temp, gHeroState.moby + 0xD0); break;
        case 2: qcopy(&temp, gHeroState.moby + 0xC0); FastVecScale(&temp, &temp, -1.0f); break;
        case 3: qcopy(&temp, gHeroState.moby + 0xC0); break;
        }
        min = D_L22_001B11A4; max = D_L22_001B11A8;
        *(void **)(ctx + 0x2B0) = gHeroState.moby + 0xC0;
        FastVecScale(&delta, &temp, RandomFloatRange(min, max));
        FastVecAdd(&delta, &delta, (&gHeroState.position));
        SpawnRandomDirectionEffect(&push, 0.1f, D_L22_001B11A4 * 0.333333343f);
        FastVecAdd(&delta, &delta, &push);
        qcopy(obj + 0x10, &delta);
        qcopy(&old, *(void **)(ctx + 0x2B0));
        vec_scale_to_length(&old, &old, *(float *)(ctx + 0x2B4));
        FastVecAdd(&old, (&gHeroState.position), &old);
        PushPointOutOfArena(&old, 7.19999981f);
        qcopy(ctx + 0x2A0, &old);
        SetMobyState(obj, 7, 5);
        *(int *)(ctx + 0x28C) = 0;
        *(int *)(ctx + 0x88) |= 0x10;
        break;
    }
    }
    UpdateFlyerTimersAndAnimation(obj);
}
