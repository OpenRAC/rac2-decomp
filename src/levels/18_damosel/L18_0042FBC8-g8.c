#include "common.h"

extern void func_002A7750(void *, int, int);
extern int func_002ACBC8(void *, int);
extern u8 D_00189EA0[];
extern u8 *func_L18_003F75E8(int, int *);
extern int func_002B3868(void *);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern void func_002E5CF8(int, int, void *);
extern void func_00282C88(void *);
extern void func_002ACB48(void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L18_003F76F0(void *, void *, void *);
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern int func_L11_00439D78(float, float, float, float);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern float func_00283C28(float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float D_L18_001B1530 __attribute__((sda));
extern float D_L18_001B1534 __attribute__((sda));
extern float D_L18_001B1538 __attribute__((sda));
extern float D_L18_001B153C __attribute__((sda));
extern float D_L18_001B1540 __attribute__((sda));
extern float D_L18_001B1544 __attribute__((sda));
extern float D_L18_001B1548 __attribute__((sda));
extern int D_L18_001B154C __attribute__((sda));
extern float D_L18_001B1550 __attribute__((sda));
extern int D_L18_001B1554 __attribute__((sda));
extern float D_L18_001B1558 __attribute__((sda));
extern float D_L18_001B155C __attribute__((sda));
extern u8 D_L18_001B1560[16] __attribute__((sda));

typedef struct {
    float angles[4];
    int firstId,  secondId,  group;
    float restHeight,  verticalSpeed,  period,  amplitude;
    int spawnCount;
} LauncherState;

typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 state;
    u8 pad21[0x47];
    LauncherState *vars;
    u8 pad6c[0x2A];
    u16 timer;
    u8 pad98[0x58];
    float rotation[4];
} LauncherObject;

/* Updates the launcher: it bounces up and down, throws out pieces on a trigger, and
   finally wobbles until it settles. */
void func_L18_0042FBC8(u8 *moby)
{
    float velocity[4], position[4];
    int count1, count2, count, i;
    u8 *piece;
    LauncherObject *object = (LauncherObject *)moby;
    LauncherState *vars = object->vars;
    float zero, duration;

    switch (object->state) {
    case 0:
        vars->restHeight = object->position[2];
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (vars->firstId != -1 && IsPointInCuboid(gHeroPosition, vars->firstId)) {
            CountGroupProtopets(vars->group, &count1);
            if (count1 >= 4)
                SetMobyState(moby, 2, -1);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(moby)) {
            object->rotation[0] = 0;
            object->rotation[1] = 0;
            zero = object->rotation[0];
            object->position[2] = vars->restHeight;
            vars->verticalSpeed += RandomFloatRange(zero, D_L18_001B1530 * 0.0166666675f);
            vars->angles[0] = RandomFloatRange(zero, D_L18_001B1534 * 0.0002908882452175021f);
            vars->angles[1] = RandomFloatRange(zero, D_L18_001B1538 * 0.0002908882452175021f);
            object->position[2] = vars->restHeight;
            PlayMobySound(0, 0, moby);
        }
        if (object->position[2] >= vars->restHeight) {
            object->position[2] += vars->verticalSpeed;
            vars->verticalSpeed -= D_L18_001B155C * 0.000277777785f;
            if (vars->verticalSpeed > 0) {
                object->rotation[0] = FastAddRotations(vars->angles[0], object->rotation[0]);
                object->rotation[1] = FastAddRotations(vars->angles[1], object->rotation[1]);
            } else {
                object->rotation[0] = FastAddRotations(-vars->angles[0], object->rotation[0]);
                object->rotation[1] = FastAddRotations(-vars->angles[1], object->rotation[1]);
            }
        } else {
            SetMobyState(moby, 2, -1);
        }
        if (vars->secondId != -1 && IsPointInCuboid(gHeroPosition, vars->secondId)) {
            CountGroupProtopets(vars->group, &count2);
            if (count2 >= 4)
                SetMobyState(moby, 3, -1);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(moby)) {
            object->rotation[0] = 0;
            object->rotation[1] = 0;
            object->position[2] = vars->restHeight;
            count = 50;
            for (i = 0; i < vars->spawnCount && count > 0; i++) {
                piece = CountGroupProtopets(vars->group, &count);
                if (piece) {
                    ClearVector128(velocity);
                    velocity[2] = D_L18_001B153C * 0.0166666675f;
                    AddRandomOffsetToVector(velocity, D_L18_001B1540 * 0.0166666675f);
                    FastVecAdd(position, moby + 0x10, D_L18_001B1560);
                    LaunchProtopetShot(piece, position, velocity);
                    *(u8 **)(piece + 0xB8) = moby;
                }
            }
            if (i) {
                SpawnExplosion(moby + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1,
                              1.0f, 20.0f, 1, 1, 0, 0);
                PlayMobySound(0, 0, moby);
                vars->verticalSpeed += RandomFloatRange(D_L18_001B1544, D_L18_001B1548) * 0.0166666675f;
                duration = (float)ComputeProjectileFlightTime(object->position[2], vars->restHeight,
                                                   vars->verticalSpeed, D_L18_001B155C * 0.000277777785f);
                vars->angles[0] = (float)RandomIntBelow(D_L18_001B154C) * 6.28318548f / duration;
                vars->angles[1] = (float)RandomIntBelow(D_L18_001B154C) * 6.28318548f / duration;
                vars->angles[2] = (float)RandomIntBelow(D_L18_001B154C) * 6.28318548f / duration;
            }
        }
        if (object->position[2] >= vars->restHeight) {
            object->position[2] += vars->verticalSpeed;
            vars->verticalSpeed -= D_L18_001B155C * 0.000277777785f;
            object->rotation[0] = FastAddRotations(vars->angles[0], object->rotation[0]);
            object->rotation[1] = FastAddRotations(vars->angles[1], object->rotation[1]);
            object->rotation[2] = FastAddRotations(vars->angles[2], object->rotation[2]);
        } else {
            SetMobyState(moby, 4, -1);
        }
        break;
    case 4:
        if (SetFirstPendingFlag(moby)) {
            ClearVector128(vars);
            ClearVector128(moby + 0xF0);
            object->position[2] = vars->restHeight;
            vars->period = IntToFloat(D_L18_001B1554);
            vars->amplitude = D_L18_001B1558;
            PlayMobySound(0, 0, moby);
        }
        if (vars->amplitude >= 0.1f) {
            object->rotation[0] = vars->amplitude * FastSinOrCosB(FastFloatHelperG(
                IntToFloat(object->timer) * 6.28318548f / vars->period));
            object->rotation[1] = vars->amplitude * FastSinOrCosA(FastFloatHelperG(
                IntToFloat(object->timer) * 6.28318548f / vars->period));
            vars->amplitude *= D_L18_001B1550;
            vars->period *= D_L18_001B1550;
        } else {
            object->rotation[0] = object->rotation[1] = object->rotation[2] = 0.0f;
            SetMobyState(moby, 5, -1);
        }
    }
    if (object->timer <= 0xFFFE)
        ++object->timer;
}
