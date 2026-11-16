#include "common.h"

/* func_PAL_L07_003F85AC, the PAL copy of func_L07_003F3E80: the same C, where the step scale
   0.0166667f becomes 0.020000001f, 0.00029088825f becomes 0.0003490659f, the 301 frame limit
   becomes 251, `size` takes the 50 Hz scale and the particle call is func_PAL_002C23B8.
   Like the template it needs -frac2-hazard-labels with -G8: retail keeps the case-1 join label
   on the mtc1 -> mul.s hazard nop. */
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern void vec_copy_helper_a(void *), FastVecCross(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *), vec_set_direction_with_complement(void *, void *, f32);
extern void quaternion_to_rotation_basis(void *, void *), multiply_matrix3x3(void *, void *, void *);
extern f32 FastVecLength(void *), math_random_signed_float_range(f32, f32), math_random_float_range(f32, f32);
extern s32 math_random_int_range(s32, s32), FloatToInt(f32), CollLine(void *, void *, s32, void *, void *);
extern f32 ApproachValue(f32 *, f32, f32);
extern void vec_scale_to_length(void *, void *, f32), lerp_vector(void *, void *, void *, f32);
extern void *part_spawn_burst_pal(void *, void *, s32, s32, s32, s32, f32, f32, f32, f32, f32);
extern void moby_set_state(void *, s32, s32), moby_mark_spawned(int);
extern s32 flag_set_first_pending(void *), moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern int snd_play_from_class_bank(s32, s32, void *, s32);
extern s32 math_random_int_below(s32);
extern void UpdateCollisionRing_pal(u8 *);
extern void gfx_add_draw_callback_first(void (*)(u8 *), u8 *);
extern u8 g_hit_position[];
extern f32 g_trail_axis_turn_rate __attribute__((sda)), g_trail_growth_rate __attribute__((sda));
extern f32 g_trail_growth_limit __attribute__((sda)), g_trail_fade_rate __attribute__((sda));
extern f32 g_trail_jitter_step __attribute__((sda));
extern s32 g_trail_particle_count __attribute__((sda));
extern u32 g_trail_particle_color __attribute__((sda));
extern s32 g_trail_size_range[] MACRO_ADDR;
extern s32 D_L07_001B0E70_gp SDATA(D_L07_001B0E70);
extern f32 g_trail_life_range[] MACRO_ADDR;
extern f32 D_L07_001B0E78_gp SDATA(D_L07_001B0E78);

/* The state block at object + 0x68; only the fields this function touches are named. */
typedef struct {
    f32 position[4];
    f32 direction[4];
    u8 *attachment;
    f32 growth, strength, phase, phase_step;
} SiberiusTrailState;

/* Updates a spark trail shot: it flies along its direction under gravity leaving particles, and on
   hitting something it turns into a growing, fading burst that is then removed (PAL: 50 Hz timings). */
void spark_trail_shot_update_pal(u8 *moby)
{
    Vector axis, up, direction;
    f32 rotation[12];
    Vector previous_position, displacement, origin, point, velocity, speed;
    f32 magnitude, life, step;
    SiberiusTrailState *trail = *(SiberiusTrailState **)(moby + 0x68);
    s32 i, size, count;
    u32 color;
    switch (moby[0x20]) {
    case 0:
        vec_copy_helper_a(&up);
        if (trail->attachment) matrix_mul_vec3(&direction, trail->direction, trail->attachment + 0xC0);
        else qcopy(&direction, trail->direction);
        FastVecCross(&axis, &up, &direction);
        vec_set_direction_with_complement(&axis, &axis, g_trail_axis_turn_rate * 0.0003490659f);
        quaternion_to_rotation_basis(&axis, rotation);
        multiply_matrix3x3(moby + 0xC0, rotation, moby + 0xC0);
        qcopy(&previous_position, moby + 0x10);
        trail->direction[2] -= trail->direction[3];
        if (trail->attachment) {
            FastVecAdd(trail->position, trail->position, trail->direction);
            matrix_mul_vec3(moby + 0x10, trail->position, trail->attachment + 0xC0);
            FastVecAdd(moby + 0x10, moby + 0x10, trail->attachment + 0x10);
            matrix_mul_vec3(&displacement, trail->direction, trail->attachment + 0xC0);
            FastVecSub(&origin, moby + 0x10, &displacement);
        } else {
            FastVecAdd(moby + 0x10, moby + 0x10, trail->direction);
            qcopy(&displacement, trail->direction);
            qcopy(&origin, &previous_position);
        }
        magnitude = FastVecLength(&displacement);
        for (i = 0; i < g_trail_particle_count; i++) {
            size = (math_random_int_range(D_L07_001B0E70_gp, g_trail_size_range[1]) * 5 + 2) / 6;
            count = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
            life = math_random_float_range(D_L07_001B0E78_gp, g_trail_life_range[1]) * 210000.0f;
            speed.f[0] = magnitude;
            ApproachValue(speed.f, 0.0f, math_random_float_range(2.0f, 6.0f) * 0.020000001f);
            vec_scale_to_length(&velocity, &displacement, speed.f[0]);
            lerp_vector(&point, moby + 0x10, &origin, math_random_float_range(0.0f, 1.0f));
            color = g_trail_particle_color;
            part_spawn_burst_pal(&point, &velocity, size, (s32)color >> 24, color & 0xFFFFFF, count,
                         life, 500.0f, 1.0f, 0.0f, 1.0f);
        }
        if (CollLine(&previous_position, moby + 0x10, 2, moby, 0)) {
            qcopy(moby + 0x10, g_hit_position);
            moby_set_state(moby, 1, -1);
        } else {
            unsigned int timer = *(u16 *)(moby + 0x96);
            unsigned int old = timer++;
            *(u16 *)(moby + 0x96) = timer;
            if (old >= 251) moby_mark_spawned((int)moby);
        }
        break;
    case 1:
        if (flag_set_first_pending(moby)) {
            snd_play_from_class_bank(4, 0, moby, 0xE5F);
            *(u32 *)(moby + 0x98) = 0;
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
            *(f32 *)(moby + 0x18) += 0.333f;
            trail->growth = 0.1f;
            trail->strength = 1.0f;
            if (math_random_int_below(2)) step = -g_trail_jitter_step * 0.020000001f;
            else step = g_trail_jitter_step * 0.020000001f;
            trail->phase_step = step;
            trail->phase = math_random_float_range(0.0f, 1.0f);
        }
        if (trail->attachment)
            moby_transform_point_and_rotation_by_parent(moby, trail->attachment, moby + 0x10, moby + 0xF0, moby + 0x10, moby + 0xF0);
        trail->growth += g_trail_growth_rate * 0.020000001f;
        if (trail->growth >= g_trail_growth_limit) {
            ApproachValue(&trail->strength, 0.0f, g_trail_fade_rate * 0.020000001f);
            if (trail->strength <= 0.0f) { moby_mark_spawned((int)moby); return; }
        }
        trail->phase += trail->phase_step;
        if (trail->phase > 1.0f) trail->phase -= 1.0f;
        else if (trail->phase < 0.0f) trail->phase += 1.0f;
        gfx_add_draw_callback_first(UpdateCollisionRing_pal, moby);
        break;
    }
}
