#include "include_asm.h"
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern s32 g_glow_strip_point_count __attribute__((sda));
extern f32 g_glow_strip_jitter __attribute__((sda));
extern f32 g_glow_strip_direction_min __attribute__((sda));
extern f32 g_glow_strip_direction_max __attribute__((sda));
extern f32 g_glow_strip_width_min __attribute__((sda));
extern f32 g_glow_strip_width_max __attribute__((sda));
extern f32 g_glow_strip_height_min __attribute__((sda));
extern f32 g_glow_strip_height_max __attribute__((sda));
extern f32 g_glow_strip_offset_scale __attribute__((sda));
extern s32 g_glow_strip_color_inner __attribute__((sda));
extern s32 g_glow_strip_color_outer __attribute__((sda));
extern void vec_add_random_offset(f32 *, f32);
extern void vec_random_direction(float *, float, float);
extern s32 math_random_int_range(s32, s32);
extern f32 math_random_float_range(f32, f32);
extern void curve_build_jittered_points(void *, s32, void *, f32);
extern void ribbon_draw_two_layer(void *, s32, s32, s32, s32, f32, f32);

/* Builds a randomized strip from two control points and two random tangents. */
/* Draws a randomly shaped glowing strip starting at the object effect point. */
void gfx_draw_random_glow_strip(char *self) {
    f32 control[10][4]; /* ten strip slots; only the first four control points are set here */
    s32 count = g_glow_strip_point_count;
    Quad points[count];
    char *state = *(char **)(self + 0x68);
    s32 texture;
    f32 width, height;
    qcopy(control[0], (state + 0x90));
    qcopy(control[1], (state + 0x90));
    vec_add_random_offset(control[1], g_glow_strip_offset_scale * *(f32 *)(state + 0xC0));
    vec_random_direction(control[2], g_glow_strip_direction_min, g_glow_strip_direction_max);
    vec_random_direction(control[3], g_glow_strip_direction_min, g_glow_strip_direction_max);
    texture = math_random_int_range(16, 64);
    width = math_random_float_range(g_glow_strip_width_min, g_glow_strip_width_max);
    height = math_random_float_range(g_glow_strip_height_min, g_glow_strip_height_max);
    curve_build_jittered_points(points, g_glow_strip_point_count, control, g_glow_strip_jitter);
    ribbon_draw_two_layer(points, g_glow_strip_point_count, texture, g_glow_strip_color_inner, g_glow_strip_color_outer, width, height);
}
