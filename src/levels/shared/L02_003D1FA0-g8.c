#include "common.h"
extern float D_L02_001B0164 __attribute__((sda)), D_L02_001B0168 __attribute__((sda));
extern float D_L02_001B0150 __attribute__((sda)), D_L02_001B0154 __attribute__((sda)), D_L02_001B0158 __attribute__((sda)), D_L02_001B015C __attribute__((sda)), D_L02_001B0160 __attribute__((sda));
extern float D_L02_001BA500[];
extern float func_002A7878(float, float), func_002A78D8(float, float);
extern int func_002A77E0(int), func_00283CF0(float);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *), func_00282F20(void *, void *, float);
extern void func_002ACEC0(float, void *, void *, void *);
extern char *func_002C2210(float, void *, int, float, int, int, int, void *, int, float);
/* Emits two particles per iteration, with opposite signed orientation. */
void func_L02_003D1FA0(float *pos, int count) {
    float vel[4] __attribute__((aligned(16)));
    float out[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float scale;
    int i, sign;
    char *particle;
    FastVecSub(dir, gCameraPosition_L02, pos);
    vec_scale_to_length(offset, dir, 0.3f);
    dir[2] = 0.0f;
    axis[0] = 0.0f; axis[1] = 0.0f; axis[2] = 1.0f; axis[3] = 1.0f;
    for (i=0;i<count;i++) {
        scale = RandomFloatRange(D_L02_001B0164, D_L02_001B0168);
        sign = RandomIntBelow(2); if (!sign) sign--;
        ApplyAxisRotationToQuaternion(RandomFloatRange(-1.047197699546814f, 1.047197699546814f), vel, dir, axis);
        vec_scale_to_length(vel, vel, RandomFloatRange(D_L02_001B0150, D_L02_001B0154) * (1.0f / 60.0f));
        vel[2] = RandomFloatRange(D_L02_001B0158, D_L02_001B015C) * (1.0f / 60.0f);
        FastVecAdd(out, pos, offset);
        pos[0] += RandomSignedFloatRange(0.0f, 0.15f);
        pos[1] += RandomSignedFloatRange(0.0f, 0.15f);
        pos[2] += RandomSignedFloatRange(0.0f, 0.15f);
        particle = SpawnGroundEffectParticle(scale * 0.1f, out, 60, scale, 0x7F007F40, 0, sign, vel, 0, D_L02_001B0160);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
        particle = SpawnGroundEffectParticle(scale * 0.07f, out, 60, scale * 0.7f, 0x047F047F, 1, -sign, vel, 0, D_L02_001B0160);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
    }
}
