#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern int FloatToInt(float);
extern int FastTweenColor(int, int, float);
extern float math_random_float_range(float, float);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern int g_spark_burst_colors_a[2] __attribute__((sda));
extern int g_spark_burst_colors_b[2] __attribute__((sda));

/* func_PAL_L02_004288E8, the PAL copy of func_L02_00423838: the same C, where the three frame counts are
   scaled to 50 Hz and the downward pull per frame becomes 0.002f. */
/* Throws a burst of twenty sparks from the back of the moby. (PAL: frame counts scaled to 50 Hz) */
void part_throw_spark_burst_pal(u8 *moby, float speed_min, float speed_max) {
    float offset[4];
    float origin[4];
    float side[4];
    float up[4];
    float velocity[4];
    float accel[4];
    int i;
    float scale;
    int life_a, life_b, life_c;
    int color_a, color_b;
    float gravity = 0.002f;

    FastVecScale(offset, moby + 0xE0, 1.75f);
    FastVecAdd(origin, offset, moby + 0x10);
    FastVecScale(offset, moby + 0xC0, -0.5f);
    FastVecAdd(origin, offset, origin);
    i = 19;
    do {
        vec_scale_to_length(up, moby + 0xD0, math_random_float_range(-1.0f, 1.0f));
        vec_scale_to_length(side, moby + 0xE0, math_random_float_range(-0.15f, 1.0f));
        FastVecAdd(velocity, moby + 0xC0, up);
        FastVecAdd(velocity, velocity, side);
        vec_scale_to_length(velocity, velocity, math_random_float_range(speed_min, speed_max));
        scale = math_random_float_range(0.5f, 1.5f);
        life_a = FloatToInt((scale * 50.0f + 2.0f) * 0.16666667f);
        life_b = FloatToInt((scale * 150.0f + 2.0f) * 0.16666667f);
        life_c = FloatToInt((scale * 35.0f + 2.0f) * 0.16666667f);
        velocity[3] = math_random_float_range(0.2f, 0.6f);
        vec_clear_128(accel);
        accel[2] = -gravity * (float)(life_a + life_b + life_c);
        FastVecAdd(accel, accel, velocity);
        accel[3] = 0.01f;
        color_a = FastTweenColor(g_spark_burst_colors_a[0], g_spark_burst_colors_a[1], math_random_float_range(0.0f, 1.0f));
        color_b = FastTweenColor(g_spark_burst_colors_b[0], g_spark_burst_colors_b[1], math_random_float_range(0.0f, 1.0f));
        part_spawn_trail(origin, velocity, accel, color_a, color_b, life_a, life_b, life_c, 0x1003C);
    } while (--i >= 0);
}
