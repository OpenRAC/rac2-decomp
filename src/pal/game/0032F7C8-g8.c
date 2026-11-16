#include "common.h"

/* func_PAL_0032F7C8, the PAL copy of func_0032DD40: the same C at 50 Hz, with scaled rates, life spans and frame counts.
 * Its first two loops take separate counters. Uses -G8 small data and -g to retain the retail loop scheduling. */
typedef struct {
    char prefix[0x140];
    float position[4];
    char gap[0x10];
    float amplitude;
    int unknown;
    int duration;
    int flag;
} BurstCamera;
extern BurstCamera g_active_camera;
extern char g_hero_state_block[], g_effect_definitions[];
extern char g_default_effect_vector[] __attribute__((sda));
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern int math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern void func_PAL_00330020(float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float mat_fast_helper_a(float, float), math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float), FastAddRotations(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern char *func_PAL_002BE9A8(void *, float, float, float, float, int, void *, int, int);
extern char *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, int, float, float, float);
/* Alternate typed interleavings preserve the EE integer and FP argument banks. */
extern char *func_002C65A0_layer(void *, void *, int, int, int, int, int,
                                   float, float, float, int) __asm__("func_002C65A0");
extern char *func_PAL_002BE9A8_smoke(void *, float, float, float, int, float,
                                   void *, int, int) __asm__("func_PAL_002BE9A8");
extern int math_random_int_range(int, int), FloatToInt(float);
extern float IntToFloat(int), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern float g_blast_delta_length __attribute__((sda));
extern float g_blast_spark_spread __attribute__((sda));
extern float g_blast_spark_size __attribute__((sda));
extern float g_blast_position_spread __attribute__((sda));
extern float g_blast_size_min __attribute__((sda));
extern float g_blast_size_max __attribute__((sda));
extern float g_blast_speed_min __attribute__((sda));
extern float g_blast_speed_max __attribute__((sda));
extern float g_blast_velocity_z_min __attribute__((sda));
extern float g_blast_velocity_z_max __attribute__((sda));
extern float g_blast_fade_life_scale __attribute__((sda));
extern float g_blast_energy_min __attribute__((sda));
extern float g_blast_energy_max __attribute__((sda));
extern float g_blast_other_spread __attribute__((sda));
extern float g_blast_back_speed_min __attribute__((sda));
extern float g_blast_back_speed_max __attribute__((sda));
extern int g_blast_spark_param __attribute__((sda));
extern int g_blast_kind_min __attribute__((sda));
extern int g_blast_kind_max __attribute__((sda));
extern int g_blast_kind_alt_min __attribute__((sda));
extern int g_blast_kind_alt_max __attribute__((sda));
extern unsigned char g_blast_sub_byte __attribute__((sda));

