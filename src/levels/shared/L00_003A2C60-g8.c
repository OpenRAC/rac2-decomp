#include "common.h"

/* The unsized macro-address view preserves the absolute flag load at -G8. */
extern float g_camera_l00_position[4];
extern float D_00189ED0[4];
extern int D_L00_001A8FF0[] MACRO_ADDR;
extern float D_L00_001AF5F8 __attribute__((sda));
extern float D_L00_001AF5FC __attribute__((sda));
extern float D_L00_001AF600 __attribute__((sda));
extern float D_L00_001AF604 __attribute__((sda));
extern float D_L00_001AF60C __attribute__((sda));
extern float D_L00_001AF610 __attribute__((sda));
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
typedef int VectorBits __attribute__((mode(TI)));
extern void vec_clear_128(VectorBits *);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, float, int);
extern int FloatToInt(float);

/* Spray paired particles perpendicular to the viewing direction. */
void part_l00_spawn_spark_spray(void *position, int count, float brightness)
{
    float velocity[4], lateral[4], axis[4], projected[4];
    FastVecSub(lateral, g_camera_l00_position, position);
    if (D_L00_001A8FF0[0] == 0) {
        lateral[2] = 0.0f;
        axis[0] = 0.0f;
        axis[1] = 0.0f;
        axis[3] = axis[2] = 1.0f;
    } else {
        FastVecSub(projected, position, D_00189ED0);
        vec_scale_to_length(axis, projected, 1.0f);
        FastVecScale(projected, axis, FastVecDot(axis, lateral));
        FastVecSub(lateral, lateral, projected);
    }
    if (count > 0) {
        do {
            char *particle;
            float angle;
            float size = math_random_float_range(D_L00_001AF60C, D_L00_001AF610);
            int spin = math_random_int_below(2);
            if (!spin)
                spin--;
            angle = math_random_float_range(-1.0471977f, 1.0471977f);
            math_apply_axis_rotation_to_quat(velocity, lateral, axis, angle);
            vec_scale_to_length(velocity, velocity, math_random_float_range(D_L00_001AF5F8, D_L00_001AF5FC) * (1.0f / 60.0f));
            velocity[2] = math_random_float_range(D_L00_001AF600, D_L00_001AF604) * (1.0f / 60.0f);
            vec_clear_128((VectorBits *)velocity);
            particle = part_spawn_ground_effect(position, 60, size * 0.1f, size,
                                     0x7F7F2020, 0, spin, velocity, brightness, 1);
            if (particle)
                *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(position, 60, size * 0.07f, size * 0.7f,
                                     0x7FFF4040, 1, -spin, velocity, brightness, 1);
            if (particle)
                *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 0x70;
        } while (--count);
    }
}
