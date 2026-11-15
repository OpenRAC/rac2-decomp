#include "common.h"

/* Uses -G8 small data and -g to retain the retail loop scheduling. */
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
extern char D_0018A0E0[], D_L00_001FE940[];
extern char D_001A8BD0[] __attribute__((sda));
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern int math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern void cam_set_zoom_effect(float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float mat_fast_helper_a(float, float), math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float), FastAddRotations(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern char *SpawnSpinningSparkParticle(void *, float, float, float, float, int, void *, int, int);
extern char *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, int, float, float, float);
/* Alternate typed interleavings preserve the EE integer and FP argument banks. */
extern char *func_002C65A0_layer(void *, void *, int, int, int, int, int,
                                   float, float, float, int) __asm__("func_002C65A0");
extern char *func_002BDCE8_smoke(void *, float, float, float, int, float,
                                   void *, int, int) __asm__("func_002BDCE8");
extern int math_random_int_range(int, int), FloatToInt(float);
extern float IntToFloat(int), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern float D_001B0804 __attribute__((sda));
extern float D_001B080C __attribute__((sda));
extern float D_001B0808 __attribute__((sda));
extern float D_001B079C __attribute__((sda));
extern float D_001B0780 __attribute__((sda));
extern float D_001B0784 __attribute__((sda));
extern float D_001B0788 __attribute__((sda));
extern float D_001B078C __attribute__((sda));
extern float D_001B0790 __attribute__((sda));
extern float D_001B0794 __attribute__((sda));
extern float D_001B0798 __attribute__((sda));
extern float D_001B07E4 __attribute__((sda));
extern float D_001B07E8 __attribute__((sda));
extern float D_001B07EC __attribute__((sda));
extern float D_001B07F0 __attribute__((sda));
extern float D_001B07F4 __attribute__((sda));
extern int D_001B0810 __attribute__((sda));
extern int D_001B07A0 __attribute__((sda));
extern int D_001B07A4 __attribute__((sda));
extern int D_001B07FC __attribute__((sda));
extern int D_001B0800 __attribute__((sda));
extern unsigned char D_001B07F8 __attribute__((sda));

/* Emits three particle groups around the object and sets camera shake when visible. */
void part_emit_blast_and_shake(char *self)
{
    float sphere[4], delta[4], center[4], position[4], velocity[4], other[4];
    int i, sign;
    float angle;
    float *eye;

    qcopy(sphere, self + 0x10);
    sphere[3] = 2;
    if (math_fast_helper_a(sphere, 48) == 1) {
        cam_set_zoom_effect(fast_vec_dist(self + 0x10, g_active_camera.position));
        g_active_camera.flag = 0;
        g_active_camera.duration = 40;
        g_active_camera.amplitude = 0.1f;
    }
    eye = g_active_camera.position;
    SpawnExplosionEffects(self, D_001A8BD0, self + 0x10, 0, 0, 0, 0, 0, 0, 0, 9, 0, -1, 20, 0, 0, -1, 0, 0x810001);
    FastVecSub(delta, eye, self + 0x10);
    vec_scale_to_length(delta, delta, D_001B0804);
    FastVecAdd(center, self + 0x10, delta);
    qcopy(self + 0x10, center);
    angle = mat_fast_helper_a(g_active_camera.position[0] - *(float *)(self + 0x10), g_active_camera.position[1] - *(float *)(self + 0x14));
    sign = 1;
    for (i = 0; i < 20; i++) {
        float speed, a, b;
        char *particle, *sub;

        sign = -sign;
        position[0] = center[0] + math_random_signed_float_range(0, D_001B080C);
        position[1] = center[1] + math_random_signed_float_range(0, D_001B080C);
        position[2] = center[2] + math_random_signed_float_range(0, D_001B080C);
        speed = math_random_float_range(0.016666668f, 0.033333335f);
        a = math_random_signed_float_range(0, 1.3962636f);
        b = math_random_signed_float_range(0, 1.5707964897155762f);
        vec_build_spherical_offset(velocity, speed, FastAddRotations(angle, b), a);
        particle = SpawnSpinningSparkParticle(position, 0, 1, 1.01f, D_001B0808 * 210000, sign, velocity, D_001B0810, 1);
        if (particle) {
            *(short *)(particle + 0xA) = math_random_int_range(40, 70);
            particle[9] = FloatToInt(4) + 64;
            sub = particle + 0x20;
            *(int *)(sub + 4) = 3;
            *(float *)(sub + 0x1C) = IntToFloat(math_random_int_range(1, 10));
            sub[0xA] = 64;
            sub[0xB] = particle[0xA];
        }
    }
    for (i = 0; i < 32; i++) {
        float size, speed, a, energy;
        int count, kind;
        char *particle;
        int definitions = (int)D_L00_001FE940;

        count = FloatToInt(math_random_signed_float_range(2, 5));
        kind = math_random_int_range(D_001B07A0, D_001B07A4);
        position[0] = center[0] + math_random_signed_float_range(0, D_001B079C);
        position[1] = center[1] + math_random_signed_float_range(0, D_001B079C);
        position[2] = center[2] + math_random_signed_float_range(0, D_001B079C);
        size = math_random_float_range(D_001B0780, D_001B0784);
        speed = math_random_float_range(D_001B0788, D_001B078C);
        a = FastAddRotations(angle, math_random_signed_float_range(0, 1.3962636f));
        velocity[0] = math_fast_sin_or_cos_a(a) * 0.016666668f * speed;
        velocity[1] = math_fast_sin_or_cos_b(a) * 0.016666668f * speed;
        velocity[2] = 0;
        velocity[2] = math_random_float_range(D_001B0790, D_001B0794) * 0.016666668f;
        energy = size * 210000;
        part_spawn_gravity_fade(position, velocity, kind, 0x7F7F7F, count, 127, 127, 1, energy, 2100, D_001B0798 * 0.00027777778f);
        other[0] = position[0] + math_random_signed_float_range(0, 0.01f);
        other[1] = position[1] + math_random_signed_float_range(0, 0.01f);
        other[2] = position[2] + math_random_signed_float_range(0, 0.01f);
        func_002C65A0_layer(other, velocity, kind, 0x7F7F7F, -count, 127, 127, energy, 2100, D_001B0798 * 0.00027777778f, 1);
        particle = part_spawn_gravity_fade(position, velocity, kind, 0x202080, -(count << 1), 48, 48, 1, size * 1260000, 4200, D_001B0798 * 0.00027777778f);
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

            FastVecScale(velocity, D_0018A0E0, -(math_random_float_range(D_001B07F0, D_001B07F4) * 0.016666668f));
            kind = math_random_int_range(D_001B07FC, D_001B0800);
            count = FloatToInt(math_random_signed_float_range(1, 2));
            energy = math_random_float_range(D_001B07E4, D_001B07E8) * 210000;
            other[0] = center[0] + math_random_signed_float_range(0, D_001B07EC);
            other[1] = center[1] + math_random_signed_float_range(0, D_001B07EC);
            other[2] = center[2] + math_random_signed_float_range(0, D_001B07EC);
            particle = func_002BDCE8_smoke(other, 0, 1, 1.01f, count, energy, velocity, 0x7F202020, 1);
            if (particle) {
                *(short *)(particle + 0xA) = kind;
                particle[3] = 0x44;
                particle[9] = FloatToInt(4) + 64;
                sub = particle + 0x20;
                *(float *)(sub + 0x1C) = IntToFloat(math_random_int_range(7, 15));
                *(int *)(sub + 4) = 3;
                sub[0xA] = D_001B07F8;
                sub[0xB] = particle[0xA];
            }
        }
    }
}