/* Emits three particle groups around the object and sets camera shake when visible. */
void func_PAL_0032F7C8(char *self)
{
    float sphere[4], delta[4], center[4], position[4], velocity[4], other[4];
    int i, j, sign;
    float angle;
    float *eye;

    qcopy(sphere, self + 0x10);
    sphere[3] = 2;
    if (math_fast_helper_a(sphere, 48) == 1) {
        func_PAL_00330020(fast_vec_dist(self + 0x10, g_active_camera.position));
        g_active_camera.flag = 0;
        g_active_camera.duration = 33;
        g_active_camera.amplitude = 0.1f;
    }
    eye = g_active_camera.position;
    SpawnExplosionEffects_pal(self, g_default_effect_vector, self + 0x10, 0, 0, 0, 0, 0, 0, 0, 9, 0, -1, 20, 0, 0, -1, 0, 0x810001);
    FastVecSub(delta, eye, self + 0x10);
    vec_scale_to_length(delta, delta, g_blast_delta_length);
    FastVecAdd(center, self + 0x10, delta);
    qcopy(self + 0x10, center);
    angle = mat_fast_helper_a(g_active_camera.position[0] - *(float *)(self + 0x10), g_active_camera.position[1] - *(float *)(self + 0x14));
    sign = 1;
    for (i = 0; i < 20; i++) {
        float speed, a, b;
        char *particle, *sub;

        sign = -sign;
        position[0] = center[0] + math_random_signed_float_range(0, g_blast_spark_spread);
        position[1] = center[1] + math_random_signed_float_range(0, g_blast_spark_spread);
        position[2] = center[2] + math_random_signed_float_range(0, g_blast_spark_spread);
        speed = math_random_float_range(0.020000001f, 0.040000003f);
        a = math_random_signed_float_range(0, 1.3962636f);
        b = math_random_signed_float_range(0, 1.5707964897155762f);
        vec_build_spherical_offset(velocity, speed, FastAddRotations(angle, b), a);
        particle = func_PAL_002BE9A8(position, 0, 1, 1.01f, g_blast_spark_size * 210000, sign, velocity, g_blast_spark_param, 1);
        if (particle) {
            *(short *)(particle + 0xA) = ((s32)math_random_int_range(40, 70) * 5 + 2) / 6;
            particle[9] = FloatToInt(4) + 64;
            sub = particle + 0x20;
            *(int *)(sub + 4) = 3;
            *(float *)(sub + 0x1C) = IntToFloat(((s32)math_random_int_range(1, 10) * 5 + 2) / 6);
            sub[0xA] = 64;
            sub[0xB] = particle[0xA];
        }
    }
    for (j = 0; j < 32; j++) {
        float size, speed, a, energy;
        int count, kind;
        char *particle;
        int definitions = (int)g_effect_definitions;

        count = FloatToInt(math_random_signed_float_range(2, 5));
        kind = math_random_int_range(g_blast_kind_min, g_blast_kind_max);
        position[0] = center[0] + math_random_signed_float_range(0, g_blast_position_spread);
        position[1] = center[1] + math_random_signed_float_range(0, g_blast_position_spread);
        position[2] = center[2] + math_random_signed_float_range(0, g_blast_position_spread);
        size = math_random_float_range(g_blast_size_min, g_blast_size_max);
        speed = math_random_float_range(g_blast_speed_min, g_blast_speed_max);
        a = FastAddRotations(angle, math_random_signed_float_range(0, 1.3962636f));
        velocity[0] = math_fast_sin_or_cos_a(a) * 0.020000001f * speed;
        velocity[1] = math_fast_sin_or_cos_b(a) * 0.020000001f * speed;
        velocity[2] = 0;
        velocity[2] = math_random_float_range(g_blast_velocity_z_min, g_blast_velocity_z_max) * 0.020000001f;
        energy = size * 210000;
        part_spawn_gravity_fade(position, velocity, ((s32)kind * 5 + 2) / 6, 0x7F7F7F, count, 127, 127, 1, energy, 2100, g_blast_fade_life_scale * 0.00040000002f);
        other[0] = position[0] + math_random_signed_float_range(0, 0.01f);
        other[1] = position[1] + math_random_signed_float_range(0, 0.01f);
        other[2] = position[2] + math_random_signed_float_range(0, 0.01f);
        func_002C65A0_layer(other, velocity, ((s32)kind * 5 + 2) / 6, 0x7F7F7F, -count, 127, 127, energy, 2100, g_blast_fade_life_scale * 0.00040000002f, 1);
        particle = part_spawn_gravity_fade(position, velocity, ((s32)kind * 5 + 2) / 6, 0x202080, -(count << 1), 48, 48, 1, size * 1260000, 4200, g_blast_fade_life_scale * 0.00040000002f);
        if (particle) particle[2] = **(char **)(definitions + 0xD4);
    }
    FastVecSub(position, g_active_camera.position, center);
    vec_scale_to_length(position, position, 1);
    FastVecAdd(center, center, position);
    {
        int i;
        for (i = 0; i < 20; i++) {
            float energy;
            int kind, count;
            char *particle, *sub;

            FastVecScale(velocity, g_hero_state_block, -(math_random_float_range(g_blast_back_speed_min, g_blast_back_speed_max) * 0.020000001f));
            kind = ((s32)math_random_int_range(g_blast_kind_alt_min, g_blast_kind_alt_max) * 5 + 2) / 6;
            count = FloatToInt(math_random_signed_float_range(1, 2));
            energy = math_random_float_range(g_blast_energy_min, g_blast_energy_max) * 210000;
            other[0] = center[0] + math_random_signed_float_range(0, g_blast_other_spread);
            other[1] = center[1] + math_random_signed_float_range(0, g_blast_other_spread);
            other[2] = center[2] + math_random_signed_float_range(0, g_blast_other_spread);
            particle = func_PAL_002BE9A8_smoke(other, 0, 1, 1.01f, count, energy, velocity, 0x7F202020, 1);
            if (particle) {
                *(short *)(particle + 0xA) = kind;
                particle[3] = 0x44;
                particle[9] = FloatToInt(4) + 64;
                sub = particle + 0x20;
                *(float *)(sub + 0x1C) = IntToFloat(((s32)math_random_int_range(7, 15) * 5 + 2) / 6);
                *(int *)(sub + 4) = 3;
                sub[0xA] = g_blast_sub_byte;
                sub[0xB] = particle[0xA];
            }
        }
    }
}
