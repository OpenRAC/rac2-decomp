#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef signed int s32;
typedef float f32;
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
extern s32 func_00337AD8(s32, s32, f32);
extern s32 coll_cast_object_line(void *, void *, void *, s32, f32, f32, s32, s32, s32);
extern f32 g_fade_burst_intensity_start __attribute__((sda));
extern f32 g_fade_burst_intensity_end[] __attribute__((sda));
extern s32 g_fade_burst_particle_scale __attribute__((sda));
extern f32 g_fade_burst_flare_size __attribute__((sda));
extern f32 math_lerp_float(f32, f32, f32);
extern s32 FloatToInt(f32);
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

/* Gives each of the two ribbon emitters random directions and a random start offset around the object (PAL). */
void ribbon_init_emitters_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    L18_EDE8f32 offset[4] __attribute__((aligned(16)));
    s32 i;

    for (i = 0; i < 2; i++) {
        u8 *emitter = vars + i * 0xA0;

        vec_random_direction(emitter + 0x60, g_ribbon_emitter_angle_a_deg * 0.0003490659f, g_ribbon_emitter_angle_b_deg * 0.0003490659f);
        vec_random_direction(emitter + 0x70, g_ribbon_emitter_angle_a_deg * 0.0003490659f, g_ribbon_emitter_angle_b_deg * 0.0003490659f);
        vec_random_direction(emitter + 0x80, g_ribbon_emitter_spread_a, g_ribbon_emitter_spread_b);
        vec_random_direction(emitter + 0x90, g_ribbon_emitter_spread_a, g_ribbon_emitter_spread_b);
        qcopy(vars, vars + 0x140);
        qcopy(vars + 0xA0, vars + 0x140);
        matrix_mul_vec3(offset, g_emitter_offset_vectors + math_random_int_below(6) * 16, moby + 0xC0);
        FastVecAdd(offset, moby + 0x10, offset);
        qcopy(vars + 0x10, offset);
    }
}
