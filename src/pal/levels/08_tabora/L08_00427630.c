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

/* Sprays a ring of dust puffs around a point, flying outward and upward (PAL: 50 Hz timings). */
void part_spawn_dust_burst_pal(char *moby, void *position, int count,
                      float speed, float rise, float max_radius, float min_radius,
                      float size, float end_size)
{
    float offset[4], velocity[4], accel[4];
    int trail_a, trail_b, trail_c;
    char *particle;

    {
        int i;
        for (i = 0; i < count; i++) {
            float x, y;
            x = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
            offset[0] = x * math_random_float_range(min_radius, max_radius);
            y = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
            y *= math_random_float_range(min_radius, max_radius);
            offset[1] = y;
            offset[2] = 0;
            matrix_mul_vec3(offset, offset, moby + 0xC0);
            {
                float range = speed * ((max_radius - FastVecLength(offset)) * 0.020000001f) / max_radius;
                vec_scale_to_length(velocity, offset, math_random_float_range(range * 0.25f, range));
            }
            velocity[2] += math_random_float_range(rise * 0.25f, rise) * 0.020000001f;
            qzero_nc(accel);
            FastVecAdd(offset, offset, position);
            velocity[3] = size;
            accel[3] = end_size;
            trail_a = FloatToInt((math_random_float_range(15.0f, 25.0f) * 5.0f + 2.0f) * 0.16666667f);
            trail_b = FloatToInt((math_random_float_range(20.0f, 40.0f) * 5.0f + 2.0f) * 0.16666667f);
            trail_c = FloatToInt((math_random_float_range(30.0f, 60.0f) * 5.0f + 2.0f) * 0.16666667f);
            particle = part_spawn_trail(offset, velocity, accel, 0x50204050, 0x7F7F7F, trail_a, trail_b, trail_c, -1);
            if (particle && (func_001163B0() & 1))
                particle[3] = 0x48;
        }
    }
}
