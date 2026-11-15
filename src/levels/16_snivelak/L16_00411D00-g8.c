#include "common.h"

typedef float V4_F411d00[4] __attribute__((aligned(16)));

extern float D_L16_001B17A0 __attribute__((sda));
extern float D_L16_001B17B0 __attribute__((sda));
extern float D_L16_001B17B8 __attribute__((sda));
extern float D_L16_001B17BC[];

extern void func_002A7A00(void *, float, float);
extern void func_00283098(void *, void *, char *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_002A7878(float, float);
extern float func_L00_0031CDD0(void *, void *, s32, float, float);
extern s32 func_0032C700(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_L16_0041F1F0(s32, void *, void *, s32, float, float);

/* Fires the object's spark: builds a short ray from its frame, tilts it by the resident angle and hands it to the effect spawner. */
void func_L16_00411D00(char *moby)
{
    V4_F411d00 offset, start, goal, velocity;
    char *vars = *(char **)(moby + 0x68);
    float rate, angle;

    RandomDirectionVector(offset, 0.0f, 1.0f);
    matrix_mul_vec3(start, &D_L16_001B17A0, moby + 0xC0);
    FastVecAdd(start, start, moby + 0x10);
    FastVecAdd(start, start, offset);
    FastVecScale(goal, offset, 3.0f);
    goal[2] = 0.0f;
    FastVecAdd(goal, goal, *(char **)(vars + 0x24C) + 0x10);
    rate = D_L16_001B17B0 * 0.016666668f;
    angle = RandomFloatRange(D_L16_001B17B8, D_L16_001B17BC[0]) * 0.00027777778f;
    FastVecSub(velocity, goal, start);
    velocity[2] = 0.0f;
    vec_scale_to_length(velocity, velocity, rate);
    velocity[2] = ComputeShotLaunchSpeed(start, goal, 0, D_L16_001B17B0 * 0.016666668f, -angle);
    SpawnExplosion(start, 0, 0x19, 0x14, 1.0f, 20.0f, 0x14, 0x14, 0x2D, 1, 1, 0, 0, 0);
    SpawnSpinningFragment(*(s32 *)(vars + 0x1F0), start, velocity, 0, angle, (float)*(u8 *)(vars + 0x36));
}
