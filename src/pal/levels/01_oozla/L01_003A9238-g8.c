#include "include_asm.h"

#include "common.h"
extern float D_L01_001B2F48 __attribute__((sda));
extern float coll_probe_ground_height_below(void *, int, float);
extern void *moby_spawn_scaled_effect(void *, float);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void part_spawn_drifting(void *, void *, int, float, float);
extern void func_PAL_002C0838(void *, void *, int, int);

void func_PAL_L01_003A96A8(char *object)
{
    float center[4], velocity[4], position[4];
    float angle, radius;
    int i, j, type, lifetime;
    int scale = 2;

    qcopy(center, (object + 0x10));
    center[2] = D_L01_001B2F48 = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
    moby_spawn_scaled_effect(center, 4.5f);
    for (i = 4; i >= 0; --i) {
        velocity[0] = *(float *)(object + 0x10) + scale * math_random_float_range(-0.3f, 0.3f);
        velocity[1] = *(float *)(object + 0x14) + scale * math_random_float_range(-0.3f, 0.3f);
        velocity[2] = D_L01_001B2F48;
        part_spawn_drifting(velocity, &D_L01_001B2F48, -1, scale * math_random_float_range(0.3f, 0.6f), 5250.0f);
    }
    for (j = 39; j >= 0; --j) {
        angle = math_random_angle();
        radius = scale * math_random_float_range(0.0f, 0.060000002f);
        velocity[0] = math_fast_sin_or_cos_a(angle) * radius;
        velocity[1] = math_fast_sin_or_cos_b(angle) * radius;
        velocity[2] = scale * math_random_float_range(0.040000003f, 0.10000001f);
        position[0] = *(float *)(object + 0x10) + velocity[0] * 8.0f;
        position[1] = *(float *)(object + 0x14) + velocity[0] * 8.0f;
        position[2] = D_L01_001B2F48 - math_random_float_range(0.0f, 0.2f);
        type = math_random_int_below(2);
        lifetime = math_random_int_range(90, 120);
        func_PAL_002C0838(position, velocity, type, scale * lifetime);
    }
}
