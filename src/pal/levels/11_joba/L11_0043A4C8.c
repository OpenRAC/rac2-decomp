#include "include_asm.h"

#include "common.h"
extern char g_hero_l11_position[];
extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int FloatToInt(float);
extern int FloatToInt(float);
extern char g_hero_l11_position[];
extern float math_random_float_range(float a, float b);

void part_l11_spawn_impact_burst_pal(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    FastVecSub(direction, (float *)g_hero_l11_position, pos);
    vec_scale_to_length((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (!sign) sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        vec_scale_to_length((char *)velocity, (char *)velocity, math_random_float_range(0.05f, 3.0f) * 0.020000001f);
        velocity[2] = math_random_float_range(1.0f, 5.0f) * 0.020000001f;
        FastVecAdd((char *)origin, (char *)pos, (char *)offset);
        pos[0] += math_random_signed_float_range(0, 0.15f);
        pos[1] += math_random_signed_float_range(0, 0.15f);
        pos[2] += math_random_signed_float_range(0, 0.15f);
        particle = part_spawn_ground_effect(origin, 50, size * 0.1f, size, 0x8020FF20, 0, sign, velocity, 0, 0.0028800003f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
        particle = part_spawn_ground_effect(origin, 50, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
    }
}




