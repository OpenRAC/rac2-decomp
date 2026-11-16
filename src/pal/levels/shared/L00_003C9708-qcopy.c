#include "include_asm.h"

#include "common.h"
extern float math_random_float_range(float min, float max);
extern int math_random_int_below(int count);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float min, float max);
extern void vec_build_spherical_offset(float *out, float a, float b, float c);
extern unsigned char *part_spawn_ground_effect(float life, void *position, int size, float secondLife, int color, int mode, int flag, float *vector, float third, int counter);
extern int FloatToInt(float value);

/* Spawns eight pairs of sparks that fly out of a position in random directions (PAL). */
void part_l00_spawn_spark_pairs_2_pal(void *position, int color)
{
    float vector[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float scale;
    float radius;
    float a;
    float b;
    int sign;
    unsigned char *particle;
    int i = 7;
    do {
        scale = math_random_float_range(1.0f, 6.0f);
        sign = math_random_int_below(2);
        if (sign == 0)
            sign--;
        radius = math_random_float_range(0.5f, 6.0f) * 0.020000001f;
        a = math_random_angle();
        b = math_random_angle();
        vec_build_spherical_offset(vector, radius, a, b);
        qcopy(offset, position);
        offset[0] += math_random_signed_float_range(0.0f, 0.1f);
        offset[1] += math_random_signed_float_range(0.0f, 0.1f);
        offset[2] += math_random_signed_float_range(0.0f, 0.1f);
        particle = part_spawn_ground_effect(scale * 0.1f, offset, 17, scale, color | 0x7F000000, 0, sign, vector, 0.0f, 1);
        if (particle)
            particle[9] = FloatToInt(4.0f) + 112;
        particle = part_spawn_ground_effect(scale * 0.04f, offset, 17, scale * 0.4f, 0x7F7F7F7F, 1, -sign, vector, 0.0f, 1);
        if (particle)
            particle[9] = FloatToInt(4.0f) + 112;
        i--;
    } while (i >= 0);
}
