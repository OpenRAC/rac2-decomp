#include "names.h"
/* func_L02_002EFB60: needs -frac2-sticky-volatile-refs (reorg stops at the copy's volatile asm); see docs/build/compiler-notes.md. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vec4;
extern int g_spark_rgb __attribute__((sda));
extern float g_spark_position_range[] SDATA(D_L02_001A8D78) __attribute__((nosda));
extern int g_spark_first_color_a __attribute__((sda));
extern int g_spark_trail_param __attribute__((sda));
extern float g_spark_position_range_max __attribute__((nosda));
extern int g_spark_first_color_b __attribute__((nosda));
extern int g_spark_second_color_a __attribute__((nosda));
extern int g_spark_second_color_b __attribute__((nosda));
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern void lerp_vector(void *, void *, void *, float);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern int FastTweenColor(int, int, float);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

/* Throws a burst of colored sparks along a line between two points. Each spark gets a random brightness, position on the line and speed. */
void part_spawn_spark_burst_line(void *owner, void *from, void *to, int count, int *colour, float speed) {
    Vec4 direction;
    Vec4 position;
    Vec4 velocity;
    float gravity = speed * 0.00027777778f;
    float brightness, blend;
    int red, green, blue, first_sprite, second_sprite, i;
    int *rgb = &g_spark_rgb;
    if (colour) rgb = colour;
    for (i = 0; i < count; i++) {
        brightness = math_random_float_range(0.7f, 1.3f);
        red = FloatToInt((float)rgb[0] * brightness);
        green = FloatToInt((float)rgb[1] * brightness);
        blue = FloatToInt((float)rgb[2] * brightness);
        lerp_vector(&direction, from, to, math_random_float_range(0.0f, 1.0f));
        qcopy(&position, &direction);
        position.f[3] = math_random_float_range(g_spark_position_range[0], g_spark_position_range_max);
        vec_clear_128(&velocity);
        velocity.f[2] = -gravity * (float)(red + green + blue);
        FastVecAdd(&velocity, &velocity, &direction);
        velocity.f[3] = position.f[3];
        blend = math_random_float_range(0.0f, 1.0f);
        first_sprite = FastTweenColor(g_spark_first_color_a, g_spark_first_color_b, blend);
        blend = math_random_float_range(0.0f, 1.0f);
        second_sprite = FastTweenColor(g_spark_second_color_a, g_spark_second_color_b, blend);
        part_spawn_trail(owner, &position, &velocity, first_sprite, second_sprite, red, green, blue, g_spark_trail_param);
    }
}
