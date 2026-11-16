#include "include_asm.h"
#include "names.h"

/* func_PAL_L02_00433B90, the PAL copy of func_L02_0042E680: the same C, where each count runs through
   the 50 Hz scale (x * 5 + 2) / 6 and gravity becomes 0.0036000002f. A unit of its own for the template's
   opt-in quadword-copy profile and scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier,
   config/cflags.txt). */

typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));

extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern int FastTweenColor(int, int, float);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern void vec_add_random_offset(void *, float);
extern int g_spark_fan_colors_a[2] __attribute__((sda));
extern int g_spark_fan_colors_b[2] __attribute__((sda));

/* Throws a fan of thirty sparks from above the moby. (PAL: frame counts scaled to 50 Hz) */
void part_throw_spark_fan_pal(u8 *moby, float speed_min, float speed_max) {
    float offset[4];
    float origin[4];
    float up[4];
    float side[4];
    float velocity[4];
    float accel[4];
    float start[4];
    int i;
    float scale;
    int life_a, life_b, life_c;
    int color_a, color_b;
    float gravity = 0.0036000002f;

    offset[0] = 0.0f;
    offset[1] = 0.0f;
    offset[2] = 4.0f;
    offset[3] = 1.0f;
    FastVecAdd(origin, offset, moby + 0x10);
    i = 29;
    do {
        vec_scale_to_length(side, moby + 0xC0, math_random_float_range(-0.8f, 0.8f));
        vec_scale_to_length(up, moby + 0xE0, math_random_float_range(0.25f, 1.0f));
        FastVecAdd(velocity, moby + 0xD0, side);
        FastVecAdd(velocity, velocity, up);
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
        color_a = FastTweenColor(g_spark_fan_colors_a[0], g_spark_fan_colors_a[1], math_random_float_range(0.0f, 1.0f));
        color_b = FastTweenColor(g_spark_fan_colors_b[0], g_spark_fan_colors_b[1], math_random_float_range(0.0f, 1.0f));
        *(TI128 *)start = *(TI128 *)origin;
        vec_add_random_offset(start, 0.25f);
        part_spawn_trail(start, velocity, accel, color_a, color_b, life_a, life_b, life_c, 0x1003C);
    } while (--i >= 0);
}
