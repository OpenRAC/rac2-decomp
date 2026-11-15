#include "common.h"

typedef int GornQuad __attribute__((mode(TI)));
extern char *D_L15_001FE480[];
extern int func_002ED688(unsigned char *);
extern int func_00282948(void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_002EE920(void *, void *);
extern int func_00283CF0(float);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282DD8(void *, void *, void *);
extern int func_002E5CF8(int, int, void *);
extern char *D_L15_001B261C __attribute__((sda));
typedef struct GornOwner {
    char pad00[0x11C];
    int flag11C;
    char *target;
    char pad124[0xC];
    int timer;
} GornOwner;
extern char D_L15_002B6CF0[];
extern char *D_L15_001BFC18[];
extern int D_L15_001B17B0[] SDATA(D_L15_001B17B0);
extern u8 D_00188660[];
extern char *func_L05_0037B440(int, int);
extern int func_L05_0037B538(void *, int, int, int);
extern int func_002EEB00(void *);
extern void func_002EE678(void *, int);
extern void func_L05_0037C160(void *);
extern int func_00283DB8(void *, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_002E59F8(int);
extern void func_002AB6D8(void *, void *);
/* Returns a pointer (src/levels/shared/L05_003D33E8.c); this caller ignores it, but the
   call must still set $v0 for local-alloc to give the joint-table base $v0. */
extern char *func_L05_00424990(void *, int, int, float, int, int, int, int, int, int, int, int);
extern void func_L15_00435838(char *);
extern void func_L15_00436298(char *);
extern void func_L15_004363C8(void *);
extern void func_L15_004360D8(void *, int);
extern void func_L15_00434D28(void *);

/* Updates the Gorn enemy ship while it flies its route: fires shots, reacts to hits and shows damage as it loses parts. */
void func_L15_00434610(char *object, int flag) {
    float up[4], point[4], matrix[16];
    char *vars = *(char **)(object + 0x68);
    GornOwner *owner;
    char *shot, *shotVars, *route, *entry;
    int i, j, routeIndex, partsLeft, sound;
    *(GornQuad *)up = 0;
    up[2] = 1.0f;
    owner = (GornOwner *)GetMobyMotionData((unsigned char *)object);
    owner->flag11C = 1;
    owner->target = D_L15_001B261C + (*(int *)(vars + 0x260) << 8);
    if (FastFloatHelperD(vars + 0x444)) {
        *(int *)(vars + 0x444) = 300;
        for (i = *(int *)(vars + 0x440) * 3; i < *(int *)(vars + 0x440) * 3 + 3; i++) {
            qcopy_nc(point, D_L15_002B6CF0 + i * 16);
            matrix_mul_vec3(point, point, object + 0xC0);
            FastVecAdd(point, point, object + 0x10);
            shot = SpawnFreeLevelObjectById(0x957 /* moby class 2391 */, 1);
            if (shot) {
                shotVars = (char *)GetMobyMotionData((unsigned char *)shot);
                qcopy_nc(shot + 0x10, point);
                vec_scale_to_length(shot + 0xC0, object + 0xD0, *(int *)(vars + 0x440) ? -1.0f : 1.0f);
                qcopy_nc(shotVars + 0x90, shot + 0xC0);
                FastVecCross(shot + 0xD0, shot + 0xC0, up);
                vec_scale_to_length(shot + 0xD0, shot + 0xD0, 1.0f);
                FastVecCross(shot + 0xE0, shot + 0xD0, shot + 0xC0);
                FastVecScale(shotVars + 0x60, shot + 0xC0, 10.0f);
                FastVecAdd(shotVars + 0x60, shot + 0x10, shotVars + 0x60);
                *(int *)(shotVars + 0x130) = 500;
            }
        }
        *(int *)(vars + 0x440) ^= 1;
    }
    if (*(int *)(vars + 0x264)) {
        for (j = 0; j < 6; j++) {
            qcopy_nc(point, D_L15_002B6CF0 + j * 16);
            matrix_mul_vec3(point, point, object + 0xC0);
            FastVecAdd(point, point, object + 0x10);
        }
    }
    AimGornShipParts(object);
    route = D_L15_001FE480[*(int *)(vars + 0x448)];
    if (HasFollowerReachedTarget(object)) {
        routeIndex = *(int *)(vars + 0x44C);
        *(int *)(vars + 0x44C) = routeIndex + 1;
        SetFollowerPushVector(object, route + 16 + routeIndex * 16);
        owner->timer = 2000000;
        if (*(int *)(vars + 0x44C) >= *(int *)route) *(int *)(vars + 0x44C) = 0;
    }
    SetFollowerState(object, 2);
    UpdateObjectMovementState(object);
    qcopy_nc(point, object + 0x10);
    point[3] = *(float *)(object + 0xC) * 0.0009765599970705807f;
    if (FastMathHelperA(point, 100.0f) != -1 &&
        CollLine(object + 0x10, owner->target + 0x10, 0, object, 0) &&
        D_L15_001BFC18[0] && *(short *)(D_L15_001BFC18[0] + 0xAA) == *(short *)(owner->target + 0xAA))
        FireGornPathMoverShots(object);
    if (FastMathHelperA(point, 192.0f) != -1 && (unsigned char)object[0x20] != 2)
        SpawnExhaustParticles_L15(object);
    if (!flag && ProcessObjectCollisionHit(object, 1, 1, 1)) {
        object[0x20] = 6;
        PlayMobySound(1, 0, object);
        sound = *(int *)(vars + 0x458);
        if (sound != -1) {
            entry = (char *)(gSoundState + sound * 0x70);
            if (*(char **)(entry + 0x88) == object && *(unsigned char *)(entry + 0x74)) StopSoundVoice(sound);
        }
        *(int *)(vars + 0x458) = -1;
        qcopy_nc(matrix, object + 0xC0);
        qcopy_nc(matrix + 4, object + 0xD0);
        qcopy_nc(matrix + 8, object + 0xE0);
        GetEulerAnglesFromMatrix(matrix, vars + 0x400);
    }
    if ((unsigned char)object[0x20] == 4) {
        if (*(float *)(vars + 0x180) <= 400.0f) {
            *(int *)(vars + 0x268) = 0;
            if (!*(int *)(vars + 0x45C)) {
                PlayMobySound(4, 0, object);
                *(int *)(vars + 0x45C) = 1;
            }
            partsLeft = FloatToInt(*(float *)(vars + 0x180) * 0.02f);
            if (partsLeft < 7 && partsLeft != *(int *)(vars + 0x26C)) {
                SpawnShockwaveBurst(object + 0x10, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                TransformMobyJointToWorld(object, D_L15_001B17B0[7-partsLeft], matrix);
                SpawnShockwaveBurst(matrix, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                SpawnLinkedPart(object, partsLeft-1);
            }
            SpawnGornShipDamageEffects(object);
            *(int *)(vars + 0x26C) = partsLeft;
            if (partsLeft > 0) *(short *)(object + 0x7C) = (1 << (partsLeft-1)) - 1;
            else *(short *)(object + 0x7C) = 0;
        }
    }
    else {
        if (*(float *)(vars + 0x180) <= 100.0f) {
            *(int *)(vars + 0x268) = 0;
            if (!*(int *)(vars + 0x45C)) {
                PlayMobySound(4, 0, object);
                *(int *)(vars + 0x45C) = 1;
            }
            partsLeft = FloatToInt(*(float *)(vars + 0x180) * 0.08f);
            if (partsLeft < 7 && partsLeft != *(int *)(vars + 0x26C)) {
                SpawnShockwaveBurst(object + 0x10, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                TransformMobyJointToWorld(object, D_L15_001B17B0[7-partsLeft], matrix);
                SpawnShockwaveBurst(matrix, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                SpawnLinkedPart(object, partsLeft-1);
            }
            SpawnGornShipDamageEffects(object);
            *(int *)(vars + 0x26C) = partsLeft;
            if (partsLeft > 0) *(short *)(object + 0x7C) = (1 << (partsLeft-1)) - 1;
            else *(short *)(object + 0x7C) = 0;
        }
    }
}
