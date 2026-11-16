#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef unsigned short u16;

typedef signed short s16;

typedef signed int s32;

typedef float f32;

/* Small-data controls this level reads through $gp in ordinary flow. */
extern s32 g_enemy_timer_threshold __attribute__((sda));

extern s32 g_enemy_timer_min __attribute__((sda));

extern s32 g_enemy_timer_max __attribute__((sda));

extern f32 g_enemy_smooth_time __attribute__((sda));

extern f32 g_shot_hit_height __attribute__((sda));

extern f32 g_probe_threshold __attribute__((sda));

extern f32 g_probe_height_range __attribute__((sda));

extern f32 g_probe_height_min __attribute__((sda));

extern f32 g_probe_height_base __attribute__((sda));

extern s32 math_random_int_range(s32, s32);

extern int FastDecTimer(void *);

extern int math_fast_float_d(s32);

extern void value_set_and_smooth(void *, void *, s32, s32, f32);

extern void moby_transform_joint_to_world(void *, s32, void *);

extern s32 func_00337AD8(s32, s32, f32);

extern void gfx_l00_draw_billboard_quad(void *, s32, f32, f32);

/* Renews the state's 0x39A banner: resamples the 0x390 countdown, refreshes the two
   clearings and bumps the object's own 0x96 counter before the shared follow-up. */
/* Asks the shared vertex probe for the object's 0x78 mask and places the resulting
   height with the state's own 0x158 rise. */
void probe_place_at_height(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    if (g_probe_threshold < *(f32 *)(state + 0x15C)) {
        s32 probe = func_00337AD8(*(s32 *)(obj + 0x78) & 0xFFFFFF, *(s32 *)(obj + 0x78),
                                  *(f32 *)(state + 0x15C));
        gfx_l00_draw_billboard_quad(obj + 0x10, probe,
                          g_probe_height_min + g_probe_height_range * *(f32 *)(state + 0x158),
                          g_probe_height_base);
    }
}

/* hands the two sampled buffers and the measured flag pair to the shared placement. */
extern s32 coll_cast_object_line(void *, void *, void *, s32, f32, f32, s32, s32, s32);

/* The state's banner timer: the shared helper refits the object's height against the
   state's own rise, and the two ends of the countdown are eased into the frame rate. */
extern f32 g_fade_burst_intensity_start __attribute__((sda));

extern f32 g_fade_burst_intensity_end[] __attribute__((sda));

extern s32 g_fade_burst_particle_scale __attribute__((sda));

extern f32 g_fade_burst_flare_size __attribute__((sda));

extern void gfx_set_gs_register_constant(void);

extern f32 math_lerp_float(f32, f32, f32);

extern s32 FloatToInt(f32);

extern void gfx_draw_lens_flare_quad(void *, void *, s32, s32, f32, f32, f32);

/* Emits a burst of effect particles whose number and size depend on the fade level at +0x158. */
void part_emit_fade_burst(u8 *obj) {
    u8 *state;
    f32 intensity;
    s32 particleCount;

    gfx_set_gs_register_constant();
    state = *(u8 **)(obj + 0x68);
    intensity = math_lerp_float(g_fade_burst_intensity_start, g_fade_burst_intensity_end[0], *(f32 *)(state + 0x158));
    if (*(f32 *)(state + 0x158) < 0.1f) {
        particleCount = FloatToInt((f32)g_fade_burst_particle_scale * *(f32 *)(state + 0x158) * 10.0f);
    } else {
        particleCount = FloatToInt((f32)g_fade_burst_particle_scale * (1.0f - *(f32 *)(state + 0x158)));
    }
    gfx_draw_lens_flare_quad(obj + 0x10, obj + 0xC0, particleCount, 0, intensity, g_fade_burst_flare_size, 0.08f);
}

extern int g_ribbon_l18_point_count __attribute__((sda));
extern float g_ribbon_step __attribute__((sda));
extern float g_ribbon_first_width_min __attribute__((sda));
extern float g_ribbon_first_width_max __attribute__((sda));
extern float g_ribbon_second_width_min __attribute__((sda));
extern float g_ribbon_second_width_max __attribute__((sda));
extern int g_ribbon_l18_color_a __attribute__((sda));
extern int g_ribbon_l18_color_b __attribute__((sda));
extern float g_ribbon_small_flare_size __attribute__((sda));
extern int g_ribbon_large_sprite_id __attribute__((sda));
extern int g_ribbon_small_sprite_id __attribute__((sda));
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern void part_build_jittered_curve(void *, int, void *, float);
extern void ribbon_draw_along_points(void *, int, int, int, int, float, float);
extern void part_draw_billboard_sprite(void *, int, float, int, float, int, int);

/* Builds and draws the state's two ribbons (control points at +0 and +0xA0, faded by the
   0x158 level), then emits the paired particle bursts at +0, +0x10, +0xA0 and +0xB0. The
   point buffer is sized by the level's count control. */
