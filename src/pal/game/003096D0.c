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
extern u8 *func_PAL_002BE9A8(V4 *, f32, f32, f32, f32, s32, V4 *, u32, s32);

/* Adapted from RAC1 emit_beam_trail_particles (OpenRAC, GPL-3.0). */
void beam_spawn_trail_particles_pal(X *x) {
    V4 l0;
    V4 a;
    V4 d;
    V4 t;
    N *g;
    f32 s;
    f32 q;
    u32 col;
    s32 i;
    s32 n;
    s32 m;
    u8 *p;

    g = x->f68;
    l0.f[0] = math_fast_sin_or_cos_a(math_random_angle()) * 0.05f;
    l0.f[1] = math_fast_sin_or_cos_b(math_random_angle()) * 0.05f;
    l0.f[2] = 0.0f;
    l0.f[2] = -math_random_float_range(0.01f, 0.03f);
    matrix_mul_vec3(&l0, &l0, &x->vC0);
    FastVecAdd(&l0, &l0, &g_hero_state.v150);
    qcopy(&a, &x->v10);
    if (g_hero_state.i2294 == 0x7B) {
        if (g_game_time % 3 == 0) {
            part_spawn_trailing_spark(&a, &l0, 0x4F007FFF, 0x1FFFFFFF, 8, 1, 10000.0f);
        }
    } else {
        part_spawn_trailing_spark(&a, &l0, 0x4F007FFF, 0x1FFFFFFF, 8, 1, 10000.0f);
    }
    if (g->f0C) {
        s = fast_vec_dist(&g->v10, &a) * 0.5f;
        FastVecSub(&d, &g->v10, &a);
        for (i = 1; i < 2; i++) {
            vec_scale_to_length(&t, &d, s * (f32)i);
            FastVecAdd(&t, &a, &t);
            part_spawn_trailing_spark(&t, &l0, 0x4F007FFF, 0x1FFFFFFF, 8, 1, 10000.0f);
        }
    }
    g->f00 = math_random_int_below(8);
    q = 1.075f;
    col = 0x808080;
    l0.f[0] = 0.0f;
    l0.f[1] = 0.0f;
    l0.f[2] = -0.3f;
    l0.f[3] = 1.0f;
    matrix_mul_vec3(&l0, &l0, &x->vC0);
    FastVecAdd(&a, &x->v10, &l0);
    l0.f[3] = 1.0f;
    l0.f[2] = -0.075f;
    l0.f[0] = 0.0f;
    l0.f[1] = 0.0f;
    matrix_mul_vec3(&l0, &l0, &x->vC0);
    l0.f[2] = 0.025f;
    FastVecAdd(&l0, &l0, &g_hero_state.v150);
    if (g_hero_state.i2294 == 8) {
        col = 0xA0A0A0;
        q = 1.0165f;
        l0.f[2] -= 0.10000001f;
    }
    if (g_hero_state.i2294 == 0x7B) {
        col = 0xA0A0A0;
        q = 1.037f;
        l0.f[2] -= 0.060000002f;
    }
    p = func_PAL_002BE9A8(&a, 0.05f, 1.01f, q, 30000.0f, 6, &l0, col, 0);
    if (p) p[3] = 0x44;
    if (g->f0C) {
        s = fast_vec_dist(&g->v10, &a) * 0.16667f;
        FastVecSub(&d, &g->v10, &a);
        m = g_hero_state.i2294;
        n = 4;
        if (m == 8) n = 2;
        if (m == 0x7B) n = 1;
        for (i = 1; i < n; i++) {
            vec_scale_to_length(&t, &d, s * (f32)i);
            FastVecAdd(&t, &a, &t);
            p = func_PAL_002BE9A8(&t, 0.05f, 1.01f, q, 30000.0f, 6, &l0, col, 0);
            if (p) p[3] = 0x44;
        }
    }
    qcopy(&g->v10, &a);
    g->f0C = 1;
}
