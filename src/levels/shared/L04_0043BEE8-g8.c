#include "common.h"
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern float math_random_float_range(float, float);
extern unsigned int FastTweenColor(int, float, int);
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(void *, int, unsigned int, int, float, float, float);
extern int g_spark_glow_color_a_start __attribute__((sda));
extern int g_spark_glow_color_a_end[] NOT_SDA;
extern int g_spark_glow_color_b_start[] NOT_SDA;
extern int g_spark_glow_color_b_end[] NOT_SDA;
extern int g_spark_glow_color_c_start[] NOT_SDA;
extern int g_spark_glow_color_c_end[] NOT_SDA;
extern int g_spark_glow_color_d_start[] NOT_SDA;
extern int g_spark_glow_color_d_end[] NOT_SDA;

/* Draws four coloured glow sprites at the current point along the curved path of the spark burst. */
void spark_burst_draw_glows(char *object)
{
    float a[4], b[4], position[4];
    char *state = *(char **)(object + 0x68);
    float factor = math_fast_sin_or_cos_b(*(float *)(state + 0x4c) * 3.1415927f);
    unsigned int color;
    float angle, fraction;
    FastVecAdd(a, state, state + 0x10);
    lerp_vector(a, state, a, factor);
    FastVecAdd(b, state + 0x20, state + 0x30);
    lerp_vector(b, state + 0x20, b, factor);
    lerp_vector(position, a, b, *(float *)(state + 0x4c));
    fraction = math_random_float_range(0.0f, 1.0f);
    color = FastTweenColor(g_spark_glow_color_a_start, fraction, g_spark_glow_color_a_end[0]);
    angle = math_random_angle();
    gfx_draw_billboard_quad(position, 0x31, color, 1, 1.0f, 0.0f, angle);
    fraction = math_random_float_range(0.0f, 1.0f);
    color = FastTweenColor(g_spark_glow_color_b_start[0], fraction, g_spark_glow_color_b_end[0]);
    angle = math_random_angle();
    gfx_draw_billboard_quad(position, 0x31, color, 1, 0.6f, 0.0f, angle);
    fraction = math_random_float_range(0.0f, 1.0f);
    color = FastTweenColor(g_spark_glow_color_c_start[0], fraction, g_spark_glow_color_c_end[0]);
    angle = math_random_angle();
    gfx_draw_billboard_quad(position, 0xb, color, 1, 1.4f, 0.0f, angle);
    fraction = math_random_float_range(0.0f, 1.0f);
    color = FastTweenColor(g_spark_glow_color_d_start[0], fraction, g_spark_glow_color_d_end[0]);
    angle = math_random_angle();
    gfx_draw_billboard_quad(position, 0xb, color, 1, 0.9f, 0.0f, angle);
}
