#include "include_asm.h"

#include "common.h"
extern float g_camera_l18_position[];
extern float math_random_float_range(float, float);
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern int func_001163B0(void);
extern void FastVecScale(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern u8 *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
typedef int TI128 __attribute__((mode(TI)));
extern void FastVecSub(float *, const float *, const float *);
extern void FastVecAdd(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);

void func_PAL_L18_0043A158(char *pos, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    *(TI128 *)axis = 0;
    axis[2] = 1.0f;
    FastVecSub(direction, g_camera_l18_position, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (sign == 0)
            sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        speed = math_random_float_range(0.05f, 3.0f) * (0.020000001f);
        vec_scale_to_length((char *)velocity, (char *)velocity, speed);
        velocity[2] = math_random_float_range(1.0f, 5.0f) * (0.020000001f);
        qcopy(point, pos);
        point[0] += math_random_signed_float_range(0.0f, 0.15f);
        point[1] += math_random_signed_float_range(0.0f, 0.15f);
        point[2] += math_random_signed_float_range(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            FastVecScale(velocity, velocity, 1.5f);
            particle = part_spawn_ground_effect(point, 50, size * 0.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.0028800003f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(point, 50, size * 0.035f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
        } else {
            FastVecSub(extra, g_camera_l18_position, point);
            vec_scale_to_length((char *)extra, (char *)extra, speed);
            FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
            particle = part_spawn_ground_effect(point, 33, size * 0.15f, size, 0x7F800000, 0, sign, velocity, 0, 0.0028800003f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(point, 33, size * 0.105000004f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
        }
        if (particle)
            particle[9] = FloatToInt(4.0f) + 0x70;
    }
}




