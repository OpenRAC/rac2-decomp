#include "common.h"

/* func_00308600 is defined in 00308600-spawn.c. */

/* func_00308768 is defined in 00308600-uv-g8.c. */

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
extern u8 *SpawnSpinningSparkParticle(V4 *, f32, f32, f32, f32, s32, V4 *, u32, s32);

/* Adapted from RAC1 emit_beam_trail_particles (OpenRAC, GPL-3.0). */
/* Spawns the smoke and spark particles that trail behind the beam at the player's hand. */
void beam_spawn_trail_particles(X *moby) {
    V4 velocity;
    V4 emit_pos;
    V4 trail_delta;
    V4 mid_point;
    N *vars;
    f32 spacing;
    f32 size_factor;
    u32 color;
    s32 i;
    s32 count;
    s32 hero_weapon;
    u8 *particle;

    vars = moby->f68;
    velocity.f[0] = math_fast_sin_or_cos_a(math_random_angle()) * 0.05f;
    velocity.f[1] = math_fast_sin_or_cos_b(math_random_angle()) * 0.05f;
    velocity.f[2] = 0.0f;
    velocity.f[2] = -math_random_float_range(0.01f, 0.03f);
    matrix_mul_vec3(&velocity, &velocity, &moby->vC0);
    FastVecAdd(&velocity, &velocity, &g_hero_state.v150);
    qcopy(&emit_pos, &moby->v10);
    if (g_hero_state.i2294 == 0x7B) {
        if (g_game_time % 3 == 0) {
            part_spawn_trailing_spark(&emit_pos, &velocity, 0x4F007FFF, 0x1FFFFFFF, 10, 1, 10000.0f);
        }
    } else {
        part_spawn_trailing_spark(&emit_pos, &velocity, 0x4F007FFF, 0x1FFFFFFF, 10, 1, 10000.0f);
    }
    if (vars->f0C) {
        spacing = fast_vec_dist(&vars->v10, &emit_pos) * 0.5f;
        FastVecSub(&trail_delta, &vars->v10, &emit_pos);
        for (i = 1; i < 2; i++) {
            vec_scale_to_length(&mid_point, &trail_delta, spacing * (f32)i);
            FastVecAdd(&mid_point, &emit_pos, &mid_point);
            part_spawn_trailing_spark(&mid_point, &velocity, 0x4F007FFF, 0x1FFFFFFF, 10, 1, 10000.0f);
        }
    }
    vars->f00 = math_random_int_below(10);
    size_factor = 1.075f;
    color = 0x808080;
    velocity.f[0] = 0.0f;
    velocity.f[1] = 0.0f;
    velocity.f[2] = -0.3f;
    velocity.f[3] = 1.0f;
    matrix_mul_vec3(&velocity, &velocity, &moby->vC0);
    FastVecAdd(&emit_pos, &moby->v10, &velocity);
    velocity.f[3] = 1.0f;
    velocity.f[2] = -0.075f;
    velocity.f[0] = 0.0f;
    velocity.f[1] = 0.0f;
    matrix_mul_vec3(&velocity, &velocity, &moby->vC0);
    velocity.f[2] = 0.025f;
    FastVecAdd(&velocity, &velocity, &g_hero_state.v150);
    if (g_hero_state.i2294 == 8) {
        color = 0xA0A0A0;
        size_factor = 1.0165f;
        velocity.f[2] -= 0.0833333358f;
    }
    if (g_hero_state.i2294 == 0x7B) {
        color = 0xA0A0A0;
        size_factor = 1.037f;
        velocity.f[2] -= 0.0500000045f;
    }
    particle = SpawnSpinningSparkParticle(&emit_pos, 0.05f, 1.01f, size_factor, 30000.0f, 6, &velocity, color, 0);
    if (particle) particle[3] = 0x44;
    if (vars->f0C) {
        spacing = fast_vec_dist(&vars->v10, &emit_pos) * 0.16667f;
        FastVecSub(&trail_delta, &vars->v10, &emit_pos);
        hero_weapon = g_hero_state.i2294;
        count = 4;
        if (hero_weapon == 8) count = 2;
        if (hero_weapon == 0x7B) count = 1;
        for (i = 1; i < count; i++) {
            vec_scale_to_length(&mid_point, &trail_delta, spacing * (f32)i);
            FastVecAdd(&mid_point, &emit_pos, &mid_point);
            particle = SpawnSpinningSparkParticle(&mid_point, 0.05f, 1.01f, size_factor, 30000.0f, 6, &velocity, color, 0);
            if (particle) particle[3] = 0x44;
        }
    }
    qcopy(&vars->v10, &emit_pos);
    vars->f0C = 1;
}


/* func_003092A0 is defined in 003092A0.c. */


/* func_0030A188 is defined in 0030A188-g8.c. */


/* func_0030BBA0 is defined in 00308600-beam-g8.c. */

/* func_0030C188 is defined in 0030C188-g8.c. */




/* func_0030CAD0 is defined in 0030CAD0-g8.c. */


/* func_0030D430 is matched in its own unit, src/game/0030D430-g8.c. */

/* func_0030D5B8 is defined in 00308600-ribbon-g8.c. */

/* func_0030DB88 is defined in 0030DB88-g8.c. */

/* func_0030DE88 is defined in 0030DE88-g8.c. */



extern char *part_find_owned_effect_slot(char *, int, int);
extern void math_fast_float_d(int *);
extern void PlayMobySound(int, int, char *);
extern void gfx_start_color_fade(char *, char *);
extern void vec_add_random_offset(float *, float);
/* Integer and float arguments have separate register banks. This interleaving
   preserves the measured argument setup order. */
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void gfx_update_color_fade(char *, char *);

/* Checks whether something hit the object. It takes damage from each hit and bursts when its health runs out. */
void moby_apply_hit_damage(char *object)
{
    char *vars = *(char **)(object + 0x68);
    char *hit = part_find_owned_effect_slot(object, 0x30001, 0);
    float direction[4];

    math_fast_float_d((int *)(vars + 0x28));
    math_fast_float_d((int *)(vars + 0x2C));
    if (hit != 0 && (*(int *)(hit + 0x20) != *(int *)(vars + 0x34) ||
                     *(int *)(vars + 0x28) == 0)) {
        *(int *)(vars + 0x34) = *(int *)(hit + 0x20);
        *(int *)(vars + 0x28) = 30;
        if (*(int *)(vars + 0x2C) == 0) {
            if (*(unsigned short *)(hit + 0x28) == 0x101 && *(int *)(vars + 0x30) == 0) {
                *(int *)(vars + 0x2C) = 100;
                *(int *)(vars + 0x30) = 1;
            } else {
                *(int *)(vars + 0x30) = 0;
            }
        }
        PlayMobySound(0, 0, object);
        *(float *)(vars + 0x24) -= *(float *)(hit + 0x2C);
        gfx_start_color_fade(object, vars);
        if (*(float *)(vars + 0x24) < 0.0f) {
            vec_add_random_offset(direction, 0.5f);
            SpawnExplosionEffects(object, direction, 0, 0.0f, 0.0f, 0, 0, 0,
                         4.0f, 3.0f, 9.0f, 1.0f, 2, 12.0f, 1, 1, -1, 0, 0x810001);
            object[0x20] = 6;
        }
    }
    ((unsigned char *)object)[0xA8] = 0xFF;
    gfx_update_color_fade(object, vars);
}

/* func_0030E8A8 is defined in 00308600-spring.c. */

/* func_0030ECC8 is defined in 00308600-ammo-g8.c. */

/* func_0030F408 is defined in 00308600-wavy.c. */
