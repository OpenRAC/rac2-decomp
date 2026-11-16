#include "include_asm.h"




#include "common.h"
typedef struct { f32 f[4]; } __attribute__((aligned(16))) V4;
typedef struct { s32 f00; u8 p04[8]; s32 f0C; V4 v10; } N;
typedef struct { u8 p00[0x10]; V4 v10; u8 p20[0x48]; N *f68; u8 p6C[0x54]; V4 vC0; } X;
typedef struct { u8 p0[0x150]; V4 v150; u8 p160[0x2294-0x160]; s32 i2294; } TrailHero;
extern TrailHero g_hero_state;
extern s32 g_game_time __attribute__((sda));
extern f32 math_random_angle(void), math_fast_sin_or_cos_a(f32), math_fast_sin_or_cos_b(f32);
extern f32 math_random_float_range(f32, f32);
extern void matrix_mul_vec3(V4 *, V4 *, V4 *);
extern void FastVecAdd(V4 *, V4 *, V4 *);
extern void FastVecSub(V4 *, V4 *, V4 *);
extern void vec_scale_to_length(V4 *, V4 *, f32);
extern f32 fast_vec_dist(V4 *, V4 *);
extern s32 math_random_int_below(s32);
extern u8 *part_spawn_trailing_spark(V4 *, V4 *, s32, s32, s32, s32, f32);
extern u8 *part_spawn_spinning_spark_pal(V4 *, f32, f32, f32, f32, s32, V4 *, u32, s32);

/* Adapted from RAC1 emit_beam_trail_particles (OpenRAC, GPL-3.0). */
void beam_spawn_trail_particles_pal(X *beam) {
    V4 spark_vel;
    V4 origin;
    V4 delta;
    V4 step_pos;
    N *trail;
    f32 step_len;
    f32 size_scale;
    u32 tint;
    s32 i;
    s32 step_count;
    s32 move_state;
    u8 *spark;

    trail = beam->f68;
    spark_vel.f[0] = math_fast_sin_or_cos_a(math_random_angle()) * 0.05f;
    spark_vel.f[1] = math_fast_sin_or_cos_b(math_random_angle()) * 0.05f;
    spark_vel.f[2] = 0.0f;
    spark_vel.f[2] = -math_random_float_range(0.01f, 0.03f);
    matrix_mul_vec3(&spark_vel, &spark_vel, &beam->vC0);
    FastVecAdd(&spark_vel, &spark_vel, &g_hero_state.v150);
    qcopy(&origin, &beam->v10);
    if (g_hero_state.i2294 == 0x7B) {
        if (g_game_time % 3 == 0) {
            part_spawn_trailing_spark(&origin, &spark_vel, 0x4F007FFF, 0x1FFFFFFF, 8, 1, 10000.0f);
        }
    } else {
        part_spawn_trailing_spark(&origin, &spark_vel, 0x4F007FFF, 0x1FFFFFFF, 8, 1, 10000.0f);
    }
    if (trail->f0C) {
        step_len = fast_vec_dist(&trail->v10, &origin) * 0.5f;
        FastVecSub(&delta, &trail->v10, &origin);
        for (i = 1; i < 2; i++) {
            vec_scale_to_length(&step_pos, &delta, step_len * (f32)i);
            FastVecAdd(&step_pos, &origin, &step_pos);
            part_spawn_trailing_spark(&step_pos, &spark_vel, 0x4F007FFF, 0x1FFFFFFF, 8, 1, 10000.0f);
        }
    }
    trail->f00 = math_random_int_below(8);
    size_scale = 1.075f;
    tint = 0x808080;
    spark_vel.f[0] = 0.0f;
    spark_vel.f[1] = 0.0f;
    spark_vel.f[2] = -0.3f;
    spark_vel.f[3] = 1.0f;
    matrix_mul_vec3(&spark_vel, &spark_vel, &beam->vC0);
    FastVecAdd(&origin, &beam->v10, &spark_vel);
    spark_vel.f[3] = 1.0f;
    spark_vel.f[2] = -0.075f;
    spark_vel.f[0] = 0.0f;
    spark_vel.f[1] = 0.0f;
    matrix_mul_vec3(&spark_vel, &spark_vel, &beam->vC0);
    spark_vel.f[2] = 0.025f;
    FastVecAdd(&spark_vel, &spark_vel, &g_hero_state.v150);
    if (g_hero_state.i2294 == 8) {
        tint = 0xA0A0A0;
        size_scale = 1.0165f;
        spark_vel.f[2] -= 0.10000001f;
    }
    if (g_hero_state.i2294 == 0x7B) {
        tint = 0xA0A0A0;
        size_scale = 1.037f;
        spark_vel.f[2] -= 0.060000002f;
    }
    spark = part_spawn_spinning_spark_pal(&origin, 0.05f, 1.01f, size_scale, 30000.0f, 6, &spark_vel, tint, 0);
    if (spark) spark[3] = 0x44;
    if (trail->f0C) {
        step_len = fast_vec_dist(&trail->v10, &origin) * 0.16667f;
        FastVecSub(&delta, &trail->v10, &origin);
        move_state = g_hero_state.i2294;
        step_count = 4;
        if (move_state == 8) step_count = 2;
        if (move_state == 0x7B) step_count = 1;
        for (i = 1; i < step_count; i++) {
            vec_scale_to_length(&step_pos, &delta, step_len * (f32)i);
            FastVecAdd(&step_pos, &origin, &step_pos);
            spark = part_spawn_spinning_spark_pal(&step_pos, 0.05f, 1.01f, size_scale, 30000.0f, 6, &spark_vel, tint, 0);
            if (spark) spark[3] = 0x44;
        }
    }
    qcopy(&trail->v10, &origin);
    trail->f0C = 1;
}
