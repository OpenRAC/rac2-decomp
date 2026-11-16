#include "include_asm.h"

#include "common.h"
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_below(int);
extern void FastVecAdd(void *, void *, void *);
extern void part_spawn_spinning_effect_record_pal(void *, void *, int, float, float);
extern float g_facing_speed_a_min __attribute__((sda));
extern float g_facing_speed_a_max __attribute__((sda));
extern float g_facing_lift_a_min __attribute__((sda));
extern float g_facing_lift_a_max __attribute__((sda));
extern float g_facing_speed_b_min __attribute__((sda));
extern float g_facing_speed_b_max __attribute__((sda));
extern float g_facing_lift_b_min __attribute__((sda));
extern float g_facing_lift_b_max __attribute__((sda));
extern int g_facing_effect_kind_a __attribute__((sda));
extern int g_facing_effect_kind_b __attribute__((sda));
extern int g_facing_effect_odds __attribute__((sda));

/* Spits out a few small particles in front of the object, along the direction it is facing (PAL: 50 Hz timings). */
void part_emit_facing_pal(char *moby) {
    float velocity[4], pos[4], offset[4];
    qcopy(pos, moby + 0x10);
    pos[2] += 3.3f + math_random_float_range(-0.05f, 0.05f);
    pos[0] += math_random_float_range(-0.1f, 0.1f);
    pos[1] += math_random_float_range(-0.1f, 0.1f);
    offset[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * 1.5f;
    offset[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * 1.5f;
    offset[2] = 0;
    FastVecAdd(pos, pos, offset);
    velocity[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * math_random_float_range(g_facing_speed_a_min * 0.020000001f, g_facing_speed_a_max * 0.020000001f);
    velocity[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * math_random_float_range(g_facing_speed_a_min * 0.020000001f, g_facing_speed_a_max * 0.020000001f);
    velocity[2] = 0;
    velocity[2] = math_random_float_range(g_facing_lift_a_min * 0.020000001f, g_facing_lift_a_max * 0.020000001f);
    part_spawn_spinning_effect_record_pal(pos, velocity, g_facing_effect_kind_b, 0.5f, 50.4f);
    part_spawn_spinning_effect_record_pal(pos, velocity, g_facing_effect_kind_b, 0.5f, 50.4f);
    if (math_random_int_below(g_facing_effect_odds) != 1) {
    velocity[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * math_random_float_range(g_facing_speed_a_min * 0.020000001f, g_facing_speed_a_max * 0.020000001f);
    velocity[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * math_random_float_range(g_facing_speed_a_min * 0.020000001f, g_facing_speed_a_max * 0.020000001f);
    velocity[2] = 0;
    velocity[2] = math_random_float_range(g_facing_lift_a_min * 0.020000001f, g_facing_lift_a_max * 0.020000001f);
        part_spawn_spinning_effect_record_pal(pos, velocity, g_facing_effect_kind_a, 0.5f, 50.4f);
    }
    if (math_random_int_below(g_facing_effect_odds) != 1) {
    velocity[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * math_random_float_range(g_facing_speed_b_min * 0.020000001f, g_facing_speed_b_max * 0.020000001f);
    velocity[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * math_random_float_range(g_facing_speed_b_min * 0.020000001f, g_facing_speed_b_max * 0.020000001f);
    velocity[2] = 0;
    velocity[2] = math_random_float_range(g_facing_lift_b_min * 0.020000001f, 0.036000002f);
        part_spawn_spinning_effect_record_pal(pos, velocity, g_facing_effect_kind_a, 0.75f, 50.4f);
    }
    if (math_random_int_below(g_facing_effect_odds) == 1) {
    velocity[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * math_random_float_range(g_facing_speed_b_min * 0.020000001f, g_facing_speed_b_max * 0.020000001f);
    velocity[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * math_random_float_range(g_facing_speed_b_min * 0.020000001f, g_facing_speed_b_max * 0.020000001f);
    velocity[2] = 0;
    velocity[2] = math_random_float_range(g_facing_lift_b_min * 0.020000001f, g_facing_lift_b_max * 0.020000001f);
        part_spawn_spinning_effect_record_pal(pos, velocity, g_facing_effect_kind_a, 0.75f, 50.4f);
    }
}

typedef unsigned int Quad __attribute__((mode(TI)));
extern void moby_set_state(char *, int, int);
extern float math_random_float_range(float,float);
extern char *part_find_owned_effect_slot(char *,int,int);
extern void FastVecScale(void *,void *,float);
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void moby_mark_spawned(char *);
extern void *part_spawn_object_following_effect(void *,void *,unsigned int,int,int,int,int,int,float,float);
extern void part_explode_object_into_pieces_pal(void *,void *,void *,void *,int,int,int,int,int,int,int);
extern void part_spawn_scaled_bolts_pal(char *,int,float);
extern void moby_compute_local_point(char *,void *,float,float,float);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void part_spawn_glow_fade_effects_pal(char *,void *,int,float,int,void *,float,unsigned int,float,float,int);
extern char g_debris_param_b[] SDATA(D_L06_001B1C08);
extern char g_debris_param_c[] SDATA(D_L06_001B1C00);
extern char g_debris_param_a[] SDATA(D_L06_001B1C10);
extern char g_effect_vector[] MACRO_ADDR;
extern int g_debris_piece_color __attribute__((sda));

/* Updates a breakable object: once hit it throws out debris and sparks, then removes itself. */
void breakable_l06_debris_update_pal(char *obj)
{
    float pos[4], a[4], b[4], c[4];
    char *vars = *(char **)(obj + 0x68);
    char *hit;
    int state = *(unsigned char *)(obj + 0x20);
    int i;

    *(Quad *)a = 0;
    a[2] = *(float *)(obj + 0x2C) * 21.5f;
    *(Quad *)pos = *(Quad *)a;
    switch (state) {
    case 0:
        part_spawn_object_following_effect(pos, obj, 0x50801420, -1, 0, -1, 0, 96, 430500.0f, 0.0f);
        part_spawn_object_following_effect(pos, obj, 0x40801420, -1, 1, -1, 0, 96, 73500.0f, 0.75f);
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        hit = part_find_owned_effect_slot(obj, 0x4010000, 0);
        if (hit && !*(int *)vars) {
            *(Quad *)a = 0;
            a[1] = a[0] = 3.0f;
            *(float *)(hit + 0x18) = 0.75f;
            FastVecScale(b, hit + 0x10, math_random_float_range(6.0f, 8.0f));
            qcopy(c, b);
            FastVecSub(b, b, a);
            FastVecAdd(c, c, a);
            part_explode_object_into_pieces_pal(obj, b, g_debris_param_b, g_debris_param_c,
                             65535, -1, g_debris_piece_color, 9, state, 255, 0);
            moby_set_state(obj, 2, -1);
        }
        ((unsigned char *)obj)[0xA8] = 255;
        break;
    case 2:
        part_explode_object_into_pieces_pal(obj, g_debris_param_a, g_debris_param_b, g_debris_param_c,
                         65535, 0, g_debris_piece_color, 7, 62, 255, 0);
        part_spawn_scaled_bolts_pal(obj, 1, pos[2] * 0.33333334f);
        moby_compute_local_point(obj, a, pos[0], pos[1], pos[2]);
        SpawnExplosionEffects_pal(obj, g_effect_vector, a, 0, 0, 8, 3, 3, 0, 0, 9, 0.35f,
                      -1, 0, 0, 0, -1, 0, 0x810001);
        for (i = 0; i < 4; i++) {
            b[0] = (i / 2 * 2 - 1) * 0.020000001f;
            b[1] = (i % 2 * 2 - 1) * 0.020000001f;
            b[2] = 0.14000002f;
            matrix_mul_vec3(b, b, obj + 0xC0);
            part_spawn_glow_fade_effects_pal(obj, a, 3, 0, 1, b, 5, 0x7FFF8080, 0.45f, 0.6f, 0);
        }
        moby_mark_spawned(obj);
        break;
    }
}