void ribbon_draw_with_bursts(char *object)
{
    char *state = *(char **)(object + 0x68);
    int count = g_ribbon_l18_point_count;
    typedef struct { float values[4]; } Point __attribute__((aligned(16)));
    Point points[count];
    float step = g_ribbon_step;
    int life;
    float first, second, large, small;

    life = math_random_int_range(48, 128);
    first = (1.0f - *(float *)(state + 0x158)) * math_random_float_range(g_ribbon_first_width_min, g_ribbon_first_width_max);
    second = (1.0f - *(float *)(state + 0x158)) * math_random_float_range(g_ribbon_second_width_min, g_ribbon_second_width_max);
    part_build_jittered_curve(points, count, state, step);
    ribbon_draw_along_points(points, count, life, g_ribbon_l18_color_a, g_ribbon_l18_color_b, first, second);
    life = math_random_int_range(48, 128);
    first = (1.0f - *(float *)(state + 0x158)) * math_random_float_range(g_ribbon_first_width_min, g_ribbon_first_width_max);
    second = (1.0f - *(float *)(state + 0x158)) * math_random_float_range(g_ribbon_second_width_min, g_ribbon_second_width_max);
    part_build_jittered_curve(points, count, state + 0xA0, step);
    ribbon_draw_along_points(points, count, life, g_ribbon_l18_color_a, g_ribbon_l18_color_b, first, second);
    small = g_ribbon_small_flare_size * (1.0f - *(float *)(state + 0x158));
    large = small * 0.5f;
    part_draw_billboard_sprite(state, g_ribbon_large_sprite_id, large, math_random_int_range(80, 96), math_random_angle(), 49, 2);
    small *= 0.7f;
    part_draw_billboard_sprite(state, g_ribbon_small_sprite_id, small, math_random_int_range(8, 22), math_random_angle(), 11, 2);
    part_draw_billboard_sprite(state + 0x10, g_ribbon_large_sprite_id, large, math_random_int_range(80, 96), math_random_angle(), 49, 2);
    part_draw_billboard_sprite(state + 0x10, g_ribbon_small_sprite_id, small, math_random_int_range(8, 22), math_random_angle(), 11, 2);
    part_draw_billboard_sprite(state + 0xA0, g_ribbon_large_sprite_id, large, math_random_int_range(80, 96), math_random_angle(), 49, 2);
    part_draw_billboard_sprite(state + 0xA0, g_ribbon_small_sprite_id, small, math_random_int_range(8, 22), math_random_angle(), 11, 2);
    part_draw_billboard_sprite(state + 0xB0, g_ribbon_large_sprite_id, large, math_random_int_range(80, 96), math_random_angle(), 49, 2);
    part_draw_billboard_sprite(state + 0xB0, g_ribbon_small_sprite_id, small, math_random_int_range(8, 22), math_random_angle(), 11, 2);
}

typedef float L18_EDE8f32;

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

extern void vec_random_direction(void *, L18_EDE8f32, L18_EDE8f32);
extern int math_random_int_below(int);
extern void matrix_mul_vec3(void *, const void *, const void *);
extern void FastVecAdd(void *, void *, void *);
extern unsigned char g_emitter_offset_vectors[];
extern L18_EDE8f32 g_ribbon_emitter_angle_a_deg __attribute__((sda));
extern L18_EDE8f32 g_ribbon_emitter_angle_b_deg __attribute__((sda));
extern L18_EDE8f32 g_ribbon_emitter_spread_a __attribute__((sda));
extern L18_EDE8f32 g_ribbon_emitter_spread_b __attribute__((sda));

/* Sets up the two ribbon emitters with random settings and a random starting point near the object. */
void ribbon_init_emitters(u8 *obj)
{
    u8 *state = *(u8 **)(obj + 0x68);
    L18_EDE8f32 point[4] __attribute__((aligned(16)));
    s32 i;

    for (i = 0; i < 2; i++) {
        u8 *emitter = state + i * 0xA0;

        vec_random_direction(emitter + 0x60, g_ribbon_emitter_angle_a_deg * 0.00029088824f, g_ribbon_emitter_angle_b_deg * 0.00029088824f);
        vec_random_direction(emitter + 0x70, g_ribbon_emitter_angle_a_deg * 0.00029088824f, g_ribbon_emitter_angle_b_deg * 0.00029088824f);
        vec_random_direction(emitter + 0x80, g_ribbon_emitter_spread_a, g_ribbon_emitter_spread_b);
        vec_random_direction(emitter + 0x90, g_ribbon_emitter_spread_a, g_ribbon_emitter_spread_b);
        qcopy(state, state + 0x140);
        qcopy(state + 0xA0, state + 0x140);
        matrix_mul_vec3(point, g_emitter_offset_vectors + math_random_int_below(6) * 16, obj + 0xC0);
        FastVecAdd(point, obj + 0x10, point);
        qcopy(state + 0x10, point);
    }
}
