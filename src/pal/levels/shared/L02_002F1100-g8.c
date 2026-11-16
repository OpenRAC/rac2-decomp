#include "names.h"
/* func_PAL_L02_002F1100, the PAL copy of func_L02_002EFB60: the same C, where the gravity factor 0.00027777778f
   becomes 0.00040000002f and the three colour arguments are scaled for 50 Hz. Needs -frac2-sticky-volatile-refs
   (reorg stops at the copy's volatile asm); see docs/build/compiler-notes.md. */
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

void func_PAL_L02_002F1100(void *owner, void *from, void *to, int count, int *colour, float speed) {
    Vec4 direction;
    Vec4 position;
    Vec4 velocity;
    float gravity = speed * 0.00040000002f;
    float brightness, t;
    int r, g, b, first, second, i;
    int *rgb = &g_spark_rgb;
    if (colour) rgb = colour;
    for (i = 0; i < count; i++) {
        brightness = math_random_float_range(0.7f, 1.3f);
        r = FloatToInt(((float)rgb[0] * brightness * 5.0f + 2.0f) * (1.0f / 6.0f));
        g = FloatToInt(((float)rgb[1] * brightness * 5.0f + 2.0f) * (1.0f / 6.0f));
        b = FloatToInt(((float)rgb[2] * brightness * 5.0f + 2.0f) * (1.0f / 6.0f));
        lerp_vector(&direction, from, to, math_random_float_range(0.0f, 1.0f));
        qcopy(&position, &direction);
        position.f[3] = math_random_float_range(g_spark_position_range[0], g_spark_position_range_max);
        vec_clear_128(&velocity);
        velocity.f[2] = -gravity * (float)(r + g + b);
        FastVecAdd(&velocity, &velocity, &direction);
        velocity.f[3] = position.f[3];
        t = math_random_float_range(0.0f, 1.0f);
        first = FastTweenColor(g_spark_first_color_a, g_spark_first_color_b, t);
        t = math_random_float_range(0.0f, 1.0f);
        second = FastTweenColor(g_spark_second_color_a, g_spark_second_color_b, t);
        part_spawn_trail(owner, &position, &velocity, first, second, r, g, b, g_spark_trail_param);
    }
}
