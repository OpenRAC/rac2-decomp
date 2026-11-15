#include "common.h"

extern void *func_002A9640(void *, int, int);
extern float func_002A96A0(void *, void *);
extern void func_002AB800(void *, void *), func_002AB8C0(void *, void *);
extern void func_002A7750(void *, int, int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float), func_00283B98(float, float);
extern int func_002ACBC8(void *, int), func_002B3868(void *);
extern void func_0029F338(void *), func_00282948(void *);
extern int func_002E5CF8(int, int, void *);
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern void func_00282F20(void *, void *, float), func_00283098(void *, void *, void *), func_002ACB48(void *, float), func_00282CC0(void *, void *, void *);
extern u8 D_00189EA0[];
extern u8 D_L18_001A8F20[] __attribute__((sda));
extern float D_L18_001B1AB0 __attribute__((sda));
extern float D_L18_001B1AB4 __attribute__((sda));
extern float D_L18_001B1AB8 __attribute__((sda));
extern float D_L18_001B1ABC __attribute__((sda));
extern float D_L18_001B1AC0 __attribute__((sda));
extern float D_L18_001B1AC4 __attribute__((sda));
extern float D_L18_001B1ACC __attribute__((sda));
extern int D_L18_001B1AD0 __attribute__((sda));
extern int D_L18_001B1AD4 __attribute__((sda));
extern u8 D_L18_001B1AE0[] SDATA(D_L18_001B1AE0);
extern u8 D_L18_001B1AF0[] SDATA(D_L18_001B1AF0);
extern u8 *func_L18_003F75E8(int, int *);
extern void func_L18_003F76F0(void *, void *, void *);

typedef struct {
    u8 pad00[0x20];
    float health;
    s16 initialized;
    u8 pad26[0xa];
    float scale;
    u8 pad34[0x1c];
    float transform[4];
    float turnX, turnY;
    u8 pad68[8];
    s32 startRegion, fireRegion, childId;
    float baseZ, velocityZ;
    s32 fireTimer;
} LauncherState;

typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 mode;
    u8 pad21[0x47];
    LauncherState *state;
    u8 pad6c[0x2a];
    u16 timer;
    u8 pad98[0x10];
    u8 opacity;
    u8 pada9[0x17];
    float matrix[12];
    float rotation[4];
} LauncherObject;

/* Updates a launcher (moby class 4440) that hops up and down and shoots out child objects when the player triggers it. It breaks when its health runs out. */
void func_L18_0043C258(LauncherObject *obj) {
    LauncherState *vars = obj->state;
    u8 *child;
    float damage, z;
    float velocity[4] __attribute__((aligned(16)));
    float muzzlePos[4] __attribute__((aligned(16)));
    int zero;

    damage = UpdateAimTargetStrength(obj, FindOwnedEffectSlot(obj, 0x10000, 0));
    vars->health -= damage;
    if (damage > 0.0f) {
        StartColorFade(obj, vars->transform);
        if (vars->health <= 0.0f) {
            SpawnExplosion(obj->position, 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
            SpawnDebrisForMaskedParts(obj, 0x3a, D_L18_001A8F20, 3, 6, 3, 6, 255);
            PlayMobySound(1, 0, obj);
            MarkMobySpawned(obj);
            return;
        }
    }
    obj->opacity = 255;
    UpdateColorFade(obj, vars->transform);
    switch (obj->mode) {
    case 0:
        vars->baseZ = obj->position[2];
        if (!vars->initialized) {
            vars->initialized = 1;
            vars->health = 1;
        }
        vars->fireTimer = -1;
        vars->scale = 1;
        SetMobyState(obj, 1, -1);
        break;
    case 1:
        if (vars->startRegion != -1 && IsPointInCuboid(gHeroPosition, vars->startRegion))
            SetMobyState(obj, 2, -1);
        break;
    case 2:
        if (SetFirstPendingFlag(obj)) {
            obj->rotation[0] = 0;
            obj->rotation[1] = 0;
            z = obj->rotation[0];
            obj->position[2] = vars->baseZ;
            vars->velocityZ += RandomFloatRange(z, D_L18_001B1AB0 * (1.0f / 60.0f));
            vars->turnX = RandomFloatRange(z, D_L18_001B1AB4 * 0.0002908882452175021f);
            vars->turnY = RandomFloatRange(z, D_L18_001B1AB8 * 0.0002908882452175021f);
            obj->position[2] = vars->baseZ;
            PlayMobySound(0, 0, obj);
        }
        if (obj->position[2] >= vars->baseZ) {
            obj->position[2] += vars->velocityZ;
            vars->velocityZ -= D_L18_001B1ACC * 0.00027777778450399637f;
            if (vars->velocityZ > 0) {
                obj->rotation[0] = FastAddRotations(vars->turnX, obj->rotation[0]);
                obj->rotation[1] = FastAddRotations(vars->turnY, obj->rotation[1]);
            } else {
                obj->rotation[0] = FastAddRotations(-vars->turnX, obj->rotation[0]);
                obj->rotation[1] = FastAddRotations(-vars->turnY, obj->rotation[1]);
            }
        } else {
            SetMobyState(obj, 2, -1);
        }
        if (vars->fireTimer == 0) {
            zero = 0;
            child = CountGroupProtopets(vars->childId, &zero);
            if (child) {
                vec_scale_to_length(velocity, D_L18_001B1AF0, D_L18_001B1AC0 * (1.0f / 60.0f));
                matrix_mul_vec3(velocity, velocity, obj->matrix);
                AddRandomOffsetToVector(velocity, D_L18_001B1ABC * (1.0f / 60.0f));
                matrix_mul_vec3(muzzlePos, D_L18_001B1AE0, obj->matrix);
                FastVecAdd(muzzlePos, muzzlePos, obj->position);
                LaunchProtopetShot(child, muzzlePos, velocity);
                *(s32 *)(child + 0xB8) = (s32)obj;
                vars->fireTimer = RandomIntRange(D_L18_001B1AD0, D_L18_001B1AD4);
            }
        } else if (vars->fireTimer == -1) {
            if (vars->fireRegion != -1 && IsPointInCuboid(gHeroPosition, vars->fireRegion)) {
                vars->fireTimer++;
                SpawnExplosion(obj->position, 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
                PlayMobySound(1, 0, obj);
                vec_scale_to_length(velocity, D_L18_001B1AF0, D_L18_001B1AC4 * (1.0f / 60.0f));
                matrix_mul_vec3(velocity, velocity, obj->matrix);
                AddRandomOffsetToVector(muzzlePos, D_L18_001B1ABC * (1.0f / 60.0f));
                FastVecAdd(velocity, velocity, muzzlePos);
                SpawnDebrisForMaskedParts(obj, 5, velocity, 3, 6, 3, 6, 255);
            }
        } else {
            FastFloatHelperD(&vars->fireTimer);
        }
        break;
    }
    if (obj->timer < 65535)
        (obj->timer)++;
}
