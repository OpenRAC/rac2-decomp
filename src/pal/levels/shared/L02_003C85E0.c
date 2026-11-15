#include "include_asm.h"


#include "common.h"
extern void FastVecSub(float *, const float *, const float *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(char *, char *, float);
extern char g_camera_l02_position[];
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int FloatToInt(float);
extern int math_random_int_below(int);

/* Emits paired particles with opposite spin and randomized velocities. */
void func_PAL_L02_003C8738(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    FastVecSub(direction, (float *)g_camera_l02_position, pos);
    vec_scale_to_length((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (!sign) sign--;
        angle = func_002A7878_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        vec_scale_to_length((char *)velocity, (char *)velocity, func_002A7878_range(0.05f, 3.0f) * 0.020000001f);
        velocity[2] = func_002A7878_range(1.0f, 5.0f) * 0.020000001f;
        FastVecAdd(origin, pos, offset);
        pos[0] += math_random_signed_float_range(0, 0.15f);
        pos[1] += math_random_signed_float_range(0, 0.15f);
        pos[2] += math_random_signed_float_range(0, 0.15f);
        particle = part_spawn_ground_effect(origin, 50, size * 0.1f, size, 0xDDFF1010, 0, sign, velocity, 0, 0.0028800003f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
        particle = part_spawn_ground_effect(origin, 50, size * 0.07f, size * 0.7f, 0xDDFF1010, 1, -sign, velocity, 0, 0.0028800003f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
    }
}


