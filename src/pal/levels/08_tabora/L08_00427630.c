#include "include_asm.h"
#include "names.h"

/* func_PAL_L08_00427630, the PAL copy of func_L08_00422190: the same C, where the per-frame 0.0166667f
   becomes 0.02f and the three particle timers are scaled to 50 Hz. */
#include "common.h"
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastVecLength(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
extern int func_001163B0(void);
extern char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

void func_PAL_L08_00427630(char *m, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4];
    int a, b, c;
    char *particle;

    {
        int i;
        for (i = 0; i < count; i++) {
            float x, y;
            x = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
            offset[0] = x * math_random_float_range(minRadius, maxRadius);
            y = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
            y *= math_random_float_range(minRadius, maxRadius);
            offset[1] = y;
            offset[2] = 0;
            matrix_mul_vec3(offset, offset, m + 0xC0);
            {
                float range = speed * ((maxRadius - FastVecLength(offset)) * 0.020000001f) / maxRadius;
                vec_scale_to_length(velocity, offset, math_random_float_range(range * 0.25f, range));
            }
            velocity[2] += math_random_float_range(rise * 0.25f, rise) * 0.020000001f;
            qzero_nc(accel);
            FastVecAdd(offset, offset, position);
            velocity[3] = size;
            accel[3] = endSize;
            a = FloatToInt((math_random_float_range(15.0f, 25.0f) * 5.0f + 2.0f) * 0.16666667f);
            b = FloatToInt((math_random_float_range(20.0f, 40.0f) * 5.0f + 2.0f) * 0.16666667f);
            c = FloatToInt((math_random_float_range(30.0f, 60.0f) * 5.0f + 2.0f) * 0.16666667f);
            particle = part_spawn_trail(offset, velocity, accel, 0x50204050, 0x7F7F7F, a, b, c, -1);
            if (particle && (func_001163B0() & 1))
                particle[3] = 0x48;
        }
    }
}
