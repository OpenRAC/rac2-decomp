#include "names.h"
/* func_PAL_L00_003A6238, the PAL copy of func_L00_003A2C60: the same C, where 60 frames become 50,
 * 1/60 becomes 0.020000001f and both particles scale brightness by 1.44f. */
#include "common.h"

/* The unsized macro-address view preserves the absolute flag load at -G8. */
extern float g_camera_l00_position[4];
extern float g_camera_position[4];
extern int g_hero_locked_flag[] MACRO_ADDR;
extern float g_spark_l00_speed_min __attribute__((sda));
extern float g_spark_l00_speed_max __attribute__((sda));
extern float g_spark_l00_up_speed_min __attribute__((sda));
extern float g_spark_l00_up_speed_max __attribute__((sda));
extern float g_spark_l00_size_min __attribute__((sda));
extern float g_spark_l00_size_max __attribute__((sda));
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
void func_PAL_L00_003A6238(void *position, int count, float brightness)
{
    float velocity[4], lateral[4], axis[4], projected[4];
    FastVecSub(lateral, g_camera_l00_position, position);
    if (g_hero_locked_flag[0] == 0) {
        lateral[2] = 0.0f;
        axis[0] = 0.0f;
        axis[1] = 0.0f;
        axis[3] = axis[2] = 1.0f;
    } else {
        FastVecSub(projected, position, g_camera_position);
        vec_scale_to_length(axis, projected, 1.0f);
        FastVecScale(projected, axis, FastVecDot(axis, lateral));
        FastVecSub(lateral, lateral, projected);
    }
    if (count > 0) {
        do {
            char *particle;
            float angle;
            float size = math_random_float_range(g_spark_l00_size_min, g_spark_l00_size_max);
            int spin = math_random_int_below(2);
            if (!spin)
                spin--;
            angle = math_random_float_range(-1.0471977f, 1.0471977f);
            math_apply_axis_rotation_to_quat(velocity, lateral, axis, angle);
            vec_scale_to_length(velocity, velocity, math_random_float_range(g_spark_l00_speed_min, g_spark_l00_speed_max) * 0.020000001f);
            velocity[2] = math_random_float_range(g_spark_l00_up_speed_min, g_spark_l00_up_speed_max) * 0.020000001f;
            vec_clear_128((VectorBits *)velocity);
            particle = part_spawn_ground_effect(position, 50, size * 0.1f, size,
                                     0x7F7F2020, 0, spin, velocity, brightness * 1.44f, 1);
            if (particle)
                *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(position, 50, size * 0.07f, size * 0.7f,
                                     0x7FFF4040, 1, -spin, velocity, brightness * 1.44f, 1);
            if (particle)
                *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 0x70;
        } while (--count);
    }
}
