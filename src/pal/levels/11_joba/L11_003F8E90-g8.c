#include "common.h"

/* func_PAL_L11_003F8E90, the PAL copy of func_L11_003F4A58: 1/60 becomes 0.02f, the particle lifetimes take the 50 Hz scale, and D_L11_001B0664 is scaled by 1.44f. */

extern float D_L11_001BA8C0[];

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

extern float D_L11_001B0654 __attribute__((sda));
extern float D_L11_001B0658 __attribute__((sda));
extern float D_L11_001B065C __attribute__((sda));
extern float D_L11_001B0660 __attribute__((sda));
extern float D_L11_001B0664 __attribute__((sda));
extern float D_L11_001B0668 __attribute__((sda));
extern float D_L11_001B066C __attribute__((sda));

void func_PAL_L11_003F8E90(char *pos, int count) {
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
    FastVecSub(direction, D_L11_001BA8C0, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(D_L11_001B0668, D_L11_001B066C);
        sign = math_random_int_below(2);
        if (sign == 0)
            sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        speed = math_random_float_range(D_L11_001B0654, D_L11_001B0658) * 0.020000001f;
        vec_scale_to_length((char *)velocity, (char *)velocity, speed);
        velocity[2] = math_random_float_range(D_L11_001B065C, D_L11_001B0660) * 0.020000001f;
        qcopy(point, pos);
        point[0] += math_random_signed_float_range(0.0f, 0.15f);
        point[1] += math_random_signed_float_range(0.0f, 0.15f);
        point[2] += math_random_signed_float_range(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            FastVecScale(velocity, velocity, 1.5f);
            particle = part_spawn_ground_effect(point, ((s32)(60) * 5 + 2) / 6, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, D_L11_001B0664 * 1.44f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(point, ((s32)(60) * 5 + 2) / 6, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, D_L11_001B0664 * 1.44f);
        } else {
            FastVecSub(extra, D_L11_001BA8C0, point);
            vec_scale_to_length((char *)extra, (char *)extra, speed);
            FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
            particle = part_spawn_ground_effect(point, ((s32)(40) * 5 + 2) / 6, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, D_L11_001B0664 * 1.44f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(point, ((s32)(40) * 5 + 2) / 6, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, D_L11_001B0664 * 1.44f);
        }
        if (particle)
            particle[9] = FloatToInt(4.0f) + 0x70;
    }
}
