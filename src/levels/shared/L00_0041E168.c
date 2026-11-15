#include "common.h"

extern char D_L00_001B8DC0[], D_00189ED0[];
typedef struct { u8 pad0[4]; u8 flag; u8 pad5[224 - 5]; } Weapon_L00_0041E168;
typedef struct { u8 pad0[0x16]; u8 slot; } Save_L00_0041E168;
extern Weapon_L00_0041E168 D_L00_00262570[];
extern Save_L00_0041E168 D_00139568;
extern int D_L00_001A8FF0 MACRO_ADDR;
extern float D_L00_001B1488 __attribute__((sda)), D_L00_001B148C __attribute__((sda));
extern float D_L00_001B1474 __attribute__((sda)), D_L00_001B1478 __attribute__((sda));
extern float D_L00_001B147C __attribute__((sda)), D_L00_001B1480 __attribute__((sda)), D_L00_001B1484 __attribute__((sda));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002C2210(void *, int, unsigned int, float, float, int, int, void *, int, float);

/* Sprays a burst of sparks out from a hit point, with a color that depends on the weapon type. */
void func_L00_0041E168(float *origin, int count, int mode)
{
    float velocity[4] __attribute__((aligned(16)));
    float previous[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float projection[4] __attribute__((aligned(16)));
    float size, rotation;
    int direction;
    unsigned int color;
    char *particle;

    FastVecSub(difference, gCameraPosition_L00, origin);
    if (D_L00_001A8FF0 == 0) {
        difference[2] = 0.0f;
        axis[0] = 0.0f;
        axis[1] = 0.0f;
        axis[2] = 1.0f;
        axis[3] = 1.0f;
    } else {
        FastVecSub(projection, origin, D_00189ED0);
        vec_scale_to_length(axis, projection, 1.0f);
        FastVecScale(projection, axis, FastVecDot(axis, difference));
        FastVecSub(difference, difference, projection);
    }
    if (count <= 0)
        return;
    do {
        size = RandomFloatRange(D_L00_001B1488, D_L00_001B148C);
        direction = RandomIntBelow(2);
        if (direction == 0)
            direction--;
        rotation = RandomFloatRange(-1.0471977f, 1.0471977f);
        ApplyAxisRotationToQuaternion(velocity, difference, axis, rotation);
        vec_scale_to_length(velocity, velocity, RandomFloatRange(D_L00_001B1474, D_L00_001B1478) * 0.016666668f);
        velocity[2] = RandomFloatRange(D_L00_001B147C, D_L00_001B1480) * 0.016666668f;
        qcopy(previous, origin);
        origin[0] += RandomSignedFloatRange(0.0f, 0.15f);
        origin[1] += RandomSignedFloatRange(0.0f, 0.15f);
        origin[2] += RandomSignedFloatRange(0.0f, 0.15f);
        if (((Weapon_L00_0041E168 *)(gItemSlotToRecord.slot * sizeof(Weapon_L00_0041E168) + (unsigned int)gWeaponTable_L00))->flag)
            color = mode ? 0x802080 : 0x802020;
        else
            color = 0x202080;
        particle = SpawnGroundEffectParticle(origin, 60, color | 0x7F000000, size * 0.1f, size, 0, direction, velocity, 1, D_L00_001B1484);
        if (particle)
            particle[9] = FloatToInt(4.0f) + 112;
        particle = SpawnGroundEffectParticle(origin, 60, 0x7F7F7F7F, size * 0.07f, size * 0.7f, 1, -direction, velocity, 1, D_L00_001B1484);
        if (particle)
            particle[9] = FloatToInt(4.0f) + 112;
    } while (--count);
}
